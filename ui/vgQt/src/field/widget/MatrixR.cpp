// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include <boost/lexical_cast.hpp>

#include "vgQt/field/widget/MatrixR.hpp"
#include "vgQt/field/widget/convenienceWidget.hpp"

#include <QHBoxLayout>
#include <QPushButton>

namespace vgQt
{

namespace field
{

namespace widget
{



MatrixR::MatrixR()
{
    // Creates the matrix edition controls layout.
    QHBoxLayout	* rows[4];

    rows[0] = new QHBoxLayout();
    rows[1] = new QHBoxLayout();
    rows[2] = new QHBoxLayout();
    rows[3] = new QHBoxLayout();

    for( int i = 0; i < 16; ++i )
    {
        m_elements[i] = new QDoubleSpinBox();
        vgQt::configure< float >( m_elements[i] );
        connect(m_elements[i], SIGNAL(valueChanged(double)), this, SIGNAL(signalChanged()));
        rows[i/4]->addWidget( m_elements[i] );
    }

    addLayout(rows[0]);
    addLayout(rows[1]);
    addLayout(rows[2]);
    addLayout(rows[3]);

    QHBoxLayout* hButtonBox = new QHBoxLayout();
    QPushButton* identityButton = new QPushButton("&Identity");
    QPushButton* nullButton = new QPushButton("&Null");

    hButtonBox->addWidget(identityButton);
    hButtonBox->addWidget(nullButton);

    connect(identityButton, SIGNAL(clicked()), this, SLOT(onIdentity()));
    connect(nullButton, SIGNAL(clicked()), this, SLOT(onNull()));

    addLayout(hButtonBox);
}



void MatrixR::clear()
{
    for(int i = 0; i < 16; ++i)
    {
        m_elements[i]->setValue(0);
    }
    Q_EMIT signalChanged();
}



const vgm::MatrixR MatrixR::getValue() const
{
    vgm::MatrixR	result;

    for( int i = 0; i < 16; ++i )
    {
        result(i/4, i%4) = static_cast< float >( m_elements[i]->value() );
    }

    return result;
}

const bool MatrixR::hasValue() const
{
    for(int i = 0; i < 16; ++i)
    {
        if( m_elements[i]->text().isEmpty() == false )
        {
            return true;
        }
    }

    return false;
}

void MatrixR::setValue( const vgm::MatrixR & value )
{
    for(int i = 0; i < 16; ++i)
    {
        m_elements[i]->setValue( value(i/4, i%4) );
    }
    Q_EMIT signalChanged();
}

const bool MatrixR::validate()
{
    return true;
}

void MatrixR::onIdentity()
{
    vgm::MatrixR	identity;

    identity.setIdentity();
    setValue( identity );
}

void MatrixR::onNull()
{
    vgm::MatrixR	null( 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 );

    setValue( null );
}

} // namespace widget

} // namespace field

} // namespace vgQt

