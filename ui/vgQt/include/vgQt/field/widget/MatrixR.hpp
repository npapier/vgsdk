// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller


#ifndef _VGQT_FIELD_WIDGET_MATRIXR_HPP_
#define _VGQT_FIELD_WIDGET_MATRIXR_HPP_

#include <vgm/Matrix.hpp>

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
 * @brief	Implements a widget for edition vgd::field::Enum edition.
 */
struct MatrixR : public QVBoxLayout, public Widget< vgm::MatrixR >
{
Q_OBJECT
public:
    MatrixR();

    const vgm::MatrixR getValue() const;
    const bool hasValue() const;
    void setValue( const vgm::MatrixR & value );
    const bool validate();

private:
    QDoubleSpinBox*	m_elements[16];	///< Entry widgets for matrix elements.

public Q_SLOTS:
    void onIdentity();
    void onNull();
    void clear();

Q_SIGNALS:
    void signalChanged();
};



} // namespace widget

} // namespace field

} // namespace vgQt



#endif // _VGQT_FIELD_WIDGET_MATRIXR_HPP_
