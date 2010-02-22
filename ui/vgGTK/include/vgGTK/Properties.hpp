// VGSDK - Copyright (C) 2009, Guillaume Brocker, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#ifndef _VGGTK_PROPERTIES_HPP_
#define _VGGTK_PROPERTIES_HPP_

#include <gtkmm/scrolledwindow.h>

#include "vgGTK/engine/Settings.hpp"
#include "vgGTK/node/LightModelEditor.hpp"
#include "vgGTK/node/DrawStyleEditor.hpp"

namespace vgUI
{
	struct BasicViewer;
}



namespace vgGTK
{

/**
 * @brief Properties for vgsdk rendering.
 */
struct VGGTK_API Properties : public Gtk::ScrolledWindow
{
	/**
	 * @brief	Constructor
	 */
	Properties();

	/**
	 * @brief	Assignes the canvas to configure.
	 *
	 * @param	canvas	a pointer to a canvas, null if none.
	 */
	void setCanvas( vgUI::BasicViewer * canvas );


private:

	vgGTK::engine::Settings			m_engineSettingsEditor;
	vgGTK::node::DrawStyleEditor	m_drawStyleEditor;
	vgGTK::node::LightModelEditor	m_lightModelEditor;
};

} // namespace vgGTK



#endif // _VGGTK_PROPERTIES_HPP_
