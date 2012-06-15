// VGSDK - Copyright (C) 2008, 2009, 2010, Guillaume Brocker, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#ifndef _VGQT_FIELD_WIDGET_NUMBER_HPP_
#define _VGQT_FIELD_WIDGET_NUMBER_HPP_

#include <vgBase/Type.hpp>

#include "vgQt/graph/convenience.hpp"
#include "vgQt/field/widget/Widget.hpp"

#include <QVBoxLayout>
#include <QDoubleSpinBox>

namespace vgQt
{

namespace field
{

namespace widget
{

/**
 * @brief	Implements a widget for the edition of any number type.
 */

struct Number : public QVBoxLayout
{
Q_OBJECT
public:
    Number();

protected:
    QDoubleSpinBox*       m_spinbox;

public Q_SLOTS:
    void buttonClicked();
    void clear();

Q_SIGNALS:
    void signalChanged();

};

} // namespace widget

} // namespace field

} // namespace vgQt

#endif // _VGQT_FIELD_WIDGET_NUMBER_HPP_
