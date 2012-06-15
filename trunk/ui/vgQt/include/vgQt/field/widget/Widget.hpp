// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_FIELD_WIDGET_WIDGET_HPP_
#define _VGQT_FIELD_WIDGET_WIDGET_HPP_

#include <QWidget>


namespace vgQt
{

namespace field
{

namespace widget
{



/**
 * @brief	Abstract implementation of edition widgets.
 */
template< typename T >
struct Widget
{	
    typedef T                           ValueType;	///< Defines the value type symbolic name.

    virtual void clear() = 0;						///< Clears the widget content.
    virtual const T getValue() const = 0;			///< Retrieves the current widget value.
    virtual const bool hasValue() const = 0;		///< Tells if the widget is currently holding a value.
    virtual void setValue( const T & value ) = 0;	///< Assigns a new value to the widget.
    virtual const bool validate() = 0;				///< Asks the widget if the current value is valid.

    /**
     * @brief	Retrieves the signal emited when the widget content has changed
     */
    virtual void signalChanged() = 0;
};



} // namespace widget

} // namespace field

} // namespace vgQt



#endif // _VGQT_FIELD_WIDGET_WIDGET_HPP_
