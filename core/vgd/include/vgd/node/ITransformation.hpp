// VGSDK - Copyright (C) 2004, 2006, 2007, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_ITRANSFORMATION_HPP
#define _VGD_NODE_ITRANSFORMATION_HPP

#include <vgm/Matrix.hpp>
#include <vgm/Rotation.hpp>
#include <vgm/Vector.hpp>

#include "vgd/vgd.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Interface to transform vertices and/or normals of a shape node.
 */
struct VGD_API ITransformation
{
	/**
	 * @brief Virtual destructor.
	 */
	virtual ~ITransformation();

	/**
	 * @brief Transforms all vertices and normals by the given matrix.
	 * 
	 * The transformed vertices are computed by multiplying each vertex(row vector) by the matrix.
	 * The transformed normals are computed by multiplying each normal(row vector) by the matrix and renormalize it if
	 * specified by method parameter \c normalize.
	 *
	 * @param matrix		the matrix used to transform vertices.
	 * @param normalize		true to activate the normalization of transformed normals, false to disable this normalization.
	 */
	virtual void transform( const vgm::MatrixR& matrix, const bool normalize = true )=0;

	/**
	 * @brief Transform all vertices by the given translation vector.
	 * 
	 * The transformed vertices are computed by multiplying each vertex(row vector) by the matrix.
	 * 
	 * @param translation	the vector used to translate vertices.
	 */
	virtual void transform( const vgm::Vec3f translation )=0;

	/**
	 * @brief Transform all vertices and normals by the given rotation.
	 * 
	 * The transformed vertices are computed by multiplying each vertex(row vector) by the 4x4 matrix corresponding to 
	 * the rotation.
	 * The transformed normals are computed by multiplying each normal(row vector) by the 4x4 matrix corresponding to 
	 * the rotation.
	 * 
	 * @param rotation		the rotation used to transform vertices.
	 */
	virtual void transform( const vgm::Rotation rotation )=0;
	//@}

	// @todo remove me (called by VertexShape::setToDefaults())
	virtual void setToDefaults() {}
	// @todo remove me (called by VertexShape::setOptionalsToDefaults())
	virtual void setOptionalsToDefaults() {}
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_ITRANSFORMATION_HPP
