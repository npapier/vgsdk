// VGSDK - Copyright (C) 2008, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGGTK_FIELD_RADIOBUTTONEDITOR_HPP_
#define _VGGTK_FIELD_RADIOBUTTONEDITOR_HPP_

#include "vgGTK/field/SingleFieldEditor.hpp"

#include <gtkmm/box.h>
#include <gtkmm/radiobutton.h>



namespace vgGTK
{

namespace field
{



/**
 * @brief	Implements a field editor based on Gtk::RadioButton widgets for vgd::TSingleField< bool >.
 */
struct RadioButtonEditor : public SingleFieldEditor
{
	/**
	 * @brief	Constructor
	 */
	RadioButtonEditor();
	
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

	Gtk::VBox			m_box;			///< Holds all managed widgets
	Gtk::RadioButton	m_trueButton;	///< Maps the true value.
	Gtk::RadioButton	m_falseButton;	///< Maps the false value
};



} // namespace field

} // namespace vgGTK



#endif // _VGGTK_FIELD_RADIOBUTTONEDITOR_HPP_
