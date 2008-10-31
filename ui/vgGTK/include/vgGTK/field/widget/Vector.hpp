// VGSDK - Copyright (C) 2008, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGGTK_FIELD_WIDGET_VECTOR_HPP_
#define _VGGTK_FIELD_WIDGET_VECTOR_HPP_

#include "vgGTK/field/widget/Widget.hpp"

#include <vector>
#include <boost/lexical_cast.hpp>
#include <gtkmm/box.h>
#include <gtkmm/entry.h>



namespace vgGTK
{

namespace field
{

namespace widget
{



template< typename V >
struct Vector : public Widget< V >, public Gtk::HBox
{
	Vector()
	:	m_hasFrame( true )
	{}
	
	~Vector()
	{
		for( EntryContainer::iterator i = m_elements.begin(); i != m_elements.end(); ++i )
		{
			delete *i;
		}
	}
	
	void clear()
	{
		for( EntryContainer::iterator i = m_elements.begin(); i != m_elements.end(); ++i )
		{
			(*i)->set_text( Glib::ustring() );
		}
	}
	
	const V getValue() const
	{
		V	result;
		
		for( unsigned int i = 0; i < m_elements.size(); ++i )
		{
			result[i] = boost::lexical_cast< V::value_type >( m_elements[i]->get_text() );
		}
		
		return result;
	}
	
	
	void setValue( const V & value )
	{
		if( m_elements.empty() )
		{
			m_elements.resize( value.getSize(), 0 );
		}
		
		assert( m_elements.size() == value.getSize() );
		
		for( unsigned int i = 0; i < value.getSize(); ++i )
		{
			Gtk::Entry	* entry = m_elements[i];
			
			if( entry == 0 )
			{
				entry = new Gtk::Entry();
			
				entry->set_width_chars( 10 );
				entry->set_has_frame( m_hasFrame );
			
				add( *entry );
				m_elements[i] = entry;
			}
			
			entry->set_text( Glib::ustring::compose("%1", value[i]) );
		}
	}
	
	const bool validate()
	{
		bool validate = true;
		
		for( unsigned int i = 0; i < m_elements.size() && validate; ++i )
		{
			try
			{
				boost::lexical_cast< V::value_type >( m_elements[i]->get_text() );
			}
			catch( const boost::bad_lexical_cast & )
			{
				showWarning("Please, enter a number!");
				m_elements[i]->grab_focus();
				validate = false;
			}
		}
		
		return validate;
	}
	
	void setFrame( const bool frame )
	{
		m_hasFrame = frame;
		for( EntryContainer::iterator i = m_elements.begin(); i != m_elements.end(); ++i )
		{
			(*i)->set_has_frame( frame );
		}
	}
				
	

private:
	
	typedef std::vector< Gtk::Entry * >	EntryContainer;
	
	bool			m_hasFrame;
	EntryContainer	m_elements;
};



} // namespace widget

} // namespace field

} // namespace vgGTK



#endif // _VGGTK_FIELD_WIDGET_VECTOR_HPP_