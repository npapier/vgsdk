// VGSDK - Copyright (C) 2008, Nicolas Papier.
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
		"TWO_SIDED_LIGHTING",
		"PER_PIXEL_LIGHTING",
		"CLIPPING_PLANE"
	};



GLSLState::GLSLState( const uint maxTexUnits )
:	m_texture(maxTexUnits),
	m_numTexture(0)
{
}


void GLSLState::reset( const uint maxTexUnits )
{
	// TBitSet
	vgeGL::engine::TBitSet<4>::reset();

	// TEXTURE
	for(	uint	i		= 0,
					iEnd	= m_texture.size();
			i != iEnd;
			++i )
	{
		if ( getTexture(i) != 0 )
		{
			setTexture( i, 0 );

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



const glo::Texture *GLSLState::getTexture( const uint indexTexUnit ) const
{
	assert( indexTexUnit >= 0 && "Invalid texture unit index." );
	assert( indexTexUnit < m_texture.size() && "Invalid texture unit index." );

	return m_texture[indexTexUnit];
}



glo::Texture *GLSLState::getTexture( const uint indexTexUnit )
{
	assert( indexTexUnit >= 0 && "Invalid texture unit index." );
	assert( indexTexUnit < m_texture.size() && "Invalid texture unit index." );

	return m_texture[indexTexUnit];
}



glo::Texture *GLSLState::setTexture( const uint indexTexUnit, glo::Texture * texture )
{
	assert( indexTexUnit >= 0 && "Invalid texture unit index." );
	assert( indexTexUnit < m_texture.size() && "Invalid texture unit index." );

	glo::Texture * oldTexture = m_texture[indexTexUnit];

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

	// LIGHTING
	setLightingEnabled( glIsEnabled(GL_LIGHTING) );		// @todo Removes glIsEnabled() call

	// TWO_SIDED_LIGHTING
	using vgd::node::LightModel;
	LightModel::TwoSidedValueType twoSidedValue;
	bDefined = engine->getStateStackTop<
		LightModel,
		int /*LightModel::TwoSidedParameterType*/,
		LightModel::TwoSidedValueType >(	LightModel::getFTwoSided(),
											LightModel::TWO_SIDED,
											twoSidedValue );
	assert( bDefined );
	setTwoSidedLightingEnabled( twoSidedValue );

	// PER_PIXEL_LIGHTING
	LightModel::ModelValueType	modelValue;
	bDefined = engine->getStateStackTop<
			LightModel,
			LightModel::ModelParameterType,
			LightModel::ModelValueType >(	LightModel::getFModel(),
											LightModel::MODEL,
											modelValue );
	assert( bDefined );
	setPerPixelLightingEnabled( modelValue == LightModel::STANDARD_PER_PIXEL );
}



} // namespace engine

} // namespace vgeGL
