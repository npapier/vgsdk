// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_FIELD_OPERATIONS_HPP_
#define _VGQT_FIELD_OPERATIONS_HPP_

#include <vgd/Shp.hpp>
#include <vgd/field/FieldManager.hpp>

#include <QString>

namespace vgQt
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
FieldEditor* createEditor( const vgd::Shp< vgd::field::FieldManager > fieldManager, QString fieldName );



/**
 * @brief	Creates an editor for the given field type.
 *
 * @return	a reference to an editor, null if none
 */
FieldEditor* createEditor( const std::type_info & fieldType );



} // namespace field

} // namespace vgQt



#endif // _VGGTK_FIELD_OPERATIONS_HPP_
