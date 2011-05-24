// VGSDK - Copyright (C) 2009, 2010, 2011, Nicolas Papier.
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
#include <vgd/node/ClearFrameBuffer.hpp>
#include <vgd/node/ClipPlane.hpp>
#include <vgd/node/CullFace.hpp>
#include <vgd/node/FrameBuffer.hpp>
#include <vgd/node/FrontFace.hpp>
#include <vgd/node/Quad.hpp>
#include <vgd/node/LightModel.hpp>
#include <vgd/node/Material.hpp>
#include <vgd/node/Program.hpp>
#include <vgd/node/MultiTransformation.hpp>
#include <vgd/node/MultipleInstances.hpp>
#include <vgd/node/OutputBufferProperty.hpp>
#include <vgd/node/Overlay.hpp>
#include <vgd/node/PostProcessing.hpp>
#include <vgd/node/SpotLight.hpp>
#include <vgd/node/TextureTransformation.hpp>
#include <vgd/node/Texture2D.hpp>
#include <vgd/node/TexGenEyeLinear.hpp>
#include <vgDebug/convenience.hpp>
#include <vge/engine/SceneManager.hpp>
#include <vge/service/Painter.hpp>
#include <vgeGL/handler/painter/PostProcessing.hpp>
#include <vgm/VectorOperations.hpp>
#include "vgeGL/engine/Engine.hpp"
#include "vgeGL/engine/GLSLState.hpp"
#include "vgeGL/handler/painter/OutputBufferProperty.hpp"
#include "vgeGL/handler/painter/Overlay.hpp"
#include "vgeGL/rc/Texture2D.hpp"
#include "vgeGL/rc/FrameBufferObject.hpp"


// ALL
// @todo installs new handler intead of doing test on node type
// @todo IShape, IGeometryTransformation... for regard/disregard
// @todo engine->disregardIfIsAKindOf< vgd::node::Dragger >(); because sub-scene graph is already collected !!!

// SHADOW
// @todo disable Depth node
// @todo CullFace and Shadow map are not compatible (cullface is used internally in shadow map technique)
// => replaces CullFace with Material Ext or uses PolygonOffset



namespace vgeGL
{

namespace technique
{



namespace
{



// BEGIN POSTPROCESSING
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
		vgAssertN( false, "Unexpected value" );
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
	"varying vec4 mgl_TexCoord[3];\n"
	"\n"
	"uniform float param1f0;\n"
	"uniform vec4 param4f0;\n"
	"uniform vec4 param4f1;\n"
	"\n";




const std::string vertexProgram =
"void main( void )\n"
"{\n"
"	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;\n"
"\n"
"INLINE_FTEXGEN\n"
"}\n";



const std::string fragmentProgram =
"void main( void )\n"
"{\n"
"	vec4 color = vec4(0);\n"
"	INLINE_POST_PROCESSING"
"	gl_FragColor = color;\n"
"}\n";
// END POSTPROCESSING





// BEGIN SHADOW
/**
 * @brief Input informations for shadow mapping
 *
 * @todo Light* and MatrixR are the informations needed to compute all shadow mapping input for a light. BoundingBox of root to adjust projection
 */
struct ShadowMappingInput
{
	struct LightInfo
	{
		typedef vgeGL::engine::LightState LightState;

		LightInfo( const vgd::Shp< LightState > lightState, const vgm::MatrixR projection )
		:	m_lightState(lightState),
			m_lightProjectionMatrix( projection)
		{}

		vgd::Shp< LightState > m_lightState;

		vgm::MatrixR m_lightProjectionMatrix;
	};




	ShadowMappingInput()
	{}

	/**
	 * @brief "Default" constructor
	 *
	 * @param engine		the engine where informations on the current state would be extracted.
	 * @param shadowType	
	 */
	void reset( const vgeGL::engine::Engine * engine, const vgd::node::LightModel::ShadowValueType shadowType );

	/**
	 * @name Accessors
	 */
	//@{
	const LightInfo& getLight( const uint index ) const;

	/**
	 * @brief Returns number of lights casting shadow.
	 */
	const uint getNumLight() const;


	const vgm::MatrixR& getLightProjectionMatrix( const uint index ) const;

	vgd::Shp< vgd::node::Texture2D > getLightDepthMap( const uint index );
	vgd::Shp< vgeGL::rc::Texture2D > getLightDepthMap( const uint index, vgeGL::engine::Engine * engine );

	vgd::Shp< vgd::node::TexGenEyeLinear > getTexGen( const uint index );

	// @todo != size for shadow map per light casting shadow
	const vgm::Vec2i getShadowMapSize() const;

	//@}


	std::vector< vgd::Shp< vgd::node::FrameBuffer > >		m_fbo;
	std::vector< vgd::Shp< vgd::node::FrameBuffer > >		m_recycleFbo;

	//std::vector< vgd::Shp< vgeGL::rc::FrameBuffer > >		m_fbo;
private:
	//std::vector< vgd::Shp< vgeGL::rc::FrameBuffer > >		m_recycleFbo;
	vgm::Vec2i												m_shadowMapSize;
// @todo only one vector
	std::vector< LightInfo >								m_lights;

	std::vector< vgd::Shp< vgd::node::Texture2D > >			m_recycleLightDepthMap;
	std::vector< vgd::Shp< vgd::node::Texture2D > >			m_lightDepthMap;
	std::vector< vgd::Shp< vgd::node::TexGenEyeLinear > >	m_recycleTexGen;
	std::vector< vgd::Shp< vgd::node::TexGenEyeLinear > >	m_texGen;
};



void ShadowMappingInput::reset(	const vgeGL::engine::Engine * engine,
								const vgd::node::LightModel::ShadowValueType shadowType )
{
	using vgd::node::LightModel;

	// Retrieves GLSLState from engine
	using vgeGL::engine::GLSLState;
	using vgeGL::engine::LightState;
	const GLSLState& state = engine->getGLSLState();

	// Computes shadow map size
	vgm::Vec2i drawingSurface = engine->getDrawingSurfaceSize();
	LightModel::ShadowMapSizeValueType shadowMapSize = engine->getOFEnum< LightModel >( LightModel::getFShadowMapSize() );
	if ( shadowMapSize == LightModel::LOW )
	{
		drawingSurface /= 2;
		drawingSurface = vgm::nextPower2(drawingSurface);
	}
	else if ( shadowMapSize == LightModel::MEDIUM )
	{
		// nothing to do
	}
	else if ( shadowMapSize == LightModel::HIGH )
	{
		drawingSurface = vgm::nextPower2(drawingSurface);
	}
	else if ( shadowMapSize == LightModel::VERY_HIGH )
	{
		drawingSurface *= 2;
		drawingSurface = vgm::nextPower2(drawingSurface);
	}
	else
	{
		vgAssertN( false, "Unexpected LightModel.shadowMapSize" );
	}

	// Takes care of the maximum viewport size
	m_shadowMapSize.setValue(	std::min(engine->getMaxViewportSize()[0], drawingSurface[0]),
								std::min(engine->getMaxViewportSize()[1], drawingSurface[1])	);

	// Lights informations
	m_lights.clear();

	m_fbo.swap( m_recycleFbo );
	m_fbo.clear();

	m_lightDepthMap.swap( m_recycleLightDepthMap );
	m_lightDepthMap.clear();

	m_texGen.swap( m_recycleTexGen );
	m_texGen.clear();

	uint		i		= 0;
	const uint	iEnd	= state.lights.getMax();

	for( uint numLightFound = 0; (i != iEnd) && (numLightFound != state.lights.getNum()); ++i )
	{
		const vgd::Shp< LightState > current = state.lights.getState( i );

		// Skip this light unit ?
		if (	!current ||
				!current->getCastShadow() )
		{
			continue;
		}

		if ( current->getLightType() == vgeGL::engine::SPOT_LIGHT )
		{
			// Computes light informations
			const bool castShadow = current->getCastShadow();

			if ( castShadow )
			{
				// LIGHT MATRICES
				const float cutOffAngle = current->getCutOffAngle();

// @todo FIXME check scene size
				const vgm::Vec2f nearFar = engine->getNearFar();
				vgAssert( nearFar.isValid() );

				vgm::MatrixR projection;
				projection.setPerspective(	cutOffAngle * 2.f,
											static_cast<float>(m_shadowMapSize[0])/static_cast<float>(m_shadowMapSize[1]),
											nearFar[0], nearFar[1] );

				m_lights.push_back( LightInfo(current, projection ) );

				// Initializes private nodes for shadow mapping
				using vgd::node::Texture;
				vgd::Shp< vgd::node::Texture2D > lightDepthMap;
				if ( m_recycleLightDepthMap.size() > 0 )
				{
					lightDepthMap = m_recycleLightDepthMap.back();
#ifdef _DEBUG
					lightDepthMap->setName("depthMap.spotLight" + vgd::basic::toString(i));
#endif
				}
				else
				{
					// node part
					lightDepthMap = vgd::node::Texture2D::create("depthMap.spotLight" + vgd::basic::toString(i));

					lightDepthMap->setWrap( Texture::WRAP_S, Texture::CLAMP );
					lightDepthMap->setWrap( Texture::WRAP_T, Texture::CLAMP );

					lightDepthMap->setUsage( Texture::SHADOW );
				}

				//
				LightModel::ShadowFilteringValueType shadowFiltering = engine->getOFEnum< LightModel >( LightModel::getFShadowFiltering() );

				switch ( shadowFiltering.value() )
				{
					case LightModel::NEAREST:
						lightDepthMap->setFilter( Texture::MIN_FILTER, Texture::NEAREST );
						lightDepthMap->setFilter( Texture::MAG_FILTER, Texture::NEAREST );
						break;

					case LightModel::LINEAR:
						lightDepthMap->setFilter( Texture::MIN_FILTER, Texture::LINEAR );
						lightDepthMap->setFilter( Texture::MAG_FILTER, Texture::LINEAR );
						break;

					default:
						vgAssertN( false, "Unexpected value %i", shadowFiltering.value() );
				}

				m_lightDepthMap.push_back( lightDepthMap );

				//
				if ( m_recycleFbo.size() > 0 )
				{
					m_fbo.push_back( m_recycleFbo.back() );
				}
				else
				{
					m_fbo.push_back( vgd::node::FrameBuffer::create("FBO for depth light POV") );
				}

				// TexGen
				if ( m_recycleTexGen.size() > 0 )
				{
					vgd::Shp< vgd::node::TexGenEyeLinear > texGen = m_recycleTexGen.back();
					//texGen->setParameters( vgm::MatrixR::getIdentity() );
					m_texGen.push_back( texGen );
				}
				else
				{
					vgd::Shp< vgd::node::TexGenEyeLinear > texGen = vgd::node::TexGenEyeLinear::create("ForwardRendering.texGenForShadow");
					texGen->setParameters( vgm::MatrixR::getIdentity() );
					m_texGen.push_back( texGen );
				}
			}
		}
		else
		{
			//vgLogDebug2( "ShadowMappingInput::ShadowMappingInput: Light %s not yet supported by shadow mapping.", current->getLightNode()->getName().c_str() );
			vgAssertN( false, "ShadowMappingInput::ShadowMappingInput: Light not yet supported by shadow mapping." );
		}

		++numLightFound;
	}
}


const ShadowMappingInput::LightInfo& ShadowMappingInput::getLight( const uint index ) const
{
	vgAssertN( index < getNumLight(), "Out of range index %i/%i", index, getNumLight() );
	return m_lights[index];
}


const uint ShadowMappingInput::getNumLight() const
{
	return m_lights.size();
}


const vgm::MatrixR& ShadowMappingInput::getLightProjectionMatrix( const uint index ) const
{
	vgAssertN( index < getNumLight(), "ShadowMappingInput::getLightProjectionMatrix(): Out of range index." );

	return m_lights[index].m_lightProjectionMatrix;
}


vgd::Shp< vgd::node::Texture2D > ShadowMappingInput::getLightDepthMap( const uint index )
{
	vgAssertN( index < getNumLight(), "ShadowMappingInput::getLightDepthMap(): Out of range index." );

	return m_lightDepthMap[index];
}


vgd::Shp< vgeGL::rc::Texture2D > ShadowMappingInput::getLightDepthMap( const uint index, vgeGL::engine::Engine * engine )
{
	vgAssertN( index < getNumLight(), "ShadowMappingInput::getLightDepthMap(): Out of range index." );

	vgd::Shp< vgd::node::Texture2D > texture2DNode = getLightDepthMap(index);

	// Gets the resource manager
	vgeGL::engine::Engine::GLManagerType& manager = engine->getGLManager();

	return manager.getShp< vgeGL::rc::Texture2D >( texture2DNode.get() );
}



vgd::Shp< vgd::node::TexGenEyeLinear > ShadowMappingInput::getTexGen( const uint index )
{
	vgAssertN( index < getNumLight(), "ShadowMappingInput::getTexGen(): Out of range index." );

	return m_texGen[index];
}



const vgm::Vec2i ShadowMappingInput::getShadowMapSize() const
{
	return m_shadowMapSize;
}




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
		vgAssert( false );
		retVal.first	= IImage::INT32;
		retVal.second	= Texture::DEPTH_COMPONENT_24;
	}

	return retVal;
}



vgd::Shp< vgd::node::Camera > setupRenderFromLightCamera( vgd::Shp< ShadowMappingInput > shadowMappingInput, const int currentLightIndex,
		const vgm::MatrixR& invViewMatrix, const vgm::MatrixR& invTransformDraggerMatrix,
		vgm::MatrixR& lightLookAt )
{
	// Creates the new camera
	vgd::Shp< vgd::node::Camera > newCamera = vgd::node::Camera::create("CameraFromLight");

	// Sets fields
	using vgeGL::engine::LightState;
	const vgd::Shp< LightState > lightState = shadowMappingInput->getLight( currentLightIndex ).m_lightState;

	const vgm::MatrixR&		lightModelViewMatrix	= lightState->getModelViewMatrix();
	vgm::Vec3f				position				= lightState->getPosition();
	vgm::Vec3f				direction				= lightState->getDirection();

	vgm::MatrixR modelMatrix = lightModelViewMatrix * invViewMatrix;
	modelMatrix.multVecMatrix( position, position );
	modelMatrix[3][0] = modelMatrix[3][1] = modelMatrix[3][2] = 0.f;
	modelMatrix.multVecMatrix( direction, direction );

	// lookAt field
	vgm::Vec3f	eye		( position );
	vgm::Vec3f	center	( position + direction );
	vgm::Vec3f	up		( 0.f, 1.f, 0.f );
	if ( direction.dot( up ) > 0.5f ) up.setValue( 1.f, 0.f, 0.f );
	lightLookAt.setLookAt( eye, center, up );
	// The transform dragger must be undo.
// @todo disable TransformDragger
	newCamera->setLookAt( invTransformDraggerMatrix * lightLookAt );

	// projection field
	newCamera->setProjection( shadowMappingInput->getLightProjectionMatrix(currentLightIndex) );

	// viewport field
	const vgm::Rectangle2i viewport( 0, 0, shadowMappingInput->getShadowMapSize()[0], shadowMappingInput->getShadowMapSize()[1] );
	newCamera->setViewport( viewport );

	// Returns the new camera
	return newCamera;
}
// END SHADOW



// @todo OPTME using new handler for Camera
void passPaintWithGivenCamera(	vgeGL::engine::Engine * engine, vge::visitor::TraverseElementVector* traverseElements,
								const vgd::Shp< vgd::node::Camera > newCamera )
{
	using vgd::node::Camera;

	vge::visitor::TraverseElementVector::const_iterator i, iEnd;
	for(	i = traverseElements->begin(), iEnd = traverseElements->end();
			i != iEnd;
			++i )
	{
		if ( (i->first)->isA< Camera >() && i->second )
		{
			Camera * currentCamera = dynamic_cast< Camera * >(i->first);
			vgAssert( currentCamera != 0 );

			engine->paint( newCamera );
		}
		else
		{
			engine->paint( *i );
		}
	}
}



//@todo handler to reuse pass::Opaque
void passOpaqueWithGivenCamera(	vgeGL::engine::Engine * engine, vge::visitor::TraverseElementVector* traverseElements,
								const vgd::Shp< vgd::node::Camera > newCamera )
{
	using vgd::node::Camera;

	vge::visitor::TraverseElementVector::const_iterator i, iEnd;
	for(	i = traverseElements->begin(), iEnd = traverseElements->end();
			i != iEnd;
			++i )
	{
		if ( (i->first)->isA< Camera >() && i->second )
		{
			Camera * currentCamera = dynamic_cast< Camera * >(i->first);
			vgAssert( currentCamera != 0 );

			engine->paint( newCamera );
		}
		else if ( (i->first)->isAKindOf< vgd::node::Shape >() )
		{
			const float opacityDiff = fabs( engine->getGLState().getOpacity() - 1.f );

			if ( opacityDiff < vgm::Epsilon<float>::value() )
			{
				// object is opaque, draw it.
				engine->paint( *i );
			}
			/*else
			{
				m_mustDoTransparencyPass = true;
			}*/
		}
		else
		{
			engine->paint( *i );
		}
	}
}



struct GeometryOnlyState
{
	GeometryOnlyState( const bool lIsLightingEnabled, const bool lIsTextureMappingEnabled )
	:	isLightingEnabled		(	lIsLightingEnabled			),
		isTextureMappingEnabled	(	lIsTextureMappingEnabled	)
	{}

	const bool isLightingEnabled;
	const bool isTextureMappingEnabled;
};

vgd::Shp< GeometryOnlyState > configureGeometryOnly( vgeGL::engine::Engine * engine )
{
	// Makes a backup of GLSL activation state
	/* @todo Engine::GLSLActivationState deprecated
	using vgeGL::engine::Engine;
	vgd::Shp< Engine::GLSLActivationState > glslActivationState = engine->getGLSLActivationState();
	engine->sethCurrentProgram();
	glDisable( GL_LIGHTING );*/

	// Saves lighting state and texture mapping
	const bool isLightingEnabledBak			= engine->setLightingEnabled(false);
	const bool isTextureMappingEnabledBak	= engine->setTextureMappingEnabled(false);

	return vgd::makeShp( new GeometryOnlyState(isLightingEnabledBak, isTextureMappingEnabledBak) );
}

void unconfigureGeometryOnly( vgeGL::engine::Engine * engine, vgd::Shp< GeometryOnlyState > state )
{
	// @todo deprecated
	// Restores GLSL activation state
	//engine->setGLSLActivationState( glslActivationState );

	// Restores texture mapping and lighting state
	engine->setTextureMappingEnabled( state->isTextureMappingEnabled );
	engine->setLightingEnabled( state->isLightingEnabled );
}


void regardForGeometryOnly( vgeGL::engine::Engine * engine )
{
	engine->disregard();

	engine->regardIfIsAKindOf<vgd::node::Shape>();

	//engine->regardIfIsAKindOf<vgd::node::Kit>();

	engine->regardIfIsAKindOf<vgd::node::Group>();

	engine->regardIfIsAKindOf<vgd::node::SingleTransformation>();
	engine->regardIfIsA<vgd::node::ClearFrameBuffer>();
	engine->regardIfIsA<vgd::node::CullFace>();
	engine->regardIfIsA<vgd::node::FrontFace>();
	engine->regardIfIsA<vgd::node::Material >(); // to update GLState.opacity

	engine->regardIfIsA<vgd::node::ClipPlane>();

	engine->regardIfIsA<vgd::node::DrawStyle>();
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

// @todo move to Engine
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



void ForwardRendering::stageInitializeOutputBuffers( vgeGL::engine::Engine * engine )
{
	// OUTPUTBUFFERS
	// Tests if output buffers of engine must be initialized/re-initialized (see Engine::getOutputBuffers())
	if ( hasOutputBufferProperties )
	{
		// drawingSurfaceSizeChanged: Computes if drawing surface size has changed
		drawingSurfaceSizeChanged = false;

		vgd::Shp< glo::FrameBufferObject > outputBuffersOfEngine = m_fbo; //engine->getOutputBuffers(); ??????????????????????
		if ( outputBuffersOfEngine && (outputBuffersOfEngine->getNumOfColors() > 0) )
		{
			vgd::Shp< glo::Texture2D > texture2D = outputBuffersOfEngine->getColorAsTexture2D();
			if ( texture2D )
			{
				// Retrieves size of OpenGL canvas
				const vgm::Vec2i drawingSurfaceSize = engine->getDrawingSurfaceSize();

				drawingSurfaceSizeChanged =	( texture2D->getWidth() != drawingSurfaceSize[0] ) ||
											( texture2D->getHeight() != drawingSurfaceSize[1] );
			}
		}

		bool callInitializeEngineBuffers =
			!outputBuffersOfEngine		||														// no output buffers
			drawingSurfaceSizeChanged	||														// size changed
			(outputBuffersOfEngine->getNumOfColors() != m_outputBufferProperties->getNum());	// number of buffers changed

		// Tests if a change occurs in output buffers properties.
		if ( !callInitializeEngineBuffers )
		{
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
						// exit from the loop
						numFound = m_outputBufferProperties->getNum();
					}
				}
			}
		}

		// Initializes OUTPUTBUFFERS
		if ( callInitializeEngineBuffers )
		{
			setPassDescription("OutputBuffers initialization stage");
			beginPass();
			initializeEngineBuffers( engine, m_outputBufferProperties );
			endPass();
		}

		//
		vgAssert( m_fbo );
		engine->setOutputBuffers( m_fbo );
	}
	// else nothing to do
}



void ForwardRendering::initializeEngineBuffers( vgeGL::engine::Engine * engine, OutputBufferPropertyStateContainer * outputBufferProperties )
{
	// *** Initializes FBO and creates textures ***
	namespace vgeGLPainter = vgeGL::handler::painter;
	m_textures.clear();
	boost::tie( m_frameBuffer, m_fbo ) = vgeGLPainter::OutputBufferProperty::createsFBO( engine, outputBufferProperties, std::back_inserter(m_textures), true );
}



///////////////////////////////////
//// passInformationsCollector ////
///////////////////////////////////
void ForwardRendering::passInformationsCollector( vgeGL::engine::Engine * engine, vge::visitor::TraverseElementVector* traverseElements )
{
	// LIGHTMODEL
	lightModel = 0;

	// PROJECTION
	camera = 0;
	transformDragger = 0;
	viewMatrix = vgm::MatrixR::getIdentity();
	invViewMatrix = vgm::MatrixR::getIdentity();

	transformDraggerMatrix.setIdentity();
	invTransformDraggerMatrix.setIdentity();

	// Beginning of the pass

	// Saves texture mapping
	// To remove texture matrices initialization @todo not very cute @todo do the same for CPU transformation
	const bool isTextureMappingEnabledBak = engine->setTextureMappingEnabled(false); // @todo TransformSeparator TextureMatrix/ push/pop texture mapping disabled

	setPassDescription("Collects informations stage");
	beginPass();

	// engine->setBufferUsagePolicy( vge::engine::BUP_NO_COLOR_NO_DEPTH ); @todo

	engine->disregard();
	engine->regardIfIsAKindOf<vgd::node::SingleTransformation>();
	engine->regardIfIsAKindOf<vgd::node::Group>();
	engine->regardIfIsAKindOf<vgd::node::Dragger>();
	engine->regardIfIsA<vgd::node::LightModel>();
// for shadow
	engine->regardIfIsAKindOf<vgd::node::Light>();
// for postprocessing
	engine->regardIfIsAKindOf<vgd::node::OutputBufferProperty>();
	engine->regardIfIsAKindOf<vgd::node::Overlay>();
	engine->regardIfIsAKindOf<vgd::node::PostProcessing>();

	vge::visitor::TraverseElementVector::const_iterator i, iEnd;
	for(	i = traverseElements->begin(), iEnd = traverseElements->end();
			i != iEnd;
			++i )
	{
		engine->evaluate( paintService(), *i );

		// CAMERA
		if ( i->first->isA< vgd::node::Camera >() && i->second )
		{
			vgAssertN( camera == 0, "More than one camera !!!" );
			camera = dynamic_cast< vgd::node::Camera * >( i->first );

			viewMatrix = camera->getLookAt() * viewMatrix; // ???
			continue;
		}
		// TRANSFORM DRAGGER
		if ( i->first->isA< vgd::node::TransformDragger >() && i->second )
		{
			vgAssertN( transformDragger == 0, "More than one dragger !!!" );
			transformDragger = dynamic_cast< vgd::node::TransformDragger * >( i->first );

			transformDraggerMatrix = transformDragger->computeMatrixFromFields();
			invTransformDraggerMatrix = transformDraggerMatrix.getInverse();
			viewMatrix = transformDraggerMatrix * viewMatrix; // ???
			continue;
		}
		// LIGHT MODEL
		else if ( i->first->isA< vgd::node::LightModel >() && i->second )
		{
			lightModel = dynamic_cast< vgd::node::LightModel * >( i->first );

			// Retrieves shadow technique to use
			shadowType = engine->getOFEnum< vgd::node::LightModel >( vgd::node::LightModel::getFShadow() );

			shadowMapType = lightModel->getShadowMapType();

			if ( shadowType != vgd::node::LightModel::SHADOW_OFF )
			{
				// Extracts informations
				m_shadowMappingInput->reset( engine, shadowType );
				isShadowEnabled = shadowType != vgd::node::LightModel::SHADOW_OFF && m_shadowMappingInput->getNumLight() > 0;
			}
			else
			{
				isShadowEnabled = false;
			}

			continue;
		}
	}

	invViewMatrix = viewMatrix.getInverse();

	// Copy the glsl state at the end of the pass
	using vgeGL::engine::GLSLState;
	glslStateFinal.reset( new GLSLState( engine->getGLSLState() ) );

	if ( !lightModel )	vgLogDebug("You must have a LightModel node in the scene graph.");
	if ( !camera )		vgLogDebug("You must have a Camera node in the scene graph.");
	if ( !lightModel || !camera )	return;

	// STEREO
	isStereoEnabled = camera->getMode() != vgd::node::Camera::MONOSCOPIC;

	// POST-PROCESSING
	// POST-PROCESSING.outputbuffers
	// Checks outputBufferProperties
	hasOutputBufferProperties = glslStateFinal->outputBufferProperties.isNotEmpty();

	if (	glslStateFinal->outputBufferProperties.getNum() > 1 &&
			glslStateFinal->postProcessing.isEmpty() )
	{
		vgLogDebug("At least one unused OutputBufferProperty (i.e. No PostProcessing node, but at least two OutputBufferProperty node)");
	}

	// Saves the outputBufferProperties state
	m_outputBufferProperties = &(glslStateFinal->outputBufferProperties);


	// POST-PROCESSING.postprocessing
	// Checks post-processing
	isPostProcessingEnabled =
		!lightModel->getIgnorePostProcessing() && glslStateFinal->outputBufferProperties.isNotEmpty() && glslStateFinal->postProcessing.isNotEmpty();

	// Saves the post-processing state
	m_postProcessing = &(glslStateFinal->postProcessing);

	// OVERLAYS
	// Checks overlays
	renderOverlays = glslStateFinal->overlays.isNotEmpty();

	// Saves the overlays state
	m_overlays = &(glslStateFinal->overlays);

	endPass();

	// Restores texture mapping and lighting state
	engine->setTextureMappingEnabled( isTextureMappingEnabledBak );
}



/**
 * Computes shadow map(s), i.e. renders scene depth from light POV
 */
void ForwardRendering::passUpdateShadowMaps( vgeGL::engine::Engine * engine, vge::visitor::TraverseElementVector* traverseElements )
{
	lightLookAt.clear();

	if ( shadowType != vgd::node::LightModel::SHADOW_OFF )
	{
		// Configures geometry only pass
		vgd::Shp< GeometryOnlyState > geometryOnlyState = configureGeometryOnly( engine );
		regardForGeometryOnly(engine);

// @todo fine grain control in VertexShape
		engine->disregardIfIsA< vgd::node::MultipleInstances >();

		// Writes only to depth buffer
		engine->setBufferUsagePolicy( vge::engine::BUP_ONLY_DEPTH );

		// CullFace is used internally. So disables it.
		engine->disregardIfIsA< vgd::node::CullFace >();

		// For each light, updates shadow map
		lightLookAt.resize( m_shadowMappingInput->getNumLight() );

		for(	uint currentLightIndex = 0;
				currentLightIndex < m_shadowMappingInput->getNumLight();
				++currentLightIndex )
		{
			setPassDescription("Depth from light POV");
			beginPass( static_cast< PassIsolationMask >(RESET_MATRICES | PUSH_POP_STATE) );

			// Configures cull face
			glEnable( GL_CULL_FACE );
			glCullFace( GL_FRONT );

			// Configures polygon offset
			const vgm::Vec2f shadowPolygonOffset = lightModel->getShadowPolygonOffset();
			glPolygonOffset( shadowPolygonOffset[0], shadowPolygonOffset[1] );
			glEnable( GL_POLYGON_OFFSET_FILL );

			vgd::Shp< vgeGL::rc::FrameBufferObject > fbo = configureShadowMap( engine, currentLightIndex );
			if ( !fbo )	continue;
			engine->setOutputBuffers( fbo );

			// RENDER FROM LIGHT
			using ::vgd::node::Camera;
			vgd::Shp< Camera > fromLightCamera = setupRenderFromLightCamera(
				m_shadowMappingInput, currentLightIndex,
				invViewMatrix, invTransformDraggerMatrix,
				lightLookAt[currentLightIndex] );

			// shadows only for opaque objects
			passOpaqueWithGivenCamera( engine, traverseElements, fromLightCamera );
			//passPaintWithGivenCamera( engine, traverseElements, fromLightCamera );

			// Re-enable rendering to the window
//			fbo->unbind();

			endPass();
		}

		// Restores engine state
		unconfigureGeometryOnly( engine, geometryOnlyState );
	}
}



// node, rc and fbo for shadow map
// @todo clean api
// @todo optme
vgd::Shp< vgeGL::rc::FrameBufferObject > ForwardRendering::configureShadowMap( vgeGL::engine::Engine * engine, const uint currentLightIndex )
{
	// Texture2D(node and rc) for ShadowMap

	// Updates Texture2D node
	vgd::Shp< vgd::node::Texture2D > texture2D = m_shadowMappingInput->getLightDepthMap( currentLightIndex );

	using vgd::basic::IImage;
	using vgd::basic::ImageInfo;

	// texture2D.image
	IImage::Type								imageType;
	vgd::node::Texture::InternalFormatValueType internalFormat;
	boost::tie( imageType, internalFormat ) = convertShadowMapType2IImageType( shadowMapType );
	vgd::Shp< ImageInfo > depthImage(
		new ImageInfo(	m_shadowMappingInput->getShadowMapSize()[0], m_shadowMappingInput->getShadowMapSize()[1], 1,
						IImage::LUMINANCE, imageType ) );
	texture2D->setImage( depthImage ); // @todo OPTME only if modified

	// texture2D.internalFormat
	if ( texture2D->getInternalFormat() !=  internalFormat )	texture2D->setInternalFormat( internalFormat );

	// texture2D.multiAttributeIndex
	const uint currentTexUnit = engine->getGLSLState().getPrivateTexUnitIndex(currentLightIndex);
	if ( texture2D->getMultiAttributeIndex() != currentTexUnit )	texture2D->setMultiAttributeIndex( currentTexUnit );

	// paint
	const bool textureMappingEnabledBak = engine->setTextureMappingEnabled(true);
	engine->regardIfIsA<vgd::node::Texture2D>();

	engine->paint( texture2D );
	engine->setTextureMappingEnabled(textureMappingEnabledBak);
	engine->disregardIfIsA<vgd::node::Texture2D>();

	// Updates FBO
// @todo moves
	// Lookups or creates fbo
// @todo remove m_fbo
	vgeGL::engine::Engine::GLManagerType& rcManager = engine->getGLManager();
	vgd::Shp< vgeGL::rc::FrameBufferObject > fbo = rcManager.getShp< vgeGL::rc::FrameBufferObject >( m_shadowMappingInput->m_fbo[currentLightIndex].get() ); // @todo not very cute
	if ( !fbo )
	{
		fbo.reset( new vgeGL::rc::FrameBufferObject() );
		rcManager.add( m_shadowMappingInput->m_fbo[currentLightIndex].get(), fbo );

		fbo->generate();

		// Enables render to depth texture
		fbo->bind();

		vgd::Shp< vgeGL::rc::Texture2D > lightDepthMap = m_shadowMappingInput->getLightDepthMap( currentLightIndex, engine );
		fbo->attachDepth( lightDepthMap );

		fbo->renderDepthOnly();

		// Check framebuffer completeness at the end of initialization.
		const std::string fboStatus = fbo->getStatusString();
		if ( fboStatus.size() > 0 )
		{
			vgLogError2( "ForwardRendering::apply(): %s", fboStatus.c_str() );
			fbo.reset();
			return fbo;
		}
		// else nothing to do
		fbo->unbind();
	}
	//else nothing to do

	return fbo;
}



void ForwardRendering::passDepthOnly( vgeGL::engine::Engine * engine, vge::visitor::TraverseElementVector* traverseElements )
{
	// Writes only to depth buffer
	engine->setBufferUsagePolicy( vge::engine::BUP_ONLY_DEPTH );

	// Backups engine output buffers
	vgd::Shp< glo::FrameBufferObject > outputBuffers = engine->getOutputBuffers();

	// Configures geometry only pass
	vgd::Shp< GeometryOnlyState > geometryOnlyState = configureGeometryOnly( engine );

	// Pass
	setPassDescription("Depth only pass");
	beginPass();

	regardForGeometryOnly(engine);

	/*const bool mustDoTransparencyPass = */evaluateOpaquePass( paintService(), PassIsolationMask(0), true );

	endPass();

	// Restores engine state
	unconfigureGeometryOnly( engine, geometryOnlyState );

	// Restores engine output buffers
	engine->setOutputBuffers( outputBuffers );
}



// SHADOW MAPPING
void ForwardRendering::stageConfigureShadowMapping( vgeGL::engine::Engine * engine )
{
	if ( isShadowEnabled )
	{
		// Prepares texture units with depth map and tex coord
		for(	uint currentLightIndex = 0;
				currentLightIndex < m_shadowMappingInput->getNumLight();
				++currentLightIndex )
		{
			const uint currentTexUnit = engine->getGLSLState().getPrivateTexUnitIndex( currentLightIndex );

	// @todo Improves vgd::node::Texture to be able to use it directly

			// *** Updates Texture ***
			vgd::Shp< vgd::node::Texture2D > lightDepthMap = m_shadowMappingInput->getLightDepthMap( currentLightIndex );
			if ( lightDepthMap->getMultiAttributeIndex() != currentTexUnit )	lightDepthMap->setMultiAttributeIndex( currentTexUnit );
			engine->paint( lightDepthMap );
	// @todo setFunction()

			// *** Updates TexGen ***
			vgd::Shp< vgd::node::TexGenEyeLinear > texGen = m_shadowMappingInput->getTexGen( currentLightIndex );
			if ( texGen->getMultiAttributeIndex() != currentTexUnit )		texGen->setMultiAttributeIndex( currentTexUnit );
			engine->paint( texGen );

			// *** Updates Texture Matrix ***
	// @todo use TextureMatrix node
			vgm::MatrixR textureMatrix;
			textureMatrix.setTranslate( vgm::Vec3f(0.5f, 0.5f, 0.5f) );	// offset
			textureMatrix.scale( vgm::Vec3f(0.5f, 0.5f, 0.5f) );		// bias
			// LIGHT FRUSTUM (Projection)
			const vgm::MatrixR& lightProjectionMatrix = m_shadowMappingInput->getLightProjectionMatrix( currentLightIndex );

			textureMatrix = invViewMatrix * (lightLookAt[currentLightIndex]) * lightProjectionMatrix * textureMatrix;

			//
			engine->activeTexture(currentTexUnit);
			glMatrixMode( GL_TEXTURE );
			glLoadMatrixf( reinterpret_cast<const float*>( textureMatrix.getValue() ) );

			engine->getTextureMatrix().setTop( textureMatrix, currentTexUnit );
		}

		// Disables CullFace
		engine->disregardIfIsA< vgd::node::CullFace >();
	}
	//else nothing to do
}



// @todo Z-only pass, use handler, disable GLSL(or passthru glsl shader), texturing...
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
// @todo Occlusion Queries
void ForwardRendering::apply( vgeGL::engine::Engine * engine, vge::visitor::TraverseElementVector* traverseElements )
{
	using vgeGL::engine::GLSLState;

	/////////////////////////////////////////////////////////
	// STEP 1 : Computes additionnal informations
	// Searches the first LightModel node
	// (and active lights at this state) and the camera.
	/////////////////////////////////////////////////////////

	engine->setTrace();
	prepareEval( engine, traverseElements );

	passInformationsCollector( engine, traverseElements);
	engine->setTrace( false );

	// STEREO
	engine->setEyeUsagePolicy( vgd::node::Camera::DEFAULT_EYEUSAGEPOLICY );
	if ( isStereoEnabled )
	{
	const std::string defaultFragmentOutputStage = 
	"\n"
	"	gl_FragData[0] = color;\n";

		engine->setEyeUsagePolicy( vgd::node::Camera::EYE_LEFT );
			beginPass();
			engine->getGLSLState().setShaderStage( GLSLState::FRAGMENT_OUTPUT, defaultFragmentOutputStage ); // @todo in GLSLState constructor ?

			engine->setBufferUsagePolicy( vge::engine::BUP_COLOR_AND_DEPTH );

			// First pass : OPAQUE PASS (draw opaque shape)
			const bool mustDoTransparencyPass = evaluateOpaquePass( paintService(), PassIsolationMask(0), true );
			endPass();
		engine->setEyeUsagePolicy( vgd::node::Camera::EYE_RIGHT );
			beginPass();
			engine->getGLSLState().setShaderStage( GLSLState::FRAGMENT_OUTPUT, defaultFragmentOutputStage ); // @todo in GLSLState constructor ?

			engine->setBufferUsagePolicy( vge::engine::BUP_COLOR_AND_DEPTH );

			// First pass : OPAQUE PASS (draw opaque shape)
			/*const bool mustDoTransparencyPass = */evaluateOpaquePass( paintService(), PassIsolationMask(0), true );
			endPass();

				//
	finishEval();
	return;
	}
	// @todo vgeGL::SceneManager * sceneManager();
	
	/*if ( isStereoEnabled )
	{
		// @todo OPTME
		GLboolean glbool;
		glGetBooleanv( GL_STEREO, &glbool );

		if ( glbool == GL_FALSE )
		{
			// Request a stereo context
			vgLogDebug("Reinitializes vgsdk for stereoscopic rendering...");
			sceneManager()->shutdownVGSDK();
			sceneManager()->startVGSDK( true );
// @todo dirtyAllDF

			// Report if a stereo context has been initialized
			glGetBooleanv( GL_STEREO, &glbool );
			if ( glbool == GL_TRUE )
			{
				vgLogDebug("vgsdk stereoscopic context initialized done.");
			}
			else
			{
				vgLogDebug("Unable to initialize a stereoscopic context for vgsdk");
			}
		}
		// else nothing to do
	}
	// else @todo remove if needed stereo context*/

	// SHADOW MAP(S)
	passUpdateShadowMaps( engine, traverseElements );

	// OUTPUT BUFFERS init
	stageInitializeOutputBuffers( engine );

	// POST PROCESSING init
	stageInitializePostProcessingBuffers( engine );

	// DEPTH ONLY PASS
	if ( engine->isDepthPrePassEnabled() )		passDepthOnly( engine, traverseElements );

/*	@todo
	passMain( engine, traverseElements );
	passMain( vgeGL::engine::Engine * engine, vge::visitor::TraverseElementVector* traverseElements )*/
	//////////////////////////////////////////////////////////////////////////
	// STEP 3: Rendering (opaque and transparent pass ) with/without shadow //
	//////////////////////////////////////////////////////////////////////////

	const std::string defaultFragmentOutputStage = 
	"\n"
	"	gl_FragData[0] = color;\n";



	std::string description = "Main rendering pass";

	if ( isShadowEnabled )	description += " with shadow";
	if ( isPostProcessingEnabled )	description += " and post-processing";
	setPassDescription( description);

	beginPass();

	engine->getGLSLState().setShaderStage( GLSLState::FRAGMENT_OUTPUT, defaultFragmentOutputStage ); // @todo in GLSLState constructor ?

	// DEPTH PRE-PASS
	engine->setBufferUsagePolicy( engine->isDepthPrePassEnabled() ? vge::engine::BUP_ONLY_COLOR : vge::engine::BUP_COLOR_AND_DEPTH );

	// SHADOW
	stageConfigureShadowMapping( engine );

	// POST-PROCESSSING
	stageConfigurePostProcessing( engine );

		// First pass : OPAQUE PASS (draw opaque shape)
		const bool mustDoTransparencyPass = evaluateOpaquePass( paintService(), PassIsolationMask(0), true );

	endPass();


// @todo ignore transparency pass
	if ( mustDoTransparencyPass )
	{
	beginPass();

	engine->getGLSLState().setShaderStage( GLSLState::FRAGMENT_OUTPUT, defaultFragmentOutputStage ); // @todo in GLSLState constructor ?

// DEPTH PRE-PASS
engine->setBufferUsagePolicy( vge::engine::BUP_ONLY_COLOR_NO_CLEAR );

const bool isShadowEnabledBak = engine->setShadowEnabled( false );


// OUTPUT BUFFERS init
stageInitializeOutputBuffers( engine );

	// SHADOW
	//stageConfigureShadowMapping( engine );

	// POST-PROCESSSING
	//stageConfigurePostProcessing( engine );

		// Second pass : TRANSPARENT PASS (draw transparent shape)

		//m_fbo->setDrawBuffers( 0 );
		evaluateTransparentPass( paintService(), PassIsolationMask(0)/*PassIsolationMask(DEFAULT_PASS_ISOLATION_MASK)*/, true );

		endPass();

//
engine->setShadowEnabled( isShadowEnabledBak );
engine->setBufferUsagePolicy( vge::engine::BUP_NOT_DEFINED );
	}





	// POST-PROCESSING
	stagePostProcessing( engine );

/*			// First pass : OPAQUE PASS (draw opaque shape)
			const bool mustDoTransparencyPass = evaluateOpaquePass( paintService() );

			// Second pass : TRANSPARENT PASS (draw transparent shape).
			if ( mustDoTransparencyPass )
			{
				if ( isPostProcessingEnabled )
				{
					// Renders in FBO
					m_fbo->bind();
					m_fbo->setDrawBuffers( 0 );
				}
				evaluateTransparentPass( paintService() );
			}
		}
*/

	// OVERLAYS
	stageOverlays( engine );

	//
	finishEval();
}



/// POST PROCESSING
void ForwardRendering::stageInitializePostProcessingBuffers( vgeGL::engine::Engine * engine )
{
	// Post-processing buffers initialization
	if ( isPostProcessingEnabled )
	{
		// Tests if initialization must be done
		if (	!m_frameBuffer0 || !m_frameBuffer1 ||	// no fbo for ping-pong rendering
				drawingSurfaceSizeChanged	)			// size changed @todo this is only valid if hasOutputBufferProperties==true => do like drawingSurfaceSizeChanged computation
		{
			setPassDescription("PostProcessing initialization stage");
			beginPass();
			initializePostProcessingBuffers( engine );
			endPass();
		}
	}
}


void ForwardRendering::initializePostProcessingBuffers( vgeGL::engine::Engine * engine )
{
	// *** Initializes FBOs and creates textures ***
	// fbo0 and fbo1
	using vgd::node::OutputBufferProperty;
	using vgeGL::engine::GLSLState;

	vgd::Shp< OutputBufferPropertyStateContainer >	myOutputBufferProperties( new OutputBufferPropertyStateContainer() );

	vgd::Shp< OutputBufferProperty > obufProperty = OutputBufferProperty::create("buf0");
	obufProperty->setFormat( OutputBufferProperty::RGBA );
	obufProperty->setType( OutputBufferProperty::FLOAT16 );

	myOutputBufferProperties->setState(0, vgd::makeShp( new GLSLState::OutputBufferPropertyState(obufProperty.get()) ) );

	namespace vgeGLPainter = vgeGL::handler::painter;
	m_textures0.clear();
	m_textures1.clear();
	boost::tie( m_frameBuffer0, m_fbo0 ) = vgeGLPainter::OutputBufferProperty::createsFBO( engine, myOutputBufferProperties.get(), std::back_inserter(m_textures0) );
	boost::tie( m_frameBuffer1, m_fbo1 ) = vgeGLPainter::OutputBufferProperty::createsFBO( engine, myOutputBufferProperties.get(), std::back_inserter(m_textures1) );
}



void ForwardRendering::stageConfigurePostProcessing( vgeGL::engine::Engine * engine )
{
	if ( isPostProcessingEnabled )
	{
		namespace vgeGLPainter = vgeGL::handler::painter;
		using vgeGL::engine::GLSLState;

		const std::string fragmentOutputDeclarationStage(
			vgeGLPainter::OutputBufferProperty::getFragmentOutputDeclarationStageString(engine, m_outputBufferProperties )
			);

		const std::string fragmentOutputStage(
			vgeGLPainter::OutputBufferProperty::getFragmentOutputStageString(engine, m_outputBufferProperties )
			);

		engine->getGLSLState().setShaderStage( GLSLState::FRAGMENT_OUTPUT_DECLARATION, fragmentOutputDeclarationStage );
		engine->getGLSLState().setShaderStage( GLSLState::FRAGMENT_OUTPUT, fragmentOutputStage );
	}
	//else nothing to do
}



void ForwardRendering::stagePostProcessing( vgeGL::engine::Engine * engine )
{
	if ( isPostProcessingEnabled )
	{
		const vgd::Shp< vgeGL::rc::FrameBufferObject > finalBuffers = applyPostProcessing( engine, m_fbo0, m_fbo1 );

		blit( engine, finalBuffers );
	}
	else
	{
		if ( hasOutputBufferProperties )
		{
			blit( engine, m_fbo );
		}
		// else nothing to do
	}
}



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
			vgAssert( postProcessingNode );

			// Parameters

			// Builds declaration section of the shaders (depends of post-processing node param* fields)
			std::string currentDeclaration = declarations;

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
					vertexProgram, "INLINE_FTEXGEN",	"	mgl_TexCoord[0] = gl_TextureMatrix[0] * mgl_MultiTexCoord0;\n"
														"	mgl_TexCoord[1] = gl_TextureMatrix[1] * mgl_MultiTexCoord1;\n"
														"	mgl_TexCoord[2] = gl_TextureMatrix[2] * mgl_MultiTexCoord2;\n" );
			}
			else if ( postProcessingNode->getInput1() != vgd::node::PostProcessing::INPUT1_NONE )
			{
				vertexShader = boost::algorithm::replace_first_copy( 
					vertexProgram, "INLINE_FTEXGEN",	"	mgl_TexCoord[0] = gl_TextureMatrix[0] * mgl_MultiTexCoord0;\n"
														"	mgl_TexCoord[1] = gl_TextureMatrix[1] * mgl_MultiTexCoord1;\n" );
			}
			else
			{
				vertexShader = boost::algorithm::replace_first_copy( 
					vertexProgram, "INLINE_FTEXGEN", "	mgl_TexCoord[0] = gl_TextureMatrix[0] * mgl_MultiTexCoord0;\n" );
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

	setPassDescription("Post-processing stage");
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
		vgAssert( nearFar.isValid() );

		vgAssertN( !engine->getUniformState().isUniform( "nearFar"), "Uniform nearFar already used" );
		engine->getUniformState().addUniform( "nearFar", nearFar );

		// param1f0
		const float param1f0 = params1f0[i];
		if ( param1f0 != std::numeric_limits<float>::max() )
		{
			vgAssertN( !engine->getUniformState().isUniform( "param1f0"), "Uniform param1f0 already used" );
			engine->getUniformState().addUniform( "param1f0", param1f0 );
		}

		// param4f0
		const vgm::Vec4f param4f0 = params4f0[i];
		if ( param4f0.isValid() )
		{
			vgAssertN( !engine->getUniformState().isUniform( "param4f0"), "Uniform param4f0 already used" );
			engine->getUniformState().addUniform( "param4f0", param4f0 );
		}

		// param4f1
		const vgm::Vec4f param4f1 = params4f1[i];
		if ( param4f1.isValid() )
		{
			vgAssertN( !engine->getUniformState().isUniform( "param4f1"), "Uniform param4f1 already used" );
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
		lfbo1->bind();
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
		//lfbo1->unbind();

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



void ForwardRendering::stageOverlays( vgeGL::engine::Engine * engine )
{
	// Renders overlays
	if ( renderOverlays )
	{
		setPassDescription("OVERLAYS stage");
		beginPass();
		vgeGL::handler::painter::Overlay::paint( engine, m_overlays );
		endPass();
	}
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
