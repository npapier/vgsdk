// VGSDK - Copyright (C) 2009, 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/technique/ForwardRendering.hpp"

#include <vgd/basic/ImageInfo.hpp>
#include <vgd/node/Camera.hpp>
#include <vgd/node/CullFace.hpp>
#include <vgd/node/LightModel.hpp>
#include <vgd/node/MultiTransformation.hpp>
#include <vgd/node/SpotLight.hpp>
#include <vgd/node/Texture2D.hpp>
#include <vgd/node/TexGenEyeLinear.hpp>
#include <vgd/node/TransformDragger.hpp>
#include <vgDebug/convenience.hpp>
#include <vge/service/Painter.hpp>
#include <vgm/VectorOperations.hpp>
#include "vgeGL/engine/Engine.hpp"
#include "vgeGL/rc/Texture2D.hpp"
#include "vgeGL/rc/FrameBufferObject.hpp"



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
	vgeGL::rc::Texture2D * getLightDepthMap( const uint index, vgeGL::engine::Engine * engine );
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
				vgm::MatrixR projection;
				projection.setPerspective(	cutOffAngle * 2.f,
											static_cast<float>(m_shadowMapSize[0])/static_cast<float>(m_shadowMapSize[1]),
											1.f, 1000.f );

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

				lightDepthMap->setWrap( Texture::WRAP_S, Texture::CLAMP_TO_EDGE ); // CLAMP, GL_CLAMP_TO_EDGE
				lightDepthMap->setWrap( Texture::WRAP_T, Texture::CLAMP_TO_EDGE );

				//lightDepthMap->setMipmap( true );
				lightDepthMap->setFilter( Texture::MIN_FILTER, Texture::LINEAR );
				//lightDepthMap->setFilter( Texture::MIN_FILTER, Texture::NEAREST );
				//lightDepthMap->setFilter( Texture::MIN_FILTER, Texture::LINEAR_MIPMAP_LINEAR /*LINEAR */);
				lightDepthMap->setFilter( Texture::MAG_FILTER, Texture::LINEAR );
				//lightDepthMap->setFilter( Texture::MAG_FILTER, Texture::NEAREST );

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






ForwardRendering::ForwardRendering()
:	m_shadowMappingInput( new ShadowMappingInput() )
{}



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

	// Retrieves GLSLState from engine
	using vgeGL::engine::GLSLState;
	const GLSLState& state = engine->getGLSLState();

	//
	vgd::Shp< vge::service::Service > paintService = vge::service::Painter::create();



	prepareEval( engine, traverseElements );

	/////////////////////////////////////////////////////////
	// STEP 1 : Computes additionnal informations
	// Searches the first LightModel node (and active lights at this state) and the camera.
	/////////////////////////////////////////////////////////

	LightModel *									lightModel = 0;
	vgd::node::LightModel::ShadowValueType			shadowType;
	vgd::node::LightModel::ShadowMapTypeValueType	shadowMapType;
	vgd::Shp< ShadowMappingInput >& shadowMappingInput = m_shadowMappingInput;

// @todo Uses state.getPrivateTexture(index);
	const uint internalTexUnitIndex = engine->getMaxTexUnits()-1;

	// VIEW MATRIX and PROJECTION MATRIX
	vgd::node::Camera *				camera				= 0;
	vgd::node::TransformDragger *	transformDragger	= 0;
	vgm::MatrixR viewMatrix		= vgm::MatrixR::getIdentity();
	vgm::MatrixR invViewMatrix	= vgm::MatrixR::getIdentity();

	setPassDescription("ForwardRendering:STEP1:Collects informations");
	beginPass();

	engine->disregard();
	engine->regardIfIsAKindOf<vgd::node::SingleTransformation>();
	engine->regardIfIsAKindOf<vgd::node::Group>();
	engine->regardIfIsAKindOf<vgd::node::Kit>();
	engine->regardIfIsAKindOf<vgd::node::Light>();
//engine->regardIfIsAKindOf<vgd::node::Shape>();

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
				shadowMappingInput->reset( engine, shadowType, shadowQuality );
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

	vgm::MatrixR lightLookAt[4]; // ????



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

		for(	uint currentLightIndex = 0;
				currentLightIndex < shadowMappingInput->getNumLight();
				++currentLightIndex )
		{
			setPassDescription("ForwardRendering:STEP2:Rendering from light POV");
			beginPass();

			// not with fbo:glColorMask( GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE );

// @todo
			glEnable( GL_CULL_FACE );
			glCullFace( GL_FRONT );
			engine->disregardIfIsA< vgd::node::CullFace >();

			glPolygonOffset( 4.f, 16.f );
			glEnable( GL_POLYGON_OFFSET_FILL );

			engine->disregardIfIsAKindOf<vgd::node::Light>();

			//engine->disregardIfIsAKindOf<vgd::node::MultiTransformation>();
			//engine->disregardIfIsAKindOf<vgd::node::TexGen>();

			engine->disregardIfIsA<vgd::node::LightModel>();

//
			vgd::Shp< vgd::node::Texture2D > texture2D = shadowMappingInput->getLightDepthMap( currentLightIndex );

			using vgd::basic::IImage;
			using vgd::basic::ImageInfo;

			vgd::basic::IImage::Type imageType;
			if ( shadowMapType == vgd::node::LightModel::FLOAT )
			{
				imageType = IImage::FLOAT;
			}
			else if ( shadowMapType == vgd::node::LightModel::INT32 )
			{
				imageType = IImage::INT32;
			}
			else if ( shadowMapType == vgd::node::LightModel::INT16 )
			{
				imageType = IImage::INT16;
			}
			else
			{
				assert( false );
				imageType = IImage::INT16;
			}

			vgd::Shp< ImageInfo > depthImage(
				new ImageInfo(	shadowMappingInput->getShadowMapSize()[0], shadowMappingInput->getShadowMapSize()[1], 1,
								IImage::LUMINANCE, imageType ) );
			texture2D->setImage( depthImage );
			const uint currentTexUnit = internalTexUnitIndex - currentLightIndex;
			texture2D->setMultiAttributeIndex( currentTexUnit );
			engine->evaluate( paintService, texture2D.get(), true );
			vgeGL::rc::Texture2D * lightDepthMap = shadowMappingInput->getLightDepthMap( currentLightIndex, engine );
// @todo moves
			if ( state.isShadowSamplerUsageEnabled() )
			{
				lightDepthMap->bind();
				lightDepthMap->parameter( GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE_ARB );
				lightDepthMap->parameter( GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL );
				lightDepthMap->parameter( GL_DEPTH_TEXTURE_MODE, GL_LUMINANCE );
			}

			// Lookups or creates fbo
			vge::rc::Manager& rcManager = engine->getGLManager();
			vgeGL::rc::FrameBufferObject * fbo = rcManager.get< vgeGL::rc::FrameBufferObject >( shadowMappingInput->m_dummyNodeForFBO[currentLightIndex].get() ); // @todo not very cute
			if ( fbo == 0 )
			{
				fbo = new vgeGL::rc::FrameBufferObject();
				rcManager.add( shadowMappingInput->m_dummyNodeForFBO[currentLightIndex].get(), fbo );

				fbo->generate();

				// Enables render to depth texture
				fbo->bind();
				fbo->renderDepthOnly();

				fbo->attachDepth( lightDepthMap );

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
				fbo->renderDepthOnly();

				fbo->attachDepth( lightDepthMap );
#ifdef _DEBUG
				// Check framebuffer completeness at the end of initialization.
				const std::string fboStatus = fbo->getStatusString();
				if ( fboStatus.size() > 0 )
				{
					vgLogError2( "ForwardRendering::apply(): %s", fboStatus.c_str() );
					return;
					// @todo
				}
				// else nothing to do
#endif
			}

			engine->disregardIfIsAKindOf<vgd::node::Texture>();
			// pre-configuration
			const bool isTextureMappingEnabledBak = engine->isTextureMappingEnabled();
			engine->setTextureMappingEnabled(false);

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

					vgm::MatrixR lightViewMatrix = shadowMappingInput->getLightViewMatrix(currentLightIndex);
					vgm::MatrixR lightMODELVIEWMatrix = shadowMappingInput->getLightMODELVIEWMatrix(currentLightIndex);
					const vgd::node::SpotLight * spotLight = shadowMappingInput->getLightNode(currentLightIndex);

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
					newCamera->setProjection( shadowMappingInput->getLightProjectionMatrix(currentLightIndex) );

					const vgm::Rectangle2i viewport( 0, 0, shadowMappingInput->getShadowMapSize()[0], shadowMappingInput->getShadowMapSize()[1] );
					newCamera->setViewport( viewport );

					engine->evaluate( paintService, newCamera.get(), i->second );
// Cullface in sg(TBT)
				}
				else
				{
					engine->evaluate( paintService, *i );
				}
			}

			// Re-enable rendering to the window
			fbo->detachDepth();			
			fbo->renderDepthOnly( false );
			glBindFramebuffer(GL_FRAMEBUFFER, 0);// @todo fbo->unbound();
//			glDrawBuffer( GL_BACK );
//			glReadBuffer( GL_BACK );

			// Rendering done, extract depth map from depth buffer and copy into a texture2D node.
			// @todo more high-level (Engine::renderTargets section ?)
			//lightDepthMap->parameter( GL_DEPTH_TEXTURE_MODE_ARB, GL_INTENSITY );
// @todo in glo
			/*glCopyTexSubImage2D(	GL_TEXTURE_2D, 0,
									0, 0, 0, 0,
									shadowMappingInput->getShadowMapSize()[0], 
									shadowMappingInput->getShadowMapSize()[1] );*/

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


//			glDisable( GL_CULL_FACE );
//			glDisable( GL_POLYGON_OFFSET_FILL );
//			glEnable( GL_LIGHTING );
//			glColorMask( GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE );
//			glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		}
		//engine->setTextureMappingEnabled(isTextureMappingEnabled);
	}



	//////////////////////////////////////////////////////////////////////////
	// STEP 3: Rendering (opaque and transparent pass ) with/without shadow //
	//////////////////////////////////////////////////////////////////////////
	if ( shadowType != LightModel::SHADOW_OFF && shadowMappingInput->getNumLight() > 0 )
	{
		setPassDescription("ForwardRendering:STEP3:Rendering with shadow");
		beginPass();

		for(	uint currentLightIndex = 0;
				currentLightIndex < shadowMappingInput->getNumLight();
				++currentLightIndex )
		{
			const uint currentTexUnit = internalTexUnitIndex - currentLightIndex;

// @todo Improves vgd::node::Texture to be able to use it directly

			// *** Updates Texture ***
			vgd::Shp< vgd::node::Texture2D > texture2D = shadowMappingInput->getLightDepthMap( currentLightIndex );
			texture2D->setMultiAttributeIndex( currentTexUnit );
// @todo setFunction()
			engine->evaluate( paintService, texture2D.get(), true );

			// *** Updates TexGen ***
			vgd::Shp< vgd::node::TexGenEyeLinear > texGen = shadowMappingInput->getTexGen( currentLightIndex );
			//texGen->setMultiAttributeIndex( texture2D->getMultiAttributeIndex() );
			texGen->setMultiAttributeIndex( currentTexUnit );
			engine->evaluate( paintService, texGen.get(), true );

			// *** Updates Texture Matrix ***
// @todo use TextureMatrix node
			vgm::MatrixR textureMatrix;
			textureMatrix.setTranslate( vgm::Vec3f(0.5f, 0.5f, 0.5f) );	// offset
			textureMatrix.scale( vgm::Vec3f(0.5f, 0.5f, 0.5f) );		// bias
			// LIGHT FRUSTUM (Projection)
			const vgm::MatrixR lightProjectionMatrix = shadowMappingInput->getLightProjectionMatrix( currentLightIndex );
			// LIGHT VIEW (Look At)
			const vgm::MatrixR lightViewMatrix = shadowMappingInput->getLightViewMatrix(currentLightIndex);
			const vgm::MatrixR lightMODELVIEWMatrix = shadowMappingInput->getLightMODELVIEWMatrix(currentLightIndex);

			textureMatrix = invViewMatrix * (lightLookAt[currentLightIndex]) * lightProjectionMatrix * textureMatrix;

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
		if ( mustDoTransparencyPass )
		{
			evaluateTransparentPass( paintService, PassIsolationMask(DEFAULT_PASS_ISOLATION_MASK), true );
		}
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
