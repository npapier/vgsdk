// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_FIELD_WIDGET_SPECIALIZEDVECTOR_HPP_
#define _VGQT_FIELD_WIDGET_SPECIALIZEDVECTOR_HPP_

#include <vgm/Vector.hpp>

#include "vgQt/field/widget/convenienceWidget.hpp"

#include "vgQt/field/widget/Vector.hpp"
#include "vgQt/field/widget/Widget.hpp"

namespace vgQt
{

namespace field
{

namespace widget
{
/**
 * @brief	Implements a widget for the edition of a vector
 */
template< typename T, int N >
struct SpecializedVector : public Vector, Widget< vgm::Vector< T, N > >
{
    SpecializedVector() : Vector( N )
    {
        for( unsigned int i = 0; i < m_elements.size(); ++i)
        {
            vgQt::configure< T >( m_elements[i] );
        }
    }

    const vgm::Vector< T, N > getValue() const
    {
        vgm::Vector< T, N >	result;

        for( unsigned int i = 0; i < m_elements.size(); ++i )
        {
            result[i] = static_cast< T >( m_elements[i]->value() );
        }

        return result;
    }

    const bool hasValue() const
    {
        for( unsigned int i = 0; i != m_elements.size(); ++i )
        {
            if( m_elements[i]->text().isEmpty() == false )
            {
                return true;
            }
        }

        return false;
    }

    void setValue( const vgm::Vector< T, N > & value )
    {
        for( unsigned int i = 0; i < m_elements.size(); ++i )
        {
            m_elements[i]->setValue( value[i] );
        }
    }

    void clear()
    {
        for( unsigned int i = 0; i != m_elements.size(); ++i )
        {
            m_elements[i]->setValue( 0 );
        }
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

#endif // _VGQT_FIELD_WIDGET_SPECIALIZEDVECTOR_HPP_
