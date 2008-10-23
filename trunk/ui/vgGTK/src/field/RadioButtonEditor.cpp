// VGSDK - Copyright (C) 2008, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include "vgGTK/field/RadioButtonEditor.hpp"



namespace vgGTK
{

namespace field
{



RadioButtonEditor::RadioButtonEditor()
:	m_box(),
	m_trueButton( "_True", true ),
	m_falseButton( "_False", true )
{
	Gtk::RadioButtonGroup	group;
	
	m_box.add( m_trueButton );
	m_box.add( m_falseButton );
	
	m_trueButton.set_group( group );
	m_falseButton.set_group( group );
}



Gtk::Widget& RadioButtonEditor::getWidget()
{
	return m_box;
}



void RadioButtonEditor::grabFocus()
{
	if( m_trueButton.get_active() )
	{
		m_trueButton.grab_focus();
	}
	else if( m_falseButton.get_active() )
	{
		m_falseButton.grab_focus();
	}
	else
	{
		m_trueButton.grab_focus();
	}
}



void RadioButtonEditor::commit()
{
	setFieldValue< bool >( m_trueButton.get_active() );
}



void RadioButtonEditor::refresh()
{
	if( getFieldValue< bool >() )
	{
		m_trueButton.set_active( true );
	}
	else
	{
		m_falseButton.set_active( true );
	}
}



} // namespace field

} // namespace vgGTK
