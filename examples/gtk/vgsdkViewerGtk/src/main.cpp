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
#include <gtkmm/recentchoosermenu.h>
#include <gtkmm/recentmanager.h>
#include <gtkmm/treeview.h>

#include <vgDebug/Global.hpp>
#include <vgGTK/Logging.hpp>

#include "vgsdkViewerGtk/actions.hpp"
#include "vgsdkViewerGtk/myCanvas.hpp"
#include "vgsdkViewerGtk/Notebook.hpp"




bool myRecentFilter( const Gtk::RecentFilter::Info& filter_info )
{
	const Glib::ustring							applicationName	= Glib::get_application_name();
	std::list< Glib::ustring >::const_iterator	found			= std::find( filter_info.applications.begin(), filter_info.applications.end(), applicationName );

	return found != filter_info.applications.end();
}



Glib::RefPtr< Gtk::ActionGroup > createDefaultActionGroup( Gtk::Window * topLevel, vgsdkViewerGtk::myCanvas * canvas )
{
	Glib::RefPtr< Gtk::ActionGroup >	actions = Gtk::ActionGroup::create();

	actions->add( Gtk::Action::create("File", "_File") );
	actions->add(
			Gtk::Action::create("New", Gtk::Stock::NEW),
			sigc::bind(sigc::ptr_fun(&vgsdkViewerGtk::fileNew), topLevel, canvas) );
	actions->add(
			Gtk::Action::create("Open", Gtk::Stock::OPEN),
			sigc::bind(sigc::ptr_fun(&vgsdkViewerGtk::fileOpen), topLevel, canvas, true) );
	actions->add(
			Gtk::Action::create("Add", Gtk::Stock::ADD),
			sigc::bind(sigc::ptr_fun(&vgsdkViewerGtk::fileOpen), topLevel, canvas, false) );
	actions->add(
			Gtk::Action::create("Recent", "Recent Files") );
	actions->add(
			Gtk::Action::create("Reload", "Reload"),
			Gtk::AccelKey("F5"),
			sigc::bind(sigc::ptr_fun(&vgsdkViewerGtk::fileReload), canvas) );
	actions->add(
			Gtk::Action::create("Quit", Gtk::Stock::QUIT),
			sigc::ptr_fun(&vgsdkViewerGtk::fileExit) );

	actions->add( Gtk::Action::create("View", "_View") );
	actions->add( 
			Gtk::Action::create("ViewAll", Gtk::Stock::ZOOM_FIT, "View _All"),
			sigc::bind(sigc::ptr_fun(&vgsdkViewerGtk::viewAll), canvas) );
	actions->add(
			Gtk::Action::create("FullScreen", Gtk::Stock::FULLSCREEN, "Full Screen"),
			Gtk::AccelKey("F11"),
			sigc::bind(sigc::ptr_fun(&vgsdkViewerGtk::fullScreen), canvas) );
			
	Gtk::RadioButtonGroup	manipulationBindingGroup;
	actions->add( Gtk::Action::create("Settings", "_Settings") );
	actions->add(
			Gtk::RadioAction::create(manipulationBindingGroup, "MouseAndKeyboardManipulation", "Mouse & Keyboard Manipulation"),
			sigc::bind(sigc::ptr_fun(&vgsdkViewerGtk::settingManipulationBinding), canvas, 1) );
	actions->add(
			Gtk::RadioAction::create(manipulationBindingGroup, "MouseOnlyManipulation", "Mouse Only Manipuation"),
			sigc::bind(sigc::ptr_fun(&vgsdkViewerGtk::settingManipulationBinding), canvas, 2) );

	actions->add( Gtk::Action::create("Help", "_Help") );
	actions->add(
			Gtk::Action::create("About", Gtk::Stock::ABOUT),
			sigc::bind(sigc::ptr_fun(&vgsdkViewerGtk::helpAbout), topLevel) );

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
		"      <menu action='Recent'/>"
		"      <menuitem action='Reload'/>"
		"      <separator/>"
		"      <menuitem action='Quit'/>"
		"    </menu>"
		"    <menu action='View'>"
		"      <menuitem action='ViewAll'/>"
		"      <menuitem action='FullScreen'/>"
		"    </menu>"
		"    <menu action='Settings'>"
		"      <menuitem action='MouseOnlyManipulation'/>"
		"      <menuitem action='MouseAndKeyboardManipulation'/>"
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
		"    <toolitem action='FullScreen'/>"
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
	Glib::set_application_name("vgsdkViewer");


	// Creates the main mainWindow content.
	Gtk::Window					window;
	Gtk::VBox					vbox;
	Gtk::HPaned					hpaned;
	vgsdkViewerGtk::Notebook	notebook;
	vgsdkViewerGtk::myCanvas	canvas;
	Gtk::Statusbar				statusBar;


	// Creates the UI manager.
	Glib::RefPtr<Gtk::UIManager>	uiManager = Gtk::UIManager::create();

	uiManager->insert_action_group( createDefaultActionGroup(&window, &canvas) );
	uiManager->add_ui_from_string( createDefaultUI() );


	// Creates and appends the recent files sub-menu. The rencent items will be filtered
	// to show only items added by this application. Also connect a signal handler to
	// load a selected entry.
// @todo	Why is the filtering not working ?
//	Gtk::RecentFilter			recentFilter;
	Gtk::RecentChooserMenu		recentChooserMenu( Gtk::RecentManager::get_default() );
	Gtk::Widget					* recentWidget		= uiManager->get_widget("/DefaultMenuBar/File/Recent");
	Gtk::MenuItem				* recentMenuItem	= dynamic_cast< Gtk::MenuItem * >( recentWidget );

//	recentFilter.add_application( Glib::get_application_name() );
//	recentChooserMenu.add_filter( recentFilter );
//	recentChooserMenu.set_filter( recentFilter );
	recentChooserMenu.set_sort_type( Gtk::RECENT_SORT_MRU );
	recentChooserMenu.signal_item_activated().connect( sigc::bind(sigc::ptr_fun(&vgsdkViewerGtk::fileRecent), &recentChooserMenu, &canvas) );
	recentMenuItem->set_submenu( recentChooserMenu );
	recentMenuItem->property_visible() = true;
	
	
	// Configures the notebook widget.
	notebook.set_border_width( 2 );
	notebook.set_size_request( 333, 0 );


	// Configures the main window.
	window.add_accel_group( uiManager->get_accel_group() );
	window.set_title("vgsdkViewer");
	window.set_reallocate_redraws( true );


	// Creates the main window content.
	window.add( vbox );
	vbox.pack_start( *uiManager->get_widget("/DefaultMenuBar"), false, true );
	vbox.pack_start( *uiManager->get_widget("/DefaultToolBar"), false, true );
	hpaned.pack1( notebook, false, true );
	hpaned.pack2( canvas, true, true );
	vbox.add( hpaned );
	vbox.pack_end( statusBar, false, true );
	window.show_all();
	
	
	// Activates the first manipulation binding action.
	Glib::RefPtr< Gtk::Action >	manipulationBindingAction = uiManager->get_action("/DefaultMenuBar/Settings/MouseAndKeyboardManipulation");
	
	if( manipulationBindingAction )
	{
		manipulationBindingAction->activate();
	}
	else
	{
		vgDebug::get().logWarning("Unable to initialize manipulation bindings.");
	}


	// Gives the canvas' root node to the notebook.
	notebook.setCanvas( canvas );


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
