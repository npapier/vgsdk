// VGSDK - Copyright (C) 2008, Guillaume Brocker, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#ifndef _VGSDKVIEWERGTK_ACTIONS_HPP_
#define _VGSDKVIEWERGTK_ACTIONS_HPP_



#include <gtkmm/window.h>



namespace vgsdkViewerGtk
{



struct myCanvas;



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
 * @brief	Exports the current scene graph in a graphviz file.
 *
 * @param	canvas	a pointer to the canvs containing the scene to export
 */
void fileExportGraphviz( myCanvas * canvas );

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
 * @brief	Implements a log handler that pushes the message to a statusbar passed in the user data.
 */
void statusbarLogHandler( const gchar *log_domain, GLogLevelFlags log_level, const gchar * message, gpointer user_data );



} // namespace vgsdkViewerGtk

#endif /*_VGSDKVIEWERGTK_ACTIONS_HPP_*/
