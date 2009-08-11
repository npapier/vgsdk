// VGSDK - Copyright (C) 2008, 2009, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGGTK_FIELD_WIDGET_WIDGET_HPP_
#define _VGGTK_FIELD_WIDGET_WIDGET_HPP_

#include <gtkmm/messagedialog.h>



namespace vgGTK
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
	typedef T ValueType;	///< Defines the value type symbolic name.
	
	/**
	 * @name	Value Accessors
	 */
	//@{
	virtual void clear() = 0;						///< Clears the widget content.
	virtual const T getValue() const = 0;			///< Retrieves the current widget value.
	virtual const bool hasValue() const = 0;		///< Tells if the widget is currently holding a value.
	virtual void setValue( const T & value ) = 0;	///< Assigns a new value to the widget.
	virtual const bool validate() = 0;				///< Asks the widget if the current value is valid.
	//@}
	
	/**
	 * @name	Aspect Accessors
	 */
	//@{
	virtual const bool resizable() const = 0;		///< Tells if the widget supports changing its size.
	virtual void setFrame( const bool frame ) = 0;	///< Tells the widget to show (or hide) its border frame.
	//@}
	
protected:

	/**
	 * @brief	Shows the given message as a warning.
	 */
	static void showWarning( const Glib::ustring & message, const bool use_markup = false )
	{
		Gtk::MessageDialog	dialog( message, use_markup, Gtk::MESSAGE_WARNING );
		
		dialog.set_title( "Error" );
		dialog.run();
	}
};



} // namespace widget

} // namespace field

} // namespace vgGTK



#endif // _VGGTK_FIELD_WIDGET_WIDGET_HPP_
