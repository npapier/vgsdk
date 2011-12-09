// VGSDK - Copyright (C) 2009, 2010, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/technique/ForwardRendering.hpp"

#include <algorithm>
#include <boost/assign/std/vector.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/foreach.hpp>
#include <boost/tuple/tuple.hpp>
#include <vgeGL/rc/GLSLProgram.hpp>
#include <strstream>
#include <vgd/basic/Image.hpp>
#include <vgd/basic/ImageInfo.hpp>
#include <vgd/node/ClearFrameBuffer.hpp>
#include <vgd/node/ClipPlane.hpp>
#include <vgd/node/CullFace.hpp>
#include <vgd/node/Fluid.hpp>
#include <vgd/node/Grid.hpp>
#include <vgd/node/FrameBuffer.hpp>
#include <vgd/node/FrontFace.hpp>
#include <vgd/node/Quad.hpp>
#include <vgd/node/LightModel.hpp>
#include <vgd/node/Material.hpp>
#include <vgd/node/Program.hpp>
#include <vgd/node/MultiTransformation.hpp>
#include <vgd/node/MultipleInstances.hpp>
#include <vgd/node/OutputBuffers.hpp>
#include <vgd/node/OutputBufferProperty.hpp>
#include <vgd/node/Overlay.hpp>
#include <vgd/node/PostProcessing.hpp>
#include <vgd/node/Separator.hpp>
#include <vgd/node/SpotLight.hpp>
#include <vgd/node/TextureTransformation.hpp>
#include <vgd/node/Texture2D.hpp>
#include <vgd/node/TexGenEyeLinear.hpp>
#include <vge/engine/SceneManager.hpp>
#include <vge/service/Painter.hpp>
#include <vge/technique/ComputeBoundingBox.hpp>
#include <vgeGL/handler/painter/PostProcessing.hpp>
#include <vgm/VectorOperations.hpp>
#include "vgeGL/engine/Engine.hpp"
#include "vgeGL/engine/GLSLState.hpp"
#include "vgeGL/handler/painter/OutputBufferProperty.hpp"
#include "vgeGL/handler/painter/Overlay.hpp"
#include "vgeGL/rc/Fluid.hpp"
#include "vgeGL/rc/Texture2D.hpp"
#include "vgeGL/rc/FrameBufferObject.hpp"
#include "vgeGL/technique/helpers.hpp"
#include "vgeGL/technique/PostProcessing.hpp"
#include "vgeGL/technique/ShadowMapping.hpp"

// sub-techniques
#include "vgeGL/technique/Noise.hpp"
#include "vgeGL/technique/DepthOfField.hpp"

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



// @todo OPTME using new handler for Camera
void passPaint(	vgeGL::engine::Engine * engine, vge::visitor::TraverseElementVector* traverseElements,
				const vgd::Shp< vgd::node::Camera > camera )
{
	// Camera
	engine->paint( camera );

	// Clear
	// @todo in engine
	using vgd::node::ClearFrameBuffer;
	vgd::Shp< ClearFrameBuffer > clear = ClearFrameBuffer::create("clear");
	engine->paint( clear );

	// LightModel
	using vgd::node::LightModel;
	vgd::Shp< LightModel > lightModel = LightModel::create("lightModel");
	lightModel->setModel( LightModel::STANDARD_PER_PIXEL );
	engine->paint( lightModel );

	vge::visitor::TraverseElementVector::const_iterator i, iEnd;
	for(	i = traverseElements->begin(), iEnd = traverseElements->end();
			i != iEnd;
			++i )
	{
		engine->paint( *i );
	}
}



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

	// Initializes sub-techniques
	m_subtechniques.push_back( vgd::makeShp( new vgeGL::technique::DepthOfField() ) );
	m_subtechniques.push_back( vgd::makeShp( new vgeGL::technique::Noise() ) );
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
// for fluid
	engine->regardIfIsA<vgd::node::Fluid>();

	isFluidEnabled = false;
	fluid = 0;
	fluidModelViewMatrix.setIdentity();


// for postprocessing
	engine->regardIfIsAKindOf<vgd::node::OutputBufferProperty>();
	engine->regardIfIsAKindOf<vgd::node::Overlay>();
	engine->regardIfIsAKindOf<vgd::node::PostProcessing>();

	//
	BOOST_FOREACH( SubTechniqueShp subtechnique, m_subtechniques )
	{
		subtechnique->reset();
		subtechnique->stageCollectInformationsBegin( engine );
	}

	vge::visitor::TraverseElementVector::const_iterator i, iEnd;
	for(	i = traverseElements->begin(), iEnd = traverseElements->end();
			i != iEnd;
			++i )
	{
		bool retVal;
		BOOST_FOREACH( SubTechniqueShp subtechnique, m_subtechniques )
		{
			//
			retVal = subtechnique->collectInformationsCallback( i );
			if ( retVal )
			{
				// Found, so stop foreach.
				break;
			}
			// else nothing to do
		}

		if ( retVal )
		{
			continue;
		}
		// else nothing to do

		// FLUID
		if ( i->first->isA< vgd::node::Fluid >() && i->second )
		{
			fluid = dynamic_cast< vgd::node::Fluid * >( i->first );
			isFluidEnabled = true;
			fluidModelViewMatrix = engine->getGeometricalMatrix().getTop();
			continue;
		}


		engine->evaluate( paintService(), *i );

		// CAMERA
		if ( i->first->isA< vgd::node::Camera >() && i->second )
		{
			vgAssertN( camera == 0, "More than one camera !!!" );
			camera = dynamic_cast< vgd::node::Camera * >( i->first );

			viewMatrix = camera->getLookAt() * viewMatrix;
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
	engine->setGlobalGLSLState( engine->getGLSLState() );
	glslStateFinal = engine->getGlobalGLSLState();

	if ( !lightModel )	vgLogDebug("You must have a LightModel node in the scene graph.");
	if ( !camera )		vgLogDebug("You must have a Camera node in the scene graph.");
	if ( !lightModel || !camera )	return;

	// STEREO
	isStereoEnabled = camera->getMode() != vgd::node::Camera::MONOSCOPIC;

	// POST-PROCESSING
	// POST-PROCESSING.outputbuffers
	// Checks outputBufferProperties
	hasOutputBufferProperties = glslStateFinal->outputBufferProperties.isNotEmpty();
	m_lastCurrentScaleForVertex = 1.f;

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

	//
	BOOST_FOREACH( SubTechniqueShp subtechnique, m_subtechniques )
	{
		subtechnique->stageCollectInformationsEnd( engine );
	}

	endPass();

	// Restores texture mapping and lighting state
	engine->setTextureMappingEnabled( isTextureMappingEnabledBak );
}



/**
 * Computes shadow map(s), i.e. renders scene depth and alpha from light POV
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
		engine->disregardIfIsA< vgd::node::Fluid >();
		engine->disregardIfIsA< vgd::node::MultipleInstances >();

		// Writes only to depth buffer
//		engine->setBufferUsagePolicy( vge::engine::BUP_ONLY_DEPTH );
		engine->setBufferUsagePolicy( vge::engine::BUP_COLOR_AND_DEPTH );

		// CullFace is used internally. So disables it.
		engine->disregardIfIsA< vgd::node::CullFace >();

		// For each light, updates shadow map
		lightLookAt.resize( m_shadowMappingInput->getNumLight() );

		// Backups current output buffers
		vgd::Shp< glo::FrameBufferObject > outputBuffersBak = engine->getOutputBuffers();

		for(	uint currentLightIndex = 0;
				currentLightIndex < m_shadowMappingInput->getNumLight();
				++currentLightIndex )
		{

//			setPassDescription("Depth from light POV");
			setPassDescription("Depth/alpha from light POV");
			beginPass( static_cast< PassIsolationMask >(RESET_MATRICES | PUSH_POP_STATE) );

// @todo disabled
			// Configures cull face
//			glEnable( GL_CULL_FACE );
//			glCullFace( GL_FRONT );

			// Configures polygon offset
			const vgm::Vec2f shadowPolygonOffset = lightModel->getShadowPolygonOffset();
			glPolygonOffset( shadowPolygonOffset[0], shadowPolygonOffset[1] );
			glEnable( GL_POLYGON_OFFSET_FILL );

			vgd::Shp< vgeGL::rc::FrameBufferObject > fbo = configureShadowMap( engine, currentLightIndex );
			if ( !fbo )	continue;
			engine->setOutputBuffers( fbo );
			engine->setCurrentPrivateOutputBuffers( 0 );

			// RENDER FROM LIGHT
			using vgeGL::engine::LightState;
			const vgd::Shp< LightState > lightState = m_shadowMappingInput->getLight( currentLightIndex ).m_lightState;

			vgd::Shp< vgd::node::Camera > fromLightCamera = setupRenderFromCamera(
				lightState->getPosition(), lightState->getDirection(), lightState->getModelViewMatrix(),
				"cameraFromLight", m_shadowMappingInput->getLightProjectionMatrix(currentLightIndex), m_shadowMappingInput->getShadowMapSize(),
				invViewMatrix, invTransformDraggerMatrix,
				lightLookAt[currentLightIndex] );

			// shadows only for opaque objects
			// passOpaqueWithGivenCamera( engine, traverseElements, fromLightCamera );

			// shadows for all objects
			passPaintWithGivenCamera( engine, traverseElements, fromLightCamera );

			// Re-enable rendering to the window
//			fbo->unbind();

			endPass();
		}

		// Restores output buffers
		engine->setOutputBuffers( outputBuffersBak );

		// Restores engine state
		unconfigureGeometryOnly( engine, geometryOnlyState );
	}
}



// node, rc and fbo for shadow map
// @todo clean api
// @todo optme
vgd::Shp< vgeGL::rc::FrameBufferObject > ForwardRendering::configureShadowMap( vgeGL::engine::Engine * engine, const uint currentLightIndex )
{
	// Texture2D(node and rc) for shadow map and alpha map

	using vgd::basic::IImage;
	using vgd::basic::ImageInfo;

	// DEPTH MAP
	// Updates Texture2D node
	vgd::Shp< vgd::node::Texture2D > depthMap = m_shadowMappingInput->getLightDepthMap( currentLightIndex );

	// depthMap.image
	IImage::Type								imageType;
	vgd::node::Texture::InternalFormatValueType internalFormat;
	boost::tie( imageType, internalFormat ) = convertShadowMapType2IImageType( shadowMapType );
	vgd::Shp< ImageInfo > depthImage(
		new ImageInfo(	m_shadowMappingInput->getShadowMapSize()[0], m_shadowMappingInput->getShadowMapSize()[1], 1,
						IImage::LUMINANCE, imageType ) );
	depthMap->setImage( depthImage ); // @todo OPTME only if modified

	// depthMap.internalFormat
	if ( depthMap->getInternalFormat() !=  internalFormat )	depthMap->setInternalFormat( internalFormat );

	// depthMap.multiAttributeIndex
	const uint currentTexUnit = engine->getGLSLState().getPrivateTexUnitIndex(currentLightIndex);
	if ( depthMap->getMultiAttributeIndex() != currentTexUnit )	depthMap->setMultiAttributeIndex( currentTexUnit );

	// ALPHA MAP
	// Updates Texture2D node
	vgd::Shp< vgd::node::Texture2D > alphaMap = m_shadowMappingInput->getLightAlphaMap( currentLightIndex );

	// alphaMap.image
	vgd::Shp< ImageInfo > alphaImage(
		new ImageInfo(	m_shadowMappingInput->getShadowMapSize()[0], m_shadowMappingInput->getShadowMapSize()[1], 1, // @todo reduce size of texture
						IImage::RGBA, IImage::UINT8 ) );
	alphaMap->setImage( alphaImage ); // @todo OPTME only if modified

	// alphaMap.multiAttributeIndex
	//const uint currentTexUnit2 = engine->getGLSLState().getPrivateTexUnitIndex(currentLightIndex+1); // @todo currentLightIndex+1 not cute => improves getPrivateTexUnitIndex() => getPrivateTexUnitIndex( std::string uniqueName )
//	if ( alphaMap->getMultiAttributeIndex() != currentTexUnit2 )	alphaMap->setMultiAttributeIndex( currentTexUnit2 );


	// paint
	const bool textureMappingEnabledBak = engine->setTextureMappingEnabled(true);
	engine->regardIfIsA<vgd::node::Texture2D>();

	engine->paint( alphaMap );
	engine->paint( depthMap );


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
		vgd::Shp< vgeGL::rc::Texture2D > lightAlphaMap = m_shadowMappingInput->getLightAlphaMap( currentLightIndex, engine );
		fbo->attachColor( lightAlphaMap );
		fbo->attachDepth( lightDepthMap );

		//fbo->renderDepthOnly();
		fbo->setDrawBuffersToAll();

		// Check framebuffer completeness at the end of initialization.
		const std::string fboStatus = fbo->getStatusString();
		if ( fboStatus.size() > 0 )
		{
			vgLogError( "ForwardRendering::apply(): %s", fboStatus.c_str() );
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

	// @todo OPTME discard more (i.e. computation done in vertex/fragment program except gl_Position = gl_ModelViewProjectionMatrix * mgl_Vertex;)
	engine->getGLSLState().setShaderStage( vgeGL::engine::GLSLState::FRAGMENT_OUTPUT, "" );

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
			const uint privateTexUnit0 = engine->getGLSLState().getPrivateTexUnitIndex( currentLightIndex );
			const uint privateTexUnit1 = engine->getGLSLState().getPrivateTexUnitIndex( currentLightIndex + 1);

	// @todo Improves vgd::node::Texture to be able to use it directly

			// *** Updates Texture ***
			// DEPTH MAP
			vgd::Shp< vgd::node::Texture2D > depthMap = m_shadowMappingInput->getLightDepthMap( currentLightIndex );
			if ( depthMap->getMultiAttributeIndex() != privateTexUnit0 )	depthMap->setMultiAttributeIndex( privateTexUnit0 );
			engine->paint( depthMap );
	// @todo setFunction()

			// ALPHA MAP
			vgd::Shp< vgd::node::Texture2D > alphaMap = m_shadowMappingInput->getLightAlphaMap( currentLightIndex );
			if ( alphaMap->getMultiAttributeIndex() != privateTexUnit1 )	alphaMap->setMultiAttributeIndex( privateTexUnit1 );
			engine->paint( alphaMap );

			// *** Updates TexGen ***
// @todo two texGen
			vgd::Shp< vgd::node::TexGenEyeLinear > texGen = m_shadowMappingInput->getTexGen( currentLightIndex );
			if ( texGen->getMultiAttributeIndex() != privateTexUnit0 )		texGen->setMultiAttributeIndex( privateTexUnit0 );
			engine->paint( texGen );

			if ( texGen->getMultiAttributeIndex() != privateTexUnit1 )		texGen->setMultiAttributeIndex( privateTexUnit1 );
			engine->paint( texGen );

			// *** Updates Texture Matrix ***
// @todo use TextureMatrix node

			// computes texture matrix
			vgm::MatrixR textureMatrix;
			textureMatrix.setTranslate( vgm::Vec3f(0.5f, 0.5f, 0.5f) );	// offset
			textureMatrix.scale( vgm::Vec3f(0.5f, 0.5f, 0.5f) );		// bias
				// LIGHT FRUSTUM (Projection)
			const vgm::MatrixR& lightProjectionMatrix = m_shadowMappingInput->getLightProjectionMatrix( currentLightIndex );

			textureMatrix = invViewMatrix * (lightLookAt[currentLightIndex]) * lightProjectionMatrix * textureMatrix;

			// tex gen for depth map
			engine->activeTexture(privateTexUnit0);
			glMatrixMode( GL_TEXTURE );
			glLoadMatrixf( reinterpret_cast<const float*>( textureMatrix.getValue() ) );

			engine->getTextureMatrix().setTop( textureMatrix, privateTexUnit0 );

			// tex gen for alpha map
			engine->activeTexture(privateTexUnit1);
			glMatrixMode( GL_TEXTURE );
			glLoadMatrixf( reinterpret_cast<const float*>( textureMatrix.getValue() ) );

			engine->getTextureMatrix().setTop( textureMatrix, privateTexUnit1 );
		}

		// Disables CullFace
		engine->disregardIfIsA< vgd::node::CullFace >();
	}
	//else nothing to do
}



// FLUID
// @todo creates fbo and texture2d using glo
// or
// @todo (framebuffer, fbo, textures) createsFBO(std::list< OutputBufferProperty >, [std::back_inserter<> textures]).
vgd::Shp< vgeGL::rc::Fluid > ForwardRendering::getFluidRC( vgeGL::engine::Engine * engine )
{
	vgeGL::engine::Engine::GLManagerType& rcManager = engine->getGLManager();

	vgd::Shp< vgeGL::rc::Fluid > fluidRC = rcManager.getShp< vgeGL::rc::Fluid >( fluid );

	return fluidRC;
}


void ForwardRendering::stageInitializeFluidPostProcessing( vgd::node::Fluid * fluid, vgd::Shp< vgeGL::rc::Fluid > fluidRC )
{
	//if ( fluidRC->postProcessing.isEmpty() )
	{
		// Creates nodes
		using vgd::node::Group;
		using vgd::node::PostProcessing;
		using vgeGL::engine::GLSLState;

		vgd::Shp< Group > group = Group::create("fluid.postProcessing");
		fluidRC->postProcessingGroup = group;

		vgd::Shp< PostProcessing > p;

		////////////////////////////
		// SIMULATION COMPUTATION //
		////////////////////////////

		// PASS0 : compute output flow texture(2) from (0) & (1) & (6)
		p = PostProcessing::create("fluid.pass0");
		p->setInput0( PostProcessing::OUTPUT_BUFFER0 );
		p->setInput1( PostProcessing::OUTPUT_BUFFER1 );
		p->setInput2( PostProcessing::OUTPUT_BUFFER6 );
		p->setOutput( PostProcessing::OUTPUT_OUTPUT_BUFFER2 );
		p->setFilter( PostProcessing::CUSTOM_FILTER );
		p->setCustomFilterDefinition( fluid->getSimulationPass0() );
		p->setCustomFilterApply(
		"	color = apply( texMap2D[0], texMap2D[1], texMap2D[2], mgl_TexCoord[0].xy, param4f0, param1f0 );\n"
		);

		group->addChild( p );
		fluidRC->postProcessing.setState( 0, vgd::makeShp( new GLSLState::PostProcessingState(p.get()) ) );

		// PASS0bis : (6) = (2)
		p = PostProcessing::create("fluid.pass0bis", 1);
		p->setInput0( PostProcessing::OUTPUT_BUFFER2 );
		p->setOutput( PostProcessing::OUTPUT_OUTPUT_BUFFER6 );
		p->setFilter( PostProcessing::IDENTITY );

		group->addChild( p );
		fluidRC->postProcessing.setState( 1, vgd::makeShp( new GLSLState::PostProcessingState(p.get()) ) );

		// PASS1 : compute new fluid height texture(3) from (0) & (1) & (2)
		p = PostProcessing::create("fluid.pass1", 2);
		p->setInput0( PostProcessing::OUTPUT_BUFFER0 );
		p->setInput1( PostProcessing::OUTPUT_BUFFER1 );
		p->setInput2( PostProcessing::OUTPUT_BUFFER2 );
		p->setOutput( PostProcessing::OUTPUT_OUTPUT_BUFFER3 );
		p->setFilter( PostProcessing::CUSTOM_FILTER );
		p->setCustomFilterDefinition( fluid->getSimulationPass1() );
		p->setCustomFilterApply(
		"	color = apply(	texMap2D[0], texMap2D[1], texMap2D[2], mgl_TexCoord[0].xy,\n"
		"					param4x4f0, param4f0 );\n"
		);

		group->addChild( p );
		fluidRC->postProcessing.setState( 2, vgd::makeShp( new GLSLState::PostProcessingState(p.get()) ) );

		// PASS2: (1) = (3)
		p = PostProcessing::create("fluid.pass2", 3);
		p->setInput0( PostProcessing::OUTPUT_BUFFER3 );
		p->setOutput( PostProcessing::OUTPUT_OUTPUT_BUFFER1 );
		p->setFilter( PostProcessing::IDENTITY );

		group->addChild( p );
		fluidRC->postProcessing.setState( 3, vgd::makeShp( new GLSLState::PostProcessingState(p.get()) ) );


		///////////////////////////
		// RENDERING COMPUTATION //
		///////////////////////////

		// Computes fluid position map
		p = PostProcessing::create("fluid.finalPositionMap", 4);
		p->setInput0( PostProcessing::OUTPUT_BUFFER0 );
		p->setInput1( PostProcessing::INPUT1_OUTPUT_BUFFER1 );
		p->setOutput( PostProcessing::OUTPUT_OUTPUT_BUFFER4 );
		p->setFilter( PostProcessing::CUSTOM_FILTER );
		p->setCustomFilterDefinition(
			"vec4 apply( sampler2D scenePositionMap, sampler2D fluidHM, vec2 texCoord, float thickness )\n"
			"{\n"
			"	vec2 left	= vec2(-1.0, 0.0);\n"
			"	vec2 right	= vec2(1.0, 0.0);\n"
			"	vec2 top	= vec2(0.0, 1.0);\n"
			"	vec2 bottom	= vec2(0.0, -1.0);\n"
			"\n"
			"	vec4 gravity = vec4( 0, 0, -1, 0 );\n"	// @todo uniform from fluid
			"\n"
			"	vec4 sceneVertex = texture( scenePositionMap, texCoord );\n"
//			"	if ( (sceneVertex.x == 0) && (sceneVertex.y == 0) && (sceneVertex.z == 0) )\n"
			"	if ( sceneVertex.z == 0.0 )\n"
			"	{\n"
			"		return vec4(0.0);\n"
			"	}\n"
			"	else\n"
			"	{\n"
			"		float fluidHeightC = texture( fluidHM, texCoord ).x;\n"
			"		if ( fluidHeightC == 0.0 )\n"
			"		{\n"
			"			vec2	fluidHMSize		= textureSize( fluidHM, 0 );\n"
			"			float	fluidHeightL	= texture( fluidHM, texCoord + left/fluidHMSize ).x;\n"
			"			float	fluidHeightR	= texture( fluidHM, texCoord + right/fluidHMSize ).x;\n"
			"			float	fluidHeightT	= texture( fluidHM, texCoord + top/fluidHMSize ).x;\n"
			"			float	fluidHeightB	= texture( fluidHM, texCoord + bottom/fluidHMSize ).x;\n"
			"			float	fluidHeightSum	= fluidHeightL + fluidHeightR + fluidHeightT + fluidHeightB;\n"
			"			if ( fluidHeightSum == 0.0 )	return vec4(0.0);\n"

			"			// fluidHeightSum != 0\n"
			"			vec2 scenePositionMapSize = textureSize( scenePositionMap, 0 );\n"
//			"			float scenePositionC	= texture( scenePositionMap, texCoord ).z;\n"
			"			float scenePositionL	= texture( scenePositionMap, texCoord + left/scenePositionMapSize ).z;\n"
			"			float scenePositionR	= texture( scenePositionMap, texCoord + right/scenePositionMapSize ).z;\n"
			"			float scenePositionT	= texture( scenePositionMap, texCoord + top/scenePositionMapSize ).z;\n"
			"			float scenePositionB	= texture( scenePositionMap, texCoord + bottom/scenePositionMapSize ).z;\n"
			"\n"
			"			float newHeight = sceneVertex.z + fluidHeightC * thickness;\n"
			"			newHeight = min( newHeight, scenePositionL + fluidHeightL * thickness );\n"
			"			newHeight = min( newHeight, scenePositionR + fluidHeightR * thickness );\n"
			"			newHeight = min( newHeight, scenePositionT + fluidHeightT * thickness );\n"
			"			newHeight = min( newHeight, scenePositionB + fluidHeightB * thickness );\n"
			"\n"
			"			return vec4( sceneVertex.xy, newHeight, 0 );\n"
//			"			return sceneVertex + gravity * 100.0;\n" // @todo 100 must be infinity
//			"			return sceneVertex + gravity * 2.0;\n" // @todo 100 must be infinity
//			"			return sceneVertex;\n"
			"		}\n"
			"		else\n"
			"		{\n"
			"			return vec4(sceneVertex.xy, sceneVertex.z + fluidHeightC * thickness, 0 );\n"
			"		}\n"
			"	}\n"
			"}\n"
			"\n\n\n" );
		p->setCustomFilterApply(
		"	color = apply( texMap2D[0], texMap2D[1], mgl_TexCoord[0].xy, param1f0 );\n"
		);

		group->addChild( p );
		fluidRC->postProcessing.setState( 4, vgd::makeShp( new GLSLState::PostProcessingState(p.get()) ) );

		// Computes fluid normal map
		p = PostProcessing::create("fluid.finalNormalMap", 5);
		p->setInput0( PostProcessing::OUTPUT_BUFFER4 );
		p->setOutput( PostProcessing::OUTPUT_OUTPUT_BUFFER5 );
		p->setFilter( PostProcessing::CUSTOM_FILTER );
		p->setCustomFilterDefinition(
			"vec4 apply( sampler2D fluidPositionMap, vec2 texCoord )"
			"{\n"
			"	vec2 left	= vec2(-1, 0);\n"
			"	vec2 right	= vec2(1, 0);\n"
			"	vec2 top	= vec2(0, 1);\n"
			"	vec2 bottom	= vec2(0, -1);\n"
			"\n"
			"	vec2 texSize = textureSize( fluidPositionMap, 0 );\n"
			"\n"
			"	vec3 heightC = texture( fluidPositionMap, texCoord ).xyz;\n"
			"	vec3 heightL = texture( fluidPositionMap, texCoord + left/texSize ).xyz;\n"
			"	if ( heightL.z == 0 )	heightL = heightC;\n"
			"	vec3 heightR = texture( fluidPositionMap, texCoord + right/texSize ).xyz;\n"
			"	if ( heightR.z == 0 )	heightR = heightC;\n"
			"	vec3 heightT = texture( fluidPositionMap, texCoord + top/texSize ).xyz;\n"
			"	if ( heightT.z == 0 )	heightT = heightC;\n"
			"	vec3 heightB = texture( fluidPositionMap, texCoord + bottom/texSize ).xyz;\n"
			"	if ( heightB.z == 0 )	heightB = heightC;\n"
			"\n"
			"	vec4 normal = vec4( heightL.z -heightR.z, heightB.z - heightT.z, 2.0, 0.0 );\n"
			"	normal = normalize( normal );\n"
			"\n"
			"	return normal;\n"
			"}\n"
			"\n\n\n" );
		p->setCustomFilterApply(
		"	color = apply( texMap2D[0], mgl_TexCoord[0].xy );\n"
		);

		group->addChild( p );
		fluidRC->postProcessing.setState( 5, vgd::makeShp( new GLSLState::PostProcessingState(p.get()) ) );
	}
	// else nothing to do
}


void ForwardRendering::stageInitializeFluidRC( vgeGL::engine::Engine * engine, vgd::node::Fluid * fluid, vgd::Shp< vgeGL::rc::Fluid > fluidRC )
{
	using vgd::node::OutputBufferProperty;
	using vgeGL::engine::GLSLState;
	typedef GLSLState::OutputBufferPropertyStateContainer OutputBufferPropertyStateContainer;

	const vgm::Vec2f heightMapSize(
		static_cast< float >(fluid->getHeightMapSize()[0]),
		static_cast< float >(fluid->getHeightMapSize()[1])	);

	// *** Initializes FBO and creates texture ***
	vgd::Shp< OutputBufferPropertyStateContainer >	myOutputBufferProperties( new OutputBufferPropertyStateContainer() );
	fluidRC->outputBufferProperties = myOutputBufferProperties;

	// OUTPUT BUFFER 0 : scene position map
	vgd::Shp< OutputBufferProperty > obufProperty0 = OutputBufferProperty::create("scene.heightmap");

	obufProperty0->setFormat( OutputBufferProperty::RGB );
	obufProperty0->setType( OutputBufferProperty::FLOAT16 );

	// for debugging
	//obufProperty0->setFormat( OutputBufferProperty::RGBA );
	//obufProperty0->setType( OutputBufferProperty::INTEGER );

	obufProperty0->setSizeSemantic( OutputBufferProperty::PIXEL_SIZE );
	obufProperty0->setSize( positionMapScaleFactor * heightMapSize );

	myOutputBufferProperties->setState(0, vgd::makeShp( new GLSLState::OutputBufferPropertyState(obufProperty0.get()) ) );

	// OUTPUT BUFFER 1 : fluid height map
	vgd::Shp< OutputBufferProperty > obufProperty1 = OutputBufferProperty::create("fluid.heightmap", 1);

	obufProperty1->setFormat( OutputBufferProperty::LUMINANCE );
//	obufProperty1->setType( OutputBufferProperty::INTEGER );
	obufProperty1->setType( OutputBufferProperty::FLOAT16 );

	obufProperty1->setSizeSemantic( OutputBufferProperty::PIXEL_SIZE );
	obufProperty1->setSize( heightMapSize );

	myOutputBufferProperties->setState(1, vgd::makeShp( new GLSLState::OutputBufferPropertyState(obufProperty1.get()) ) );

	// OUTPUT BUFFER 2 : output flow texture
	vgd::Shp< OutputBufferProperty > obufProperty2 = OutputBufferProperty::create("fluid.outputFlowTexture", 2);

	obufProperty2->setFormat( OutputBufferProperty::RGBA );
	obufProperty2->setType( OutputBufferProperty::INTEGER );
//	obufProperty2->setType( OutputBufferProperty::FLOAT16 );

	obufProperty2->setSizeSemantic( OutputBufferProperty::PIXEL_SIZE );
	obufProperty2->setSize( heightMapSize );

	myOutputBufferProperties->setState(2, vgd::makeShp( new GLSLState::OutputBufferPropertyState(obufProperty2.get()) ) );

	// OUTPUT BUFFER 3 : new fluid height map
	vgd::Shp< OutputBufferProperty > obufProperty3 = OutputBufferProperty::create("fluid.newHeightmap", 3);

	obufProperty3->setFormat( OutputBufferProperty::LUMINANCE );
//	obufProperty3->setType( OutputBufferProperty::INTEGER );
	obufProperty3->setType( OutputBufferProperty::FLOAT16 );

	obufProperty3->setSizeSemantic( OutputBufferProperty::PIXEL_SIZE );
	obufProperty3->setSize( heightMapSize );

	myOutputBufferProperties->setState(3, vgd::makeShp( new GLSLState::OutputBufferPropertyState(obufProperty3.get()) ) );

	// OUTPUT BUFFER 4 : fluid position map (scene position map + fluid HM)
	vgd::Shp< OutputBufferProperty > obufProperty4 = OutputBufferProperty::create("displacementMap", 4);

	obufProperty4->setFormat( OutputBufferProperty::RGB );
	obufProperty4->setType( OutputBufferProperty::FLOAT16 );

	obufProperty4->setSizeSemantic( OutputBufferProperty::PIXEL_SIZE );
	obufProperty4->setSize( positionMapScaleFactor * heightMapSize );


	myOutputBufferProperties->setState(4, vgd::makeShp( new GLSLState::OutputBufferPropertyState(obufProperty4.get()) ) );

	// OUTPUT BUFFER 5 : fluid normal map
	vgd::Shp< OutputBufferProperty > obufProperty5 = OutputBufferProperty::create("normalMap", 5);

	obufProperty5->setFormat( OutputBufferProperty::RGB );
	//obufProperty5->setFormat( OutputBufferProperty::RGBA );
//	obufProperty5->setType( OutputBufferProperty::INTEGER );
	obufProperty5->setType( OutputBufferProperty::FLOAT16 );

	/*obufProperty5->setFormat( OutputBufferProperty::RGBA );
	obufProperty5->setType( OutputBufferProperty::FLOAT16 );*/

	obufProperty5->setSizeSemantic( OutputBufferProperty::PIXEL_SIZE );
	obufProperty5->setSize( heightMapSize );

	myOutputBufferProperties->setState(5, vgd::makeShp( new GLSLState::OutputBufferPropertyState(obufProperty5.get()) ) );

	// OUTPUT BUFFER 6 : previous output flow texture
	vgd::Shp< OutputBufferProperty > obufProperty6 = OutputBufferProperty::create("fluid.previousOutputFlowTexture", 6);

	obufProperty6->setFormat( OutputBufferProperty::RGBA );
	obufProperty6->setType( OutputBufferProperty::INTEGER );
	//obufProperty6->setType( OutputBufferProperty::FLOAT16 );

	obufProperty6->setSizeSemantic( OutputBufferProperty::PIXEL_SIZE );
	obufProperty6->setSize( heightMapSize );

	myOutputBufferProperties->setState(6, vgd::makeShp( new GLSLState::OutputBufferPropertyState(obufProperty6.get()) ) );

	// Clears previous heightmaps
	fluidRC->heightMaps.clear();

	// Creates new fbo and textures
	namespace vgeGLPainter = vgeGL::handler::painter;
	boost::tie( fluidRC->frameBuffer, fluidRC->fbo ) = vgeGLPainter::OutputBufferProperty::createsFBO( engine, myOutputBufferProperties.get(), std::back_inserter(fluidRC->heightMaps), true );

	//
	fluidRC->postProcessingFBO.reset( new vgeGL::rc::FrameBufferObject() );
	fluidRC->postProcessingFBO->generate();
	fluidRC->postProcessingFBO->bind();
	fluidRC->postProcessingFBO->attachColor( fluidRC->fbo->getColor(0), 0 );
	fluidRC->postProcessingFBO->attachColor( fluidRC->fbo->getColor(1), 1 );
	fluidRC->postProcessingFBO->attachColor( fluidRC->fbo->getColor(2), 2 );
	fluidRC->postProcessingFBO->attachColor( fluidRC->fbo->getColor(3), 3 );
	fluidRC->postProcessingFBO->attachColor( fluidRC->fbo->getColor(4), 4 );
	fluidRC->postProcessingFBO->attachColor( fluidRC->fbo->getColor(5), 5 );
	fluidRC->postProcessingFBO->attachColor( fluidRC->fbo->getColor(6), 6 );
	fluidRC->postProcessingFBO->unbind();

	//
	fluidRC->fbo->bind();
	fluidRC->fbo->setDrawBuffersToAll();
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	fluidRC->fbo->detachColor( 1 );
	fluidRC->fbo->detachColor( 2 );
	fluidRC->fbo->detachColor( 3 );
	fluidRC->fbo->detachColor( 4 );
	fluidRC->fbo->detachColor( 5 );
	fluidRC->fbo->detachColor( 6 );
	fluidRC->fbo->unbind();


// for debug
	/*using vgd::node::Texture;
	fluidRC->heightMaps[1] = vgd::node::Texture2D::create("attachment1");
	fluidRC->heightMaps[1]->setWrap( Texture::WRAP_S, Texture::CLAMP_TO_EDGE );
	fluidRC->heightMaps[1]->setWrap( Texture::WRAP_T, Texture::CLAMP_TO_EDGE );
	fluidRC->heightMaps[1]->setFilter( Texture::MIN_FILTER, Texture::NEAREST );
	fluidRC->heightMaps[1]->setFilter( Texture::MAG_FILTER, Texture::NEAREST );

	fluidRC->heightMaps[0]->setFilter( Texture::MIN_FILTER, Texture::LINEAR );
	fluidRC->heightMaps[0]->setFilter( Texture::MAG_FILTER, Texture::LINEAR );
	*/

	engine->clearTextureUnits();

	// Initializes grid and separator
	fluidRC->grid = vgd::node::Grid::create("fluid.grid");
	const int	widthSlice	= static_cast<int>( (fluid->getHeightMapSize()[0]-1) * positionMapScaleFactor );
	const int	heightSlice	= static_cast<int>( (fluid->getHeightMapSize()[1]-1) * positionMapScaleFactor );
	fluidRC->grid->initializeGeometry( 1.f, 1.f, widthSlice, heightSlice, false );
	fluidRC->grid->initializeTexUnits( 3, widthSlice, heightSlice, false );

	fluidRC->separator = vgd::node::Separator::create("fluid.separator");

	// Initializes post-processing
	stageInitializeFluidPostProcessing( fluid, fluidRC );
}


void ForwardRendering::stageUpdateFluidEmittersAndDrainers( vgeGL::engine::Engine * engine, vgd::node::Fluid * fluid, vgd::Shp< vgeGL::rc::Fluid > fluidRC )
{
	// Retrieves emittersOrDrainers multi-field.
	using vgd::field::EditorRO;
	using vgd::node::Fluid;

	const uint maxEmittersOrDrainers =		 4;
	EditorRO< Fluid::FEmittersOrDrainersType > emittersOrDrainers = fluid->getEmittersOrDrainersRO();
	vgAssertN( emittersOrDrainers->size() <= maxEmittersOrDrainers, "Too many emitters/drainers in fluid node named %s", fluid->getName().c_str() );

	// Retrieves fluid.pass1
	using vgd::node::PostProcessing;
	vgd::Shp< PostProcessing > pass1 = fluidRC->postProcessingGroup->getChild< PostProcessing >( 2 );

	// For each emitter/drainer, update post-processing
	vgm::MatrixR	param4x4f0;
	param4x4f0.setNull();
	vgm::Vec4f		param4f0;
	param4f0.setNull();

	const int iEnd = std::min( maxEmittersOrDrainers, emittersOrDrainers->size() );
	for( int i = 0; i < iEnd; ++i )
	{
		const vgm::Vec5f properties = (*emittersOrDrainers)[i];

		param4x4f0.setRow( i, vgm::Vec4f(properties) );
		param4f0[i] = properties[4];
	}

	pass1->setParam4x4f0( param4x4f0 );
	pass1->setParam4f0( param4f0 );
}


void ForwardRendering::stageUpdateFluidSimulationParameters( vgeGL::engine::Engine * engine, vgd::node::Fluid * fluid, vgd::Shp< vgeGL::rc::Fluid > fluidRC )
{
	// Retrieves fluid.pass0
	using vgd::node::PostProcessing;
	vgd::Shp< PostProcessing > pass0 = fluidRC->postProcessingGroup->getChild< PostProcessing >( 0 );

	pass0->setParam4f0(
		vgm::Vec4f(	fluid->getCellSize(), fluid->getCss(),
					fluid->getGravity()[3], fluid->getTimeStep() ) );
	pass0->setParam1f0( fluid->getDamping() );

	// Retrieves fluid.finalPositionMap
	vgd::Shp< PostProcessing > finalPositionMap = fluidRC->postProcessingGroup->getChild< PostProcessing >( 4 );

	finalPositionMap->setParam1f0( fluid->getThickness() );
}


void ForwardRendering::stageInitializeFluid( vgeGL::engine::Engine * engine, vge::visitor::TraverseElementVector * traverseElements )
{
	if ( isFluidEnabled )
	{
		// Do nothing if 'scene' field is not initialized
		using vgd::node::Group;
		vgd::Shp< Group > scene = vgd::dynamic_pointer_cast< Group >( fluid->getScene().lock() );
		if ( !scene )
		{
			vgAssertN( scene, "'scene' field of fluid node %s is not a vgd::node::Group.", fluid->getName().c_str() );
			//engine->getGLManager().remove( fluid );
			return;
		}

		positionMapScaleFactor = 1.f;

		// INITIALIZATION

		// Tests if output buffers used by fluid must be initialized/re-initialized
		bool callInitialize = false;

		vgd::Shp< vgeGL::rc::Fluid > fluidRC = getFluidRC( engine );

		if ( !fluidRC )
		{
			// Initialization stage must be done
			callInitialize = true;

			// Creates fluid resource
			fluidRC.reset( new vgeGL::rc::Fluid );

			// Register node and its resource into manager
			vgeGL::engine::Engine::GLManagerType& rcManager = engine->getGLManager();
			rcManager.add( fluid, fluidRC );
		}
		else
		{
			vgAssert( fluidRC->fbo );

			// Tests if the current output buffers size is the same as size specified by heightMapSize field.
			vgd::Shp< glo::Texture2D > texture2D = fluidRC->fbo->getColorAsTexture2D(0);
			if ( texture2D )
			{
				callInitialize =	( texture2D->getWidth() != fluid->getHeightMapSize()[0] * positionMapScaleFactor) ||
									( texture2D->getHeight() != fluid->getHeightMapSize()[1] * positionMapScaleFactor);
			}
			else
			{
				vgAssertN( false, "Internal error" );
			}
		}

		if ( callInitialize )
		{
			// Initializes output buffers and grid
			setPassDescription("Fluid initialization stage");

			beginPass();
			stageInitializeFluidRC( engine, fluid, fluidRC );
			endPass();
		}

		// Updates fluid emitters and drainers.
		stageUpdateFluidEmittersAndDrainers( engine, fluid, fluidRC );

		// Updates fluid simulation parameters
		stageUpdateFluidSimulationParameters( engine, fluid, fluidRC );
	}
	// else nothing to do
}


void ForwardRendering::stageFluidUpdateSceneHeightMap( vgeGL::engine::Engine * engine, vge::visitor::TraverseElementVector * traverseElements )
{
	vgd::Shp< vgeGL::rc::Fluid > fluidRC = getFluidRC( engine );
	if ( !isFluidEnabled || !fluidRC )	return;

	// RENDERING
//engine->regard();
	// Configures geometry only pass
		vgd::Shp< GeometryOnlyState > geometryOnlyState = configureGeometryOnly( engine );
		regardForGeometryOnly(engine);
// @todo fine grain control in VertexShape
		engine->disregardIfIsA< vgd::node::MultipleInstances >();

engine->disregardIfIsA< vgd::node::Fluid >();
	// Enables lighting to have ecPosition.
	// But Light nodes are disregard, so lighting computation is not performed
	engine->setLightingEnabled();
		engine->regardIfIsA<vgd::node::LightModel>();

// @todo same of shadow maps and co
		engine->disregardIfIsA< vgd::node::OutputBufferProperty >();
		engine->disregardIfIsA< vgd::node::OutputBuffers >();

	engine->setBufferUsagePolicy( vge::engine::BUP_COLOR_AND_DEPTH );

	// Backups current output buffers
	vgd::Shp< glo::FrameBufferObject > outputBuffersBak = engine->getOutputBuffers();

	setPassDescription("Update scene height map");
	beginPass( static_cast< PassIsolationMask >(RESET_MATRICES | PUSH_POP_STATE) );

	engine->setOutputBuffers( fluidRC->fbo );
	engine->setCurrentPrivateOutputBuffers( 0 );
	

	using vgeGL::engine::GLSLState;
	engine->getGLSLState().setShaderStage( GLSLState::VERTEX_ECPOSITION_COMPUTATION,
		"	ecPosition	= position;\n" );
	engine->getGLSLState().setShaderStage( GLSLState::FRAGMENT_OUTPUT,
			"\n"
			"	gl_FragData[0] = ecPosition;\n"
			//"	outputBuffer0 = ecPosition;\n"
//			"	gl_FragData[0] = gl_ModelViewMatrixInverse * ecPosition;\n" // @todo OPTME
//			"	gl_FragData[0] = color;\n" // for debugging
 		);

	// Computes bounding box of 'scene'
	using vgd::node::Group;
	vgd::Shp< Group > scene = vgd::dynamic_pointer_cast< Group >( fluid->getScene().lock() );
	vgAssertN( scene, "'scene' field of fluid node %s is not a vgd::node::Group.", fluid->getName().c_str() );

	vge::visitor::NodeCollectorExtended<> collector;
	scene->traverse( collector );

	const bool isTraceEnabledBak = engine->isTraceEnabled();
	engine->setTrace(false);

	engine->getGeometricalMatrix().pushAll();
	engine->getProjectionMatrix().pushAll();
	//engine->getTextureMatrix().pushAll();

	vge::technique::ComputeBoundingBox computeBB;
	computeBB.setParameters( engine, collector.getTraverseElements() );
	computeBB.apply( engine, collector.getTraverseElements() );

	//engine->getTextureMatrix().popAll();
	engine->getProjectionMatrix().popAll();
	engine->getGeometricalMatrix().popAll();
	 //engine->popStateStack();
	//engine->pop();

	engine->setTrace( isTraceEnabledBak );

	const vgm::Box3f sceneBB = scene->getBoundingBox();
	if ( sceneBB.isEmpty() || sceneBB.isInvalid() )
	{
		vgAssertN( false, "'scene' field of fluid node %s contains an empty scene", fluid->getName().c_str() );
		return;
	}

	// Setup camera
	const vgm::Vec3f	sceneBBSize		= sceneBB.getSize();
	const vgm::Vec3f	sceneBBCenter	= sceneBB.getCenter();
	const float			sceneBBSizeMax	= vgm::max( sceneBBSize[0], sceneBBSize[1], sceneBBSize[2] );

	vgm::MatrixR cameraProjection;
	const float projectionSize = sceneBBSizeMax * 1.05f;/* * 1.42f */
	cameraProjection.setOrtho(
			-projectionSize/2.f, projectionSize/2.f,
			-projectionSize/2.f, projectionSize/2.f,
			projectionSize/2048.f, projectionSize * 4.f );

	vgm::Vec3f			gravity		( fluid->getGravity() );
	gravity.normalize();
	const vgm::Vec3f	position	( sceneBBCenter + sceneBBSizeMax /*/2.f*1.42f*/ * gravity );

	// Updates fluid.feedbackInformations
	vgm::Vec5f feedbackInformations( position );
	feedbackInformations[3] = projectionSize;
	feedbackInformations[4] = projectionSize;
	fluid->setFeedbackInformations( feedbackInformations );
	fluid->setFeedbackInformationsBis( cameraProjection );

	vgm::MatrixR identity = vgm::MatrixR::getIdentity();
	vgd::Shp< glo::Texture2D > color0 = fluidRC->fbo->getColorAsTexture2D();
	vgm::MatrixR cameraLookAt;
	vgd::Shp< vgd::node::Camera > newCamera = setupRenderFromCamera(
		position, vgm::Vec3f(-fluid->getGravity()), identity,
		"SceneHeightMapCamera", cameraProjection, vgm::Vec2i( color0->getWidth(), color0->getHeight() ), //fluid->getHeightMapSize(),
		identity, identity,
		cameraLookAt );

	// Rendering of scene height map
	passPaint( engine, collector.getTraverseElements(), newCamera );
	endPass();

	// Restores output buffers
	engine->setOutputBuffers( outputBuffersBak );
	engine->setCurrentPrivateOutputBuffers();

	// Restores engine state
	unconfigureGeometryOnly( engine, geometryOnlyState );
}


void ForwardRendering::stageFluidSimulation( vgeGL::engine::Engine * engine )
{
	vgd::Shp< vgeGL::rc::Fluid > fluidRC = getFluidRC( engine );
	if ( !isFluidEnabled || !fluidRC )	return;

	applyPostProcessing( engine, fluidRC->heightMaps, &(fluidRC->postProcessing) );

// @todo framework to capture texture image and display in an overlay
	if ( fluid->getRequestFeedback() )
	{
		using vgd::basic::Image;
		vgd::Shp< Image > image = getImage( fluidRC->postProcessingFBO, 4 );
		/*namespace bfs = boost::filesystem;
		image->convertTo( Image::RGB, Image::UINT8 );
		bfs::remove( "D:\\fluid.png" );
		image->save("D:\\fluid.png");*/

		fluid->setFluidPositionFeedback( image );
		fluid->setRequestFeedback( false );
	}
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
// STAGE 1
	engine->setTrace();
	prepareEval( engine, traverseElements );

	passInformationsCollector( engine, traverseElements);
	engine->setTrace( false );

// STAGE 2
	// RC
	BOOST_FOREACH( SubTechniqueShp subtechnique, m_subtechniques )
	{
		subtechnique->stageInitializeRC( this, engine );
	}

	// STEREO
	engine->setEyeUsagePolicy( vgd::node::Camera::DEFAULT_EYEUSAGEPOLICY );
	if ( isStereoEnabled )
	{
		const bool shadowBAK = engine->setShadowEnabled(false);

		engine->setEyeUsagePolicy( vgd::node::Camera::EYE_LEFT );

			beginPass();

			engine->setBufferUsagePolicy( vge::engine::BUP_COLOR_AND_DEPTH );

			// First pass : OPAQUE PASS (draw opaque shape)
			const bool mustDoTransparencyPass = evaluateOpaquePass( paintService(), PassIsolationMask(0), true );
			endPass();

		engine->setEyeUsagePolicy( vgd::node::Camera::EYE_RIGHT );
			beginPass();

			engine->setBufferUsagePolicy( vge::engine::BUP_COLOR_AND_DEPTH );

			// First pass : OPAQUE PASS (draw opaque shape)
			/*const bool mustDoTransparencyPass = */evaluateOpaquePass( paintService(), PassIsolationMask(0), true );

			if ( camera->getRightEye() == false )
			{
				glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
			}

			endPass();

		// OVERLAYS
		stageOverlays( engine );

		// Restores
		engine->setShadowEnabled(shadowBAK);

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

// STAGE 3
	// SHADOW MAP(S)
	passUpdateShadowMaps( engine, traverseElements );

	// FLUID
	stageInitializeFluid( engine, traverseElements );
	stageFluidUpdateSceneHeightMap( engine, traverseElements );
	stageFluidSimulation( engine );

	// DepthOfField and Noise stagePrePaint() must be done before stageInitializeOutputBuffers()
	BOOST_FOREACH( SubTechniqueShp subtechnique, m_subtechniques )
	{
		subtechnique->stagePrePaint( this, engine );
	}

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



	std::string description = "Main rendering pass";

	if ( isShadowEnabled )	description += " with shadow";
	if ( isPostProcessingEnabled )	description += " and post-processing";
	BOOST_FOREACH( SubTechniqueShp subtechnique, m_subtechniques )
	{
		if ( subtechnique->isEnabled() )
		{
			description += ", ";
			description += typeid(*subtechnique).name();
		}
	}
	setPassDescription( description );

	beginPass();

	// DEPTH PRE-PASS
	engine->setBufferUsagePolicy( engine->isDepthPrePassEnabled() ? vge::engine::BUP_ONLY_COLOR : vge::engine::BUP_COLOR_AND_DEPTH );

	// SHADOW
	stageConfigureShadowMapping( engine );

	// POST-PROCESSSING
	stageConfigurePostProcessing( engine );

	BOOST_FOREACH( SubTechniqueShp subtechnique, m_subtechniques )
	{
		subtechnique->stageBeginPaint( this, engine );
	}

		// First pass : OPAQUE PASS (draw opaque shape)
		const bool mustDoTransparencyPass = evaluateOpaquePass( paintService(), PassIsolationMask(0), true );
		BOOST_FOREACH( SubTechniqueShp subtechnique, m_subtechniques )
		{
			subtechnique->stagePaint( this, engine );
		}

	BOOST_FOREACH( SubTechniqueShp subtechnique, m_subtechniques )
	{
		subtechnique->stageEndPaint( this, engine );
	}

	endPass();


// @todo ignore transparency pass
	if ( mustDoTransparencyPass )
	{
	description += " (transparency pass)";
	setPassDescription( description);
	beginPass();

// DEPTH PRE-PASS
engine->setBufferUsagePolicy( vge::engine::BUP_ONLY_COLOR_NO_CLEAR );

// OUTPUT BUFFERS init
stageInitializeOutputBuffers( engine );

	// SHADOW
	stageConfigureShadowMapping( engine );

	// POST-PROCESSSING
	//stageConfigurePostProcessing( engine );

		// Second pass : TRANSPARENT PASS (draw transparent shape)

	BOOST_FOREACH( SubTechniqueShp subtechnique, m_subtechniques )
	{
		subtechnique->stageBeginPaint( this, engine );
	}

		//m_fbo->setDrawBuffers( 0 );
		evaluateTransparentPass( paintService(), PassIsolationMask(0)/*PassIsolationMask(DEFAULT_PASS_ISOLATION_MASK)*/, true );
		BOOST_FOREACH( SubTechniqueShp subtechnique, m_subtechniques )
		{
			subtechnique->stagePaint( this, engine );
		}

		BOOST_FOREACH( SubTechniqueShp subtechnique, m_subtechniques )
		{
			subtechnique->stageEndPaint( this, engine );
		}

		endPass();

		engine->setBufferUsagePolicy( vge::engine::BUP_NOT_DEFINED );
	}


	BOOST_FOREACH( SubTechniqueShp subtechnique, m_subtechniques )
	{
		subtechnique->stagePostPaint( this, engine );
	}

	// POST-PROCESSING
// @todo enable it
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
		if (	!pppRC.frameBuffer0 || !pppRC.frameBuffer1 ||	// no fbo for ping-pong rendering
				drawingSurfaceSizeChanged			)			// size changed @todo this is only valid if hasOutputBufferProperties==true => do like drawingSurfaceSizeChanged computation
		{
			setPassDescription("PostProcessing initialization stage");
			beginPass();

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
				pppRC.textures0.clear();
				pppRC.textures1.clear();
				boost::tie( pppRC.frameBuffer0, pppRC.fbo0 ) = vgeGLPainter::OutputBufferProperty::createsFBO( engine, myOutputBufferProperties.get(), std::back_inserter(pppRC.textures0) );
				boost::tie( pppRC.frameBuffer1, pppRC.fbo1 ) = vgeGLPainter::OutputBufferProperty::createsFBO( engine, myOutputBufferProperties.get(), std::back_inserter(pppRC.textures1) );

			endPass();
		}
	}
}



void ForwardRendering::stageConfigurePostProcessing( vgeGL::engine::Engine * engine )
{
	if ( hasOutputBufferProperties || isPostProcessingEnabled )
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
	if ( isPostProcessingEnabled && m_postProcessing->getNum()>0 )
	{
		const vgd::Shp< vgeGL::rc::FrameBufferObject > finalBuffers = applyPostProcessing( engine, m_textures, m_postProcessing );
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
// @todo moves applyPostProcessing and blit() in PostProcessing handler.
// @todo Composite for glo::Resource/std::string
const vgd::Shp< vgeGL::rc::FrameBufferObject > ForwardRendering::applyPostProcessing(
	vgeGL::engine::Engine *								engine,

	std::vector< vgd::Shp< vgd::node::Texture2D > >&	outputBuffers,
	PostProcessingStateContainer *						postProcessingContainer )
{
	//////////////////////////
	// Constructs resources //
	//////////////////////////
	using vgd::node::PostProcessing;
	using vgd::node::Program;
	using vgd::node::Texture;
	using vgd::node::Texture2D;
	using vgeGL::engine::GLSLState;

	if ( !pppRC.outputFbo )
	{
		pppRC.outputFbo.reset( new vgeGL::rc::FrameBufferObject() );
		pppRC.outputFbo->generate();
	}

	std::vector< float >							params1f0;
	std::vector< float >							params1f1;
	std::vector< vgm::Vec4f >						params4f0;
	std::vector< vgm::Vec4f >						params4f1;
	std::vector< vgm::MatrixR >						params4x4f0;

	std::vector< vgd::Shp< Texture2D > >			textures0;

	std::vector< PostProcessing::Input0ValueType >	inputs0;
	std::vector< PostProcessing::Input1ValueType >	inputs1;
	std::vector< PostProcessing::Input2ValueType >	inputs2;

	std::vector< PostProcessing::OutputValueType >	output;

	std::vector< vgd::Shp< Program > >				programs;
	std::vector< float >							scales;


	uint		i		= 0;
	const uint	iEnd	= postProcessingContainer->getMax(); // @todo beginIndex(), endIndex(), iterators

	float currentScaleForTexCoord	= 1.f;
	float currentScaleForVertex		= 1.f;

	for( uint foundPP = 0; i != iEnd; ++i )
	{
		const vgd::Shp< GLSLState::PostProcessingState > current = postProcessingContainer->getState( i );

		if ( current )
		{
			vgd::node::PostProcessing * postProcessingNode = current->getNode();
			vgAssert( postProcessingNode != 0 );

			// Parameters

			// Builds declaration section of the shaders (depends of post-processing node param* fields)
			std::string currentDeclaration = getPostProcessingDeclarations();

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

			// param1f1
			if ( postProcessingNode->hasParam1f1() )
			{
				float value;
				postProcessingNode->getParam1f1(value);

				params1f1.push_back( value );
			}
			else
			{
				params1f1.push_back( std::numeric_limits<float>::max() );
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

			// param4x4f0
			if ( postProcessingNode->hasParam4x4f0() )
			{
				vgm::MatrixR value;
				postProcessingNode->getParam4x4f0(value);

				params4x4f0.push_back( value );
			}
			else
			{
				params4x4f0.push_back( vgm::MatrixR::getInvalid() );
			}

			// texture0
			if ( postProcessingNode->hasTexture0() )
			{
				vgd::Wkp< vgd::node::Node > value;
				postProcessingNode->getTexture0( value );

				vgd::Shp< vgd::node::Node > node = value.lock();
				vgAssert( node );

				vgd::Shp< Texture2D > texture = vgd::dynamic_pointer_cast< Texture2D >( node );
				vgAssertN( texture, "Field texture0 of PostProcessing node named %s is invalid.", node->getName().c_str() );

				textures0.push_back( texture );
			}
			else
			{
				textures0.push_back( vgd::makeShp( (vgd::node::Texture2D*)0 ) );
			}

			// Inputs
			inputs0.push_back( postProcessingNode->getInput0() );
			inputs1.push_back( postProcessingNode->getInput1() );
			inputs2.push_back( postProcessingNode->getInput2() );

			// Ouput
			output.push_back( postProcessingNode->getOutput() );

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
					getPostProcessingVertexProgram(), "INLINE_FTEXGEN",	"	mgl_TexCoord[0] = gl_TextureMatrix[0] * mgl_MultiTexCoord0;\n"
																		"	mgl_TexCoord[1] = gl_TextureMatrix[1] * mgl_MultiTexCoord1;\n"
																		"	mgl_TexCoord[2] = gl_TextureMatrix[2] * mgl_MultiTexCoord2;\n" );
			}
			else if ( postProcessingNode->getInput1() != vgd::node::PostProcessing::INPUT1_NONE )
			{
				vertexShader = boost::algorithm::replace_first_copy( 
					getPostProcessingVertexProgram(), "INLINE_FTEXGEN",	"	mgl_TexCoord[0] = gl_TextureMatrix[0] * mgl_MultiTexCoord0;\n"
																		"	mgl_TexCoord[1] = gl_TextureMatrix[1] * mgl_MultiTexCoord1;\n" );
			}
			else
			{
				vertexShader = boost::algorithm::replace_first_copy( 
					getPostProcessingVertexProgram(), "INLINE_FTEXGEN",	"	mgl_TexCoord[0] = gl_TextureMatrix[0] * mgl_MultiTexCoord0;\n" );
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
				boost::algorithm::replace_first_copy( getPostProcessingFragmentProgram(), "INLINE_POST_PROCESSING", filter.second );

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
			if ( foundPP == postProcessingContainer->getNum() )
			{
				break;
			}
		}
		// else empty state, nothing to do
	}

	m_lastCurrentScaleForVertex = currentScaleForVertex;


	/////////////////////////////////////////
	// Post-processing rendering draw code //
	/////////////////////////////////////////

	const vgm::Rectangle2i	viewport				( 0, 0, engine->getDrawingSurfaceSize()[0], engine->getDrawingSurfaceSize()[1] );

	// Enables texture mapping
	const bool				isTextureMappingEnabled	( engine->setTextureMappingEnabled() );

	// Backups current output buffers
	vgd::Shp< glo::FrameBufferObject > outputBuffersBak = engine->getOutputBuffers();

	setPassDescription("Post-processing stage");
	beginPass();
	engine->begin2DRendering( &viewport, false );

	vgd::Shp< vgeGL::rc::FrameBufferObject >			lfbo0		= pppRC.fbo0;
	vgd::Shp< vgeGL::rc::FrameBufferObject >			lfbo1		= pppRC.fbo1;
	std::vector< vgd::Shp< vgd::node::Texture2D > >*	ltex0		= &pppRC.textures0;
	std::vector< vgd::Shp< vgd::node::Texture2D > >*	ltex1		= &pppRC.textures1;

	currentScaleForTexCoord	= 1.f;
	currentScaleForVertex	= 1.f;

	pppRC.outputFbo->bind();

	for( uint i=0; i < programs.size(); ++i )
	{
		// sources		: ltex0
		// destination	: lfbo1
		engine->clearTextureUnits();

		vgd::Shp< Program >	program = programs[i];
		engine->paint( program );

		std::vector< vgd::Shp< vgd::node::Texture2D > > textures;
		textures.push_back( textures0[i] );

		// output
		vgd::Shp< vgd::node::Texture2D > outputTexture		= getOutputTexture( output[i], &outputBuffers, ltex1 );
		vgd::Shp< vgeGL::rc::Texture2D > outputTextureGLO	= engine->getRCShp< vgeGL::rc::Texture2D >( outputTexture );
		vgAssertN( outputTextureGLO, "Texture2D node named '%s' does not have its managed OpenGL texture", outputTexture->getName().c_str() );

// @todo FIXME workaround a bug in glFramebufferTexture2D() ? or ?
		//pppRC.outputFbo.reset( new vgeGL::rc::FrameBufferObject() );
		//pppRC.outputFbo->release();
		//pppRC.outputFbo->generate();

		pppRC.outputFbo->detachColor();
		pppRC.outputFbo->attachColor( outputTextureGLO );
		pppRC.outputFbo->setDrawBuffer();

		currentScaleForVertex *= scales[i];
		glViewport( 0, 0,
					(uint)(outputTextureGLO->getWidth() * currentScaleForVertex),
					(uint)(outputTextureGLO->getHeight() * currentScaleForVertex) );

//engine->begin2DRendering( &lviewport, false );
// @todo a light version of begin2DRendering

		// random
		engine->setUniformRandom();

		// time
		engine->setUniformTime();

		// nearFar
		engine->setUniformNearFar();

		// param1f0
		const float param1f0 = params1f0[i];
		if ( param1f0 != std::numeric_limits<float>::max() )
		{
			vgAssertN( !engine->getUniformState().isUniform( "param1f0"), "Uniform param1f0 already used" );
			engine->getUniformState().addUniform( "param1f0", param1f0 );
		}

		// param1f1
		const float param1f1 = params1f1[i];
		if ( param1f1 != std::numeric_limits<float>::max() )
		{
			vgAssertN( !engine->getUniformState().isUniform( "param1f1"), "Uniform param1f1 already used" );
			engine->getUniformState().addUniform( "param1f1", param1f1 );
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

		// param4x4f0
		const vgm::MatrixR param4x4f0 = params4x4f0[i];
		if ( param4x4f0.isValid() )
		{
			vgAssertN( !engine->getUniformState().isUniform( "param4x4f0"), "Uniform param4x4f0 already used" );
			engine->getUniformState().addUniform( "param4x4f0", param4x4f0 );
		}

		// input0
		vgd::Shp< Texture2D > inputTexture0 = getInputTexture( inputs0[i], &outputBuffers, textures0, ltex0 );
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
		vgd::Shp< Texture2D > inputTexture1 = getInputTexture( inputs1[i], &outputBuffers, textures0, ltex0 );
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
		vgd::Shp< Texture2D > inputTexture2 = getInputTexture( inputs2[i], &outputBuffers, textures0, ltex0 );
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

		/*outputFbo->detach();
		outputFbo->unbind();*/

		if ( output[i] == vgd::node::PostProcessing::OUTPUT_TMP0 )
		{
			lfbo0.swap( lfbo1 );
			std::swap( ltex0, ltex1 );
		}

		currentScaleForTexCoord *= scales[i];

		engine->getUniformState().clear();
	}

	//if ( lfbo0 )	lfbo0->unbind();

	engine->end2DRendering( false );
	endPass();

	// Restores output buffers
	engine->setOutputBuffers( outputBuffersBak );

	engine->setTextureMappingEnabled( isTextureMappingEnabled );

	return lfbo0;
}



// @todo glo api : blit( fboSrc, fboDst, COLOR:DEPTH:STENCIL ) LINEAR or NEAREST,  blit( ..., srcRect, ..., dstRext... ).
void ForwardRendering::blit( vgeGL::engine::Engine * engine, vgd::Shp< vgeGL::rc::FrameBufferObject > source )
{
	source->bind();
	source->setReadBuffer();
	glo::FrameBufferObject::setDrawToDefaultFrameBuffer();

// @todo removes warnings
	glBlitFramebuffer(	0, 0, engine->getDrawingSurfaceSize()[0], engine->getDrawingSurfaceSize()[1],
						0, 0, engine->getDrawingSurfaceSize()[0], engine->getDrawingSurfaceSize()[1],
//						0, 0, engine->getDrawingSurfaceSize()[0] * m_lastCurrentScaleForVertex, engine->getDrawingSurfaceSize()[1] * m_lastCurrentScaleForVertex,
						GL_COLOR_BUFFER_BIT, GL_NEAREST );
	glo::FrameBufferObject::setReadToDefaultFrameBuffer();
}


void ForwardRendering::blit( vgeGL::engine::Engine * engine, vgd::Shp< vgeGL::rc::FrameBufferObject > source, vgd::Shp< vgeGL::rc::FrameBufferObject > destination )
{
	source->bindToRead();
	source->setReadBuffer();

	const std::vector< int > destinationDrawBuffers = destination->getFullDrawBuffers();
	destination->bindToDraw();
	destination->setDrawBuffer();

	glBlitFramebuffer(	0, 0, engine->getDrawingSurfaceSize()[0], engine->getDrawingSurfaceSize()[1],
						0, 0, engine->getDrawingSurfaceSize()[0], engine->getDrawingSurfaceSize()[1],
//						0, 0, engine->getDrawingSurfaceSize()[0] * m_lastCurrentScaleForVertex, engine->getDrawingSurfaceSize()[1] * m_lastCurrentScaleForVertex,
						GL_COLOR_BUFFER_BIT, GL_NEAREST );

	// Restores
	glo::FrameBufferObject::setReadToDefaultFrameBuffer();

	destination->setDrawBuffers( destinationDrawBuffers );
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

