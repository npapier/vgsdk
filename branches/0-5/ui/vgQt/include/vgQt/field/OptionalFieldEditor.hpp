// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_FIELD_OPTIONALFIELDEDITOR_HPP_
#define _VGQT_FIELD_OPTIONALFIELDEDITOR_HPP_

#include <vgd/field/EditorRO.hpp>
#include <vgd/field/EditorRW.hpp>
#include <vgd/field/TOptionalField.hpp>

#include "vgQt/field/FieldEditor.hpp"
#include "vgQt/field/widget/Widget.hpp"

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>

namespace vgQt
{

namespace field
{

/**
 * @brief	Implements a editor for optional fields.
 *
 * The template parameter must specify a vgQt::field::widget::Widget derived type.
 */
template< typename Widget >
struct OptionalFieldEditor : public FieldEditor
{
    OptionalFieldEditor()
    {
        m_box = new QHBoxLayout();
        m_widget = new Widget();
        m_box->addLayout(m_widget);
        m_clear = new QPushButton("&Clear");
        m_box->addWidget(m_clear);

        connect(m_clear, SIGNAL(clicked()), m_widget, SLOT(clear()));
    }

    ~OptionalFieldEditor()
    {
        delete m_box;
    }

    QLayout* getWidget()
    {
        return m_widget;
    }

    QLayout* getLayout()
    {
        return m_box;
    }

    void commit()
    {
        typedef vgd::field::TOptionalField< typename Widget::ValueType > FieldType;

        vgd::field::EditorRW< FieldType >	fieldEditor	= m_fieldManager->getFieldRW< FieldType >( m_fieldName.toStdString() );

        if( m_widget->hasValue() )
        {
            fieldEditor->setValue( m_widget->getValue() );
        }
        else
        {
            fieldEditor->eraseValue();
        }
    }

    void refresh()
    {
        typedef vgd::field::TOptionalField< typename Widget::ValueType > FieldType;

        vgd::field::EditorRO< FieldType >	fieldEditor	= m_fieldManager->getFieldRO< FieldType >( m_fieldName.toStdString() );
        typename Widget::ValueType			value;
        bool								hasValue;

        hasValue = fieldEditor->getValue( value );

        if( hasValue )
        {
            m_widget->setValue( value );
            m_backupValue = value;
        }
        else
        {
            m_widget->clear();
            m_backupValue = boost::optional< typename Widget::ValueType >();
        }
    }

    void rollback()
    {
        typedef vgd::field::TOptionalField< typename Widget::ValueType > FieldType;

        vgd::field::EditorRW< FieldType >	fieldEditor	= m_fieldManager->getFieldRW< FieldType >( m_fieldName.toStdString() );

        if( m_backupValue )
        {
            fieldEditor->setValue( *m_backupValue );
            fieldEditor.release();
            m_widget->setValue( *m_backupValue );
        }
        else
        {
            fieldEditor->eraseValue();
            fieldEditor.release();
            m_widget->clear();
        }
    }

    const bool validate()
    {
        typedef vgd::field::TOptionalField< typename Widget::ValueType > FieldType;

        vgd::field::EditorRO< FieldType >	fieldEditor	= m_fieldManager->getFieldRO< FieldType >( m_fieldName.toStdString() );

        return fieldEditor->hasValue() == false || m_widget->validate();
    }

private:

    QHBoxLayout*                                  	m_box;			///< The root widget.
    QPushButton*                                    m_clear;        ///< The widget to clear the value.
    Widget*                                         m_widget;		///< The widget used to edit the field value, assumed to be a widget::Widget derived class.
    boost::optional< typename Widget::ValueType >	m_backupValue;	///< The backup of the initial field value.
};

} // namespace field

} // namespace vgQt



#endif // _VGQT_FIELD_OPTIONALFIELDEDITOR_HPP_
