// VGSDK - Copyright (C) 2008, 2009, 2010, Guillaume Brocker, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#ifndef _VGQT_FIELD_WIDGET_RECTANGLE_HPP_
#define _VGQT_FIELD_WIDGET_RECTANGLE_HPP_

#include <vgBase/Type.hpp>

#include "vgQt/graph/convenience.hpp"
#include "vgQt/field/widget/Widget.hpp"

#include <QGridLayout>
#include <QDoubleSpinBox>

namespace vgQt
{

namespace field
{

namespace widget
{

/**
 * @brief	Implements a widget for vgm::Rectangle edition.
 */

struct Rectangle : public QGridLayout
{
Q_OBJECT
public:
    Rectangle();
    ~Rectangle();

protected:
    QDoubleSpinBox * m_x;
    QDoubleSpinBox * m_y;
    QDoubleSpinBox * m_width;
    QDoubleSpinBox * m_height;

public Q_SLOTS:
    void clear();

Q_SIGNALS:
    void signalChanged();

};

} // namespace widget

} // namespace field

} // namespace vgQt

#endif // _VGQT_FIELD_WIDGET_RECTANGLE_HPP_
