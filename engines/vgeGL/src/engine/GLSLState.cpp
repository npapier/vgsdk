// VGSDK - Copyright (C) 2008, 2009, 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/engine/GLSLState.hpp"

#include <glo/Texture.hpp>
#include <vgd/basic/toString.hpp>
#include <vgd/node/LightModel.hpp>
#include <vgd/node/SpotLight.hpp>
#include "vgeGL/engine/Engine.hpp"



namespace vgeGL
{

namespace engine
{



// LightState
const vgd::node::SpotLight *GLSLState::LightState::getSpotLightNode() const
{
	return dynamic_cast< vgd::node::SpotLight * >(m_light);
}



const std::string GLSLState::m_indexString[] =
	{
		"LIGHTING",
		"PER_PIXEL_LIGHTING",
		"LOCAL_VIEWER",
		"TWO_SIDED_LIGHTING",

		"DIRECTIONAL_LIGHT",
		"POINT_LIGHT",
		"SPOT_LIGHT",
		"SPOT_LIGHT_CASTING_SHADOW",

		"CLIPPING_PLANE",

		"FLAT_SHADING",

		"POINT_STYLE",

		"PROGRAM",

		"COLOR4_BIND_PER_VERTEX"
	};



const std::string& GLSLState::toString( const BitSetIndexType bitSetIndexType )
{
	assert( bitSetIndexType >= 0 && "Out of range index." );
	assert( bitSetIndexType < MAX_BITSETINDEXTYPE && "Out of range index." );

	return m_indexString[bitSetIndexType];
}



GLSLState::GLSLState( const uint maxLightUnits, const uint maxTexUnits, const bool isShadowSamplerUsageEnabled )
:	m_isShadowSamplerEnabled(isShadowSamplerUsageEnabled),

	m_light(maxLightUnits),
	m_numLight(0),
	m_texture(maxTexUnits),
	m_numTexture(0)
{
}


void GLSLState::reset( const uint maxLightUnits, const uint maxTexUnits, const bool isShadowSamplerUsageEnabled )
{
	// TBitSet
	vgeGL::engine::TBitSet< 13 >::reset();

	// LIGHT
	for(	uint	i		= 0,
					iEnd	= m_light.size();
			i != iEnd;
			++i )
	{
		if ( getLight(i) != 0 )
		{
			setLight( i );

			if ( getNumLight() == 0 )
			{
				break;
			}
		}
	}
	assert( m_numLight == 0 );

	m_light.resize( maxLightUnits );

	// TEXTURE
	for(	uint	i		= 0,
					iEnd	= m_texture.size();
			i != iEnd;
			++i )
	{
		if ( getTexture(i) != 0 )
		{
			setTexture( i );

			if ( getNumTexture() == 0 )
			{
				break;
			}
		}
	}
	assert( m_numTexture == 0 );

	m_texture.resize( maxTexUnits );

	// @todo others ( at this time default values for others are initialized by GLSLState::update() )
	setProgram( 0 );

	setShadowType( vgd::node::LightModel::DEFAULT_SHADOW );
	setSamplingSize( 1.f );
	setShadowMapType( vgd::node::LightModel::DEFAULT_SHADOWMAPTYPE );
	setIlluminationInShadow( 0.4f ); // @todo Adds const float DEFAULT_ILLUMINATIONINSHADOW in node

	setShadowSamplerUsageEnabled( isShadowSamplerUsageEnabled );
}



const bool GLSLState::isLightingEnabled() const
{
	return isEnabled( LIGHTING );
}


void GLSLState::setLightingEnabled( const bool enabled )
{
	setEnabled( LIGHTING, enabled );
}


const bool GLSLState::isTwoSidedLightingEnabled() const
{
	return isEnabled( TWO_SIDED_LIGHTING );
}


void GLSLState::setTwoSidedLightingEnabled( const bool enabled )
{
	setEnabled( TWO_SIDED_LIGHTING, enabled );
}


const bool GLSLState::isPerPixelLightingEnabled() const
{
	return isEnabled( PER_PIXEL_LIGHTING );
}


const bool GLSLState::isPerVertexLightingEnabled() const
{
	return !isPerPixelLightingEnabled();
}


void GLSLState::setPerPixelLightingEnabled( const bool enabled )
{
	setEnabled( PER_PIXEL_LIGHTING, enabled );
}



const vgd::Shp< GLSLState::LightState > GLSLState::getLight( const uint indexLightUnit ) const
{
	assert( indexLightUnit >= 0 && "Invalid light unit index." );
	assert( indexLightUnit < m_light.size() && "Invalid light unit index." );

	return m_light[indexLightUnit];
}



vgd::Shp< GLSLState::LightState > GLSLState::getLight( const uint indexLightUnit )
{
	assert( indexLightUnit >= 0 && "Invalid light unit index." );
	assert( indexLightUnit < m_light.size() && "Invalid light unit index." );

	return m_light[indexLightUnit];
}



vgd::Shp< GLSLState::LightState > GLSLState::setLight( const uint indexLightUnit, vgd::Shp< LightState > lightState )
{
	assert( indexLightUnit >= 0 && "Invalid light unit index." );
	assert( indexLightUnit < m_light.size() && "Invalid light unit index." );

	// Sets the light
	vgd::Shp< LightState > oldLight = m_light[indexLightUnit];

	m_light[indexLightUnit] = lightState;

	// Updates light count
	if ( oldLight )
	{
		m_numLight += ( lightState != 0 ) ? 0 : -1;
	}
	else
	{
		m_numLight += ( lightState != 0 ) ? 1 : 0;
	}
	assert( m_numLight >= 0 );
	assert( m_numLight <= m_light.size() );

	return oldLight;
}



const uint GLSLState::getNumLight() const
{
	return m_numLight;
}



const uint GLSLState::getMaxLight() const
{
	return m_light.size();
}



const vgd::Shp< GLSLState::TexUnitState > GLSLState::getTexture( const uint indexTexUnit ) const
{
	assert( indexTexUnit >= 0 && "Invalid texture unit index." );
	assert( indexTexUnit < m_texture.size() && "Invalid texture unit index." );

	return m_texture[indexTexUnit];
}



vgd::Shp< GLSLState::TexUnitState > GLSLState::getTexture( const uint indexTexUnit )
{
	assert( indexTexUnit >= 0 && "Invalid texture unit index." );
	assert( indexTexUnit < m_texture.size() && "Invalid texture unit index." );

	return m_texture[indexTexUnit];
}



vgd::Shp< GLSLState::TexUnitState > GLSLState::setTexture( const uint indexTexUnit, vgd::Shp< TexUnitState > texture )
{
	assert( indexTexUnit >= 0 && "Invalid texture unit index." );
	assert( indexTexUnit < m_texture.size() && "Invalid texture unit index." );

	// Sets the texture
	vgd::Shp< TexUnitState > oldTexture = m_texture[indexTexUnit];

	m_texture[indexTexUnit] = texture;

	// Updates texture count
	if ( oldTexture )
	{
		m_numTexture += ( texture != 0 ) ? 0 : -1;
	}
	else
	{
		m_numTexture += ( texture != 0 ) ? 1 : 0;
	}
	assert( m_numTexture >= 0 );
	assert( m_numTexture <= m_texture.size() );

	return oldTexture;
}



const uint GLSLState::getNumTexture() const
{
	return m_numTexture;
}


const uint GLSLState::getMaxTexture() const
{
	return m_texture.size();
}



const uint GLSLState::getPrivateTexUnitIndex( const uint index ) const
{
	const uint retVal = (getMaxTexture()-1) - index;
	return retVal;
}



const std::string GLSLState::getPrivateTexUnit( const uint index ) const
{
	const uint retVal = getPrivateTexUnitIndex( index );
	return vgd::basic::toString(retVal);
}



const uint GLSLState::getPrivateIndex( const uint privateTexUnitIndex )
{
	const uint retVal = (getMaxTexture()-1) - privateTexUnitIndex;
	return retVal;
}



const std::string GLSLState::getPrivate( const uint privateTexUnitIndex )
{
	const uint retVal = getPrivateIndex( privateTexUnitIndex );
	return vgd::basic::toString(retVal);
}



vgd::node::Program * GLSLState::getProgram() const
{
	return m_program;
}



void GLSLState::setProgram( vgd::node::Program * program )
{
	m_program = program;
}



const bool GLSLState::isShadowSamplerUsageEnabled() const
{
	return m_isShadowSamplerEnabled;
}



void GLSLState::setShadowSamplerUsageEnabled( const bool enabled )
{
	m_isShadowSamplerEnabled = enabled;
}



} // namespace engine

} // namespace vgeGL
