// VGSDK - Copyright (C) 2008, Pierre-Jean Bensoussan, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Pierre-Jean Bensoussan
// Author Nicolas Papier

#ifndef _VGALG_NODE_VERTEXSHAPE_HPP
#define _VGALG_NODE_VERTEXSHAPE_HPP

#include "vgAlg/vgAlg.hpp"
 
namespace vgd
{
	template<class T> struct Shp;

	namespace node { struct VertexShape; }
}

namespace vgAlg
{

namespace node
{



/**
 * @brief Inverse the orientation of primitives.
 * 
 * @param vertexShape		the vertexShape node
 * 
 * This method reverses (clockwise to conterclockwise or ccw to cw) the orientation 
 * of each triangles and quads of the given vertexShape.
 */
VGALG_API void invertPrimitiveOrientation( vgd::Shp< vgd::node::VertexShape > vertexShape );


/**
 * @brief Inverse the orientation of normals.
 * 
 * @param vertexShape		the vertexShape node
 * 
 * This method reverses the orientation of each normals of the given vertexShape.
 */
VGALG_API void invertNormalOrientation( vgd::Shp< vgd::node::VertexShape > vertexShape );

} // namespace node

} //namespace vgAlg

#endif // #ifndef _VGALG_NODE_VERTEXSHAPE_HPP
