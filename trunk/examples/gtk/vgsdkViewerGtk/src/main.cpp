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
#include <gtkmm/paned.h>
#include <gtkmm/treeview.h>

#include <vgDebug/Global.hpp>
#include <vgGTK/Logging.hpp>
#include <vgGTK/graph/Browser.hpp>

#include "vgsdkViewerGtk/actions.hpp"
#include "vgsdkViewerGtk/myCanvas.hpp"



Glib::RefPtr< Gtk::ActionGroup > createDefaultActionGroup( Gtk::Window * topLevel, vgsdkViewerGtk::myCanvas * canvas )
{
	Glib::RefPtr< Gtk::ActionGroup >	actions = Gtk::ActionGroup::create();

	actions->add( Gtk::Action::create("File", "_File")																														);
	actions->add( Gtk::Action::create("New", Gtk::Stock::NEW),								sigc::bind(sigc::ptr_fun(&vgsdkViewerGtk::fileNew), topLevel, canvas)			);
	actions->add( Gtk::Action::create("Open", Gtk::Stock::OPEN),							sigc::bind(sigc::ptr_fun(&vgsdkViewerGtk::fileOpen), topLevel, canvas, true)	);
	actions->add( Gtk::Action::create("Add", Gtk::Stock::ADD),								sigc::bind(sigc::ptr_fun(&vgsdkViewerGtk::fileOpen), topLevel, canvas, false)	);
	actions->add( Gtk::Action::create("Reload",	"Reload"),			Gtk::AccelKey("F5"),	sigc::bind(sigc::ptr_fun(&vgsdkViewerGtk::fileReload), canvas)					);
	actions->add( Gtk::Action::create("ExportGraphviz", "Export Graphviz"),					sigc::bind(sigc::ptr_fun(&vgsdkViewerGtk::fileExportGraphviz), canvas)			);
	actions->add( Gtk::Action::create("Quit", Gtk::Stock::QUIT),							sigc::ptr_fun(&vgsdkViewerGtk::fileExit)										);

	actions->add( Gtk::Action::create("View", "_View")																														);
	actions->add( Gtk::Action::create("ViewAll", Gtk::Stock::ZOOM_FIT, "View _All"),		sigc::bind(sigc::ptr_fun(&vgsdkViewerGtk::viewAll), canvas)						);

	actions->add( Gtk::Action::create("Help", "_Help")																														);
	actions->add( Gtk::Action::create("About", Gtk::Stock::ABOUT),							sigc::bind(sigc::ptr_fun(&vgsdkViewerGtk::helpAbout), topLevel)					);

	return actions;
}

const Glib::ustring & createDefaultUI()
{
	static Glib::ustring	ui =
		"<ui>"
		"  <menubar name='DefaultMenuBar'>"
		"    <menu action='File'>"
		"      <menuitem action='New'/>"
		"      <menuitem action='Open'/>"
		"      <menuitem action='Add'/>"
		"      <menuitem action='Reload'/>"
		"      <separator/>"
		"      <menuitem action='ExportGraphviz'/>"
		"      <separator/>"
		"      <menuitem action='Quit'/>"
		"    </menu>"
		"    <menu action='View'>"
		"      <menuitem action='ViewAll'/>"
		"    </menu>"
		"    <menu action='Help'>"
		"      <menuitem action='About'/>"
		"    </menu>"
		"  </menubar>"
		"  <toolbar name='DefaultToolBar'>"
		"    <toolitem action='New'/>"
		"    <toolitem action='Open'/>"
		"    <toolitem action='Add'/>"
		"    <separator/>"
		"    <toolitem action='ViewAll'/>"
		"    <separator/>"
		"    <toolitem action='About'/>"
		"  </toolbar>"
		"</ui>";

	return ui;
}



int main( int argc, char ** argv )
{
	// Initializes the gtk system.
	Gtk::Main	kit( &argc, &argv );

	// Installs the GTK-based logging.
	vgDebug::set< vgGTK::Logging >();

	// Set the human readable name of the application.
	Glib::set_application_name("vgsdkViewerGtk");


	// Creates the main mainWindow content.
	Gtk::Window						window;
	Gtk::VBox						vbox;
	Gtk::HPaned						hpaned;
	vgGTK::graph::Browser			graphBrowser;
	vgsdkViewerGtk::myCanvas		canvas;
	Gtk::Statusbar					statusBar;


	// Creates the UI manager.
	Glib::RefPtr<Gtk::UIManager>	uiManager = Gtk::UIManager::create();

	uiManager->insert_action_group( createDefaultActionGroup(&window, &canvas) );
	uiManager->add_ui_from_string( createDefaultUI() );


	// Configures the main window.
	window.set_title("vgsdkViewer");
	window.set_reallocate_redraws( true );


	// Creates the main window content.
	window.add( vbox );
	vbox.pack_start( *uiManager->get_widget("/DefaultMenuBar"), false, true );
	vbox.pack_start( *uiManager->get_widget("/DefaultToolBar"), false, true );
	hpaned.pack1( graphBrowser, false, true );
	hpaned.pack2( canvas, true, true );
	vbox.add( hpaned );
	vbox.pack_end( statusBar, false, true );
	window.show_all();


	// Gives the canvas' root node to the graph browser.
	graphBrowser.setRoot( canvas.getRoot() );


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
