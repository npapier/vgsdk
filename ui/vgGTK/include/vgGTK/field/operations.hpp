// VGSDK - Copyright (C) 2008, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGGTK_FIELD_OPERATIONS_HPP_
#define _VGGTK_FIELD_OPERATIONS_HPP_

#include <vgd/Shp.hpp>



namespace vgGTK
{

namespace field
{

struct Editor;



/**
 * @brief	Creates an editor for the given field type.
 *
 * @return	a reference to an editor, null if none
 */
vgd::Shp< Editor > createEditor( const std::type_info & fieldType );



} // namespace field

} // namespace vgGTK



#endif // _VGGTK_FIELD_OPERATIONS_HPP_
