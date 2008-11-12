// VGSDK - Copyright (C) 2008, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGGTK_FIELD_SINGLEFIELDEDITOR_HPP_
#define _VGGTK_FIELD_SINGLEFIELDEDITOR_HPP_

#include <vgd/field/EditorRO.hpp>
#include <vgd/field/EditorRW.hpp>
#include <vgd/field/TSingleField.hpp>

#include "vgGTK/field/Editor.hpp"



namespace vgGTK
{

namespace field
{



/**
 * @brief	Abstract editor for vgd::field::TSingleField<T>.
 */
template< typename Widget >
struct SingleFieldEditor : public Editor
{
	Gtk::Widget& getWidget()
	{
		return m_widget;
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
	
		typedef vgd::field::TSingleField< Widget::ValueType > FieldType;
		
		vgd::field::EditorRW< FieldType >	fieldEditor	= m_fieldManager->getFieldRW< FieldType >( m_fieldName );
	
		return fieldEditor.get()->setValue( m_widget.getValue() );
	}
	
	void refresh()
	{
		assert( m_fieldManager != false );
		assert( m_fieldName.empty() == false );
	
		typedef vgd::field::TSingleField< Widget::ValueType > FieldType;

		vgd::field::EditorRO< FieldType >	fieldEditor	= m_fieldManager->getFieldRO< FieldType >( m_fieldName );
	
		m_widget.setValue( fieldEditor.get()->getValue() );
	}
	
	const bool validate()
	{
		return m_widget.validate();
	}
	

private:

	Widget	m_widget;	///< The widget used to edit the field value, assumed to be a widget::Widget derived class.
};



} // namespace field

} // namespace vgGTK



#endif // _VGGTK_FIELD_SINGLEFIELDEDITOR_HPP_
