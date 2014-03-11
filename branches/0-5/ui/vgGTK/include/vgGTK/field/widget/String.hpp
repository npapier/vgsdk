// VGSDK - Copyright (C) 2008, 2009, 2010, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGGTK_FIELD_WIDGET_STRING_HPP_
#define _VGGTK_FIELD_WIDGET_STRING_HPP_

#include <gtkmm/box.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/entry.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/textview.h>

#include "vgGTK/field/widget/Widget.hpp"



namespace vgGTK
{

namespace field
{

namespace widget
{



/**
 * @brief	Implements a widget for std::string edition.
 */
struct String : public Widget< std::string >, public Gtk::VBox
{
	String();

	/**
	 * @brief	Tells if the widget is in multiline edition mode.
	 */
	const bool isMultiLine() const;

	/**
	 * @brief	Switch the multi-line edition mode.
	 */
	void setMultiLine( const bool multi = true );
	
	void clear();
	const bool hasValue() const;
	const std::string getValue() const;
	void setValue( const std::string & value );
	const bool validate();
	
	void grabFocus();
	const bool resizable() const;
	void setFrame( const bool frame );

protected:

	Gtk::Entry			m_entry;				///< The widget for the single line edition mode.
	Gtk::TextView		m_textView;				///< The widget for the multi-line edition mode.
	Gtk::ScrolledWindow	m_textViewScroll;		///< The widget for scrolling multi-line edition widget .
	Gtk::CheckButton	m_multiLineButton;		///< The widget for toggling multi/single line edition mode.
	bool				m_ignoreTextChanges;	///< Tells to ignore text changes.

	/**
	 * @name	Signal handlers
	 */
	//@{
	void onMultiLineToggled();	///< Handles multi-line toggle button changes.
	void onTextChanged();		///< Handles text changes.
	//@}

	void show_all_vfunc();	///< Overriden to manage custom child visibility
};



} // namespace widget

} // namespace field

} // namespace vgGTK



#endif // _VGGTK_FIELD_WIDGET_STRING_HPP_
