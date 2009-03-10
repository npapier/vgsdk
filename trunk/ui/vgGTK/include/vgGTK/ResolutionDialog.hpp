// VGSDK - Copyright (C) 2009, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGGTK_RESOLUTIONDIALOG_HPP_
#define _VGGTK_RESOLUTIONDIALOG_HPP_

#include <gtkmm/button.h>
#include <gtkmm/comboboxentrytext.h>
#include <gtkmm/dialog.h>
#include <gtkmm/widget.h>

#include "vgGTK/vgGTK.hpp"



namespace vgGTK
{



struct VGGTK_API ResolutionDialog : public Gtk::Dialog
{
	/**
	 * @brief	Constructor
	 *
	 * @param	widget	a pointer to the widget to change its resolution
	 */
	ResolutionDialog( Gtk::Widget * widget );
	
private:

	/**
	 * @name	Edition widgets
	 */
	//@{
	Gtk::Button				m_resetButton;	///< Allows to reset the widget to its original size.
	Gtk::Button				m_applyButton;	///< Allows to apply the desired resolution.
	Gtk::ComboBoxEntryText	m_resolutions;	///< Allows the user to define a resolution.
	//@}

	/**
	 * @name	Widget whose resolution is being edited
	 */
	//@{
	Gtk::Widget					* m_widget;			///< Points to the widget o edit.
	const std::pair< int, int >	m_oldResolution;	///< Holds the original widget resolution.
	std::pair< int, int >		m_newResolution;	///< Holds the resolution to apply on the widget.
	//@}
	
	/**
	 * @name	Signal handlers
	 */
	//@{
	void applyClicked();
	void resetClicked();
	void resolutionChanged();
	//@}
	
	/**
	 * @name	Helpers
	 */
	//@{
	static void applyResolution( Gtk::Widget * widget, const int width, const int height );			///< Applyes the resolution on the given widget.
	static const bool resolutionFromString( const Glib::ustring & str, int & width, int & height );	///< Parses the given string to extract the resolution and tells if it succeeded.
	static const Glib::ustring resolutionToString( const int width, const int height );				///< Builds the string representing the given resolution.
	//@}
};



} // namespace vgGTK



#endif // _VGGTK_RESOLUTIONDIALOG_HPP_
