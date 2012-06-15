// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller


#ifndef _VGQT_FIELD_WIDGET_BOOL_HPP_
#define _VGQT_FIELD_WIDGET_BOOL_HPP_

#include "vgQt/field/widget/Widget.hpp"

#include <QRadioButton>
#include <QVBoxLayout>

namespace vgQt
{

namespace field
{

namespace widget
{

/**
 * @brief	Implements a widget for boolean edition.
 */
struct Bool : public QVBoxLayout, public Widget< bool >
{
Q_OBJECT
public:
	Bool();

    const bool getValue() const;
    const bool hasValue() const;
    void setValue( const bool & value );
    const bool validate();

private:
    QRadioButton*	m_trueButton;	///< Maps the true value.
    QRadioButton*   m_falseButton;	///< Maps the false value

public Q_SLOTS:
    void clear();

Q_SIGNALS:
    void signalChanged();
};



} // namespace widget

} // namespace field

} // namespace vgQt



#endif // _VGQT_FIELD_WIDGET_BOOL_HPP_
