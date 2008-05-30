// VGSDK - Copyright (C) 2008, Guillaume Brocker, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGSDKVIEWERGTK_NOTEBOOK_HPP
#define _VGSDKVIEWERGTK_NOTEBOOK_HPP

#include <gtkmm/notebook.h>
#include <vgd/Shp.hpp>
#include <vgGTK/engine/Settings.hpp>
#include <vgGTK/graph/Browser.hpp>

namespace vgd
{
	namespace node
	{
		struct Group;
	}
}

namespace vgUI
{
	struct Canvas;
}



namespace vgsdkViewerGtk
{



/**
 * @brief	Implements a notebook that provides pages to browse a vgSDK graph and
 *		to configure the rendering engine.
 */
struct Notebook : public Gtk::Notebook
{
	/**
	 * @brief	Constrcutor
	 */
	Notebook();

	/**
	 * @brief	Assignes the canvas that is used for the rendering.
	 *
	 * @param	canvas	a reference to a canvas
	 */
	void setCanvas( vgUI::Canvas & canvas );
	
	
private:

	vgGTK::engine::Settings	m_engineSettings;	///< the engine settings widget.
	vgGTK::graph::Browser	m_graphBrowser;		///< The graph browser widget.
};



} // namespace vgsdkViewerGtk

#endif //  _VGSDKVIEWERGTK_NOTEBOOK_HPP
