// VGSDK - Copyright (C) 2008, 2009, 2010, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGGTK_FIELD_SINGLEFIELDEDITOR_HPP_
#define _VGGTK_FIELD_SINGLEFIELDEDITOR_HPP_

#include <vgd/field/EditorRO.hpp>
#include <vgd/field/EditorRW.hpp>
#include <vgd/field/TSingleField.hpp>

#include "vgGTK/field/FieldEditor.hpp"



namespace vgGTK
{

namespace field
{



/**
 * @brief	Abstract editor for vgd::field::TSingleField<T>.
 */
template< typename Widget >
struct SingleFieldEditor : public FieldEditor
{
	Gtk::Widget& getWidget()
	{
		return m_widget;
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
		setField( m_widget.getValue() );
	}
	
	void refresh()
	{
		assert( m_fieldManager != false );
		assert( m_fieldName.empty() == false );
	
		typedef vgd::field::TSingleField< typename Widget::ValueType > FieldType;

		vgd::field::EditorRO< FieldType > fieldEditor = m_fieldManager->getFieldRO< FieldType >( m_fieldName );
		m_backupValue = fieldEditor->getValue();
		fieldEditor.release();
	
		m_widget.setValue( m_backupValue );
	}

	void rollback()
	{
		setField( m_backupValue );
		m_widget.setValue( m_backupValue );
	}

	sigc::signal< void > & signalChanged()
	{
		return m_widget.signalChanged();
	}
	
	const bool validate()
	{
		return m_widget.validate();
	}
	

private:

	Widget						m_widget;		///< The widget used to edit the field value, assumed to be a widget::Widget derived class.
	typename Widget::ValueType	m_backupValue;	///< The backup of the initial field value.


	/**
	 * @brief	Assigns a given value to the field to edit.
	 */
	void setField( const typename Widget::ValueType & value )
	{
		assert( m_fieldManager != false );
		assert( m_fieldName.empty() == false );
	
		typedef vgd::field::TSingleField< typename Widget::ValueType > FieldType;
		
		vgd::field::EditorRW< FieldType > fieldEditor = m_fieldManager->getFieldRW< FieldType >( m_fieldName );
	
		fieldEditor->setValue( value );
	}
};



} // namespace field

} // namespace vgGTK



#endif // _VGGTK_FIELD_SINGLEFIELDEDITOR_HPP_
