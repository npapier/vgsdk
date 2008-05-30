// VGSDK - Copyright (C) 2008, Guillaume Brocker, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef VGGTK_ENGINE_SETTINGS_HPP
#define VGGTK_ENGINE_SETTINGS_HPP

#include <gtkmm/buttonbox.h>

#include "vgGTK/vgGTK.hpp"

namespace vgUI
{
	struct Canvas;
}



namespace vgGTK
{

namespace engine
{



/**
 * @brief	A widget allowing to configure rendering engine's settings.
 */
struct VGGTK_API Settings : public Gtk::VButtonBox
{
	/**
	 * @brief	Constructor
	 */
	Settings();
	
	/**
	 * @brief	Assignes the canvas used for rendering
	 *
	 * @param	canvas	a pointer to a canvas
	 */
	void setCanvas( vgUI::Canvas * canvas );
	
	
private:

	vgUI::Canvas	* m_canvas;	///< Points to the rendering canvas.
	
	/**
	 * @name	Signal Handlers
	 */
	//@{
	void onBench();	///< Handles the bench button's activation.
	//@}
	
	/**
	 * @brief	Refreshes sensitiveness of child widgets.
	 */
	void refreshChildrenSensitiveness();
};



} // namespace engine

} // namespace vgGTK

#endif // VGGTK_ENGINE_SETTINGS_HPP