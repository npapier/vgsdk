// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_FIELD_SINGLEFIELDEDITOR_HPP_
#define _VGQT_FIELD_SINGLEFIELDEDITOR_HPP_

#include <vgd/field/EditorRO.hpp>
#include <vgd/field/EditorRW.hpp>
#include <vgd/field/TSingleField.hpp>

#include "vgQt/field/FieldEditor.hpp"
#include "vgQt/field/widget/Widget.hpp"

#include <QWidget>

namespace vgQt
{

namespace field
{

/**
 * @brief	Abstract editor for vgd::field::TSingleField<T>.
 */
template< typename Widget >
struct SingleFieldEditor : public FieldEditor
{
    SingleFieldEditor()
    {
        m_widget = new Widget();
    }

    ~SingleFieldEditor()
    {
        delete m_widget;
    }

    QLayout* getWidget()
	{
        return m_widget;
	}

    QLayout* getLayout()
    {
        return m_widget;
    }

    void commit()
    {
        setField( m_widget->getValue() );
    }
	
    void refresh()
    {
        typedef vgd::field::TSingleField< typename Widget::ValueType > FieldType;

        vgd::field::EditorRO< FieldType > fieldEditor = m_fieldManager->getFieldRO< FieldType >( m_fieldName.toStdString() );
        m_backupValue = fieldEditor->getValue();
        fieldEditor.release();

        m_widget->setValue( m_backupValue );
    }

    void rollback()
    {
        setField( m_backupValue );
        m_widget->setValue( m_backupValue );
    }

    const bool validate()
    {
        return m_widget->validate();
    }

private:

    Widget*						m_widget;		///< The widget used to edit the field value, assumed to be a widget::Widget derived class.
    typename Widget::ValueType	m_backupValue;	///< The backup of the initial field value.

    /**
     * @brief	Assigns a given value to the field to edit.
     */
    void setField( const typename Widget::ValueType & value )
    {
        typedef vgd::field::TSingleField< typename Widget::ValueType > FieldType;

        vgd::field::EditorRW< FieldType > fieldEditor = m_fieldManager->getFieldRW< FieldType >( m_fieldName.toStdString() );

        fieldEditor->setValue( value );
    }
};

} // namespace field

} // namespace vgQt



#endif // _VGQT_FIELD_SINGLEFIELDEDITOR_HPP_
