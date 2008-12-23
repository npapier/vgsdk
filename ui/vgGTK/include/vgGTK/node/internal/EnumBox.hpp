// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGGTK_NODE_INTERNAL_ENUMBOX_HPP_
#define _VGGTK_NODE_INTERNAL_ENUMBOX_HPP_

#include <map>
#include <vector>

#include <gtkmm/box.h>
#include <gtkmm/radiobutton.h>



namespace vgGTK
{

namespace node
{

namespace internal
{



/**
 * @brief	Implements a widget that allows to represent and select enumeration values with radio buttons.
 */
template< typename EnumType >
struct EnumBox : public Gtk::VBox
{
	typedef std::pair< EnumType, std::string >			Value;
	typedef std::vector< Value >						ValueContainer;
	typedef sigc::slot< void, const EnumType >			SlotChanged;
	
	
private:
	typedef std::map< EnumType, Gtk::RadioButton * >	ButtonContainer;
	
	ButtonContainer	m_buttons;
	
	
public:
	
	EnumBox( const ValueContainer & values, SlotChanged slotChanged )
	{
		Gtk::RadioButtonGroup	radioGroup;
		
		for( typename ValueContainer::const_iterator i = values.begin(); i != values.end(); ++i )
		{
			Gtk::RadioButton	* button = Gtk::manage( new Gtk::RadioButton(radioGroup, i->second) );
			
			m_buttons[ i->first ] = button;
			add( *button );
			button->signal_clicked().connect( sigc::bind(slotChanged, i->first) );
		}
	}
	
	const EnumType getValue() const
	{
		EnumType	result;
		
		for( typename ButtonContainer::const_iterator i = m_buttons.begin(); i != m_buttons.end(); ++i )
		{
			if( i->second->get_active() )
			{
				result = i->first;
				break;
			}
		}
		return result;
	}
	
	void setValue( const EnumType & value )
	{
		typename ButtonContainer::iterator	found = m_buttons.find( value );
		
		if( found != m_buttons.end() )
		{
			found->second->set_active();
		}
	}
};




} // namespace internal

} // namespace noce

} // namespace vgGTK



#endif /*_VGGTK_NODE_INTERNAL_ENUMBOX_HPP_*/
