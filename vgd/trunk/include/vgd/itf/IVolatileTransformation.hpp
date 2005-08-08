// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_ITF_IVOLATILETRANSFORMATION_HPP
#define _VGD_ITF_IVOLATILETRANSFORMATION_HPP

#include <vgm/Matrix.hpp>
#include <vgm/Rotation.hpp>
#include <vgm/Vector.hpp>
#include "vgd/vgd.hpp"



namespace vgd
{

namespace itf
{

/**
 * @brief Interface to apply geometrical transformations to shape node.
 * 
 * This interface permits to transform shape like ITransformation, but transformations are not directly applied to
 * the data owned by the shape node (i.e. during a rendering the GPU receive the shape and the matrix it must used to 
 * transform the geometry). This class is useful when transformations are changing frequently.
 */
struct VGD_API IVolatileTransformation
{
	/**
	 * @brief Add a new transformation given by the matrix.
	 * 
	 * The transformed vertices are computed by multiplying each vertex(row vector) by the matrix.
	 * The transformed normals are computed by multiplying each normal(row vector) by the matrix and renormalize.
	 *
	 * @param matrix		this matrix defines the transformation.
	 */
	virtual void vTransform( const vgm::MatrixR& matrix )=0;

	/**
	 * @brief Add a new translation.
	 * 
	 * @param translation	this vector is used to translate vertices.
	 */
	virtual void vTransform( const vgm::Vec3f translation )=0;

	/**
	 * @brief Add a new rotation.
	 * 
	 * @param rotation		this rotation is used to transform vertices.
	 */
	virtual void vtransform( const vgm::Rotation rotation )=0;
	//@}
};


} // namespace itf

} // namespace vgd

#endif //#ifndef _VGD_ITF_IVOLATILETRANSFORMATION_HPP
