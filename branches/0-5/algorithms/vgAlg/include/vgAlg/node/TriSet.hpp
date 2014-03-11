// VGSDK - Copyright (C) 2007, 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGALG_NODE_TRISET_HPP
#define _VGALG_NODE_TRISET_HPP

#include "vgAlg/vgAlg.hpp"
 
namespace vgd
{
	template<class T> struct Shp;
	
	namespace node { struct TriSet; struct VertexShape; }
}



namespace vgAlg
{

namespace node
{



/**
 * @brief Tests if the given shape is only composed of triangles.
 *
 * @return true if the given shape is only composed of triangles, false otherwise.
 */
const bool isATriSet( const vgd::node::VertexShape * vertexShape );


/**
 * @brief Inverse the orientation of triangles.
 * 
 * @param triset		the triset node
 * 
 * The triset is a set of triangles. This method reverses (clockwise to conterclockwise or ccw to cw) the orientation 
 * of each triangles of the given shape.
 */
VGALG_API void invertTriangleOrientation( vgd::Shp< vgd::node::TriSet > triset );



} // namespace node

} //namespace vgAlg

#endif // #ifndef _VGALG_NODE_TRISET_HPP
