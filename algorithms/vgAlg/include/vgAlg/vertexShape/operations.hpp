// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGALG_VERTEXSHAPE_OPERATIONS_HPP
#define _VGALG_VERTEXSHAPE_OPERATIONS_HPP

#include "vgAlg/vgAlg.hpp"
#include <vector>

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
 * @name Vertex shape creation method
 */
//@{

/**
 * @brief Create a vertex shape with only part of its triangles
 *
 * Create a new vertex shape using VERTEX and NORMAL fields from the given vertexShape and indices from trianglesIndices.
 *
 * @param vertexShape		the input vertex shape where VERTEX and NORMAL fields are used to build the sub-mesh
 * @param trianglesIndices	an array containing triangles indices (a smaller VERTEX_INDEX field)
 * @param ignoreNormals		true to create a sub-mesh without NORMAL field, false to create a sub-mesh with NORMAL FIELD
 *
 * @return the newly created sub-mesh with VERTEX, VERTEX INDEX, NORMAL and PRIMITIVES fields initialized.
 */
VGALG_API vgd::Shp< vgd::node::VertexShape > createSubTriSet( const vgd::node::VertexShape * vertexShape, const std::vector< uint32 >& trianglesIndices, const bool ignoreNormals = false );


//@}


} // namespace vertexShape

} //namespace vgAlg

#endif // #ifndef _VGALG_VERTEXSHAPE_OPERATIONS_HPP
