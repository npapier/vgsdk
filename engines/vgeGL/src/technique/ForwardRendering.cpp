// VGSDK - Copyright (C) 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/technique/ForwardRendering.hpp"

#include <vgd/basic/ImageInfo.hpp>
#include <vgd/node/Camera.hpp>
#include <vgd/node/CullFace.hpp>
#include <vgd/node/LightModel.hpp>
#include <vgd/node/SpotLight.hpp>
#include <vgd/node/Texture2D.hpp>
#include <vgd/node/TexGenEyeLinear.hpp>
#include <vgd/node/TransformDragger.hpp>
#include <vgDebug/convenience.hpp>
#include <vge/service/Painter.hpp>
#include <vgm/VectorOperations.hpp>
#include "vgeGL/engine/Engine.hpp"
#include "vgeGL/rc/Texture2D.hpp"


#include <vgd/basic/Image.hpp> // ???




namespace vgeGL
{

namespace technique
{



namespace
{

/**
 * @brief Input informations for shadow mapping
 *
 * @todo Light* and MatrixR are the informations needed to compute all shadow mapping input for a light. BoundingBox of root to adjust projection
 */
struct ShadowMappingInput
{
	/**
	 * @brief Default constructor
	 *
	 * @param engine		the engine where informations on the current state would be extracted.
	 * @param shadowType	
	 */
	ShadowMappingInput( const vgeGL::engine::Engine * engine, const vgd::node::LightModel::ShadowValueType shadowType );


	/**
	 * @name Accessors
	 */
	//@{

	/**
	 * @brief Returns number of light casting shadow.
	 */
	const uint getNumLight() const;

	const vgm::MatrixR& getLightViewMatrix( const uint index );
	const vgm::MatrixR& getLightMODELVIEWMatrix( const uint index );
	const vgm::MatrixR& getLightProjectionMatrix( const uint index );

	//vgd::Shp< glo::Texture2D > getLightDepthMap( const uint index );
	vgd::Shp< vgd::node::Texture2D > getLightDepthMap( const uint index );
	vgeGL::rc::Texture2D * getLightDepthMap( const uint index, vgeGL::engine::Engine * engine );
	vgd::Shp< vgd::node::TexGenEyeLinear > getTexGen( const uint index );

	const vgm::Vec2i getShadowMapSize() const;

	/*const vgd::node::LightModel::ShadowValueType& getType() const;
	void setType( const vgd::node::LightModel::ShadowValueType& type );*/
	//@}


private:
// @todo only one vector
	std::vector< vgm::MatrixR >					m_lightViewMatrix;
	std::vector< vgm::MatrixR >					m_lightMODELVIEWMatrix;
	std::vector< vgm::MatrixR >					m_lightProjectionMatrix;

	std::vector< vgd::Shp< vgd::node::Texture2D > >			m_lightDepthMap;
//	std::vector< vgd::Shp< glo::Texture2D > >				m_lightDepthMap;
	std::vector< vgd::Shp< vgd::node::TexGenEyeLinear > >	m_texGen;

	vgm::Vec2i												m_shadowMapSize;
	//vgd::node::LightModel::ShadowValueType					m_type;
};



ShadowMappingInput::ShadowMappingInput( const vgeGL::engine::Engine * engine, const vgd::node::LightModel::ShadowValueType shadowType )
{
	// Retrieves GLSLState from engine
	using vgeGL::engine::GLSLState;
	const GLSLState& state = engine->getGLSLState();

	// Computes shadow map size and type
	const vgm::Vec2i drawingSurface = engine->getDrawingSurfaceSize();
	//const vgm::Vec2i drawingSurfacePower2( /*vgm::nextPower2(*/drawingSurface/*)*/ ); // @todo still useful ?
	//const vgm::Vec2f drawingSurfacePower2f( drawingSurfacePower2 );
	//const vgm::Vec2i drawingSurfacePower2i( drawingSurfacePower2f/2.f );
	m_shadowMapSize = drawingSurface; //drawingSurfacePower2i; // @todo wait FBO

	// Lights informations
	uint		i		= 0;
	const uint	iEnd	= state.getMaxLight();

	for( uint numLightFound = 0; (i != iEnd) && (numLightFound != state.getNumLight()); ++i )
	{
		const vgd::Shp< GLSLState::LightState > current = state.getLight( i );
		if ( !current )
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
				m_lightViewMatrix.push_back( current->lightViewMatrix );
				m_lightMODELVIEWMatrix.push_back( current->lightMODELVIEWMatrix );

// @todo FIXME check scene size
				vgm::MatrixR projection;
				projection.setPerspective(	45.f,
											m_shadowMapSize[0]/m_shadowMapSize[1], //1.f, /* see aspect ratio of FBO */ 
											1.f, 1000.f );
				m_lightProjectionMatrix.push_back( projection );

				// Initializes private nodes for shadow mapping
// @todo recycle nodes
				using vgd::node::Texture;
				vgd::Shp< vgd::node::Texture2D > lightDepthMap = vgd::node::Texture2D::create("depthMap.spotLight" + vgd::basic::toString( static_cast<int>(spot->getMultiAttributeIndex())) );

				std::string function;
				if ( shadowType == vgd::node::LightModel::SHADOW_OFF )
				{
					function = "";
				}
				else if ( shadowType == vgd::node::LightModel::SHADOW_MAPPING )
				{
					// 1X
					function = "color = lookupShadowMap(2, vec2(0,0));\n";
				}
				else if ( shadowType == vgd::node::LightModel::SHADOW_MAPPING_4U )
				{
					// 4X uniform
					function =	"float sum = 0.0;\n"
								"	sum += lookupShadowMap(2, vec2(-0.5, -0.5) );\n"
								"	sum += lookupShadowMap(2, vec2(0.5, -0.5) );\n"
								"	sum += lookupShadowMap(2, vec2(-0.5, 0.5) );\n"
								"	sum += lookupShadowMap(2, vec2(0.5, 0.5) );\n"
								"	color = sum * 0.25 * color;\n";
				}
				else if ( shadowType == vgd::node::LightModel::SHADOW_MAPPING_4D )
				{
					// 4X dither
					// with modulo
					function =	"// use modulo to vary the sample pattern\n"
								"	vec2 o = mod(floor(gl_FragCoord.xy), 2.0);\n"
								"	float sum = 0.0;\n"
								"	sum += lookupShadowMap(2, vec2(-1.5, 1.5) + o );\n"
								"	sum += lookupShadowMap(2, vec2(0.5, 1.5) + o );\n"
								"	sum += lookupShadowMap(2, vec2(-1.5, -0.5) + o );\n"
								"	sum += lookupShadowMap(2, vec2(0.5, -0.5) + o );\n"
								"	color = sum * 0.25 * color;\n";
				}
				else if ( shadowType == vgd::node::LightModel::SHADOW_MAPPING_16U )
				{
					// 16X
					// with modulo
					function =	"// use modulo to vary the sample pattern\n"
								"	vec2 o = mod(floor(gl_FragCoord.xy), 2.0);\n"
								"	float sum = 0.0;\n"
								"	float x, y;\n"
								"	for (y = -1.5; y <= 1.5; y += 1.0)\n"
								"		for (x = -1.5; x <= 1.5; x += 1.0)\n"
								"			sum += lookupShadowMap(2, vec2(x, y) + o);\n"
								"	color = sum / 16.0 * color;\n";
					/*// 16X
					function =	"float sum = 0.0;\n"
								"	float x, y;\n"
								"	for (y = -1.5; y <= 1.5; y += 1.0)\n"
								"		for (x = -1.5; x <= 1.5; x += 1.0)\n"
								"			sum += lookupShadowMap(2, vec2(x, y) );\n"
								"	color = sum / 16.0 * color;\n";*/
				}
				else if ( shadowType == vgd::node::LightModel::SHADOW_MAPPING_32U )
				{
					/*// 16X
					function =	"float sum = 0.0;\n"
								"	float x, y;\n"
								"	for (y = -1.5; y <= 1.5; y += 1.0)\n"
								"		for (x = -1.5; x <= 1.5; x += 1.0)\n"
								"			sum += lookupShadowMap(2, vec2(x, y) );\n"
								"	color = sum / 16.0 * color;\n";*/

					// DEBUG
					function = "color *= texture2DProj(texUnit2, gl_TexCoord[2] );\n";

					/*// 32X
					// @todo
					function =	"float coef = 2.0;\n"
								"float sum = 0.0;\n"
								"	float x, y;\n"
								"	for (y = -1.5*coef; y <= 1.5*coef; y += 1.0)\n"
								"		for (x = -1.5*coef; x <= 1.5*coef; x += 1.0)\n"
								"			sum += lookupShadowMap(2, vec2(x, y) );\n"
								"	color = sum / (16.0*coef) * color;\n";*/
				}

				lightDepthMap->setFunction( function );

				//lightDepthMap->sethFunction( vgd::node::Texture2D::FUN_MODULATE );
				// vgd::Shp< glo::Texture2D > lightDepthMap( new glo::Texture2D() );

				lightDepthMap->setWrap( Texture::WRAP_S, Texture::CLAMP ); // GL_CLAMP_TO_EDGE
				lightDepthMap->setWrap( Texture::WRAP_T, Texture::CLAMP );

				//lightDepthMap->setMipmap( true );
				lightDepthMap->setFilter( Texture::MIN_FILTER, Texture::LINEAR );
				//lightDepthMap->setFilter( Texture::MIN_FILTER, Texture::LINEAR_MIPMAP_LINEAR /*LINEAR */);
				lightDepthMap->setFilter( Texture::MAG_FILTER, Texture::LINEAR );


				lightDepthMap->setUsage( Texture::SHADOW );

				m_lightDepthMap.push_back( lightDepthMap );

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
	return m_lightViewMatrix.size();
}


const vgm::MatrixR& ShadowMappingInput::getLightViewMatrix( const uint index )
{
	assert( index < getNumLight() && "ShadowMappingInput::getLightViewMatrix(): Out of range index." );

	return m_lightViewMatrix[index];
}


const vgm::MatrixR& ShadowMappingInput::getLightMODELVIEWMatrix( const uint index )
{
	assert( index < getNumLight() && "ShadowMappingInput::getLightMODELVIEWMatrix(): Out of range index." );

	return m_lightMODELVIEWMatrix[index];
}



const vgm::MatrixR& ShadowMappingInput::getLightProjectionMatrix( const uint index )
{
	assert( index < getNumLight() && "ShadowMappingInput::getLightProjectionMatrix(): Out of range index." );

	return m_lightProjectionMatrix[index];
}


vgd::Shp< vgd::node::Texture2D > ShadowMappingInput::getLightDepthMap( const uint index )
{
	assert( index < getNumLight() && "ShadowMappingInput::getLightDepthMap(): Out of range index." );

	return m_lightDepthMap[index];
}


vgeGL::rc::Texture2D * ShadowMappingInput::getLightDepthMap( const uint index, vgeGL::engine::Engine * engine )
{
	assert( index < getNumLight() && "ShadowMappingInput::getLightDepthMap(): Out of range index." );

	vgd::Shp< vgd::node::Texture2D > texture2DNode = getLightDepthMap(index);

	// Gets the resource manager
	vge::rc::Manager& manager = engine->getGLManager();

	return manager.get< vgeGL::rc::Texture2D >( texture2DNode.get() );
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



} // namespace {



// DONE: compatible with GLSL, texturing, MultiMain (embeded a technique into another one)
// Ulis SG(run)
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
	using vgd::node::LightModel;

	//
	vgd::Shp< vge::service::Service > paintService = vge::service::Painter::create();

	prepareEval( engine, traverseElements );

	/////////////////////////////////////////////////////////
	// STEP 1 : Computes additionnal informations
	// Searches the first LightModel node (and active lights at this state) and the camera.
	/////////////////////////////////////////////////////////

	vgd::node::LightModel::ShadowValueType shadowType;
	vgd::Shp< ShadowMappingInput > shadowMappingInput;

	const uint internalTexUnitIndex = engine->getMaxTexUnits()-1;

	// VIEW MATRIX and PROJECTION MATRIX
	vgd::node::Camera *				camera				= 0;
	vgd::node::TransformDragger *	transformDragger	= 0;
	vgm::MatrixR viewMatrix		= vgm::MatrixR::getIdentity();
	vgm::MatrixR invViewMatrix	= vgm::MatrixR::getIdentity();

	setPassDescription("ForwardRendering:STEP1:Collects informations");
	beginPass();

	/*engine->disregard();
	engine->regardIfIsAKindOf<vgd::node::SingleTransformation>();
	engine->regardIfIsAKindOf<vgd::node::Group>();
	engine->regardIfIsAKindOf<vgd::node::Kit>();
	engine->regardIfIsAKindOf<vgd::node::Light>();
	engine->regardIfIsAKindOf<vgd::node::Shape>();*/

	bool foundLightModel = false;
	vge::visitor::TraverseElementVector::const_iterator i, iEnd;
	for(	i = traverseElements->begin(), iEnd = traverseElements->end();
			!foundLightModel && i != iEnd;
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
			LightModel * lightModel = dynamic_cast< LightModel * >( i->first );

			// Retrieves shadow technique to use
			bool isDefined = lightModel->getShadow( shadowType );	// @todo getDefaultShadow(LightModel::DEFAULT_SHADOW ); value = getShadow() 
			if ( !isDefined )	shadowType = LightModel::DEFAULT_SHADOW; // @todo not very cute

			//
			if ( shadowType != LightModel::SHADOW_OFF )
			{
				// Extracts informations
				shadowMappingInput.reset( new ShadowMappingInput( engine, shadowType ) );
				//shadowMappingInput->setType( shadow );
			}
			// else nothing to do

			// Stops this pass
			foundLightModel = true;
			continue;
		}
	}

	assert( camera != 0 );

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


	/////////////////////////////////////////////////////////
	// STEP 2: Computes shadow map, i.e. renders scene from light POV
	/////////////////////////////////////////////////////////
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
		//glPolygonOffset( 2.f, 16.f ); // 1.1, 4 from MJK // @todo must be adaptative
		//glEnable( GL_POLYGON_OFFSET_FILL );
// @todo think about interaction whith CullFace ? Don't use it, but see PolygonOffset


		for(	uint currentLightIndex = 0;
				currentLightIndex < shadowMappingInput->getNumLight();
				++currentLightIndex )
		{
			setPassDescription("ForwardRendering:STEP2:Rendering from light POV");
			beginPass();

			// pre-configuration
			glColorMask( GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE );

// @todo
			glEnable( GL_CULL_FACE );
			glCullFace( GL_FRONT );
			engine->disregardIfIsA< vgd::node::CullFace >();

			//glPolygonOffset( 1.1f, 4.f ); //2.f, 16.f ); // 1.1, 4 from MJK // @todo must be adaptative
			//glEnable( GL_POLYGON_OFFSET_FILL );

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

					//
					//engine->evaluate( paintService, *i );

					// Uses my camera
					vgd::Shp< Camera > newCamera = Camera::create("ForwardRendering::CameraFromLight");

					vgm::MatrixR lightViewMatrix = shadowMappingInput->getLightViewMatrix(currentLightIndex);
					vgm::MatrixR lightMODELVIEWMatrix = shadowMappingInput->getLightMODELVIEWMatrix(currentLightIndex);
/*// I must undo the transform dragger action => @todo disable TransformDragger
					newCamera->setLookAt(
						 invTransformDraggerMatrix * lightViewMatrix
						);*/
					newCamera->setLookAt(
						 invTransformDraggerMatrix * (lightMODELVIEWMatrix * invViewMatrix * lightViewMatrix)
						);
					newCamera->setProjection( shadowMappingInput->getLightProjectionMatrix(currentLightIndex) );

					const vgm::Rectangle2i viewport( 0, 0, shadowMappingInput->getShadowMapSize()[0], shadowMappingInput->getShadowMapSize()[1] );
					newCamera->setViewport( viewport );

					engine->evaluate( paintService, newCamera.get(), i->second );
// PB RENDER Point Of Light and
// Cullface in sg(TBT)
				}
				else
				{
					engine->evaluate( paintService, *i );
				}
			}


			// Rendering done, extract depth map  from depth buffer and copy into a texture2D node.
// @todo more high-level (Engine::renderTargets section ?)
			vgd::Shp< vgd::node::Texture2D > texture2D = shadowMappingInput->getLightDepthMap( currentLightIndex );

// @todo Image::DEPTH ?
			using vgd::basic::IImage;
			using vgd::basic::ImageInfo;
			vgd::Shp< ImageInfo > depthImage(
				new ImageInfo(	shadowMappingInput->getShadowMapSize()[0], shadowMappingInput->getShadowMapSize()[1], 1,
								IImage::LUMINANCE, IImage::FLOAT/*,0*/ ) );
			texture2D->setImage( depthImage );
			const uint currentTexUnit = internalTexUnitIndex - currentLightIndex;
			texture2D->setMultiAttributeIndex( currentTexUnit );
			engine->evaluate( paintService, texture2D.get(), true );
			vgeGL::rc::Texture2D * lightDepthMap = shadowMappingInput->getLightDepthMap( currentLightIndex, engine );
			lightDepthMap->bind();

// @todo in Texture handler
			lightDepthMap->parameter( GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE_ARB );
			lightDepthMap->parameter( GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL );
			lightDepthMap->parameter( GL_DEPTH_TEXTURE_MODE_ARB, GL_INTENSITY );
// @todo in glo
			glCopyTexSubImage2D(	GL_TEXTURE_2D, 0,
									0, 0, 0, 0,
									shadowMappingInput->getShadowMapSize()[0], 
									shadowMappingInput->getShadowMapSize()[1] );

			// to debug projective texturing
/*			static vgd::Shp< vgd::basic::Image > image( new vgd::basic::Image("ulis_gbr_0571.png") );
			lightDepthMap->texImage( 0,
									GL_RGB, image->width(), image->height(), image->depth(),
									0,
									GL_RGB,
									GL_UNSIGNED_BYTE,
									image->pixels() );*/

			endPass();

// @todo param HIGH-QUALITY => GL_FLOAT
/*			using vgd::basic::IImage;
			vgd::Shp< vgd::basic::Image > image( new vgd::basic::Image(
				getShadowMapSize()[0], getShadowMapSize()[1], 1,
				IImage::LUMINANCE, Image::FLOAT ) );

			texture2D->setImage( image );
			const GLenum internalDepthFormat = engine->getGLDepthTextureFormatFromDepthBits();
			lightDepthMap->texImage(	0, internalDepthFormat,
										getShadowMapSize()[0],
										getShadowMapSize()[1],
										0,
										0, // border
										GL_DEPTH_COMPONENT, GL_FLOAT 
										// GL_UNSIGNED_INT, GL_UNSIGNED_BYTE 
										);

			lightDepthMap->parameter( GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE_ARB );
			lightDepthMap->parameter( GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL );
			lightDepthMap->parameter( GL_DEPTH_TEXTURE_MODE_ARB, GL_INTENSITY );

			glCopyTexSubImage2D(	GL_TEXTURE_2D, 0, 0, 0, 0, 0,
									shadowMappingInput->getShadowMapSize()[0], 
									shadowMappingInput->getShadowMapSize()[1] );*/



//			glDisable( GL_CULL_FACE );
//			glDisable( GL_POLYGON_OFFSET_FILL );
//			glEnable( GL_LIGHTING );
//			glColorMask( GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE );
//			glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		}
	}



	/////////////////////////////////////////////////////////
	// STEP 3: Rendering (opaque and transparent pass ) with/without shadow
	/////////////////////////////////////////////////////////
	if ( shadowType != LightModel::SHADOW_OFF && shadowMappingInput->getNumLight() > 0 )
	{
		setPassDescription("ForwardRendering:STEP3:Rendering with shadow");
		beginPass();

// @todo
		for(	uint currentLightIndex = 0;
				currentLightIndex < shadowMappingInput->getNumLight();
				++currentLightIndex )
		{
			const uint currentTexUnit = internalTexUnitIndex - currentLightIndex;

// @todo must be compatible with texturing from SG
// @todo Improves vgd::node::Texture to be able to use it directly

			// *** Updates Texture ***
			vgd::Shp< vgd::node::Texture2D > texture2D = shadowMappingInput->getLightDepthMap( currentLightIndex );
			//texture2D->setMultiAttributeIndex( currentTexUnit );
// @todo setFunction()
			engine->evaluate( paintService, texture2D.get(), true );
			
			//vgeGL::rc::Texture2D * lightDepthMap( shadowMappingInput->getLightDepthMap( currentLightIndex, engine ) );
			//glo::Texture::active( GL_TEXTURE0_ARB + currentTexUnit );
			//lightDepthMap->bind();
			//lightDepthMap->enable();

			// *** Updates TexGen ***
			/*glMatrixMode( GL_MODELVIEW );
			glPushMatrix();
			glLoadIdentity();
//			glLoadMatrixf( reinterpret_cast<const float*>( transformDragger->getMatrix().getValue() ) );
			glLoadMatrixf( reinterpret_cast<const float*>( transformDragger->computeMatrixFromFields().getValue() ) );*/

			vgd::Shp< vgd::node::TexGenEyeLinear > texGen = shadowMappingInput->getTexGen( currentLightIndex );
			texGen->setMultiAttributeIndex( currentTexUnit );
			engine->evaluate( paintService, texGen.get(), true );

			//glPopMatrix();

			// *** Updates Texture Matrix ***
/*// @todo use TextureMatrix node
			vgm::MatrixR textureMatrix;
			textureMatrix.setTranslate( vgm::Vec3f(0.5f, 0.5f, 0.5f) );	// offset
			textureMatrix.scale( vgm::Vec3f(0.5f, 0.5f, 0.5f) );		// bias
			// LIGHT FRUSTUM (Projection)
			const vgm::MatrixR lightProjectionMatrix = shadowMappingInput->getLightProjectionMatrix( currentLightIndex );
			textureMatrix = lightProjectionMatrix * textureMatrix;
			// LIGHT VIEW (Look At)
			textureMatrix = (invViewMatrix * shadowMappingInput->getLightViewMatrix(0)) * textureMatrix;*/

// @todo use TextureMatrix node
			vgm::MatrixR textureMatrix;
			textureMatrix.setTranslate( vgm::Vec3f(0.5f, 0.5f, 0.5f) );	// offset
			textureMatrix.scale( vgm::Vec3f(0.5f, 0.5f, 0.5f) );		// bias
			// LIGHT FRUSTUM (Projection)
			const vgm::MatrixR lightProjectionMatrix = shadowMappingInput->getLightProjectionMatrix( currentLightIndex );
			// LIGHT VIEW (Look At)
			const vgm::MatrixR lightViewMatrix = shadowMappingInput->getLightViewMatrix(currentLightIndex);
			const vgm::MatrixR lightMODELVIEWMatrix = shadowMappingInput->getLightMODELVIEWMatrix(currentLightIndex);

			//textureMatrix = invViewMatrix * lightViewMatrix * lightProjectionMatrix * textureMatrix;
			textureMatrix = invViewMatrix * (lightMODELVIEWMatrix * invViewMatrix * lightViewMatrix) * lightProjectionMatrix * textureMatrix;

			//
			engine->activeTexture(currentTexUnit);
			glMatrixMode( GL_TEXTURE );
			glLoadMatrixf( reinterpret_cast<const float*>( textureMatrix.getValue() ) );

			engine->getTextureMatrix().setTop( textureMatrix, currentTexUnit );
		}

		engine->disregardIfIsA< vgd::node::CullFace >();

		/////////////////////////////////////////////////////////
		// First pass : OPAQUE PASS (draw opaque shape)
		const bool mustDoTransparencyPass = evaluateOpaquePass( paintService, PassIsolationMask(0), true );

		// Second pass : TRANSPARENT PASS (draw transparent shape).
		/*if ( mustDoTransparencyPass )
		{
			evaluateTransparentPass( paintService, PassIsolationMask(DEFAULT_PASS_ISOLATION_MASK), true );
		}*/
		/////////////////////////////////////////////////////////

		endPass();
	}
	else
	/////////////////////////////////////////////////////////
	// STEP 3 bis : Rendering (opaque and transparent pass )
	/////////////////////////////////////////////////////////
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

	//
	finishEval();
}



} // namespace technique

} // namespace vgeGL
