// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include "vgQt/field/widget/String.hpp"

namespace vgQt
{

namespace field
{

namespace widget
{

String::String()
{
    m_entry = new QLineEdit();
    m_textView = new QTextEdit();
    m_textView->setVisible(false);
    m_multiLineButton = new QCheckBox("Multi-line");

    addWidget(m_entry);
    addWidget(m_textView);
    addWidget(m_multiLineButton);

    connect(m_entry, SIGNAL(textChanged(const QString &)), this, SIGNAL(signalChanged()));
    connect(m_textView, SIGNAL(textChanged()), this, SIGNAL(signalChanged()));

    connect(m_multiLineButton, SIGNAL(toggled(bool)), this, SLOT(onMultiLineToggled()));
}

void String::clear()
{
    m_entry->setText(tr(""));
    m_textView->setText(tr(""));

    Q_EMIT signalChanged();
}

const std::string String::getValue() const
{
    return isMultiLine() ? m_textView->toPlainText().toStdString() : m_entry->text().toStdString();
}

const bool String::hasValue() const
{
    return m_entry->text().isEmpty() == false;
}

void String::setValue( const std::string & value )
{
    m_entry->setText(QString(value.c_str()));
    m_textView->setText(QString(value.c_str()));

    Q_EMIT signalChanged();
}

const bool String::validate()
{
    return true;
}

void String::onMultiLineToggled()
{
    setMultiLine( m_multiLineButton->isChecked() );
}

void String::setMultiLine( const bool multi )
{
    if( multi )
    {
        m_entry->setVisible(false);
        m_textView->setVisible(true);
        m_textView->setText(m_entry->text());
    }
    else
    {
        m_textView->setVisible(false);
        m_entry->setVisible(true);
        m_entry->setText(m_textView->toPlainText());
    }
}

const bool String::isMultiLine() const
{
    return m_multiLineButton->isChecked();
}

} // namespace widget

} // namespace field

} // namespace vgQt

