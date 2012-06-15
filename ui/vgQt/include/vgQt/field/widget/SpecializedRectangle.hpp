// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_FIELD_WIDGET_SPECIALIZEDRECTANGLE_HPP_
#define _VGQT_FIELD_WIDGET_SPECIALIZEDRECTANGLE_HPP_

#include <vgm/Rectangle.hpp>

#include "vgQt/field/widget/convenienceWidget.hpp"

#include "vgQt/field/widget/Widget.hpp"
#include "vgQt/field/widget/Rectangle.hpp"

namespace vgQt
{

namespace field
{

namespace widget
{
/**
 * @brief	Implements a widget for the edition of a rectangle
 */
template< typename T >
struct SpecializedRectangle : public Rectangle, Widget< vgm::Rectangle< T > >
{
    SpecializedRectangle()
    {
        vgQt::configure< T >( m_x );
        vgQt::configure< T >( m_y );
        vgQt::configure< T >( m_width );
        vgQt::configure< T >( m_height );
    }

    const vgm::Rectangle< T > getValue() const
    {
        const T	x		= static_cast< T >( m_x->value() );
        const T	y		= static_cast< T >( m_y->value() );
        const T	width	= static_cast< T >( m_width->value() );
        const T	height	= static_cast< T >( m_height->value() );

        return vgm::Rectangle< T >(x, y, width, height);
    }

    const bool hasValue() const
    {
        return	!(m_x->text().toDouble() == 0			&&
                 m_y->text().toDouble() == 0			&&
                 m_width->text().toDouble() == 0		&&
                 m_height->text().toDouble() == 0);
    }

    void setValue( const vgm::Rectangle< T > & value )
    {
        m_x->setValue( value.x() );
        m_y->setValue( value.y() );
        m_width->setValue( value.width() );
        m_height->setValue( value.height() );
    }

    void clear()
    {
        m_x->setValue( 0 );
        m_y->setValue( 0 );
        m_width->setValue( 0 );
        m_height->setValue( 0 );
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

#endif // _VGQT_FIELD_WIDGET_SPECIALIZEDRECTANGLE_HPP_
