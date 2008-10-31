// VGSDK - Copyright (C) 2008, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGGTK_FIELD_WIDGET_STRING_HPP_
#define _VGGTK_FIELD_WIDGET_STRING_HPP_



#include <gtkmm/entry.h>
#include "vgGTK/field/widget/Widget.hpp"



namespace vgGTK
{

namespace field
{

namespace widget
{


struct String : public Widget< std::string >, public Gtk::Entry
{
	String();
	
	void clear();
	const std::string getValue() const;
	void setValue( const std::string & value );
	const bool validate();
	
	void setFrame( const bool frame );
};



} // namespace widget

} // namespace field

} // namespace vgGTK



#endif // _VGGTK_FIELD_WIDGET_STRING_HPP_
