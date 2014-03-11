// VGSDK - Copyright (C) 2009, 2010, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include "vgGTK/field/widget/Enum.hpp"



namespace vgGTK
{

namespace field
{

namespace widget
{


	
Enum::Enum()
{
	// Should do the widget creation job here.
}



void Enum::clear()
{
	for( EntryContainer::const_iterator i = m_entries.begin(); i != m_entries.end(); ++i )
	{
		i->second->set_inconsistent( true );
	}
	m_signalChanged.emit();
}



const vgd::field::Enum Enum::getValue() const
{
	// Scans entry widgets to get the one active, 
	// and if there is one, return the associated enumeration value.
	for( EntryContainer::const_iterator i = m_entries.begin(); i != m_entries.end(); ++i )
	{
		if( i->second->get_active() && i->second->get_inconsistent() == false )
		{
			return vgd::field::Enum( i->first );
		}
	}

	// Default response.
	return vgd::field::Enum();
}



void Enum::grabFocus()
{
	for( EntryContainer::const_iterator i = m_entries.begin(); i != m_entries.end(); ++i )
	{
		if( i->second->get_active() || i->second->get_inconsistent() )
		{
			i->second->grab_focus();
			break;
		}
	}
}



const bool Enum::hasValue() const
{
	// Scans entry widgets to see if there is one begin active.
	for( EntryContainer::const_iterator i = m_entries.begin(); i != m_entries.end(); ++i )
	{
		if( i->second->get_active() && i->second->get_inconsistent() == false )
		{
			return true;
		}
	}

	// Default response.
	return false;
}



void Enum::onButtonClicked()
{
	for( EntryContainer::const_iterator i = m_entries.begin(); i != m_entries.end(); ++i )
	{
		i->second->set_inconsistent( false );
	}

	m_signalChanged.emit();
}



const bool Enum::resizable() const
{
	return false;
}



void Enum::setFrame( const bool frame )
{
	// Nothing to be done.
}



void Enum::setValue( const vgd::field::Enum & value )
{
	// First, check the entries for the enumeration values have been created.
	// This should be done in the constructor.
	if( m_entries.empty() )
	{
		typedef std::vector< std::pair< int, std::string > >	EnumEntries;
		
		const EnumEntries		entries = value.valuesAndStrings();
		Gtk::RadioButton::Group	radioGroup;

		for( EnumEntries::const_iterator i = entries.begin(); i != entries.end(); ++i )
		{
			Gtk::RadioButton	* radioButton = Gtk::manage( new Gtk::RadioButton(i->second) );

			radioButton->set_group( radioGroup );
			radioButton->signal_clicked().connect( sigc::mem_fun(this, &Enum::onButtonClicked) );

			add( *radioButton );
			m_entries.push_back( Entry(i->first, radioButton) );
		}


		// Shows all chid widgets.
		show_all();
	}


	// Assignes the new value.
	for( EntryContainer::iterator i = m_entries.begin(); i != m_entries.end(); ++i )
	{
		i->second->set_active( vgd::field::Enum(i->first) == value );
		i->second->set_inconsistent( false );
	}

	// Notifies about the change.
	m_signalChanged.emit();
}



const bool Enum::validate()
{
	return true;
}



} // namespace widget

} // namespace field

} // namespace vgGTK
