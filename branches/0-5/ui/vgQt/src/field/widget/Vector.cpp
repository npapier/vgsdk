// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include "vgQt/field/widget/Vector.hpp"

namespace vgQt
{

namespace field
{

namespace widget
{

Vector::Vector(int N)
{
    for( int i = 0; i < N; ++i )
    {
        m_elements.push_back(new QDoubleSpinBox());
        connect(m_elements[i], SIGNAL(valueChanged(double)), this, SIGNAL(signalChanged()));
        addWidget( m_elements[i] );
    }
}

void Vector::clear()
{
    for( unsigned int i = 0; i != m_elements.size(); ++i )
    {
        m_elements[i]->setValue( 0 );
    }

    Q_EMIT signalChanged();
}

} // namespace widget

} // namespace field

} // namespace vgQt
