// VGSDK - Copyright (C) 2009, 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/technique/ForwardRendering.hpp"

#include <algorithm>
#include <boost/assign/std/vector.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/tuple/tuple.hpp>
#include <vgeGL/rc/GLSLProgram.hpp>
#include <strstream>
#include <vgd/basic/Image.hpp>
#include <vgd/basic/ImageInfo.hpp>
#include <vgd/node/Camera.hpp>
#include <vgd/node/CullFace.hpp>
#include <vgd/node/FrameBuffer.hpp>
#include <vgd/node/Quad.hpp>
#include <vgd/node/LightModel.hpp>
#include <vgd/node/Program.hpp>
#include <vgd/node/MultiTransformation.hpp>
#include <vgd/node/OutputBufferProperty.hpp>
#include <vgd/node/Overlay.hpp>
#include <vgd/node/PostProcessing.hpp>
#include <vgd/node/SpotLight.hpp>
#include <vgd/node/Texture2D.hpp>
#include <vgd/node/TexGenEyeLinear.hpp>
#include <vgd/node/TransformDragger.hpp>
#include <vgDebug/convenience.hpp>
#include <vge/service/Painter.hpp>
#include <vgeGL/handler/painter/PostProcessing.hpp>
#include <vgm/VectorOperations.hpp>
#include "vgeGL/engine/Engine.hpp"
#include "vgeGL/handler/painter/OutputBufferProperty.hpp"
#include "vgeGL/handler/painter/Overlay.hpp"
#include "vgeGL/rc/Texture2D.hpp"
#include "vgeGL/rc/FrameBufferObject.hpp"



namespace vgeGL
{

namespace technique
{



namespace
{



vgd::Shp< vgd::node::Texture2D > getInputTexture( const vgd::node::PostProcessing::Input0ValueType input,
	std::vector< vgd::Shp< vgd::node::Texture2D > >* outputBufferTexture,
	std::vector< vgd::Shp< vgd::node::Texture2D > >* previousTexture )
{
	using vgd::node::PostProcessing;
	vgd::Shp< vgd::node::Texture2D > retVal;

	//
	const int	inputValue = input.value();
	int			outputBufferIndex	= -1;
	int			previousBufferIndex	= -1;

	// OUTPUT_BUFFER
	if (	(PostProcessing::OUTPUT_BUFFER0 <= inputValue) &&
			(inputValue <= PostProcessing::OUTPUT_BUFFER7)	)
	{
		outputBufferIndex = inputValue - PostProcessing::OUTPUT_BUFFER0;
	}
	else if (	(PostProcessing::INPUT1_OUTPUT_BUFFER0 <= inputValue) &&
				(inputValue <= PostProcessing::INPUT1_OUTPUT_BUFFER7)	)
	{
		outputBufferIndex = inputValue - PostProcessing::INPUT1_OUTPUT_BUFFER0;
	}
	else if (	(PostProcessing::INPUT2_OUTPUT_BUFFER0 <= inputValue) &&
				(inputValue <= PostProcessing::INPUT2_OUTPUT_BUFFER7)	)
	{
		outputBufferIndex = inputValue - PostProcessing::INPUT2_OUTPUT_BUFFER0;
	}
	// PREVIOUS
	else if (	(PostProcessing::PREVIOUS0 == inputValue) ||
				(PostProcessing::INPUT1_PREVIOUS0 == inputValue) ||
				(PostProcessing::INPUT2_PREVIOUS0 == inputValue)	)
	{
		previousBufferIndex = 0;
	}
	// NONE
	else if (	(PostProcessing::NONE == inputValue) ||
				(PostProcessing::INPUT1_NONE == inputValue) ||
				(PostProcessing::INPUT2_NONE == inputValue)	)
	{
		// @todo returns black texture
	}
	else
	{
		assert( false && "Unexpected value" );
	}

	// Final processing
	if ( outputBufferIndex >= 0 )
	{
		if ( outputBufferIndex < static_cast< int >(outputBufferTexture->size()) )
		{
			retVal = (*outputBufferTexture)[outputBufferIndex];
		}
		else
		{
			vgLogDebug2("Out of range OUTPUT_BUFFER%i", outputBufferIndex);
		}
	}
	else if ( previousBufferIndex >= 0 )
	{
		if ( previousBufferIndex < static_cast< int >(previousTexture->size()) )
		{
			retVal = (*previousTexture)[previousBufferIndex];
		}
		else
		{
			vgLogDebug2("Out of range PREVIOUS%i", previousBufferIndex);
		}
	}
	
	return retVal;
}



//// Filters
// Detects edges and highlights them (using NORMAL buffer)
// @todo debug
const std::string normalEdgeDetect =
"vec2 normalEdgeDetectKernel4[4] = vec2[4](\n"
"vec2(0, 1), vec2(1, 0), vec2(0, -1), vec2(-1, 0)\n"
");\n"
"\n"
"// Performs edge detection and highlighting.\n"
"vec4 normalEdgeDetect( sampler2D texMap, vec2 texCoord )\n"
"{\n"
"	vec2 texSize = textureSize( texMap, 0 );\n"
"	vec4 orig = texture( texMap, texCoord );\n"
"	vec4 sum = vec4(0);\n"
"	for( int i = 0; i < 4; ++i )\n"
"	{\n"
"		float computedDot = dot( orig.xyz, texture( texMap, texCoord + normalEdgeDetectKernel4[i]/texSize ).xyz );\n"
"		sum += vec4( clamp( 1.0 - computedDot, 0.0, 1.0 ));\n"
"	}\n"
"	return vec4(sum.xyz, 1);\n"
"}\n"
"\n\n\n";
const std::string applyNormalEdgeDetect(
	"	color = normalEdgeDetect( texMap2D[0], mgl_TexCoord[0].xy );\n" );




////
const std::string declarations =
"uniform sampler2D texMap2D[3];\n"
"\n"
"varying vec4 mgl_TexCoord[3];\n"
"\n";



const std::string vertexProgram =
"invariant gl_Position;\n"
"\n"
"void main( void )\n"
"{\n"
"	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;\n"
//"	gl_Position	= ftransform();\n"
"\n"
"	INLINE_FTEXGEN\n"
"}\n";



const std::string fragmentProgram =
"void main( void )\n"
"{\n"
"	vec4 color = vec4(0);\n"
"	INLINE_POST_PROCESSING"
"	gl_FragColor = color;\n"
"}\n";






/**
 * @brief Input informations for shadow mapping
 *
 * @todo Light* and MatrixR are the informations needed to compute all shadow mapping input for a light. BoundingBox of root to adjust projection
 */
struct ShadowMappingInput
{
	ShadowMappingInput()
	{}

	/**
	 * @brief "Default" constructor
	 *
	 * @param engine		the engine where informations on the current state would be extracted.
	 * @param shadowType	
	 */
	void reset( const vgeGL::engine::Engine * engine, const vgd::node::LightModel::ShadowValueType shadowType, const vgd::node::LightModel::ShadowQualityValueType shadowQuality );

	/**
	 * @name Accessors
	 */
	//@{

	/**
	 * @brief Returns number of light casting shadow.
	 */
	const uint getNumLight() const;

	const vgm::MatrixR& getLightViewMatrix( const uint index ) const;
	const vgm::MatrixR& getLightMODELVIEWMatrix( const uint index ) const;
	const vgm::MatrixR& getLightProjectionMatrix( const uint index ) const;
	const vgd::node::SpotLight *getLightNode( const uint index ) const;

	//vgd::Shp< glo::Texture2D > getLightDepthMap( const uint index );
	vgd::Shp< vgd::node::Texture2D > getLightDepthMap( const uint index );
	vgd::Shp< vgeGL::rc::Texture2D > getLightDepthMap( const uint index, vgeGL::engine::Engine * engine );
	vgd::Shp< vgd::node::TexGenEyeLinear > getTexGen( const uint index );

	const vgm::Vec2i getShadowMapSize() const;

	/*const vgd::node::LightModel::ShadowValueType& getType() const;
	void setType( const vgd::node::LightModel::ShadowValueType& type );*/

	//@}



	struct LightInfo
	{
		LightInfo(	const vgm::MatrixR lightView, const vgm::MatrixR lightMODELVIEW, const vgm::MatrixR projection,
					const vgd::node::SpotLight * spotLight )
		:	m_lightViewMatrix(lightView),
			m_lightMODELVIEWMatrix(lightMODELVIEW),
			m_lightProjectionMatrix( projection),
			m_spotLight(spotLight)
		{}

		vgm::MatrixR m_lightViewMatrix;
		vgm::MatrixR m_lightMODELVIEWMatrix;
		vgm::MatrixR m_lightProjectionMatrix;
		const vgd::node::SpotLight * m_spotLight;
	};




	std::vector< vgd::Shp< vgd::node::Texture2D > >			m_dummyNodeForFBO; // @todo FIXME
	std::vector< vgd::Shp< vgd::node::Texture2D > >			m_recycleDummyNodeForFBO; // @todo FIXME

private:
	vgm::Vec2i												m_shadowMapSize;
// @todo only one vector
	std::vector< LightInfo >								m_lights;

	std::vector< vgd::Shp< vgd::node::Texture2D > >			m_recycleLightDepthMap;
	std::vector< vgd::Shp< vgd::node::Texture2D > >			m_lightDepthMap;
	std::vector< vgd::Shp< vgd::node::TexGenEyeLinear > >	m_texGen;
};



void ShadowMappingInput::reset(	const vgeGL::engine::Engine * engine,
								const vgd::node::LightModel::ShadowValueType shadowType,
								const vgd::node::LightModel::ShadowQualityValueType shadowQuality )
{
	using vgd::node::LightModel;

	// Retrieves GLSLState from engine
	using vgeGL::engine::GLSLState;
	const GLSLState& state = engine->getGLSLState();

	// Computes shadow map size and type
	// @todo param HIGH-QUALITY => GL_FLOAT
	vgm::Vec2i drawingSurface = engine->getDrawingSurfaceSize();
	if ( shadowQuality == LightModel::LOW )
	{
		drawingSurface /= 2;
		drawingSurface = vgm::nextPower2(drawingSurface);
	}
	else if ( shadowQuality == LightModel::MEDIUM )
	{
		// nothing to do
	}
	else if ( shadowQuality == LightModel::HIGH )
	{
		drawingSurface *= 2;
		drawingSurface = vgm::nextPower2(drawingSurface);
	}
	else if ( shadowQuality == LightModel::VERY_HIGH )
	{
		drawingSurface *= 3;
		drawingSurface = vgm::nextPower2(drawingSurface);
	}

	// Takes care of the maximum viewport size
	m_shadowMapSize.setValue(	std::min(engine->getMaxViewportSize()[0], drawingSurface[0]),
								std::min(engine->getMaxViewportSize()[1], drawingSurface[1])	);

	// Lights informations
	m_lights.clear();

	m_recycleDummyNodeForFBO.clear();
	m_dummyNodeForFBO.swap( m_recycleDummyNodeForFBO );

	m_recycleLightDepthMap.clear();
	m_lightDepthMap.swap( m_recycleLightDepthMap );

	m_texGen.clear();
	// @todo recycle texGen

	uint		i		= 0;
	const uint	iEnd	= state.getMaxLight();

	for( uint numLightFound = 0; (i != iEnd) && (numLightFound != state.getNumLight()); ++i )
	{
		const vgd::Shp< GLSLState::LightState > current = state.getLight( i );

		// Skip this light unit ?
		if (	!current ||
				(current->getLightNode() && current->getLightNode()->getCastShadow() == false )	)
		{
			continue;
		}

		if ( current->getLightType() == GLSLState::SPOT_LIGHT )
		{
			// Computes light informations
			using vgd::node::SpotLight;
			const SpotLight *spot = current->getSpotLightNode();
			assert( spot != 0 );

			const bool castShadow = spot->getCastShadow();

			if ( castShadow )
			{
				// LIGHT MATRICES
				assert( spot->hasCutOffAngle() ); // @todo
				float cutOffAngle;
				/*hasCutOffAngle = */ spot->getCutOffAngle( cutOffAngle );

// @todo FIXME check scene size
				const vgm::Vec2f nearFar = engine->getNearFar();
				assert( nearFar.isValid() );

				vgm::MatrixR projection;
				projection.setPerspective(	cutOffAngle * 2.f,
											static_cast<float>(m_shadowMapSize[0])/static_cast<float>(m_shadowMapSize[1]),
											nearFar[0], nearFar[1] );

				m_lights.push_back( LightInfo(current->lightViewMatrix, current->lightMODELVIEWMatrix, projection, spot ) );

				// Initializes private nodes for shadow mapping
// @todo TBT recycle nodes
				using vgd::node::Texture;
				vgd::Shp< vgd::node::Texture2D > lightDepthMap;
				if ( m_recycleLightDepthMap.size() > 0 )
				{
					lightDepthMap = m_recycleLightDepthMap.back();
					lightDepthMap->setName("depthMap.spotLight" + vgd::basic::toString( static_cast<int>(spot->getMultiAttributeIndex())));
				}
				else
				{
					lightDepthMap = vgd::node::Texture2D::create("depthMap.spotLight" + vgd::basic::toString( static_cast<int>(spot->getMultiAttributeIndex())) );
				}

				lightDepthMap->setWrap( Texture::WRAP_S, Texture::CLAMP );
				lightDepthMap->setWrap( Texture::WRAP_T, Texture::CLAMP );

				//lightDepthMap->setMipmap( true );
				//lightDepthMap->setFilter( Texture::MIN_FILTER, Texture::LINEAR );
				lightDepthMap->setFilter( Texture::MIN_FILTER, Texture::NEAREST );
				//lightDepthMap->setFilter( Texture::MIN_FILTER, Texture::LINEAR_MIPMAP_LINEAR /*LINEAR */);
				//lightDepthMap->setFilter( Texture::MAG_FILTER, Texture::LINEAR );
				lightDepthMap->setFilter( Texture::MAG_FILTER, Texture::NEAREST );

				lightDepthMap->setUsage( Texture::SHADOW );

				m_lightDepthMap.push_back( lightDepthMap );

				//
				if ( m_recycleDummyNodeForFBO.size() > 0 )
				{
					m_dummyNodeForFBO.push_back( m_recycleDummyNodeForFBO.back() );
				}
				else
				{
					m_dummyNodeForFBO.push_back( vgd::node::Texture2D::create("dummyNodeForFBO") );
				}

				// TexGen
				// @todo recycle texgen node
				vgd::Shp< vgd::node::TexGenEyeLinear > texGen = vgd::node::TexGenEyeLinear::create("ForwardRendering.texGenForShadow");
				texGen->setParameters( vgm::MatrixR::getIdentity() );

				m_texGen.push_back( texGen );
			}
		}
		else
		{
			vgLogDebug2( "ShadowMappingInput::ShadowMappingInput: Light %s not yet supported by shadow mapping.", current->getLightNode()->getName().c_str() );
		}

		++numLightFound;
	}
}


const uint ShadowMappingInput::getNumLight() const
{
	return m_lights.size();
}


const vgm::MatrixR& ShadowMappingInput::getLightViewMatrix( const uint index ) const
{
	assert( index < getNumLight() && "ShadowMappingInput::getLightViewMatrix(): Out of range index." );

	return m_lights[index].m_lightViewMatrix;
}


const vgm::MatrixR& ShadowMappingInput::getLightMODELVIEWMatrix( const uint index ) const
{
	assert( index < getNumLight() && "ShadowMappingInput::getLightMODELVIEWMatrix(): Out of range index." );

	return m_lights[index].m_lightMODELVIEWMatrix;
}



const vgm::MatrixR& ShadowMappingInput::getLightProjectionMatrix( const uint index ) const
{
	assert( index < getNumLight() && "ShadowMappingInput::getLightProjectionMatrix(): Out of range index." );

	return m_lights[index].m_lightProjectionMatrix;
}


const vgd::node::SpotLight *ShadowMappingInput::getLightNode( const uint index ) const
{
	assert( index < getNumLight() && "ShadowMappingInput::getLightNode(): Out of range index." );

	return m_lights[index].m_spotLight;
}



vgd::Shp< vgd::node::Texture2D > ShadowMappingInput::getLightDepthMap( const uint index )
{
	assert( index < getNumLight() && "ShadowMappingInput::getLightDepthMap(): Out of range index." );

	return m_lightDepthMap[index];
}


vgd::Shp< vgeGL::rc::Texture2D > ShadowMappingInput::getLightDepthMap( const uint index, vgeGL::engine::Engine * engine )
{
	assert( index < getNumLight() && "ShadowMappingInput::getLightDepthMap(): Out of range index." );

	vgd::Shp< vgd::node::Texture2D > texture2DNode = getLightDepthMap(index);

	// Gets the resource manager
	vgeGL::engine::Engine::GLManagerType& manager = engine->getGLManager();

	return manager.getShp< vgeGL::rc::Texture2D >( texture2DNode.get() );
}



vgd::Shp< vgd::node::TexGenEyeLinear > ShadowMappingInput::getTexGen( const uint index )
{
	assert( index < getNumLight() && "ShadowMappingInput::getTexGen(): Out of range index." );

	return m_texGen[index];
}



const vgm::Vec2i ShadowMappingInput::getShadowMapSize() const
{
	return m_shadowMapSize;
}



/*const vgd::node::LightModel::ShadowValueType& ShadowMappingInput::getType() const
{
	return m_type;
}

void ShadowMappingInput::setType( const vgd::node::LightModel::ShadowValueType& type )
{
	m_type = type;
}*/



//
std::pair< vgd::basic::IImage::Type, vgd::node::Texture::InternalFormatValueType > convertShadowMapType2IImageType( const vgd::node::LightModel::ShadowMapTypeValueType shadowMapType )
{
	using vgd::basic::IImage;
	using vgd::node::LightModel;
	using vgd::node::Texture;

	std::pair< IImage::Type, Texture::InternalFormatValueType > retVal;

	if ( shadowMapType == LightModel::FLOAT32 )
	{
		retVal.first	= IImage::FLOAT;
		retVal.second	= Texture::DEPTH_COMPONENT_32F;
	}
	else if ( shadowMapType == LightModel::INT32 )
	{
		retVal.first	= IImage::INT32;
		retVal.second	= Texture::DEPTH_COMPONENT_32;
	}
	else if ( shadowMapType == LightModel::INT24 )
	{
		retVal.first	= IImage::INT32;
		retVal.second	= Texture::DEPTH_COMPONENT_24;
	}			
	else if ( shadowMapType == LightModel::INT16 )
	{
		retVal.first	= IImage::INT16;
		retVal.second	= Texture::DEPTH_COMPONENT_16;
	}
	else
	{
		assert( false );
		retVal.first	= IImage::INT32;
		retVal.second	= Texture::DEPTH_COMPONENT_24;
	}

	return retVal;
}



} // namespace {






ForwardRendering::ForwardRendering()
:	m_shadowMappingInput( new ShadowMappingInput() )
{
	// Initializes Quad for PostProcessing	
	if ( !m_quad1 )
	{
		m_quad1 = vgd::node::Quad::create("ForwardRendering.fullscreenQuad1Tex");
		const vgm::Vec3f translateToOrigin( 0.5f, 0.5f, 0.f );
		m_quad1->transform( translateToOrigin );
		m_quad1->initializeTexUnits( 1 );
	}

	if ( !m_quad2 )
	{
		m_quad2 = vgd::node::Quad::create("ForwardRendering.fullscreenQuad2Tex");
		const vgm::Vec3f translateToOrigin( 0.5f, 0.5f, 0.f );
		m_quad2->transform( translateToOrigin );
		m_quad2->initializeTexUnits( 2 );
	}

	if ( !m_quad3 )
	{
		m_quad3 = vgd::node::Quad::create("ForwardRendering.fullscreenQuad3Tex");
		const vgm::Vec3f translateToOrigin( 0.5f, 0.5f, 0.f );
		m_quad3->transform( translateToOrigin );
		m_quad3->initializeTexUnits( 3 );
	}

	// Creates a black texture
	using vgd::node::Texture;
	if ( !m_blackTexture2D )
	{
		m_blackTexture2D = vgd::node::Texture2D::create( "black" );
		m_blackTexture2D->setWrap( Texture::WRAP_S, Texture::REPEAT );
		m_blackTexture2D->setWrap( Texture::WRAP_T, Texture::REPEAT );
		m_blackTexture2D->setFilter( Texture::MIN_FILTER, Texture::NEAREST );
		m_blackTexture2D->setFilter( Texture::MAG_FILTER, Texture::NEAREST );
		using vgd::basic::Image;
		uint8 imageData = 0;
		vgd::Shp< Image > image( new Image( 1, 1, 1, Image::LUMINANCE, Image::UINT8, &imageData ) );
		m_blackTexture2D->setImage( image );
	}
}



void ForwardRendering::initializeEngineBuffers( vgeGL::engine::Engine * engine, vgd::Shp< OutputBufferPropertyStateContainer > outputBufferProperties )
{
	// *** Initializes FBO and creates textures ***
	namespace vgeGLPainter = vgeGL::handler::painter;
	m_textures.clear();	
	boost::tie( m_frameBuffer, m_fbo ) = vgeGLPainter::OutputBufferProperty::createsFBO( engine, outputBufferProperties, std::back_inserter(m_textures), true );
}



void ForwardRendering::initializePostProcessingBuffers( vgeGL::engine::Engine * engine )
{
	// *** Initializes FBOs and creates textures ***
	// fbo0 and fbo1
	using vgd::node::OutputBufferProperty;
	using vgeGL::engine::GLSLState;

	vgd::Shp< OutputBufferPropertyStateContainer >	myOutputBufferProperties( new OutputBufferPropertyStateContainer(1) );
	vgd::Shp< OutputBufferProperty >				obufProperty;

	obufProperty = OutputBufferProperty::create("buf0");
	obufProperty->setFormat( OutputBufferProperty::RGBA );
	obufProperty->setType( OutputBufferProperty::FLOAT16 );

	myOutputBufferProperties->setState(0, vgd::makeShp( new GLSLState::OutputBufferPropertyState(obufProperty.get()) ) );

	namespace vgeGLPainter = vgeGL::handler::painter;
	m_textures0.clear();
	m_textures1.clear();	
	boost::tie( m_frameBuffer0, m_fbo0 ) = vgeGLPainter::OutputBufferProperty::createsFBO( engine, myOutputBufferProperties, std::back_inserter(m_textures0) );
	boost::tie( m_frameBuffer1, m_fbo1 ) = vgeGLPainter::OutputBufferProperty::createsFBO( engine, myOutputBufferProperties, std::back_inserter(m_textures1) );
}



// @todo Depth peeling to replace cullface => no, MaterialExt
// @todo CullFace
// @todo depth comparison pb : polygonOffset or Cullface

// @todo FBO (in ForwardRendering and in MultiMain);
// @todo aliasing artifacts : antialiased edges
// @todo OPT: shadowCaster/shadowReceiver
// @todo switch Light position in sg before Dragger to be invariant and after to move with the scene
// @todo rc container owned by this technique => useful for handler too
// @todo be able to disable kit (reminder: sub-scene graph of kit are expended in main TraverseElementVector !!!)
//
// @todo Z-only pass
void ForwardRendering::apply( vgeGL::engine::Engine * engine, vge::visitor::TraverseElementVector* traverseElements )
{
	using vgeGL::engine::GLSLState;

	//
	vgd::Shp< vge::service::Service > paintService = vge::service::Painter::create();

	prepareEval( engine, traverseElements );

	/////////////////////////////////////////////////////////
	// STEP 1 : Computes additionnal informations
	// Searches the first LightModel node
	// (and active lights at this state) and the camera.
	/////////////////////////////////////////////////////////
	using vgd::node::LightModel;

	// LightModel
	LightModel *									lightModel = 0;
	vgd::node::LightModel::ShadowValueType			shadowType;
	vgd::node::LightModel::ShadowMapTypeValueType	shadowMapType;

	// VIEW MATRIX and PROJECTION MATRIX
	vgd::node::Camera *				camera				= 0;
	vgd::node::TransformDragger *	transformDragger	= 0;

	vgm::MatrixR	viewMatrix		= vgm::MatrixR::getIdentity();
	vgm::MatrixR	invViewMatrix	= vgm::MatrixR::getIdentity();

	// Beginning of the pass
	setPassDescription("ForwardRendering:STEP1:Collects informations");
	beginPass();

	engine->disregard();
	engine->regardIfIsAKindOf<vgd::node::SingleTransformation>();
	engine->regardIfIsAKindOf<vgd::node::Group>();
	engine->regardIfIsAKindOf<vgd::node::Kit>();
	engine->regardIfIsAKindOf<vgd::node::Light>();
	engine->regardIfIsAKindOf<vgd::node::OutputBufferProperty>();
	engine->regardIfIsAKindOf<vgd::node::Overlay>();
	engine->regardIfIsAKindOf<vgd::node::PostProcessing>();

	//bool foundLightModel = false;
	vge::visitor::TraverseElementVector::const_iterator i, iEnd;
	for(	i = traverseElements->begin(), iEnd = traverseElements->end();
			/*!foundLightModel && */i != iEnd;
			++i )
	{
		engine->evaluate( paintService, *i );

		// CAMERA
		if ( i->first->isA< vgd::node::Camera >() && i->second )
		{
			assert( camera == 0 && "More than one camera !!!" );
			camera = dynamic_cast< vgd::node::Camera * >( i->first );

			viewMatrix = camera->getLookAt() * viewMatrix;
		}
		// TRANSFORM DRAGGER
		if ( i->first->isA< vgd::node::TransformDragger >() && i->second )
		{
			assert( transformDragger == 0 && "More than one dragger !!!" );
			transformDragger = dynamic_cast< vgd::node::TransformDragger * >( i->first );

			viewMatrix = transformDragger->computeMatrixFromFields() * viewMatrix;
		}
		// LIGHT MODEL
		else if ( i->first->isA< LightModel >() && i->second )
		{
			lightModel = dynamic_cast< LightModel * >( i->first );

			// Retrieves shadow technique to use
			bool isDefined = lightModel->getShadow( shadowType );	// @todo getDefaultShadow(LightModel::DEFAULT_SHADOW ); value = getShadow() 
			if ( !isDefined )	shadowType = LightModel::DEFAULT_SHADOW; // @todo not very cute

			LightModel::ShadowQualityValueType shadowQuality;
			isDefined = lightModel->getShadowQuality( shadowQuality );	// @todo getDefaultShadowQuality();
			if ( !isDefined )	shadowQuality = LightModel::DEFAULT_SHADOWQUALITY; // @todo not very cute

			shadowMapType = lightModel->getShadowMapType();

			//
			if ( shadowType != LightModel::SHADOW_OFF )
			{
				// Extracts informations
				m_shadowMappingInput->reset( engine, shadowType, shadowQuality );
				//m_shadowMappingInput->setType( shadow );
			}
			// else nothing to do

			//// Stops this pass
			//foundLightModel = true;
			//continue;
		}
	}

	///
	// Checks outputBufferProperties
	///
	const bool hasOutputBufferProperties = engine->getGLSLState().outputBufferProperties.isNotEmpty();

	if (	engine->getGLSLState().outputBufferProperties.getNum() > 1 &&
			engine->getGLSLState().postProcessing.isEmpty() )
	{
		vgLogDebug("At least one unused OutputBufferProperty (i.e. No PostProcessing node, but at least two OutputBufferProperty node)");
	}

	// Saves the outputBufferProperties state
	m_outputBufferProperties.reset( new OutputBufferPropertyStateContainer(engine->getGLSLState().outputBufferProperties) );

	///
	// Checks post-processing
	///
	const bool isPostProcessingEnabled =
		!lightModel->getIgnorePostProcessing() && engine->getGLSLState().outputBufferProperties.isNotEmpty() && engine->getGLSLState().postProcessing.isNotEmpty();

	// Saves the post-processing state
	m_postProcessing.reset( new PostProcessingStateContainer(engine->getGLSLState().postProcessing) );

	///
	// Checks overlays
	///
	const bool renderOverlays = engine->getGLSLState().overlays.isNotEmpty();

	// Saves the overlays state
	m_overlays.reset( new OverlayStateContainer(engine->getGLSLState().overlays) );

	//
	if ( !lightModel )
	{
		vgLogDebug("ForwardRendering::apply(): You must have a LightModel node in the scene graph.");
		return;
	}

	if ( !camera )
	{
		vgLogDebug("ForwardRendering::apply(): You must have a Camera node in the scene graph.");
		return;
	}

	vgm::MatrixR transformDraggerMatrix;
	vgm::MatrixR invTransformDraggerMatrix;
	if ( transformDragger )
	{
		transformDraggerMatrix = transformDragger->computeMatrixFromFields();
		invTransformDraggerMatrix = transformDraggerMatrix.getInverse();
	}
	else
	{
		transformDraggerMatrix.setIdentity();
		invTransformDraggerMatrix.setIdentity();
	}

	invViewMatrix = viewMatrix.getInverse();

	endPass();

	// @todo FIXME not generic
	vgm::MatrixR lightLookAt[4];



	////////////////////////////////////////////////////////////////////
	// STEP 2: Computes shadow map, i.e. renders scene from light POV //
	////////////////////////////////////////////////////////////////////
	if ( shadowType != LightModel::SHADOW_OFF )
	{
// @todo engine->disregardIfIsAKindOf< vgd::node::Dragger >(); because sub-scene graph is already collected !!!

//			engine->disregard();
//			engine->regardIfIsA<vgd::node::DrawStyle>();
//			engine->regardIfIsA<vgd::node::FrontFace>();
//
//			engine->regardIfIsAKindOf<vgd::node::SingleTransformation>();
//			engine->regardIfIsAKindOf<vgd::node::Group>();
//			engine->regardIfIsAKindOf<vgd::node::Kit>();
//
//			engine->regardIfIsAKindOf<vgd::node::Shape>();
//		//		// @todo FIXME IShape, IGeometryTransformation...
//			engine->disregardIfIsA<vgd::node::ClearFrameBuffer>();
		//engine->disregardIfIsAKindOf<vgd::node::Texture>();
		//engine->disregardIfIsA<vgd::node::LightModel>();
		//glDisable( GL_LIGHTING );

// @todo replaces LightModel
// @todo installs new handler intead of doing test on node type

		// @todo creates node polygonOffset
// @todo think about interaction whith CullFace ? Don't use it, but see PolygonOffset

		//const bool isTextureMappingEnabled(engine->isTextureMappingEnabled());
		const vgm::Vec2f shadowPolygonOffset = lightModel->getShadowPolygonOffset();

		for(	uint currentLightIndex = 0;
				currentLightIndex < m_shadowMappingInput->getNumLight();
				++currentLightIndex )
		{
			setPassDescription("ForwardRendering:STEP2:Rendering from light POV");
			beginPass();

			// not with fbo:glColorMask( GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE );

// @todo
			glEnable( GL_CULL_FACE );
			glCullFace( GL_FRONT );
			engine->disregardIfIsA< vgd::node::CullFace >();

			glPolygonOffset( shadowPolygonOffset[0], shadowPolygonOffset[1] );
			glEnable( GL_POLYGON_OFFSET_FILL );

			engine->disregardIfIsAKindOf<vgd::node::Light>();

			//engine->disregardIfIsAKindOf<vgd::node::MultiTransformation>();
			//engine->disregardIfIsAKindOf<vgd::node::TexGen>();

			engine->disregardIfIsA<vgd::node::LightModel>();

//
			vgd::Shp< vgd::node::Texture2D > texture2D = m_shadowMappingInput->getLightDepthMap( currentLightIndex );

			using vgd::basic::IImage;
			using vgd::basic::ImageInfo;

			IImage::Type								imageType;
			vgd::node::Texture::InternalFormatValueType internalFormat;
			
			boost::tie( imageType, internalFormat ) = convertShadowMapType2IImageType( shadowMapType );

			vgd::Shp< ImageInfo > depthImage(
				new ImageInfo(	m_shadowMappingInput->getShadowMapSize()[0], m_shadowMappingInput->getShadowMapSize()[1], 1,
								IImage::LUMINANCE, imageType ) );
			texture2D->setImage( depthImage );
			texture2D->setInternalFormat( internalFormat );
			const uint currentTexUnit = engine->getGLSLState().getPrivateTexUnitIndex(currentLightIndex);
			texture2D->setMultiAttributeIndex( currentTexUnit );
			engine->paint( texture2D );

			vgd::Shp< vgeGL::rc::Texture2D > lightDepthMap = m_shadowMappingInput->getLightDepthMap( currentLightIndex, engine );
// @todo moves
			if ( engine->getGLSLState().isShadowSamplerUsageEnabled() )
			{
				lightDepthMap->bind();
				lightDepthMap->parameter( GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE_ARB );
				lightDepthMap->parameter( GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL );
				lightDepthMap->parameter( GL_DEPTH_TEXTURE_MODE, GL_LUMINANCE );
			}

			// Lookups or creates fbo
// @todo remove m_dummyNodeForFBO
			vgeGL::engine::Engine::GLManagerType& rcManager = engine->getGLManager();
			vgeGL::rc::FrameBufferObject * fbo = rcManager.get< vgeGL::rc::FrameBufferObject >( m_shadowMappingInput->m_dummyNodeForFBO[currentLightIndex].get() ); // @todo not very cute
			if ( !fbo )
			{
				fbo = new vgeGL::rc::FrameBufferObject();
				rcManager.add( m_shadowMappingInput->m_dummyNodeForFBO[currentLightIndex].get(), fbo );

				fbo->generate();

				// Enables render to depth texture
				fbo->bind();
				fbo->attachDepth( lightDepthMap );

				fbo->renderDepthOnly();

				// Check framebuffer completeness at the end of initialization.
				const std::string fboStatus = fbo->getStatusString();
				if ( fboStatus.size() > 0 )
				{
					vgLogError2( "ForwardRendering::apply(): %s", fboStatus.c_str() );
					return;
					// @todo
				}
				// else nothing to do
			}
			else
			{
				// Enables render to depth texture
				fbo->bind();
			}

			const bool isTextureMappingEnabledBak = engine->isTextureMappingEnabled();
// @todo FIXME : This should work on NV GPU !!!
			if ( !engine->getGLSLState().isShadowSamplerUsageEnabled() )
			//if ( gleGetCurrent()->getDriverProvider() == gle::OpenGLExtensions::ATI_DRIVERS )
			{
				engine->disregardIfIsAKindOf<vgd::node::Texture>();
				// pre-configuration
				engine->setTextureMappingEnabled(false);
			}

			vge::visitor::TraverseElementVector::const_iterator i, iEnd;
			for(	i = traverseElements->begin(), iEnd = traverseElements->end();
					i != iEnd;
					++i )
			{
				using ::vgd::node::Camera;

				if ( (i->first)->isA< Camera >() && i->second )
				{
					Camera * currentCamera = dynamic_cast< Camera * >(i->first);
					assert( currentCamera != 0 );
					assert( currentCamera == camera );

					// Uses my camera
					vgd::Shp< Camera > newCamera = Camera::create("ForwardRendering::CameraFromLight");

					vgm::MatrixR lightViewMatrix = m_shadowMappingInput->getLightViewMatrix(currentLightIndex);
					vgm::MatrixR lightMODELVIEWMatrix = m_shadowMappingInput->getLightMODELVIEWMatrix(currentLightIndex);
					const vgd::node::SpotLight * spotLight = m_shadowMappingInput->getLightNode(currentLightIndex);

					bool isDefined;
					vgd::node::SpotLight::PositionValueType		position;
					vgd::node::SpotLight::DirectionValueType	direction;

					isDefined = spotLight->getPosition( position );
					assert( isDefined );

					isDefined = spotLight->getDirection( direction );
					assert( isDefined );

					vgm::MatrixR current = lightMODELVIEWMatrix * invViewMatrix;
					current.multVecMatrix( position, position );
					current[3][0] = current[3][1] = current[3][2] = 0.f;
					current.multVecMatrix( direction, direction );

					vgm::Vec3f	eye		( position );
					vgm::Vec3f	center	( position + direction );
					vgm::Vec3f	up		( 0.f, 1.f, 0.f );

					if ( direction.dot( up ) > 0.5f )
					{
						up.setValue( 1.f, 0.f, 0.f );
					}
					/*current.multVecMatrix( eye, eye );
					current.multVecMatrix( center, center );
					current.multVecMatrix( up,up );*/
					lightLookAt[currentLightIndex].setLookAt( eye, center, up );
// I must undo the transform dragger action => @todo disable TransformDragger
					newCamera->setLookAt(
						 invTransformDraggerMatrix * lightLookAt[currentLightIndex]
						);
					newCamera->setProjection( m_shadowMappingInput->getLightProjectionMatrix(currentLightIndex) );

					const vgm::Rectangle2i viewport( 0, 0, m_shadowMappingInput->getShadowMapSize()[0], m_shadowMappingInput->getShadowMapSize()[1] );
					newCamera->setViewport( viewport );

					engine->paint( newCamera );
// Cullface in sg(TBT)
				}
				else
				{
					engine->evaluate( paintService, *i );
				}
			}

			// Re-enable rendering to the window
			fbo->unbind();

			// Rendering done, extract depth map from depth buffer and copy into a texture2D node.
			// @todo more high-level (Engine::renderTargets section ?)
			//lightDepthMap->parameter( GL_DEPTH_TEXTURE_MODE_ARB, GL_INTENSITY );
// @todo in glo
			/*glCopyTexSubImage2D(	GL_TEXTURE_2D, 0,
									0, 0, 0, 0,
									m_shadowMappingInput->getShadowMapSize()[0], 
									m_shadowMappingInput->getShadowMapSize()[1] );*/

			// to debug projective texturing
/*			static vgd::Shp< vgd::basic::Image > image( new vgd::basic::Image("ulis_gbr_0571.png") );
			lightDepthMap->texImage( 0,
									GL_RGB, image->width(), image->height(), image->depth(),
									0,
									GL_RGB,
									GL_UNSIGNED_BYTE,
									image->pixels() );*/

			endPass();
			engine->setTextureMappingEnabled( isTextureMappingEnabledBak );
		}
		//engine->setTextureMappingEnabled(isTextureMappingEnabled);
	}
// @todo test rc after enable postproc/disable, same with engineOutputBuffers

	// Computes if drawing surface size has changed
	bool drawingSurfaceSizeChanged = false;

	const vgm::Vec2i drawingSurfaceSize = engine->getDrawingSurfaceSize(); // Retrieves drawing surface size

	vgd::Shp< glo::FrameBufferObject > outputBuffersOfEngine = engine->getOutputBuffers();
	if ( outputBuffersOfEngine && (outputBuffersOfEngine->getNumOfColors() > 0) )
	{
		vgd::Shp< glo::Texture2D > texture2D = outputBuffersOfEngine->getColorAsTexture2D();
		if ( texture2D )
		{
			drawingSurfaceSizeChanged =	( texture2D->getWidth() != drawingSurfaceSize[0] ) ||
										( texture2D->getHeight() != drawingSurfaceSize[1] );
		}
	}

	// Tests if output buffers of engine must be initialized/re-initialized (see Engine::getOutputBuffers())
	if ( hasOutputBufferProperties )
	{
		bool callInitializeEngineBuffers =
			!outputBuffersOfEngine ||
			drawingSurfaceSizeChanged ||
			(outputBuffersOfEngine->getNumOfColors() != m_outputBufferProperties->getNum());

		if ( !callInitializeEngineBuffers )
		{
			// Tests if a a change occurs in output buffers properties.
			uint numFound = 0;
			for( uint i = 0; numFound < m_outputBufferProperties->getNum(); ++i )
			{
				using vgeGL::engine::GLSLState;
				vgd::Shp< GLSLState::OutputBufferPropertyState > outputBufferPropertyState = m_outputBufferProperties->getState(i);

				if ( outputBufferPropertyState )
				{
					++numFound;
					vgd::node::OutputBufferProperty * outputBufferProperty = outputBufferPropertyState->getNode();
					if (	outputBufferProperty &&
							outputBufferProperty->getDirtyFlag(outputBufferProperty->getDFNode())->isDirty()	)
					{
						callInitializeEngineBuffers = true;
						break;
					}
				}
			}
		}

		if ( callInitializeEngineBuffers )
		{
			setPassDescription("ForwardRendering:STEP2BIS: Buffers initialization stage");
			beginPass();
			initializeEngineBuffers( engine, m_outputBufferProperties );
			endPass();

			//
			engine->setOutputBuffers( m_fbo );
		}
	}

	// Post-processing buffers initialization
	if ( isPostProcessingEnabled )
	{
		// Tests if initialization must be done
		if (	!m_frameBuffer0 || !m_frameBuffer1 ||
				drawingSurfaceSizeChanged	)
		{
			setPassDescription("ForwardRendering:STEP2BIS: Buffers initialization stage for PostProcessing");
			beginPass();
			initializePostProcessingBuffers( engine );
			endPass();
		}
	}

	//////////////////////////////////////////////////////////////////////////
	// STEP 3: Rendering (opaque and transparent pass ) with/without shadow //
	//////////////////////////////////////////////////////////////////////////
	namespace vgeGLPainter = vgeGL::handler::painter;

	const std::string defaultFragmentOutputStage = 
	"\n"
	"	gl_FragData[0] = color;\n";

	const std::string fragmentOutputDeclarationStage(
		vgeGLPainter::OutputBufferProperty::getFragmentOutputDeclarationStageString(engine, m_outputBufferProperties )
		);

	const std::string fragmentOutputStage(
		vgeGLPainter::OutputBufferProperty::getFragmentOutputStageString(engine, m_outputBufferProperties )
		);

	if ( shadowType != LightModel::SHADOW_OFF && m_shadowMappingInput->getNumLight() > 0 )
	{
		if ( isPostProcessingEnabled )
		{
			setPassDescription("ForwardRendering:STEP3:Rendering with shadow and post-processing");
		}
		else
		{
			setPassDescription("ForwardRendering:STEP3:Rendering with shadow");
		}
		beginPass();

		// Prepares texture units with depth map and tex coord
		for(	uint currentLightIndex = 0;
				currentLightIndex < m_shadowMappingInput->getNumLight();
				++currentLightIndex )
		{
			const uint currentTexUnit = engine->getGLSLState().getPrivateTexUnitIndex( currentLightIndex );

// @todo Improves vgd::node::Texture to be able to use it directly

			// *** Updates Texture ***
			vgd::Shp< vgd::node::Texture2D > texture2D = m_shadowMappingInput->getLightDepthMap( currentLightIndex );
			texture2D->setMultiAttributeIndex( currentTexUnit );
// @todo setFunction()
			engine->paint( texture2D );

			// *** Updates TexGen ***
			vgd::Shp< vgd::node::TexGenEyeLinear > texGen = m_shadowMappingInput->getTexGen( currentLightIndex );
			texGen->setMultiAttributeIndex( currentTexUnit );
			//if ( texGen->getMultiAttributeIndex() != currentTexUnit )	texGen->setMultiAttributeIndex( currentTexUnit );
			engine->paint( texGen );

			// *** Updates Texture Matrix ***
// @todo use TextureMatrix node
			vgm::MatrixR textureMatrix;
			textureMatrix.setTranslate( vgm::Vec3f(0.5f, 0.5f, 0.5f) );	// offset
			textureMatrix.scale( vgm::Vec3f(0.5f, 0.5f, 0.5f) );		// bias
			// LIGHT FRUSTUM (Projection)
			const vgm::MatrixR lightProjectionMatrix = m_shadowMappingInput->getLightProjectionMatrix( currentLightIndex );
			// LIGHT VIEW (Look At)
			const vgm::MatrixR lightViewMatrix = m_shadowMappingInput->getLightViewMatrix(currentLightIndex);
			const vgm::MatrixR lightMODELVIEWMatrix = m_shadowMappingInput->getLightMODELVIEWMatrix(currentLightIndex);

			textureMatrix = invViewMatrix * (lightLookAt[currentLightIndex]) * lightProjectionMatrix * textureMatrix;

			//
			engine->activeTexture(currentTexUnit);
			glMatrixMode( GL_TEXTURE );
			glLoadMatrixf( reinterpret_cast<const float*>( textureMatrix.getValue() ) );

			engine->getTextureMatrix().setTop( textureMatrix, currentTexUnit );
		}

		//
		engine->disregardIfIsA< vgd::node::CullFace >();

		if ( isPostProcessingEnabled )
		{
			// Renders in FBO
			m_fbo->bind();
			m_fbo->setDrawBuffers( 0 );

			engine->getGLSLState().setShaderStage( GLSLState::FRAGMENT_OUTPUT_DECLARATION, fragmentOutputDeclarationStage );			
			engine->getGLSLState().setShaderStage( GLSLState::FRAGMENT_OUTPUT, fragmentOutputStage );
		}
		else
		{
			engine->getGLSLState().setShaderStage( GLSLState::FRAGMENT_OUTPUT, defaultFragmentOutputStage );
		}
			

		/////////////////////////////////////////////////////////

		// First pass : OPAQUE PASS (draw opaque shape)
		const bool mustDoTransparencyPass = evaluateOpaquePass( paintService, PassIsolationMask(0), true );

		// Second pass : TRANSPARENT PASS (draw transparent shape).
		if ( mustDoTransparencyPass )
		{
			evaluateTransparentPass( paintService, PassIsolationMask(DEFAULT_PASS_ISOLATION_MASK), true );
		}
		/////////////////////////////////////////////////////////

		if ( isPostProcessingEnabled )
		{
			//
			m_fbo->unbind();
		}

		endPass();

		// Applies post-processing and blits it to the default framebuffer
		if ( isPostProcessingEnabled )
		{
			const vgd::Shp< vgeGL::rc::FrameBufferObject > finalBuffers = applyPostProcessing( engine, m_fbo0, m_fbo1 );

			blit( engine, finalBuffers );
		}
	}
	else
	{
		if ( isPostProcessingEnabled )
		{
			// Renders in FBO
			m_fbo->bind();
			m_fbo->setDrawBuffers( 0 );

			engine->getGLSLState().setShaderStage( GLSLState::FRAGMENT_OUTPUT_DECLARATION, fragmentOutputDeclarationStage );			
			engine->getGLSLState().setShaderStage( GLSLState::FRAGMENT_OUTPUT, fragmentOutputStage );
		}
		else
		{
			engine->getGLSLState().setShaderStage( GLSLState::FRAGMENT_OUTPUT, defaultFragmentOutputStage );
		}	
		
		//////////////////////////////////////////////////////////
		// STEP 3 bis : Rendering (opaque and transparent pass) //
		//////////////////////////////////////////////////////////
		{
			setPassDescription("ForwardRendering:begin:Default rendering");

			// First pass : OPAQUE PASS (draw opaque shape)
			const bool mustDoTransparencyPass = evaluateOpaquePass( paintService );

			// Second pass : TRANSPARENT PASS (draw transparent shape).
			if ( mustDoTransparencyPass )
			{
				evaluateTransparentPass( paintService );
			}
		}

		if ( isPostProcessingEnabled )
		{
			m_fbo->unbind();

			const vgd::Shp< vgeGL::rc::FrameBufferObject > finalBuffers = applyPostProcessing( engine, m_fbo0, m_fbo1 );
			blit( engine, finalBuffers );
		}		

	}

	// Renders overlays
	if ( renderOverlays )
	{
		setPassDescription("ForwardRendering:OVERLAYS");
		beginPass();
		vgeGL::handler::painter::Overlay::paint( engine, m_overlays );
		endPass();
	}

	//
	finishEval();
}





	/// POST PROCESSING
// @todo FrameBuffer node with getColor() => Texture node to remove m_textures....
// @todo glCopyTexImage2D() and co in glo
const vgd::Shp< vgeGL::rc::FrameBufferObject > ForwardRendering::applyPostProcessing( vgeGL::engine::Engine * engine,
	const vgd::Shp< vgeGL::rc::FrameBufferObject > fbo0,
	const vgd::Shp< vgeGL::rc::FrameBufferObject > fbo1 )
{
// @todo moves applyPostProcessing and blit() in PostProcessing handler.
// @todo Composite for glo::Resource/std::string
	using vgd::node::Program;
	using vgd::node::Texture2D;

	// Retrieves GLSLState from engine
	using vgeGL::engine::GLSLState;
	//const GLSLState& state = engine->getGLSLState();

	// 
	std::vector< float >										params1f0;
	std::vector< vgm::Vec4f >									params4f0;
	std::vector< vgm::Vec4f >									params4f1;
	std::vector< vgd::node::PostProcessing::Input0ValueType >	inputs0;
	std::vector< vgd::node::PostProcessing::Input1ValueType >	inputs1;
	std::vector< vgd::node::PostProcessing::Input2ValueType >	inputs2;
	std::vector< uint >											output;

	std::vector< vgd::Shp< Program > >							programs;
	std::vector< float >										scales;

	uint		i		= 0;
	const uint	iEnd	= m_postProcessing->getMax(); // @todo beginIndex(), endIndex(), iterators
	//const uint	iEnd	= state.postProcessing.getMax(); // @todo beginIndex(), endIndex(), iterators

	float currentScaleForTexCoord	= 1.f;
	float currentScaleForVertex		= 1.f;

	for( uint foundPP = 0; i != iEnd; ++i )
	{
		const vgd::Shp< GLSLState::PostProcessingState > current = m_postProcessing->getState( i );
		//const vgd::Shp< GLSLState::PostProcessingState > current = state.postProcessing.getState( i );

		if ( current )
		{
			vgd::node::PostProcessing * postProcessingNode = current->getNode();
			assert( postProcessingNode );

			// Parameters

			// Builds declaration section of the shaders (depends of post-processing node param* fields)
			std::string currentDeclaration = 
			"uniform float param1f0;\n"
			"uniform vec4 param4f0;\n"
			"uniform vec4 param4f1;\n\n";

			// param1f0
			if ( postProcessingNode->hasParam1f0() )
			{
				float value;
				postProcessingNode->getParam1f0(value);

				params1f0.push_back( value );
			}
			else
			{
				params1f0.push_back( std::numeric_limits<float>::max() );
			}

			// param4f0
			if ( postProcessingNode->hasParam4f0() )
			{
				vgm::Vec4f value;
				postProcessingNode->getParam4f0(value);

				params4f0.push_back( value );
			}
			else
			{
				params4f0.push_back( vgm::Vec4f::getInvalid() );
			}

			// param4f1
			if ( postProcessingNode->hasParam4f1() )
			{
				vgm::Vec4f value;
				postProcessingNode->getParam4f1(value);

				params4f1.push_back( value );
			}
			else
			{
				params4f1.push_back( vgm::Vec4f::getInvalid() );
			}

			currentDeclaration += declarations;

			// Inputs
			inputs0.push_back( postProcessingNode->getInput0() );
			inputs1.push_back( postProcessingNode->getInput1() );
			inputs2.push_back( postProcessingNode->getInput2() );

			// Ouput
			//output.push_back( postProcessingNode->getOutput().value() - vgd::node::PostProcessing::OUTPUT_TMP0 );

			// Creates Program node
			vgd::Shp< Program > program = Program::create("program");
			programs.push_back( program );

			// Initializes Program node
			std::pair< std::string, std::string > filter = vgeGL::handler::painter::PostProcessing::getFilter( postProcessingNode, postProcessingNode->getFilter() );
			std::pair< float, float > scale = vgeGL::handler::painter::PostProcessing::getScale( postProcessingNode->getFilter() );

			// Scales
			scales.push_back(scale.second);

			// Builds Vertex shader
			std::string vertexShader;
			if ( postProcessingNode->getInput2() != vgd::node::PostProcessing::INPUT2_NONE )
			{			
				vertexShader = boost::algorithm::replace_first_copy( 
					vertexProgram, "INLINE_FTEXGEN",	"mgl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;"
														"mgl_TexCoord[1] = gl_TextureMatrix[1] * gl_MultiTexCoord1;"
														"mgl_TexCoord[2] = gl_TextureMatrix[2] * gl_MultiTexCoord2;" );
			}
			else if ( postProcessingNode->getInput1() != vgd::node::PostProcessing::INPUT1_NONE )
			{
				vertexShader = boost::algorithm::replace_first_copy( 
					vertexProgram, "INLINE_FTEXGEN",	"mgl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;"
														"mgl_TexCoord[1] = gl_TextureMatrix[1] * gl_MultiTexCoord1;" );
			}
			else
			{
				vertexShader = boost::algorithm::replace_first_copy( 
					vertexProgram, "INLINE_FTEXGEN", "mgl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;" );
			}

			currentScaleForVertex *= scale.second;

			/*if ( vgm::notEquals( currentScaleForVertex, 1.f ) )
			{
				// Scales quad using vertex shader
				const std::string pattern( "gl_Position	= ftransform();" );
				
				std::strstream scaleStr;
				scaleStr << "gl_Position = " << currentScaleForVertex << "* gl_ModelViewProjectionMatrix " << currentScaleForVertex << " * gl_Vertex;\n" << std::ends;

				vertexShader = boost::algorithm::replace_first_copy( vertexShader, pattern, scaleStr.str() );
			}
			// else nothing to do*/

// @todo OPTME reduce glsl code size
			program->setShader( Program::VERTEX, currentDeclaration + vertexShader );

			// Builds Fragment shader
			std::string fragmentShader = currentDeclaration + filter.first +
				boost::algorithm::replace_first_copy( fragmentProgram, "INLINE_POST_PROCESSING", filter.second );

			if ( vgm::notEquals( currentScaleForTexCoord, 1.f ) )
			{
				// Scales texCoord using fragment shader
				const std::string pattern( "mgl_TexCoord[0].xy" );

				std::strstream scaleStr;
				scaleStr << "mgl_TexCoord[0].xy * " << currentScaleForTexCoord << std::ends;
				
				fragmentShader = boost::algorithm::replace_first_copy( fragmentShader, pattern, scaleStr.str() );
			}
			// else nothing to do

			program->setShader( Program::FRAGMENT, fragmentShader );

			//
			currentScaleForTexCoord *= scale.second;

			//
			++foundPP;
			if ( foundPP == m_postProcessing->getNum() )
			//if ( foundPP == state.postProcessing.getNum() )
			{
				break;
			}
		}
		// else empty state, nothing to do
	}

	//
	m_lastCurrentScaleForVertex = currentScaleForVertex;


	/////////////////////////////////////////
	// Post-processing rendering draw code //
	/////////////////////////////////////////

	// Enables texture mapping
	const bool isTextureMappingEnabled(engine->isTextureMappingEnabled());
	engine->setTextureMappingEnabled();

	const vgm::Rectangle2i	viewport( 0, 0, engine->getDrawingSurfaceSize()[0], engine->getDrawingSurfaceSize()[1] );

	setPassDescription("ForwardRendering:Post-processing stage");
	beginPass();
	engine->begin2DRendering( &viewport, false );

	vgd::Shp< vgeGL::rc::FrameBufferObject >			lfbo0 = fbo0;
	vgd::Shp< vgeGL::rc::FrameBufferObject >			lfbo1 = fbo1;
	std::vector< vgd::Shp< vgd::node::Texture2D > >*	ltex0 = &m_textures0;
	std::vector< vgd::Shp< vgd::node::Texture2D > >*	ltex1 = &m_textures1;

	currentScaleForTexCoord	= 1.f;
	currentScaleForVertex	= 1.f;

	for( uint i=0; i < programs.size(); ++i )
	{
		// sources		: ltex0
		// destination	: lfbo1

		vgd::Shp< Program >	program = programs[i];
		engine->paint( program );

		currentScaleForVertex *= scales[i];
		glViewport( 0, 0,
					static_cast<int>(engine->getDrawingSurfaceSize()[0] * currentScaleForVertex),
					static_cast<int>(engine->getDrawingSurfaceSize()[1] * currentScaleForVertex) );
//engine->begin2DRendering( &lviewport, false );
// @todo a light version of begin2DRendering
// @todo uses DF and cache

		// nearFar
		const vgm::Vec2f nearFar = engine->getNearFar();
		assert( nearFar.isValid() );

		assert( !engine->getUniformState().isUniform( "nearFar") && "Uniform nearFar already used" );
		engine->getUniformState().addUniform( "nearFar", nearFar );

		// param1f0
		const float param1f0 = params1f0[i];
		if ( param1f0 != std::numeric_limits<float>::max() )
		{
			assert( !engine->getUniformState().isUniform( "param1f0") && "Uniform param1f0 already used" );
			engine->getUniformState().addUniform( "param1f0", param1f0 );
		}

		// param4f0
		const vgm::Vec4f param4f0 = params4f0[i];
		if ( param4f0.isValid() )
		{
			assert( !engine->getUniformState().isUniform( "param4f0") && "Uniform param4f0 already used" );
			engine->getUniformState().addUniform( "param4f0", param4f0 );
		}

		// param4f1
		const vgm::Vec4f param4f1 = params4f1[i];
		if ( param4f1.isValid() )
		{
			assert( !engine->getUniformState().isUniform( "param4f1") && "Uniform param4f1 already used" );
			engine->getUniformState().addUniform( "param4f1", param4f1 );
		}

		// input0
		vgd::Shp< Texture2D > inputTexture0 = getInputTexture( inputs0[i], &m_textures, ltex0 );
		if ( inputTexture0 )
		{
			if ( inputTexture0->getMultiAttributeIndex() != 0 )		inputTexture0->setMultiAttributeIndex(0);
			engine->paint( inputTexture0 );
		}
		else
		{
			if ( m_blackTexture2D->getMultiAttributeIndex() != 0 )		m_blackTexture2D->setMultiAttributeIndex(0);
			engine->paint( m_blackTexture2D );
		}

		// input1
		vgd::Shp< Texture2D > inputTexture1 = getInputTexture( inputs1[i], &m_textures, ltex0 );
		if ( inputTexture1 )
		{
			if ( inputTexture1->getMultiAttributeIndex() != 1 )		inputTexture1->setMultiAttributeIndex(1);
			engine->paint( inputTexture1 );
		}
		else
		{
			if ( m_blackTexture2D->getMultiAttributeIndex() != 1 )		m_blackTexture2D->setMultiAttributeIndex(1);
			engine->paint( m_blackTexture2D );
		}

		// input2
		vgd::Shp< Texture2D > inputTexture2 = getInputTexture( inputs2[i], &m_textures, ltex0 );
		if ( inputTexture2 )
		{
			if ( inputTexture2->getMultiAttributeIndex() != 2 )		inputTexture2->setMultiAttributeIndex(2);
			engine->paint( inputTexture2 );
		}
		else
		{
			if ( m_blackTexture2D->getMultiAttributeIndex() != 2 )		m_blackTexture2D->setMultiAttributeIndex(2);
			engine->paint( m_blackTexture2D );
		}

		// render
		//lfbo1->bind();
		lfbo1->setDrawBuffer();
		lfbo1->setDrawBuffers( 0 );
		//lfbo1->setDrawBuffers( output[i] );

		if ( inputTexture0 && !inputTexture1 && !inputTexture2 )
		{
			engine->paint( m_quad1 );
		}
		else if ( inputTexture0 && inputTexture1 && !inputTexture2 )
		{
			engine->paint( m_quad2 );
		}
		else if ( inputTexture0 && inputTexture1 && inputTexture2 )
		{
			engine->paint( m_quad3 );
		}
		else
		{
			vgLogDebug("Found a PostProcessing node without any input textures.");
		}

		lfbo0.swap( lfbo1 );
		std::swap( ltex0, ltex1 );

		currentScaleForTexCoord *= scales[i];

		engine->getUniformState().clear();
	}

	lfbo0->unbind();

	engine->end2DRendering( false );
	endPass();
	engine->setTextureMappingEnabled( isTextureMappingEnabled );

	return lfbo0;
}



// @todo glo api : blit( fboSrc, fboDst, COLOR:DEPTH:STENCIL ) LINEAR or NEAREST,  blit( ..., srcRect, ..., dstRext... ).
void ForwardRendering::blit( vgeGL::engine::Engine * engine, vgd::Shp< vgeGL::rc::FrameBufferObject > fbo )
{
	fbo->setReadBuffer();
	glo::FrameBufferObject::setDrawToDefaultFrameBuffer();

// @todo removes warnings
	glBlitFramebuffer(	0, 0, engine->getDrawingSurfaceSize()[0] * m_lastCurrentScaleForVertex, engine->getDrawingSurfaceSize()[1] * m_lastCurrentScaleForVertex,
//						0, 0, engine->getDrawingSurfaceSize()[0], engine->getDrawingSurfaceSize()[1],
						0, 0, engine->getDrawingSurfaceSize()[0] * m_lastCurrentScaleForVertex, engine->getDrawingSurfaceSize()[1] * m_lastCurrentScaleForVertex,
						GL_COLOR_BUFFER_BIT, GL_NEAREST );
	glo::FrameBufferObject::setReadToDefaultFrameBuffer();
}



} // namespace technique

} // namespace vgeGL

/*// Copies FBO into FBO 0
			// @todo glo api
			vgd::Shp< glo::Texture2D > texSrc;
			vgd::Shp< glo::Texture2D > texDst;

			//
			texSrc = m_fbo->getColorAsTexture2D(0);
			texSrc->bind();
			const GLint internalFormat = texSrc->getInternalFormat();

			texDst = m_fbo0->getColorAsTexture2D(0);
			m_fbo->setReadBuffer(0);
			texDst->bind();
// ???			
			glCopyTexImage2D( GL_TEXTURE_2D, 0, internalFormat, 0, 0, texSrc->getWidth(), texSrc->getHeight(), 0 );

			//
			texSrc = m_fbo->getColorAsTexture2D(1);
			texDst = m_fbo0->getColorAsTexture2D(1);
			m_fbo->setReadBuffer(1);
			texDst->bind();

			glCopyTexImage2D( GL_TEXTURE_2D, 0, internalFormat, 0, 0, texSrc->getWidth(), texSrc->getHeight(), 0 );*/
