// VGSDK - Copyright (C) 2008, 2009, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include "vgGTK/field/widget/Bool.hpp"



namespace vgGTK
{

namespace field
{

namespace widget
{



Bool::Bool()
:	m_trueButton( "_True", true ),
	m_falseButton( "_False", true )
{
	Gtk::RadioButtonGroup	group;
	
	add( m_trueButton );
	add( m_falseButton );
	
	m_trueButton.set_group( group );
	m_falseButton.set_group( group );
}



void Bool::clear()
{
	m_trueButton.set_active( false );
	m_falseButton.set_active( false );
}



const bool Bool::hasValue() const
{
	return m_trueButton.get_active() || m_falseButton.get_active();
}



const bool Bool::getValue() const
{
	return m_trueButton.get_active();
}



void Bool::setValue( const bool & value )
{
	m_trueButton.set_active( value );
	m_falseButton.set_active( !value );
}



const bool Bool::validate()
{
	if( m_trueButton.get_active() == false && m_falseButton.get_active() == false )
	{
		showWarning( "You must select a value." );
		
		return false;
	}
	else
	{
		return true;
	}
}



const bool Bool::resizable() const
{
	return false;
}



void Bool::setFrame( const bool frame )
{}



} // namespace widget

} // namespace field

} // namespace vgGTK
