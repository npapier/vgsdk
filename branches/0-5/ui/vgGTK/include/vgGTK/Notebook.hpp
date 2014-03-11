// VGSDK - Copyright (C) 2008, 2009, Guillaume Brocker, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#ifndef _VGGTK_NOTEBOOK_HPP_
#define _VGGTK_NOTEBOOK_HPP_

#include <gtkmm/notebook.h>
#include <vgd/Shp.hpp>
#include <vgGTK/graph/Browser.hpp>
#include <vgGTK/Properties.hpp>


namespace vgd
{
	namespace node
	{
		struct Group;
	}
}

namespace vgUI
{
	struct BasicManipulator;
}



namespace vgGTK
{



/**
 * @brief	Implements a notebook that provides pages to browse a vgSDK graph and
 *		to configure properties of the rendering engine.
 */
struct VGGTK_API Notebook : public Gtk::Notebook
{
	/**
	 * @brief	Constructor
	 */
	Notebook();

	/**
	 * @brief	Assignes the canvas that is used for the rendering.
	 *
	 * @param	canvas	a reference to a canvas
	 */
	void setCanvas( vgUI::BasicManipulator & canvas );
	
	
private:

	vgGTK::graph::Browser		m_graphBrowser;		///< the graph browser widget
	vgGTK::Properties			m_properties;
};



} // namespace vgGTK

#endif //  _VGGTK_NOTEBOOK_HPP_
