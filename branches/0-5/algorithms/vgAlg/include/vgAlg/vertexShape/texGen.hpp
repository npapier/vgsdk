// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGALG_VERTEXSHAPE_TEXGEN_HPP
#define _VGALG_VERTEXSHAPE_TEXGEN_HPP

#include "vgAlg/vgAlg.hpp"

#include <vgm/Vector.hpp>

namespace vgd
{
	template<class T> struct Shp;
	namespace node { struct VertexShape; }
}



namespace vgAlg
{

namespace vertexShape
{


/**
 * @name Texture-Coordinate Generation method
 */
//@{

/**
 * @brief Generates texture coordinates similar to GL_OBJECT_LINEAR
 *
 * @param vertexShape		shape where the field texCoordX will be generated (with X equal to parameter texCoordIndex)
 * @param s					texture generation parameters for the s texture coordinates (s,t)
 * @param t					texture generation parameters for the t texture coordinates (s,t)
 * @param texCoordIndex		see description of vertexShape parameter
 */
VGALG_API void computeTexGenObjectLinear( vgd::Shp< vgd::node::VertexShape > vertexShape, const vgm::Vec4f s, const vgm::Vec4f t, const uint texCoordIndex = 0 );

//@}


} // namespace vertexShape

} //namespace vgAlg

#endif // #ifndef _VGALG_VERTEXSHAPE_TEXGEN_HPP
