// VGSDK - Copyright (C) 2008, Guillaume Brocker, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#include <cassert>

#include <gtk/gtk.h>

#include <gtkmm.h>
#include <gtkmm/container.h>
#include <gtkmm/menu.h>
#include <gtkmm/menuitem.h>

#include <vgDebug/Global.hpp>
#include <vgGTK/Logging.hpp>

#include "vgsdkViewerGtk/actions.hpp"
#include "vgsdkViewerGtk/myCanvas.hpp"



void fill( Gtk::Window * topLevel, Gtk::MenuBar & menuBar, vgsdkViewerGtk::myCanvas * canvas )
{
	using Gtk::AccelKey;
	using Gtk::Menu;
	using Gtk::Menu_Helpers::MenuElem;
	using Gtk::Menu_Helpers::MenuList;
	using Gtk::Menu_Helpers::SeparatorElem;

	// File menu creation.
	Menu		* fileMenu = Gtk::manage( new Gtk::Menu() );
	MenuList	& fileList = fileMenu->items();

	fileList.push_back( MenuElem("_New...",  AccelKey("<control>N"), sigc::bind(sigc::ptr_fun(&vgsdkViewerGtk::fileNew), topLevel, canvas) ) );
	fileList.push_back( MenuElem("_Open...", AccelKey("<control>O"), sigc::bind(sigc::ptr_fun(&vgsdkViewerGtk::fileOpen), topLevel, canvas, true) ) );
	fileList.push_back( MenuElem("_Add...",  AccelKey("<control>A"), sigc::bind(sigc::ptr_fun(&vgsdkViewerGtk::fileOpen), topLevel, canvas, false) ) );
	fileList.push_back( MenuElem("_Reload",  AccelKey("F5"),         sigc::bind(sigc::ptr_fun(&vgsdkViewerGtk::fileReload), canvas) ) );
	fileList.push_back( SeparatorElem() );
	fileList.push_back( MenuElem("E_xit...", AccelKey("<alt>X"),     sigc::ptr_fun(&vgsdkViewerGtk::fileExit) ) );


	// View menu creation.
	Menu		* viewMenu = Gtk::manage( new Gtk::Menu() );
	MenuList	& viewList = viewMenu->items();

	viewList.push_back( MenuElem("View _All", sigc::bind(sigc::ptr_fun(&vgsdkViewerGtk::viewAll), canvas)) );


	// Help menu creation
	Menu		* helpMenu = Gtk::manage( new Gtk::Menu() );
	MenuList	& helpList = helpMenu->items();

	helpList.push_back( MenuElem("About...", sigc::bind(sigc::ptr_fun(&vgsdkViewerGtk::helpAbout), topLevel)) );


	// Fills the menu bar.
	MenuList	& menuBarList = menuBar.items();

	menuBarList.push_back( MenuElem("_File", *fileMenu) );
	menuBarList.push_back( MenuElem("_View", *viewMenu) );
	menuBarList.push_back( MenuElem("_Help", *helpMenu) );
}


int main( int argc, char ** argv )
{
	// Initializes the gtk system.
	Gtk::Main	kit( &argc, &argv );

	// Installs the GTK-based logging.
	vgDebug::set< vgGTK::Logging >();

	// Set the human readable name of the application.
	Glib::set_application_name("vgsdkViewerGtk");

	std::cout << Glib::get_application_name() << std::endl;
	std::cout << Glib::get_prgname() << std::endl;

	// Creates the main mainWindow content.
	Gtk::Window						window;
	Gtk::VBox						vbox;
	Gtk::MenuBar					menuBar;
	vgsdkViewerGtk::myCanvas		canvas;
	Gtk::Statusbar					statusBar;

	fill( &window, menuBar, &canvas );

	window.set_title("vgsdkViewer GTK");
	window.set_reallocate_redraws( true );
	window.add( vbox );
	vbox.pack_start( menuBar, false, true );
	vbox.add( canvas );
	vbox.pack_end( statusBar, false, true );
	window.show_all();


	// Activates drag and drop on the main window.
	std::vector< Gtk::TargetEntry >	targetEntries;

	targetEntries.push_back( Gtk::TargetEntry("text/plain") );
	targetEntries.push_back( Gtk::TargetEntry("text/uri-list") );
	targetEntries.push_back( Gtk::TargetEntry("STRING") );

	window.drag_dest_set( targetEntries, Gtk::DEST_DEFAULT_DROP );
	window.signal_drag_data_received().connect( sigc::bind<0>(sigc::ptr_fun(&vgsdkViewerGtk::dragDataReceived), &canvas) );

	// Installs our status bar log handler.
	g_log_set_handler(
			0,
			(GLogLevelFlags) (G_LOG_LEVEL_MESSAGE|G_LOG_LEVEL_INFO|G_LOG_LEVEL_WARNING|G_LOG_FLAG_RECURSION),
			vgsdkViewerGtk::statusbarLogHandler,
			& statusBar
		);


	// Enters the main loop.
	Gtk::Main::run( window );
 	return 0;
}
