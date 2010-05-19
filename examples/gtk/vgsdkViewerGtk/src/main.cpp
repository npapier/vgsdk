// VGSDK - Copyright (C) 2008, 2009, 2010, Guillaume Brocker, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#include <cassert>

#include <gtk/gtk.h>

#include <gtkmm.h>
#include <gtkmm/container.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/menu.h>
#include <gtkmm/menuitem.h>
#include <gtkmm/paned.h>
#include <gtkmm/recentchoosermenu.h>
#include <gtkmm/recentmanager.h>
#include <gtkmm/treeview.h>

#include <vgDebug/Global.hpp>
#include <vgGTK/event/sdl.hpp>
#include <vgGTK/Logging.hpp>
#include <vgGTK/node/EditMenu.hpp>

#include "vgsdkViewerGtk/actions.hpp"
#include "vgsdkViewerGtk/myCanvas.hpp"
#include "vgsdkViewerGtk/Properties.hpp"
#include "vgsdkViewerGtk/stock/stock.hpp"



/*bool myRecentFilter( const Gtk::RecentFilter::Info& filter_info )
{
	const Glib::ustring							applicationName	= Glib::get_application_name();
	std::list< Glib::ustring >::const_iterator	found			= std::find( filter_info.applications.begin(), filter_info.applications.end(), applicationName );

	return found != filter_info.applications.end();
}*/



Glib::RefPtr< Gtk::ActionGroup > createDefaultActionGroup( Glib::RefPtr< Gtk::UIManager > uiManager, Gtk::Window * topLevel, vgsdkViewerGtk::myCanvas * canvas, vgsdkViewerGtk::Properties * properties )
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
			Gtk::AccelKey("<control>R"),
			sigc::bind(sigc::ptr_fun(&vgsdkViewerGtk::fileReload), canvas) );
	actions->add(
			Gtk::Action::create("Quit", Gtk::Stock::QUIT),
			sigc::ptr_fun(&vgsdkViewerGtk::fileExit) );

	actions->add( Gtk::Action::create("Edit", "_Edit") );

	Gtk::RadioButtonGroup	viewModeGroup;
	actions->add( Gtk::Action::create("View", "_View") );
	actions->add( 
			Gtk::Action::create("ViewAll", Gtk::Stock::ZOOM_FIT, "View _All"),
			sigc::bind(sigc::ptr_fun(&vgsdkViewerGtk::viewAll), canvas) );
	actions->add(
			Gtk::Action::create("FullScreen", Gtk::Stock::FULLSCREEN, "Full Screen"),
			Gtk::AccelKey("F11"),
			sigc::bind(sigc::ptr_fun(&vgsdkViewerGtk::fullscreen), canvas) );
	actions->add(
			Gtk::Action::create("SetResolution", vgsdkViewerGtk::stock::RESOLUTION, "Set Resolution"),
			sigc::bind(sigc::ptr_fun(&vgsdkViewerGtk::setResolution), canvas) );
	actions->add(
			Gtk::ToggleAction::create("Properties", Gtk::Stock::PROPERTIES),
			sigc::bind(sigc::ptr_fun(&vgsdkViewerGtk::showHideProperties), uiManager, properties, false) );
	actions->add(
			Gtk::RadioAction::create(viewModeGroup, "SingleView", vgsdkViewerGtk::stock::SINGLE_VIEW, "Single View"),
			sigc::bind(sigc::mem_fun(canvas,&vgsdkViewerGtk::myCanvas::setViewMode), vgsdkViewerGtk::myCanvas::SINGLE_VIEW) );
	actions->add(
			Gtk::RadioAction::create(viewModeGroup, "MultiViewSided", vgsdkViewerGtk::stock::MULTI_VIEW_SIDED, "Left-Sided Views"),
			sigc::bind(sigc::mem_fun(canvas,&vgsdkViewerGtk::myCanvas::setViewMode), vgsdkViewerGtk::myCanvas::LEFT_SIDED_VIEWS) );
	actions->add(
			Gtk::RadioAction::create(viewModeGroup, "MultiViewSquared", vgsdkViewerGtk::stock::MULTI_VIEW_SQUARED, "Four Views"),
			sigc::bind(sigc::mem_fun(canvas,&vgsdkViewerGtk::myCanvas::setViewMode), vgsdkViewerGtk::myCanvas::SQUARED_VIEWS) );
			
	Gtk::RadioButtonGroup	manipulationBindingGroup;
	actions->add( Gtk::Action::create("Settings", "_Settings") );
	actions->add(
			Gtk::RadioAction::create(manipulationBindingGroup, "MouseAndKeyboardManipulation", "Mouse & Keyboard Manipulation"),
			sigc::bind(sigc::ptr_fun(&vgsdkViewerGtk::settingManipulationBinding), canvas, 1) );
	actions->add(
			Gtk::RadioAction::create(manipulationBindingGroup, "MouseOnlyManipulation", "Mouse Only Manipulation"),
			sigc::bind(sigc::ptr_fun(&vgsdkViewerGtk::settingManipulationBinding), canvas, 2) );

	actions->add(
			Gtk::Action::create("UserSettings", Gtk::Stock::PROPERTIES, "User Settings"),
			sigc::bind(sigc::ptr_fun(&vgsdkViewerGtk::userSettings), topLevel, canvas) );

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
		"    <menu name='EditMenu' action='Edit'/>"
		"    <menu action='View'>"
		"      <menuitem action='Properties'/>"
		"      <separator/>"
		"      <menuitem action='ViewAll'/>"
		"      <menuitem action='FullScreen'/>"
		"      <menuitem action='SetResolution'/>"
		"      <separator/>"
		"      <menuitem action='SingleView'/>"
		"      <menuitem action='MultiViewSided'/>"
		"      <menuitem action='MultiViewSquared'/>"
		"    </menu>"
		"    <menu action='Settings'>"
		"      <menuitem action='MouseOnlyManipulation'/>"
		"      <menuitem action='MouseAndKeyboardManipulation'/>"
		"      <separator/>"
		"      <menuitem action='UserSettings'/>"
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
		"    <toolitem action='Properties'/>"
		"    <toolitem action='UserSettings'/>"
		"    <separator/>"
		"    <toolitem action='ViewAll'/>"
		"    <toolitem action='FullScreen'/>"
		"    <toolitem action='SetResolution'/>"
		"    <separator/>"
		"    <toolitem action='SingleView'/>"
		"    <toolitem action='MultiViewSided'/>"
		"    <toolitem action='MultiViewSquared'/>"
		"    <separator/>"
		"    <toolitem action='About'/>"
		"  </toolbar>"
		"</ui>";

	return ui;
}



int main( int argc, char ** argv )
{
	// Glib thread system initialization.
	//Glib::thread_init();

	// Initializes the gtk system.
	Gtk::Main	kit( &argc, &argv );

	// Installs the GTK-based logging.
	vgDebug::set< vgGTK::Logging >();

	// Another initialization thing.
	vgGTK::event::initSDL();

	// Set the human readable name of the application.
	Glib::set_application_name("vgsdkViewer");

	// Initializes the local stock icons.
	vgsdkViewerGtk::stock::initialize();

	// Forces the language to english to avoid half translate interfaces.
	Glib::setenv("LANG", "en");

	// Creates the main content.
	Gtk::Window					window;
	Gtk::VBox					vbox;
	Gtk::HPaned					hpaned;
	Gtk::HBox					hbox;
	Gtk::DrawingArea			atiFullScreenTrick;
	vgsdkViewerGtk::Properties	properties;
	vgsdkViewerGtk::myCanvas	canvas;
	Gtk::Statusbar				statusBar;

	// Creates the UI manager.
	Glib::RefPtr<Gtk::UIManager>	uiManager = Gtk::UIManager::create();

	uiManager->insert_action_group( createDefaultActionGroup(uiManager, &window, &canvas, &properties) );
	uiManager->add_ui_from_string( createDefaultUI() );


	// Creates and appends the recent files sub-menu. The recent items will be filtered
	// to show only items added by this application. Also connect a signal handler to
	// load a selected entry.
// @todo	Why is the filtering not working ?
	Gtk::Widget				* recentWidget		= uiManager->get_widget("/DefaultMenuBar/File/Recent");
	Gtk::MenuItem			* recentMenuItem	= dynamic_cast< Gtk::MenuItem * >( recentWidget );

	Gtk::RecentChooserMenu	* recentChooserMenu	= Gtk::manage( new Gtk::RecentChooserMenu(Gtk::RecentManager::get_default()) );
	Gtk::RecentFilter		* recentFilter		= Gtk::manage( new Gtk::RecentFilter() );

	recentMenuItem->set_submenu( * recentChooserMenu );
	recentMenuItem->property_visible() = true;

	recentChooserMenu->set_sort_type( Gtk::RECENT_SORT_MRU );
	recentChooserMenu->set_show_tips( true );
	recentChooserMenu->signal_item_activated().connect( sigc::bind(sigc::ptr_fun(&vgsdkViewerGtk::fileRecent), recentChooserMenu, &canvas) );

	recentFilter->add_application( Glib::get_application_name() );
	recentChooserMenu->add_filter( *recentFilter );

	Gtk::Widget		* editWidget		= uiManager->get_widget("/DefaultMenuBar/EditMenu");
	Gtk::MenuItem	* editMenuItem		= dynamic_cast< Gtk::MenuItem * >( editWidget );

	vgGTK::node::EditMenu * editMenu = new vgGTK::node::EditMenu();

	editMenuItem->set_submenu( *editMenu->getMenu() );
	editMenuItem->property_visible() = true;

	// Configures the properties widget.
	properties.set_border_width( 2 );
	properties.set_size_request( 333, 0 );
	properties.signalClose().connect( sigc::bind(sigc::ptr_fun(&vgsdkViewerGtk::showHideProperties), uiManager, &properties, true) );


	// Connects to some signal on the canvas.
	canvas.signal_key_release_event().connect( sigc::bind(sigc::ptr_fun(&vgsdkViewerGtk::canvasKeyReleaseEvent), uiManager, &canvas) );


	// Configures the main window.
	window.add_accel_group( editMenu->getUIManager()->get_accel_group() );
	window.add_accel_group( uiManager->get_accel_group() );
	window.set_title("vgsdkViewer");
//window.set_default_size( 1024, 768 );
	window.set_reallocate_redraws( true );


	// Configures the ati full-screen trik.
	// It is a drawing area that has a 1 pixel width and placed on the left canvas side.
	// Its background is black to make it as unvisible as possible.
	atiFullScreenTrick.modify_bg( Gtk::STATE_NORMAL, Gdk::Color("000000") );
	atiFullScreenTrick.set_size_request( 1, 0 );
	hbox.pack_start( atiFullScreenTrick, Gtk::PACK_SHRINK );
	hbox.add( canvas );


	// Creates the main window content.
	window.add( vbox );
	
	vbox.pack_start( *uiManager->get_widget("/DefaultMenuBar"), false, true );
	vbox.pack_start( *uiManager->get_widget("/DefaultToolBar"), false, true );
	vbox.add( hpaned );
	vbox.pack_end( statusBar, false, true );
	
	hpaned.pack1( properties, false, true );
	hpaned.pack2( hbox, true, true );
	
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


	// Shows the properties.
	Glib::RefPtr< Gtk::ToggleAction >	showProperties = Glib::RefPtr<Gtk::ToggleAction>::cast_dynamic( uiManager->get_action("/DefaultMenuBar/View/Properties") );
	
	if( showProperties )
	{
		showProperties->set_active(true);
	}


	// Gives the canvas' root node to the properties.
	properties.setCanvas( canvas );


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