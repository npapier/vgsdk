// VGSDK - Copyright (C) 2008, 2009, 2010, 2011, Guillaume Brocker, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#ifndef _VGSDKVIEWERGTK_ACTIONS_HPP_
#define _VGSDKVIEWERGTK_ACTIONS_HPP_

#include <gtkmm/recentchooser.h>
#include <gtkmm/uimanager.h>
#include <gtkmm/window.h>



namespace vgsdkViewerGtk
{



struct myCanvas;



/**
 * @brief	Handles key release events on the canvas.
 */
bool canvasKeyReleaseEvent( GdkEventKey*, Glib::RefPtr<Gtk::UIManager>, myCanvas* );

/**
 * @brief	Implements an action that quits the application.
 */
void fileExit();

/**
 * @brief	Implements the file/new action.
 *
 * This will ask the user to confirm the reset of the scene, and if confirmed, will
 * remove all objects.
 *
 * @param	topLevel	a pointer to the top level window
 * @param	canvas		a pointer to canvas to update
 */
void fileNew( Gtk::Window * topLevel, myCanvas * canvas );

/**
 * @brief	Implements the file/open action
 *
 * @param	topLevel	a pointer to the top level window
 * @param	canvas		a pointer to the canvas to update
 * @param	clearScene	true to remove any object from the scene
 */
void fileOpen( Gtk::Window * topLevel, myCanvas * canvas, const bool clearScene );

/**
 * @brief	Implements an action that reloads all objects currently in the canvas.
 *
 * @param	canvas	a pointer to the a canvas to update
 */
void fileReload( myCanvas * canvas );

/**
 * @brief	Implements an action that will load a file from the recent chooser menu.
 *
 * @param	recentChooser	a pointer to the recent chooser that triggered the action
 * @param	canvas			a pointer to the canvas whose content is to update
 */
void fileRecent( Gtk::RecentChooser * recentChooser, myCanvas * canvas );

/**
 * @brief	Implements an action that shows the canvas in full screen
 * 
 * @param	canvas			a pointer to the canvas that must be displayed full screen.
 * @param	uiManager		a reference to the ui manager
 * @param	properties		a pointer to the properties widget
 *
 * @remark	The canvas is expected to be a direct child of the top level window.
 */
void fullscreen( myCanvas * canvas, Glib::RefPtr< Gtk::UIManager > uiManager, Gtk::Widget * properties );

/**
 * @brief	Implements an action that will recenter the camera on the objects visible in the scene.
 *
 * @param	canvas	a pointer to the a canvas to update
 */
void viewAll( myCanvas * canvas );

/**
 * @brief	Implements an action that show the about box on top of the given top level window.
 *
 * @param	topLevel	a pointer to a top level window
 */
void helpAbout( Gtk::Window * topLevel );

/**
 * @brief	Drop data received
 *
 * @param	canvas	a pointer to the canvas to update
 *
 * @remark	Other parameters are gtkmm specific.
 */
void dragDataReceived( myCanvas * canvas, const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, const Gtk::SelectionData& selection_data, guint info, guint time );

/**
 * @brief	Show a Dialog when a Collada file is open to select the open mode.
 * @return the open mode (geometry, material, texture, all).
 */
int openOpenCOLLADAFile( );

/**
 * @brief	Updates the resolution of the given canvas.
 *
 * @param	canvas	a pointer to the canvas to update
 */
void setResolution( myCanvas * canvas );

/**
 * @brief	Updates the manipulation bindings of the given canvas.
 *
 * Supported binding identifiers are @c 1 and @c 2.
 *
 * @param	canvas	a pointer to the canvas to update
 * @param	binding	an integer identifiying a binding
 */
void settingManipulationBinding( myCanvas * canvas, const int binding );

/**
 * @brief	Shows/hides the vgSdk properties widget.
 *
 * @param	uiManager		a reference to the ui manager
 * @param	properties		a pointer to the properties widget
 * @param	hiddenForced	true to force the properties to get hidden
 */
void showHideProperties( Glib::RefPtr< Gtk::UIManager > uiManager, Gtk::Widget * properties, const bool hiddenForced );

/**
 * @brief	Implements a log handler that pushes the message to a statusbar passed in the user data.
 */
void statusbarLogHandler( const gchar *log_domain, GLogLevelFlags log_level, const gchar * message, gpointer user_data );

/**
 * @brief	Configure user engine's settings
 */
void renderSettings( Gtk::Window * toplevel, myCanvas * canvas );


} // namespace vgsdkViewerGtk

#endif /*_VGSDKVIEWERGTK_ACTIONS_HPP_*/
