// VGSDK - Copyright (C) 2008, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include "vgGTK/field/EntryEditor.hpp"

#include <cassert>
#include <string>



namespace vgGTK
{

namespace field
{



EntryEditor::EntryEditor()
:	m_entry()
{}




Gtk::Widget& EntryEditor::getWidget()
{
	return m_entry;
}



void EntryEditor::grabFocus()
{
	m_entry.grab_focus();
}



void EntryEditor::commit()
{
	const std::string newValue = m_entry.get_text();
	
	setFieldValue< std::string >( newValue );
}



void EntryEditor::refresh()
{
	const std::string	fieldValue	= getFieldValue< std::string >();
	
	m_entry.set_text( fieldValue );
}



} // namespace field

} // namespace vgGTK
