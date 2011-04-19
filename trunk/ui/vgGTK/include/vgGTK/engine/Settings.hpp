// VGSDK - Copyright (C) 2008, 2009, 2011, Guillaume Brocker, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

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
GTKMM_BEGIN_CLASS()
struct VGGTK_API Settings : public Gtk::VBox
{
	/**
	 * @brief	Constructor
	 */
	Settings();
	
	/**
	 * @brief	Assignes the canvas used for rendering
	 *
	 * @param	canvas	a pointer to a canvas, null if none
	 */
	void setCanvas( vgUI::Canvas * canvas );
	
	
private:

	vgUI::Canvas	* m_canvas;	///< Points to the rendering canvas.
	
	/**
	 * @name	Signal Handlers
	 */
	//@{
	void onGLSL();

	void onDisableLighting();
	void onDisableTexture();
	void onDisableShadow();
	void onDisableDisplayList();
	void onDisableVBO();
	void onDisableDepthPrePass();

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

	Gtk::CheckButton	* m_disableLighting;	///< Button to disable lighting in engine
	Gtk::CheckButton	* m_disableTexture;		///< Button to disable texture in engine
	Gtk::CheckButton	* m_disableShadow;		///< Button to disable shadow in engine

	Gtk::CheckButton	* m_disableDisplayList;	///< Button to disable display list in engine
	Gtk::CheckButton	* m_disableVBO;			///< Button to disable VBO in engine
	Gtk::CheckButton	* m_disableDepthPrePass;///< Button to disable depth pre-pass in engine

	Gtk::CheckButton	* m_showFPS;			///< Widget to choose which debug overlay must be displayed
	Gtk::CheckButton	* m_debugEvents;		///< Button to enable/disable event logging
	Gtk::CheckButton	* m_captureButton;		///< Widget to enable screenshot/video capture hotkey
};
GTKMM_END_CLASS()



} // namespace engine

} // namespace vgGTK

#endif // VGGTK_ENGINE_SETTINGS_HPP
