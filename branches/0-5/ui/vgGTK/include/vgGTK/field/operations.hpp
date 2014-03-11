// VGSDK - Copyright (C) 2008, 2009, 2010, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGGTK_FIELD_OPERATIONS_HPP_
#define _VGGTK_FIELD_OPERATIONS_HPP_

#include <string>
#include <vgd/Shp.hpp>
#include <vgd/field/FieldManager.hpp>



namespace vgGTK
{

namespace field
{

struct FieldEditor;



/**
 * @brief	Creates an editor for the given  field.
 *
 * @param	fieldManager	a reference to the field manager that owns the field to edit
 * @param	fieldName		the name of the field to edit
 *
 * @return	a reference to an editor, null if none
 */
vgd::Shp< FieldEditor > createEditor( const vgd::Shp< vgd::field::FieldManager > fieldManager, const std::string & fieldName );



/**
 * @brief	Creates an editor for the given field type.
 *
 * @return	a reference to an editor, null if none
 */
vgd::Shp< FieldEditor > createEditor( const std::type_info & fieldType );



} // namespace field

} // namespace vgGTK



#endif // _VGGTK_FIELD_OPERATIONS_HPP_
