// VGSDK - Copyright (C) 2004, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_FIELD_MATRIXR_HPP
#define _VGD_FIELD_MATRIXR_HPP

#include "vgd/field/Enum.hpp"
#include <vgm/Matrix.hpp>



namespace vgd
{

namespace field
{



/**
 * @name Container definitions of row-order matrix type
 */
//@{
typedef TSingleField< vgm::MatrixR >					SFMatrixR;

typedef TMultiField< vgm::MatrixR  >					MFMatrixR;

typedef TSingleAssociativeField< vgm::MatrixR >			SAFMatrixR;

typedef TPairAssociativeField< Enum, vgm::MatrixR >		PAFMatrixR;

//@}



} // namespace field

} // namespace vgd

#endif //#ifndef _VGD_FIELD_MATRIXR_HPP
