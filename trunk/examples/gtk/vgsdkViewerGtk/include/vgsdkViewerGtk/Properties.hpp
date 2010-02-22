// VGSDK - Copyright (C) 2010, Guillaume Brocker, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGSDKVIEWERGTK_PROPERTIES_HPP_
#define _VGSDKVIEWERGTK_PROPERTIES_HPP_

#include <gtkmm/box.h>
#include <vgGTK/Notebook.hpp>



namespace vgsdkViewerGtk
{

struct myCanvas;



/**
 * @brief	A widget that holds the vgSdk propteries notbeook and allows to request the widget to hide or close.
 */
struct Properties : public Gtk::VBox
{
	/**
	 * @brief	Constructor
	 */
	Properties();

	/**
	 * @brief	Assignes the canvas.
	 */
	void setCanvas( myCanvas & canvas );

	/**
	 * @brief	Retrieves the signal triggered when the user clicks the close box.
	 */
	sigc::signal<void> & signalClose();

private:

	vgGTK::Notebook		m_notebook;
	sigc::signal<void>	m_signalClose;
};



} // namespace vgdkViewerGtk



#endif // _VGSDKVIEWERGTK_PROPERTIES_HPP_
