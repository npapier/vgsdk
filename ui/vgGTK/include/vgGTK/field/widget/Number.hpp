// VGSDK - Copyright (C) 2008, 2009, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGGTK_FIELD_WIDGET_NUMBER_HPP_
#define _VGGTK_FIELD_WIDGET_NUMBER_HPP_

#include <boost/lexical_cast.hpp>
#include <gtkmm/entry.h>
#include "vgGTK/field/widget/Widget.hpp"



namespace vgGTK
{

namespace field
{

namespace widget
{



/**
 * @brief	Implements a widget for the edition of any number type.
 */
template< typename NumberType >
struct Number : public Widget< NumberType >, public Gtk::Entry
{
	Number()
	{
		set_activates_default( true );
	}
	
	void clear()
	{
		set_text( Glib::ustring() );
	}
	
	const NumberType getValue() const
	{
		try
		{
			return boost::lexical_cast< NumberType >( get_text() );
		}
		catch( const boost::bad_lexical_cast & )
		{
			return static_cast< NumberType >( 0 );
		}
	}

	const bool hasValue() const
	{
		return get_text().empty() == false;
	}
	
	void setValue( const NumberType & value )
	{
		set_text( Glib::ustring::compose("%1", value) );
	}
	
	const bool validate()
	{
		try
		{
			boost::lexical_cast< NumberType >( get_text() );
			return true;
		}
		catch( const boost::bad_lexical_cast & )
		{
			vgGTK::field::widget::Widget< NumberType >::showWarning("Please, enter a number!");
			grab_focus();
			return false;
		}
	}
	
	const bool resizable() const
	{
		return false;
	}
	
	void setFrame( const bool frame )
	{
		set_has_frame( frame );
	}
};



} // namespace widget

} // namespace field

} // namespace vgGTK



#endif // _VGGTK_FIELD_WIDGET_NUMBER_HPP_
