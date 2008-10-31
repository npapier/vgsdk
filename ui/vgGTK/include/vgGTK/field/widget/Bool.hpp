// VGSDK - Copyright (C) 2008, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGGTK_FIELD_WIDGET_BOOL_HPP_
#define _VGGTK_FIELD_WIDGET_BOOL_HPP_

#include "vgGTK/field/widget/Widget.hpp"

#include <gtkmm/box.h>
#include <gtkmm/radiobutton.h>



namespace vgGTK
{

namespace field
{

namespace widget
{



struct Bool : public Widget< bool >, public Gtk::VBox
{
	Bool();
	
	void clear();
	const bool getValue() const;
	void setValue( const bool & value );
	const bool validate();
	
	void setFrame( const bool frame );

private:
	Gtk::RadioButton	m_trueButton;	///< Maps the true value.
	Gtk::RadioButton	m_falseButton;	///< Maps the false value
};



} // namespace widget

} // namespace field

} // namespace vgGTK



#endif // _VGGTK_FIELD_WIDGET_BOOL_HPP_