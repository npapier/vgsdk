// VGSDK - Copyright (C) 2008, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGGTK_FIELD_ENTRYEDITOR_HPP_
#define _VGGTK_FIELD_ENTRYEDITOR_HPP_

#include "vgGTK/field/SingleFieldEditor.hpp"

#include <gtkmm/entry.h>



namespace vgGTK
{

namespace field
{



/**
 * @brief	Implements a field editor that is based on a Gtk::Entry widget.
 */
struct EntryEditor : public SingleFieldEditor
{
	/**
	 * @brief	Constructor
	 */
	EntryEditor();
	
	/**
	 * @name	Widget Management Interface
	 */
	//@{	
	Gtk::Widget& getWidget();
	void grabFocus();
	//@}
	
	/**
	 * @name	Data Management Interface
	 */
	//@{
	void commit();
	void refresh();
	//@}	
	
private:
	
	Gtk::Entry	m_entry;	///< The entry widget
};



} // namespace field

} // namespace vgGTK



#endif // _VGGTK_FIELD_ENTRYEDITOR_HPP_
