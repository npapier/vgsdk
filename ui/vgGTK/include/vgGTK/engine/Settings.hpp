// VGSDK - Copyright (C) 2008, Guillaume Brocker, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef VGGTK_ENGINE_SETTINGS_HPP
#define VGGTK_ENGINE_SETTINGS_HPP

#include <gtkmm/box.h>

#include "vgGTK/vgGTK.hpp"

namespace Gtk
{
	class CheckButton;
}

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
struct VGGTK_API Settings : public Gtk::VBox
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
	void onGLSL();

	void onDisableTexture();

	void onBench();

	void onShowFPS();
	void onDebugEvents();
	void onClearGLResources();

	void onCaptureButton();
	//@}

	/**
	 * @brief	Refreshes sensitiveness of child widgets.
	 */
	void refreshChildrenSensitiveness();

	Gtk::CheckButton	* m_glslButton;			///< Button to enable/disable glsl rendering pipeline
	Gtk::CheckButton	* m_disableTexture;		///< Button to disable texture
	Gtk::CheckButton	* m_showFPS;			///< Widget to choose which debug overlay must be displayed
	Gtk::CheckButton	* m_debugEvents;		///< Button to enable/disable event logging
	Gtk::CheckButton	* m_captureButton;		///< Widget to enable screenshot/video capture hotkey
};



} // namespace engine

} // namespace vgGTK

#endif // VGGTK_ENGINE_SETTINGS_HPP