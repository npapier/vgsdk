// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_UNIFORM_HPP
#define _VGD_FIELD_UNIFORM_HPP

#include <boost/variant.hpp>
//#include "vgd/field/containers.hpp"
#include <vgm/Matrix.hpp>



namespace vgd
{

namespace field
{

/**
 * @brief Definition of a single uniform value
 *
 * A single uniform value could be of one of the following type
 */
typedef boost::variant<
		int,
		float,
		// @todo vgm::Vec2i, vgm::Vec3i, vgm::Vec4i,
		vgm::Vec2f, vgm::Vec3f, vgm::Vec4f,
		// @todo int[], float[]
		vgm::MatrixR
		// @todo matrix[]
		>	UniformValue;

/**
 * @name Typedefs for fields containing elements of UniformValue type
 */
//@{

//typedef TSingleField< UniformValue		> SFUniformValue;
//typedef TOptionalField< UniformValue	> OFUniformValue;
//typedef TMultiField< UniformValue		> MFUniformValue;

//@}



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_UNIFORM_HPP
