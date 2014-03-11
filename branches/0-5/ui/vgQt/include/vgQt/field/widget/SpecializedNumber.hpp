// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_FIELD_WIDGET_SPECIALIZEDNUMBER_HPP_
#define _VGQT_FIELD_WIDGET_SPECIALIZEDNUMBER_HPP_

#include "vgQt/field/widget/convenienceWidget.hpp"

#include "vgQt/field/widget/Widget.hpp"
#include "vgQt/field/widget/Number.hpp"

namespace vgQt
{

namespace field
{

namespace widget
{

/**
 * @brief	Implements a widget for the edition of any number type.
 */
template< typename NumberType >
struct SpecializedNumber : public Number, Widget< NumberType >
{
    SpecializedNumber()
    {
        vgQt::configure< NumberType >( m_spinbox );
    }

    const NumberType getValue() const
    {
        return static_cast< NumberType >( m_spinbox->value() );
    }

    const bool hasValue() const
    {
        return true;
    }

    void setValue( const NumberType & value )
    {
        m_spinbox->setValue( value );
    }

    void clear()
    {
        m_spinbox->setValue(0);
    }

    const bool validate()
    {
        return true;
    }

    void signalChanged(){}

};

} // namespace widget

} // namespace field

} // namespace vgQt

#endif // _VGQT_FIELD_WIDGET_SPECIALIZEDNUMBER_HPP_
