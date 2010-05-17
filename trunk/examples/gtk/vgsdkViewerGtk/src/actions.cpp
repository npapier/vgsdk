// VGSDK - Copyright (C) 2008, 2009, 2010, Guillaume Brocker, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#include "vgsdkViewerGtk/actions.hpp"

#include <iostream>
#include <sstream>
#include <string>

#include <boost/regex.hpp>

#include <glibmm/convert.h>

#include <gtkmm/aboutdialog.h>
#include <gtkmm/filechooserdialog.h>
#include <gtkmm/filefilter.h>
#include <gtkmm/main.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/statusbar.h>
#include <gtkmm/stock.h>
#include <gtkmm/toggleaction.h>
#include <gtkmm/window.h>

#include <vgDebug/convenience.hpp>
#include <vge/engine/UserSettings.hpp>
#include <vgGTK/ResolutionDialog.hpp>
#include <vgGTK/engine/UserSettingsDialog.hpp>

#include "vgsdkViewerGtk/myCanvas.hpp"



namespace vgsdkViewerGtk
{



bool canvasKeyReleaseEvent( GdkEventKey * event, Glib::RefPtr<Gtk::UIManager> uiManager, myCanvas * canvas )
{
	if( event->keyval == GDK_Escape && canvas->isFullscreen() )
	{
		Glib::RefPtr< Gtk::Action >	action = uiManager->get_action( "/DefaultMenuBar/View/FullScreen" );

		if( action )
		{
			action->activate();
		}
	}
	return false;
}



void fileExit()
{
	Gtk::Main::quit();
}



void fileNew( Gtk::Window * topLevel, myCanvas * canvas )
{
	Gtk::MessageDialog	dialog( "Reset the content of the current scene ?", false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO, true );

	dialog.set_transient_for( *topLevel );
	dialog.set_keep_above( true );
	if( dialog.run() == Gtk::RESPONSE_YES )
	{
		canvas->clearScene();
		canvas->refresh();
	}
}



void fileOpen( Gtk::Window * topLevel, myCanvas * canvas, const bool clearScene )
{
	Gtk::FileChooserDialog	chooser( *topLevel, "Choose file(s)", Gtk::FILE_CHOOSER_ACTION_OPEN );
	Gtk::FileFilter			allFilter;
	Gtk::FileFilter			trianFilter;
	Gtk::FileFilter			colladaFilter;
	Gtk::FileFilter			objFilter;

	allFilter.set_name( "All supported files" );
	allFilter.add_pattern( "*.trian" );
	allFilter.add_pattern( "*.trian2" );
	allFilter.add_pattern( "*.dae" );
	allFilter.add_pattern( "*.obj" );

	trianFilter.set_name( "Trian files (*.trian, *.trian2)" );
	trianFilter.add_pattern( "*.trian" );
	trianFilter.add_pattern( "*.trian2" );

	colladaFilter.set_name( "All collada files (*.dae)" );
	colladaFilter.add_pattern( "*.dae" );

	objFilter.set_name( "Wavefront objects (*.obj)" );
	objFilter.add_pattern( "*.obj" );

	chooser.add_filter( allFilter );
	chooser.add_filter( trianFilter );
	chooser.add_filter( colladaFilter );
	chooser.add_filter( objFilter );
	chooser.add_button( Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL );
	chooser.add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK );
	chooser.set_select_multiple( true );

	const int result = chooser.run();
	chooser.hide();

	if( result == Gtk::RESPONSE_OK )
	{
		// Clears the canvas if requested.
		if( clearScene )
		{
			canvas->clearScene();
		}


		// Submits the choosen files to the canvas and refresh the whole thing.
		const std::vector< Glib::ustring >	filenames = chooser.get_filenames();

		for( std::vector< Glib::ustring >::const_iterator i = filenames.begin(); i != filenames.end(); ++i )
		{
			const Glib::ustring	filename	= *i;
			bool				success		= false;

			// Appends the model contained in the current file to the canvas' scene.
			success = canvas->appendToScene( filename );

			// On success, adds the current file to the recent history.
			if ( success )
			{
				Glib::ustring uri = Glib::filename_to_uri(filename);
				Gtk::RecentManager::get_default()->add_item( uri );
			}
		}


		// Refreshes the canvas content.
		canvas->refresh();
	}
}



void fileReload( myCanvas * canvas )
{
	if ( canvas->isEmpty() )
	{
		// @todo a function in vgGTK ?
		// If no scene has been loaded, then we use the recent files.
		typedef Glib::RefPtr< Gtk::RecentInfo >	InfoRefPtr;
		typedef std::vector< InfoRefPtr >		InfoContainer;

		// We first look for the most recent file loaded by this application.
		const Glib::ustring	appName	= Glib::get_application_name();
		InfoContainer		infos	= Gtk::RecentManager::get_default()->get_items();
		InfoRefPtr			recentInfo;

		for( InfoContainer::iterator i = infos.begin(); i != infos.end(); ++i )
		{
			InfoRefPtr currentInfo = *i;

			if( currentInfo->has_application(appName) && (recentInfo ==  false || currentInfo->get_modified() > recentInfo->get_modified()) )
			{
				recentInfo = currentInfo;
			}
		}

		// If we got one, then we uses this.
		if( recentInfo )
		{
			const std::string				recentFile( Glib::filename_from_uri( recentInfo->get_uri() ) );

			// Removes any content of the scene and loads the given recent file.
			canvas->clearScene();
			const bool success = canvas->appendToScene( recentFile );

			// According to the success, appends or removes the file from the default recent manager.
			if( success )
			{
				Gtk::RecentManager::get_default()->add_item( recentInfo->get_uri() );
			}
			else
			{
				Gtk::RecentManager::get_default()->remove_item( recentInfo->get_uri() );
			}
		}
	}
	else
	{
		canvas->reloadScene();
	}

	canvas->refresh();
}



void fileRecent( Gtk::RecentChooser * recentChooser, myCanvas * canvas )
{
	bool				success			= false;
	const Glib::ustring	uriRecentFile	= recentChooser->get_current_uri();
	const std::string	recentFile		= Glib::filename_from_uri( uriRecentFile );

	// Removes any content of the scene and loads the given recent file.
	canvas->clearScene();
	success = canvas->appendToScene( recentFile );
	canvas->refresh();

	// According to the success, appends or removes the file from the default recent manager.
	if( success )
	{
		Gtk::RecentManager::get_default()->add_item( uriRecentFile );
	}
	else
	{
		Gtk::RecentManager::get_default()->remove_item( uriRecentFile );
	}
}



void fullscreen( myCanvas * canvas )
{
	canvas->switchFullscreen();

	const bool isFullscreen = canvas->isFullscreen();

	// Retrieves the top level window.
	Gtk::Window	* topLevel	= dynamic_cast< Gtk::Window * >( canvas->get_toplevel() );

	if ( topLevel )
	{
		// Stops refreshs.
		topLevel->get_window()->freeze_updates();

		// Configures the layout.		
		if ( isFullscreen )
		{
			topLevel->get_child()->hide_all();
			
			// We want to see the canvas. So we walk from the canvas to the top level window
			// and show each.
			for( Gtk::Widget * widget = canvas; widget != topLevel; widget = widget->get_parent() )
			{
				widget->show();
			}
		}
		else
		{
			topLevel->get_child()->show_all();
		}

		// Refresh the window again.
		topLevel->get_window()->thaw_updates();
	}
	// else do nothing
}


void viewAll( myCanvas * canvas )
{
	canvas->viewAll();
	canvas->refresh();
}



void setResolution( myCanvas * canvas )
{
	vgGTK::ResolutionDialog	dialog( canvas );
	
	dialog.run();
}



void settingManipulationBinding( myCanvas * canvas, const int binding )
{
	switch( binding )
	{
		case 1:
			canvas->getSceneTransformation()->setBindingsToDefaults();
			break;
			
		case 2:
			canvas->getSceneTransformation()->setBindingsToDefaults2();
			break;
			
		default:
			vgLogWarning( "Invalid manipulation binding specified." );
	}
}



void showHideProperties( Glib::RefPtr< Gtk::UIManager > uiManager, Gtk::Widget * properties, const bool hiddenForced )
{
	Glib::RefPtr< Gtk::ToggleAction >	action = Glib::RefPtr< Gtk::ToggleAction >::cast_dynamic( uiManager->get_action("/DefaultMenuBar/View/Properties") );

	assert( action );

	if( hiddenForced )
	{
		action->set_active( false );
	}
	else if( action->get_active() )
	{
		properties->show();
	}
	else
	{
		properties->hide();
	}
}



void helpAbout( Gtk::Window * topLevel )
{
	Gtk::AboutDialog				aboutDialog;
	std::vector< Glib::ustring >	authors;

	authors.push_back( Glib::ustring("Guillaume Brocker") );
	authors.push_back( Glib::ustring("Nicolas Papier") );
	authors.push_back( Glib::ustring("Maxime Peresson") );

	aboutDialog.set_transient_for( *topLevel );
	aboutDialog.set_authors( authors );
	aboutDialog.set_comments( "This programm is a simple demonstration of vgSDK capabilities. It allows you to load meshes (obj, trian, trian2 and dae), manipulate them and browse the rendering scene graph." );
	aboutDialog.set_copyright( "Copyright (C) 2008, 2009, 2010, Guillaume Brocker, Nicolas Papier, Maxime Peresson and Digital Trainers SAS." );
	aboutDialog.set_license( "Distributed under the terms of the GNU Library General Public License (LGPL) as published by the Free Software Foundation." );
	aboutDialog.set_website("http://code.google.com/p/vgsdk");
	aboutDialog.set_wrap_license( true );

	aboutDialog.run();
}



void dragDataReceived( myCanvas * canvas, const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, const Gtk::SelectionData& selection_data, guint info, guint time )
{
	// Ask to clear the scene when necessary.
	if( canvas->isEmpty() == false )
	{
		Gtk::MessageDialog	dialog( *dynamic_cast<Gtk::Window *>(canvas->get_toplevel()), "Clear scene prior loading new files ?", false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO, true );

		if( dialog.run() == Gtk::RESPONSE_YES )
		{
			canvas->clearScene();
		}
	}

	// Go for loading !
	const std::string			data( selection_data.get_data_as_string() );
	const boost::regex			regex( "(.+?)[\r\n]+" );
	std::string::const_iterator	start = data.begin();
	boost::smatch				result;

	while( boost::regex_search(start, data.end(), result, regex) )
	{
		// Loads the current file.
		const std::string	line = result[1].str();
		const std::string	filename = Glib::filename_from_uri( line );

		if( Glib::file_test(filename, Glib::FILE_TEST_EXISTS|Glib::FILE_TEST_IS_REGULAR) )
		{
			const bool success = canvas->appendToScene(filename);

			// On success, adds the current file to the recent history.
			if ( success )
			{
				Glib::ustring uri = Glib::filename_to_uri(filename);
				bool retVal = Gtk::RecentManager::get_default()->add_item( uri );
				assert( retVal );
			}
		}
		else
		{
			vgLogWarning2( "\"%s\": missing or invalid file path.", filename.c_str() );
		}

		// Moves the match start forward.
		start = result[0].second;
	}
}



int openOpenCOLLADAFile( )
{
	Gtk::Dialog	dialog( "How to open COLLADA file?" );
	dialog.set_keep_above( true );
	dialog.add_button("Geometry", 0);
	dialog.add_button("Material", 1);
	dialog.add_button("Texture", 2);
	dialog.set_default_response(2);
	return dialog.run();
}



void statusbarLogHandler( const gchar *log_domain, GLogLevelFlags log_level, const gchar *message, gpointer user_data )
{
	Gtk::Statusbar		* statusbar( reinterpret_cast<Gtk::Statusbar *>(user_data) );

	statusbar->push( Glib::ustring(message) );
}



void userSettings( Gtk::Window * toplevel, myCanvas * canvas )
{
	vgGTK::engine::UserSettingsDialog	dialog( toplevel, vge::engine::UserSettings(*canvas) );
	
	dialog.show_all();
	if( dialog.run() == Gtk::RESPONSE_OK )
	{
		dialog.get().apply( *canvas );
	}
}



} // namespace vgsdkViewerGtk

