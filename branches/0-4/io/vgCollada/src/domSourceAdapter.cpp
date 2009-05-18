// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgCollada/domSourceAdapter.hpp"

#include <dom/domSource.h>
#include <vgDebug/convenience.hpp>



namespace vgCollada
{



domSourceAdapter::domSourceAdapter()
:	m_arrayType( NONE )
{}



domSourceAdapter::domSourceAdapter( domSource * source )
:	m_arrayType( NONE )
{
	// domTechnique_common
	domSource::domTechnique_common * technique = source->getTechnique_common();

	if ( technique == 0 )
	{
		vgLogWarning("domSourceAdapter: Unable to find COMMON technique.");
		return;
	}

	// domAccessor
	domAccessor * accessor = technique->getAccessor();

	// Initializes m_arrayType
	const uint stride = accessor->getStride();
	switch ( stride )
	{
		case 1:
			m_arrayType = FLOAT;
			break;
		case 2:
			m_arrayType = VEC2F;
			break;
		case 3:
			m_arrayType = VEC3F;
			break;
		case 4:
			m_arrayType = VEC4F;
			break;
		default:
			vgLogWarning2("Unsupported stride %i.", stride );
			return;
	}

	const uint count = accessor->getCount();

	// Fills array
	daeDoubleArray * float_array = 0;
	if ( source->getFloat_array() != 0 )
	{
		float_array = &(source->getFloat_array()->getValue());
	}
	else
	{
		vgLogDebug("Only float array supported and no float array found.");
		return;
	}

	daeDoubleArray& va = *float_array;

	switch( stride )
	{
		case 1:
			for( size_t i = 0; i < count; ++i )
			{
				m_float.push_back( va[i] );
			}
			break;

		case 2:
			for( size_t i = 0; i < count; ++i )
			{
				m_vec2f.push_back( vgm::Vec2f(va[i*2], va[i*2+1]) );
			}
			break;

		case 3:
			for( size_t i = 0; i < count; ++i )
			{
				m_vec3f.push_back( vgm::Vec3f(va[i*3], va[i*3+1], va[i*3+2]) );
			}
			break;

		case 4:
			for( size_t i = 0; i < count; ++i )
			{
				m_vec4f.push_back( vgm::Vec4f(va[i*4], va[i*4+1], va[i*4+2], va[i*4+3]) );
			}
			break;

		default:
			vgLogDebug("Unsupported stride %i.", stride);
	}
}



} // namespace vgCollada
