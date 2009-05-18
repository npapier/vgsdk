// VGSDK - Copyright (C) 2008, Guillaume Brocker.
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



template< typename T >
struct Widget
{
	typedef T ValueType;	///< Defines the value type symbolic name.
	
	/**
	 * @name	Value Accessors
	 */
	//@{
	virtual void clear() = 0;
	virtual const T getValue() const = 0;
	virtual void setValue( const T & value ) = 0;
	virtual const bool validate() = 0;
	//@}
	
	/**
	 * @name	Aspect Accessors
	 */
	//@{
	virtual const bool resizable() const = 0;
	virtual void setFrame( const bool frame ) = 0;
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