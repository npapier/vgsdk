// VGSDK - Copyright (C) 2008, 2009, 2010, Guillaume Brocker, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#ifndef _VGGTK_FIELD_WIDGET_NUMBER_HPP_
#define _VGGTK_FIELD_WIDGET_NUMBER_HPP_

#include <gtkmm/spinbutton.h>
#include <vgBase/Type.hpp>

#include "vgGTK/convenience.hpp"
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
struct Number : public Widget< NumberType >, public Gtk::SpinButton
{
	Number()
	{
		set_activates_default( true );
		set_text( Glib::ustring() );
		vgGTK::configure< NumberType >( *this );
	}
	
	void clear()
	{
		set_text( Glib::ustring() );
	}
	
	const NumberType getValue() const
	{
		return static_cast< NumberType >( get_value() );

		/*try
		{
			return boost::lexical_cast< NumberType >( get_text() );			
		}
		catch( const boost::bad_lexical_cast & )
		{
			return static_cast< NumberType >( 0 );
		}*/
	}

	const bool hasValue() const
	{
		return get_text().empty() == false;
	}
	
	void setValue( const NumberType & value )
	{
		set_value( value );
	}
	
	const bool validate()
	{
		/*try
		{
			boost::lexical_cast< NumberType >( get_text() );
			return is_number();
		}
		catch( const boost::bad_lexical_cast & )
		{
			vgGTK::field::widget::Widget< NumberType >::showWarning("Please, enter a number!");
			grab_focus();
			return false;
		}*/

		return true;
	}

	void grabFocus()
	{
		grab_focus();
	}
	
	const bool resizable() const
	{
		return false;
	}
	
	void setFrame( const bool frame )
	{
		set_has_frame( frame );
	}

protected:

	void on_changed()
	{
		Gtk::SpinButton::on_changed();
		m_signalChanged.emit();
	}
};



///
/// Following specializations are now obsolat since the use of Gtk::SpinButton
///

/**
 * @brief	Specialized version of a widget for the edition of int8 number type.
 */
/*struct Int8Number : public Number< int8 >
{
	const int8 getValue() const
	{
		try
		{
			return static_cast< int8 >(
				boost::lexical_cast< int >( get_text() )
					);
		}
		catch( const boost::bad_lexical_cast & )
		{
			return static_cast< int8 >( 0 );
		}
	}

	void setValue( const int & value )
	{
		set_text( Glib::ustring::compose("%1", value) );
	}

	const bool validate()
	{
		try
		{
			boost::lexical_cast< int >( get_text() );
			return true;
		}
		catch( const boost::bad_lexical_cast & )
		{
			vgGTK::field::widget::Widget< int8 >::showWarning("Please, enter a number!");
			grab_focus();
			return false;
		}
	}
};*/



/**
 * @brief	Specialized version of a widget for the edition of uint8 number type.
 */
/*struct UInt8Number : public Number< uint8 >
{
	const uint8 getValue() const
	{
		try
		{
			return static_cast< uint8 >(
				boost::lexical_cast< int >( get_text() )
					);
		}
		catch( const boost::bad_lexical_cast & )
		{
			return static_cast< uint8 >( 0 );
		}
	}

	void setValue( const int & value )
	{
		set_text( Glib::ustring::compose("%1", value) );
	}

	const bool validate()
	{
		try
		{
			boost::lexical_cast< int >( get_text() );
			return true;
		}
		catch( const boost::bad_lexical_cast & )
		{
			vgGTK::field::widget::Widget< uint8 >::showWarning("Please, enter a number!");
			grab_focus();
			return false;
		}
	}
};*/



} // namespace widget

} // namespace field

} // namespace vgGTK



#endif // _VGGTK_FIELD_WIDGET_NUMBER_HPP_
