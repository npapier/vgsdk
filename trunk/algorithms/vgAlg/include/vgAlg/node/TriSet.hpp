// VGSDK - Copyright (C) 2007, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGALG_NODE_TRISET_HPP
#define _VGALG_NODE_TRISET_HPP

#include "vgAlg/vgAlg.hpp"
 
namespace vgd
{
	template<class T> struct Shp;
	
	namespace node { struct TriSet; }
}

namespace vgAlg
{

namespace node
{



/**
 * @brief Inverse the orientation of triangles.
 * 
 * @param triset		the triset node
 * 
 * The triset is a set of triangles. This method reverses (clockwise to conterclockwise or ccw to cw) the orientation 
 * of each triangles of the given shape.
 */
VGALG_API void invertTriangleOrientation( vgd::Shp< vgd::node::TriSet > triset );



/**
 * brief Tests if the given shape is valid.
 * 
 * param triset		the triset node to validate
 * 
 * return true if valid, false if not.
 */
//const bool isValid( vgd::Shp< vgd::node::TriSet > triset ) const;



/**
 * brief Computes the volume of the given shape.
 * 
 * param triset		the triset node
 * 
 * return the computed volume
 */
//const double computeVolume( vgd::Shp< vgd::node::TriSet > triset ) const;



/**
 * brief Returns if the number of hole is equal to zero
 * 
 * return true if there is no hole in the mesh
 */
//bool isNumHoleEqualToZero();



} // namespace node

} //namespace vgAlg

#endif // #ifndef _VGALG_NODE_TRISET_HPP
