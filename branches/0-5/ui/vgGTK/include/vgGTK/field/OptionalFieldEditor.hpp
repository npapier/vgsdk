// VGSDK - Copyright (C) 2009, 2010, 2011, Guillaume Brocker, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#ifndef _VGGTK_FIELD_OPTIONALFIELDEDITOR_HPP_
#define _VGGTK_FIELD_OPTIONALFIELDEDITOR_HPP_

#include <gtkmm/alignment.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/stock.h>

#include <vgd/field/TOptionalField.hpp>
#include "vgGTK/field/FieldEditor.hpp"



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
struct OptionalFieldEditor : public FieldEditor
{
	OptionalFieldEditor()
	:	m_box( false, 12 ),
		m_clear( Gtk::Stock::CLEAR )
	{
		Gtk::Alignment	* alignment = Gtk::manage( new Gtk::Alignment(0.5, 1.0, 1.0, 0.0) );

		m_box.add( m_widget );
		m_box.pack_end( *alignment, Gtk::PACK_SHRINK );

		alignment->add( m_clear );

		m_clear.signal_clicked().connect( sigc::mem_fun(&m_widget, &Widget::clear) );
	}

	Gtk::Widget& getWidget()
	{
		return m_box;
	}
	
	void grabFocus()
	{
		m_widget.grabFocus();
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
			fieldEditor->setValue( m_widget.getValue() );
		}
		else
		{
			fieldEditor->eraseValue();
		}
	}
	
	void refresh()
	{
		assert( m_fieldManager != false );
		assert( m_fieldName.empty() == false );
	
		typedef vgd::field::TOptionalField< typename Widget::ValueType > FieldType;

		vgd::field::EditorRO< FieldType >	fieldEditor	= m_fieldManager->getFieldRO< FieldType >( m_fieldName );
		typename Widget::ValueType			value;
		bool								hasValue;

		hasValue = fieldEditor->getValue( value );

		if( hasValue )
		{
			m_widget.setValue( value );
			m_backupValue = value;
		}
		else
		{
			m_widget.clear();
			m_backupValue = boost::optional< typename Widget::ValueType >();
		}
	}

	void rollback()
	{
		assert( m_fieldManager != false );
		assert( m_fieldName.empty() == false );
	
		typedef vgd::field::TOptionalField< typename Widget::ValueType > FieldType;

		vgd::field::EditorRW< FieldType >	fieldEditor	= m_fieldManager->getFieldRW< FieldType >( m_fieldName );

		if( m_backupValue )
		{
			fieldEditor->setValue( *m_backupValue );
			fieldEditor.release();
			m_widget.setValue( *m_backupValue );
		}
		else
		{
			fieldEditor->eraseValue();
			fieldEditor.release();
			m_widget.clear();
		}
	}

	sigc::signal< void > & signalChanged()
	{
		return m_widget.signalChanged();
	}
	
	const bool validate()
	{
		assert( m_fieldManager != false );
		assert( m_fieldName.empty() == false );
	
		typedef vgd::field::TOptionalField< typename Widget::ValueType > FieldType;

		vgd::field::EditorRO< FieldType >	fieldEditor	= m_fieldManager->getFieldRO< FieldType >( m_fieldName );

		return fieldEditor->hasValue() == false || m_widget.validate();
	}

private:

	Gtk::HBox										m_box;			///< The root widget.
	Gtk::Button										m_clear;		///< The widget to clear the value.
	Widget											m_widget;		///< The edition widget.
	boost::optional< typename Widget::ValueType >	m_backupValue;	///< Holds a backup of the initial field value.
};



} // namespace field

} // namespace vgGTK



#endif // _VGGTK_FIELD_OPTIONALFIELDEDITOR_HPP_
