// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include "vgQt/field/widget/Rectangle.hpp"
#include <QLabel>

namespace vgQt
{

namespace field
{

namespace widget
{

Rectangle::Rectangle()
{
    m_x = new QDoubleSpinBox();
    m_y = new QDoubleSpinBox();
    m_width = new QDoubleSpinBox();
    m_height = new QDoubleSpinBox();

    QLabel * positionLabel = new QLabel(tr("Position"));
    QLabel * sizeLabel = new QLabel(tr("Size"));
    QLabel * xLabel = new QLabel(tr("x"));
    QLabel * yLabel = new QLabel(tr("y"));
    QLabel * widthLabel = new QLabel(tr("width"));
    QLabel * heightLabel = new QLabel(tr("height"));

    addWidget(positionLabel, 0, 0);
    addWidget(sizeLabel, 0, 2);
    addWidget(xLabel, 1, 0);
    addWidget(m_x, 1, 1);
    addWidget(widthLabel, 1, 2);
    addWidget(m_width, 1, 3);
    addWidget(yLabel, 2, 0);
    addWidget(m_y, 2, 1);
    addWidget(heightLabel, 2, 2);
    addWidget(m_height, 2, 3);

    connect(m_x, SIGNAL(valueChanged(double)), this, SIGNAL(signalChanged()));
    connect(m_y, SIGNAL(valueChanged(double)), this, SIGNAL(signalChanged()));
    connect(m_width, SIGNAL(valueChanged(double)), this, SIGNAL(signalChanged()));
    connect(m_height, SIGNAL(valueChanged(double)), this, SIGNAL(signalChanged()));
}

Rectangle::~Rectangle()
{
//    m_x->disconnect();
//    m_y->disconnect();
//    m_width->disconnect();
//    m_height->disconnect();
}

void Rectangle::clear()
{
    m_x->setValue( 0 );
    m_y->setValue( 0 );
    m_width->setValue( 0 );
    m_height->setValue( 0 );

    Q_EMIT signalChanged();
}

} // namespace widget

} // namespace field

} // namespace vgQt
