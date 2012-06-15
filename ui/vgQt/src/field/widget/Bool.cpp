// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include "vgQt/field/widget/Bool.hpp"

#include <QVBoxLayout>

namespace vgQt
{

namespace field
{

namespace widget
{

Bool::Bool()
{
    m_trueButton = new QRadioButton( "True" );
    m_falseButton = new QRadioButton( "False" );
    addWidget(m_trueButton);
    addWidget(m_falseButton);

    connect(m_trueButton, SIGNAL(clicked()), this, SIGNAL(signalChanged()));
    connect(m_falseButton, SIGNAL(clicked()), this, SIGNAL(signalChanged()));
}

void Bool::clear()
{
    m_trueButton->setCheckable(false);
    m_trueButton->update();
    m_trueButton->setCheckable(true);

    m_falseButton->setCheckable(false);
    m_falseButton->update();
    m_falseButton->setCheckable(true);

    Q_EMIT signalChanged();
}

const bool Bool::getValue() const
{
    return m_trueButton->isChecked();
}

const bool Bool::hasValue() const
{
    return ( m_trueButton->isChecked() || m_falseButton->isChecked() );
}

void Bool::setValue( const bool & value )
{
    m_trueButton->setChecked( value );
    m_falseButton->setChecked( !value );

    Q_EMIT signalChanged();
}


const bool Bool::validate()
{
    if ( ! m_trueButton->isChecked() && ! m_falseButton->isChecked())
    {
        return false;
    }
    else
    {
        return true;
    }
}

} // namespace widget

} // namespace field

} // namespace vgQt
