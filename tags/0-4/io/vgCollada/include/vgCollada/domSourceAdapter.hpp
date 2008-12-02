// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGCOLLADA_DOMSOURCEADAPTER_HPP
#define _VGCOLLADA_DOMSOURCEADAPTER_HPP

#include <vector>
#include <vgm/Vector.hpp>

class domSource;



namespace vgCollada
{



/**
 * @brief Converts domSource to vgSDK arrays
 */
struct domSourceAdapter
{
	enum ArrayType
	{
		NONE,
		FLOAT,
		VEC2F,
		VEC3F,
		VEC4F
	};

	domSourceAdapter();
	domSourceAdapter( domSource * src );

	const ArrayType getArrayType() const		{ return m_arrayType; }

	std::vector< float >&		getFloatArray()	{ return m_float; }
	std::vector< vgm::Vec2f >&	getVec2fArray()	{ return m_vec2f; }
	std::vector< vgm::Vec3f >&	getVec3fArray()	{ return m_vec3f; }
	std::vector< vgm::Vec4f >&	getVec4fArray()	{ return m_vec4f; }

protected:
	ArrayType m_arrayType;

	std::vector< float >		m_float;
	std::vector< vgm::Vec2f >	m_vec2f;
	std::vector< vgm::Vec3f >	m_vec3f;
	std::vector< vgm::Vec4f >	m_vec4f;
};



} // namespace vgCollada

#endif // _VGCOLLADA_DOMSOURCEADAPTER_HPP
