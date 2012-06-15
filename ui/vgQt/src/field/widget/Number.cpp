// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include "vgQt/field/widget/Number.hpp"

namespace vgQt
{

namespace field
{

namespace widget
{

Number::Number()
{
    m_spinbox = new QDoubleSpinBox();
    addWidget(m_spinbox);

    connect(m_spinbox, SIGNAL(valueChanged(double)), this, SIGNAL(signalChanged()));
}

void Number::buttonClicked()
{
    Q_EMIT signalChanged();
}

void Number::clear()
{
    m_spinbox->setValue(0);
    Q_EMIT signalChanged();
}

} // namespace widget

} // namespace field

} // namespace vgQt
