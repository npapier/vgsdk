// VGSDK - Copyright (C) 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/technique/ShadowMapping.hpp"

//#include <vgd/node/Texture2D.hpp>
#include <vgd/node/FrameBuffer.hpp>
#include <vgd/node/TexGenEyeLinear.hpp>
#include "vgeGL/engine/Engine.hpp"
#include "vgeGL/rc/Texture2D.hpp"
#include "vgeGL/rc/FrameBufferObject.hpp"
#include <vgm/VectorOperations.hpp>



namespace vgeGL
{

namespace technique
{



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

/*	m_lightAlphaMap.swap( m_recycleLightAlphaMap );
	m_lightAlphaMap.clear();*/

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
				// depth map
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

					lightDepthMap->setWrapS( Texture::CLAMP );
					lightDepthMap->setWrapT( Texture::CLAMP );

					lightDepthMap->setUsage( Texture::SHADOW );
				}

				//
				LightModel::ShadowFilteringValueType shadowFiltering = engine->getOFEnum< LightModel >( LightModel::getFShadowFiltering() );

				switch ( shadowFiltering.value() )
				{
					case LightModel::NEAREST:
						lightDepthMap->setMinFilter( Texture::NEAREST );
						lightDepthMap->setMagFilter( Texture::NEAREST );
						break;

					case LightModel::LINEAR:
						lightDepthMap->setMinFilter( Texture::LINEAR );
						lightDepthMap->setMagFilter( Texture::LINEAR );
						break;

					default:
						vgAssertN( false, "Unexpected value %i", shadowFiltering.value() );
				}

				m_lightDepthMap.push_back( lightDepthMap );

				/*// ALPHA MAP
				vgd::Shp< vgd::node::Texture2D > lightAlphaMap;
				if ( m_recycleLightAlphaMap.size() > 0 )
				{
					lightAlphaMap = m_recycleLightAlphaMap.back();
#ifdef _DEBUG
					lightAlphaMap->setName("alphaMap.spotLight" + vgd::basic::toString(i));
#endif
				}
				else
				{
					// node part
					lightAlphaMap = vgd::node::Texture2D::create("alphaMap.spotLight" + vgd::basic::toString(i));

					lightAlphaMap->setWrap( Texture::WRAP_S, Texture::CLAMP );
					lightAlphaMap->setWrap( Texture::WRAP_T, Texture::CLAMP );
				}

				switch ( shadowFiltering.value() )
				{
					case LightModel::NEAREST:
						lightAlphaMap->setFilter( Texture::MIN_FILTER, Texture::NEAREST );
						lightAlphaMap->setFilter( Texture::MAG_FILTER, Texture::NEAREST );
						break;

					case LightModel::LINEAR:
						lightAlphaMap->setFilter( Texture::MIN_FILTER, Texture::LINEAR );
						lightAlphaMap->setFilter( Texture::MAG_FILTER, Texture::LINEAR );
						break;

					default:
						vgAssertN( false, "Unexpected value %i", shadowFiltering.value() );
				}

				m_lightAlphaMap.push_back( lightAlphaMap );*/

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
			//vgLogDebug( "ShadowMappingInput::ShadowMappingInput: Light %s not yet supported by shadow mapping.", current->getLightNode()->getName().c_str() );
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
	vgd::Shp< vgd::node::Texture2D > texture2DNode = getLightDepthMap(index);
	return engine->getRCShp< vgeGL::rc::Texture2D >( texture2DNode );
}



/*vgd::Shp< vgd::node::Texture2D > ShadowMappingInput::getLightAlphaMap( const uint index )
{
	vgAssertN( index < getNumLight(), "ShadowMappingInput::getLightAlphaMap(): Out of range index." );

	return m_lightAlphaMap[index];
}


vgd::Shp< vgeGL::rc::Texture2D > ShadowMappingInput::getLightAlphaMap( const uint index, vgeGL::engine::Engine * engine )
{
	vgd::Shp< vgd::node::Texture2D > texture2DNode = getLightAlphaMap(index);
	return engine->getRCShp< vgeGL::rc::Texture2D >( texture2DNode );
}*/



vgd::Shp< vgd::node::TexGenEyeLinear > ShadowMappingInput::getTexGen( const uint index )
{
	vgAssertN( index < getNumLight(), "ShadowMappingInput::getTexGen(): Out of range index." );

	return m_texGen[index];
}



const vgm::Vec2i ShadowMappingInput::getShadowMapSize() const
{
	return m_shadowMapSize;
}



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



} // namespace technique

} // namespace vgeGL
