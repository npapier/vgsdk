// VGSDK - Copyright (C) 2008, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/engine/GLSLState.hpp"

#include <glo/Texture.hpp>
#include <vgd/node/LightModel.hpp>
#include "vgeGL/engine/Engine.hpp"



namespace vgeGL
{

namespace engine
{



const std::string GLSLState::indexString[] =
	{
		"LIGHTING",
		"PER_PIXEL_LIGHTING",
		"LOCAL_VIEWER",
		"TWO_SIDED_LIGHTING",

		"DIRECTIONAL_LIGHT",
		"POINT_LIGHT",
		"SPOT_LIGHT",
		"CLIPPING_PLANE"
	};



GLSLState::GLSLState( const uint maxLightUnits, const uint maxTexUnits )
:	m_light(maxLightUnits),
	m_numLight(0),
	m_texture(maxTexUnits),
	m_numTexture(0)
{
}


void GLSLState::reset( const uint maxLightUnits, const uint maxTexUnits )
{
	// TBitSet
	vgeGL::engine::TBitSet<8>::reset();

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
	assert( m_numLight < m_light.size() );

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
	assert( m_numTexture < m_texture.size() );

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



void GLSLState::update( vgeGL::engine::Engine * engine )
{
	bool bDefined;

	using vgd::node::LightModel;

	// LIGHTING
	LightModel::ModelValueType	modelValue;
	bDefined = engine->getStateStackTop<
			LightModel,
			LightModel::ModelParameterType,
			LightModel::ModelValueType >(	LightModel::getFModel(),
											LightModel::MODEL,
											modelValue );
	assert( bDefined );
	setLightingEnabled( modelValue != LightModel::LIGHTING_OFF );
	//glIsEnabled(GL_LIGHTING) );		// @todo Removes glIsEnabled() call

	// PER_PIXEL_LIGHTING
	setPerPixelLightingEnabled( modelValue == LightModel::STANDARD_PER_PIXEL );

	// LOCAL_VIEWER
	LightModel::ViewerValueType viewerValue;
	bDefined = engine->getStateStackTop<
		LightModel,
		LightModel::ViewerParameterType,
		LightModel::ViewerValueType >(	LightModel::getFViewer(),
										LightModel::VIEWER,
										viewerValue );
	assert( bDefined );
	setEnabled( LOCAL_VIEWER, viewerValue == LightModel::AT_EYE );
/*	GLint isLocalViewer;
	glGetIntegerv( GL_LIGHT_MODEL_LOCAL_VIEWER, &isLocalViewer );

	setEnabled( LOCAL_VIEWER, isLocalViewer == GL_TRUE );*/

	// TWO_SIDED_LIGHTING
	LightModel::TwoSidedValueType twoSidedValue;
	bDefined = engine->getStateStackTop<
		LightModel,
		int /*LightModel::TwoSidedParameterType*/,
		LightModel::TwoSidedValueType >(	LightModel::getFTwoSided(),
											LightModel::TWO_SIDED,
											twoSidedValue );
	assert( bDefined );
	setTwoSidedLightingEnabled( twoSidedValue );
}



} // namespace engine

} // namespace vgeGL
