// VGSDK - Copyright (C) 2008, 2009, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGGTK_FIELD_WIDGET_VECTOR_HPP_
#define _VGGTK_FIELD_WIDGET_VECTOR_HPP_

#include "vgGTK/field/widget/Widget.hpp"

#include <boost/lexical_cast.hpp>
#include <gtkmm/box.h>
#include <gtkmm/entry.h>
#include <vgm/Vector.hpp>



namespace vgGTK
{

namespace field
{

namespace widget
{



/**
 * @brief	Implements a widget for vgm::Vector edition.
 */
template< typename T, int N >
struct Vector : public Widget< vgm::Vector<T, N> >, public Gtk::HBox
{
	Vector()
	:	m_hasFrame( true )
	{
		for( unsigned int i = 0; i < N; ++i )
		{
			m_elements[i].set_width_chars( 10 );
			m_elements[i].set_size_request( 75, -1 );
			m_elements[i].set_has_frame( m_hasFrame );
			m_elements[i].set_activates_default();
		
			add( m_elements[i] );
		}
	}
	
	void clear()
	{
		for( unsigned int i = 0; i != N; ++i )
		{
			m_elements[i].set_text( Glib::ustring() );
		}
	}
	
	const vgm::Vector< T, N > getValue() const
	{
		vgm::Vector< T, N >	result;
		
		for( unsigned int i = 0; i < N; ++i )
		{
			try
			{
				result[i] = boost::lexical_cast< T >( m_elements[i].get_text() );
			}
			catch( const boost::bad_lexical_cast & )
			{
				result[i] = static_cast< T >( 0 );
			}
		}
		
		return result;
	}
	
	const bool hasValue() const
	{
		for( unsigned int i = 0; i != N; ++i )
		{
			if( m_elements[i].get_text().empty() == false )
			{
				return true;
			}
		}

		return false;
	}
	
	void setValue( const vgm::Vector< T, N > & value )
	{
		for( unsigned int i = 0; i < N; ++i )
		{
			m_elements[i].set_text( Glib::ustring::compose("%1", value[i]) );
		}
	}
	
	const bool validate()
	{
		bool validate = true;
		
		for( unsigned int i = 0; i < N && validate; ++i )
		{
			try
			{
				boost::lexical_cast< T >( m_elements[i].get_text() );
			}
			catch( const boost::bad_lexical_cast & )
			{
				showWarning("Please, enter a number!");
				m_elements[i].grab_focus();
				validate = false;
			}
		}
		
		return validate;
	}
	
	const bool resizable() const
	{
		return false;
	}
	
	void setFrame( const bool frame )
	{
		m_hasFrame = frame;
		for( unsigned int i = 0; i != N; ++i )
		{
			m_elements[i].set_has_frame( frame );
		}
	}


private:
	
	bool		m_hasFrame;		///< Tells if edition fields must show a frame.
	Gtk::Entry	m_elements[N];	///< Holds all edition widgets.
};



} // namespace widget

} // namespace field

} // namespace vgGTK



#endif // _VGGTK_FIELD_WIDGET_VECTOR_HPP_
