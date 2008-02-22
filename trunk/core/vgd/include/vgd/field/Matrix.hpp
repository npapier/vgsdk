// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_MATRIX_HPP
#define _VGD_FIELD_MATRIX_HPP

#include "vgd/vgd.hpp"

#include <vgm/Matrix.hpp>

#include "vgd/field/TSingleField.hpp"
#include "vgd/field/TMultiField.hpp"
#include "vgd/field/TSingleAssociativeField.hpp"
#include "vgd/field/TPairAssociativeField.hpp"



namespace vgd
{
	
namespace field
{



/**
 * @name Typedefs for fields containing elements of vgm::Matrix type.
 */
//@{
typedef TSingleField< vgm::MatrixR >					SFMatrixR;

typedef TMultiField< vgm::MatrixR  >					MFMatrixR;

typedef TSingleAssociativeField< vgm::MatrixR >		SAFMatrixR;

// typedef TPairAssociativeField< vgm::MatrixR >		PAFMatrixR;
//@}



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_MATRIX_HPP
