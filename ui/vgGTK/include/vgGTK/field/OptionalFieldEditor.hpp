// VGSDK - Copyright (C) 2009, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGGTK_FIELD_OPTIONALFIELDEDITOR_HPP_
#define _VGGTK_FIELD_OPTIONALFIELDEDITOR_HPP_

#include <gtkmm/alignment.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>

#include "vgGTK/field/Editor.hpp"



namespace vgGTK
{

namespace field
{



/**
 * @brief	Implements a editor for optional fields.
 *
 * The template parameter must specify a vgGTK::field::widget::Widget derived type.
 */
template< typename Widget >
struct OptionalFieldEditor : public Editor
{
	OptionalFieldEditor()
	:	m_box( false, 12 ),
		m_clear( Gtk::Stock::CLEAR )
	{
		Gtk::Alignment	* alignment = Gtk::manage( new Gtk::Alignment(0.5, 1.0, 1.0, 0.0) );

		m_box.add( m_widget );
		m_box.pack_end( *alignment, Gtk::PACK_SHRINK );

		alignment->add( m_clear );

		m_clear.signal_clicked().connect( sigc::mem_fun(this, &OptionalFieldEditor<Widget>::clearClicked) );
	}

	Gtk::Widget& getWidget()
	{
		return m_box;
	}
	
	void grabFocus()
	{
		m_widget.grab_focus();
	}
	
	const bool resizable() const
	{
		return m_widget.resizable();
	}
	
	void commit()
	{
		assert( m_fieldManager != false );
		assert( m_fieldName.empty() == false );
	
		typedef vgd::field::TOptionalField< typename Widget::ValueType > FieldType;

		vgd::field::EditorRW< FieldType >	fieldEditor	= m_fieldManager->getFieldRW< FieldType >( m_fieldName );

		if( m_widget.hasValue() )
		{
			fieldEditor.get()->setValue( m_widget.getValue() );
		}
		else
		{
			fieldEditor.get()->eraseValue();
		}
	}
	
	void refresh()
	{
		assert( m_fieldManager != false );
		assert( m_fieldName.empty() == false );
	
		typedef vgd::field::TOptionalField< typename Widget::ValueType > FieldType;

		vgd::field::EditorRO< FieldType >	fieldEditor	= m_fieldManager->getFieldRO< FieldType >( m_fieldName );
		Widget::ValueType					value;
		bool								hasValue;

		hasValue = fieldEditor.get()->getValue( value );

		if( hasValue )
		{
			m_widget.setValue( value );
		}
		else
		{
			m_widget.clear();
		}
	}
	
	const bool validate()
	{
		assert( m_fieldManager != false );
		assert( m_fieldName.empty() == false );
	
		typedef vgd::field::TOptionalField< typename Widget::ValueType > FieldType;

		vgd::field::EditorRO< FieldType >	fieldEditor	= m_fieldManager->getFieldRO< FieldType >( m_fieldName );

		return fieldEditor.get()->hasValue() == false || m_widget.validate();
	}

private:

	Gtk::HBox	m_box;		///< The root widget.
	Gtk::Button	m_clear;	///< The widget to clear the value.
	Widget		m_widget;	///< The edition widget.

	void clearClicked()
	{
		m_widget.clear();
	}
};



} // namespace field

} // namespace vgGTK



#endif // _VGGTK_FIELD_OPTIONALFIELDEDITOR_HPP_
