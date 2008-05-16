// VGSDK - Copyright (C) 2008, Guillaume Brocker, Nicolas Papier.
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
#include <gtkmm/window.h>

#include <vgDebug/Global.hpp>

#include "vgsdkViewerGtk/myCanvas.hpp"



namespace vgsdkViewerGtk
{



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



void fileExportGraphviz( myCanvas * canvas )
{
	canvas->writeGraphviz();
}



void fileOpen( Gtk::Window * topLevel, myCanvas * canvas, const bool clearScene )
{
	Gtk::FileChooserDialog	chooser( *topLevel, "Choose file(s)", Gtk::FILE_CHOOSER_ACTION_OPEN );
	Gtk::FileFilter			allFilter;
	Gtk::FileFilter			trianFilter;
// Not supported yet !
//	Gtk::FileFilter			colladaFilter;
	Gtk::FileFilter			objFilter;

	allFilter.set_name( "All supported files" );
	allFilter.add_pattern( "*.trian" );
	allFilter.add_pattern( "*.trian2" );
// Not supported yet !
//	allFilter.add_pattern( "*.DAE" );
	allFilter.add_pattern( "*.obj" );

	trianFilter.set_name( "Trian files (*.trian, *.trian2)" );
	trianFilter.add_pattern( "*.trian" );
	trianFilter.add_pattern( "*.trian2" );

// Not supported yet !
//	colladaFilter.set_name( "All collada files (*.DAE)" );
//	colladaFilter.add_pattern( "*.DAE" );

	objFilter.set_name( "Wavefront objects (*.obj)" );
	objFilter.add_pattern( "*.obj" );

	chooser.add_filter( allFilter );
	chooser.add_filter( trianFilter );
// Not supported yet !
//	chooser.add_filter( colladaFilter );
	chooser.add_filter( objFilter );
	chooser.add_button( Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL );
	chooser.add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK );
	chooser.set_select_multiple( true );

	const int result = chooser.run();
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
			const Glib::ustring	filename = *i;
			bool				success = false;

			// Appends the model contained in the current file to the canvas' scene.
			success = canvas->appendToScene( filename );

			// On success, adds the current file to the recent history.
			Gtk::RecentManager::get_default()->add_item( filename );
		}


		// Refreshes the canvas content.
		canvas->refresh();
	}
}



void fileReload( myCanvas * canvas )
{
	canvas->reloadScene();
}



void fileRecent( Gtk::RecentChooser * recentChooser, myCanvas * canvas )
{
	bool				success = false;
	const Glib::ustring	recentFile = recentChooser->get_current_uri();

	// Removes any content of the scene and loads the given recent file.
	canvas->clearScene();
	success = canvas->appendToScene( recentFile );
	canvas->refresh();

	// According to the sucess, appends or removes the file from the default recent manager.
	if( success )
	{
		Gtk::RecentManager::get_default()->add_item( recentFile );
	}
	else
	{
		Gtk::RecentManager::get_default()->remove_item( recentFile );
	}
}



void fullScreen( myCanvas * canvas )
{
	// Remembers the current state.
	static bool	isFullScreen = false;
	
	
	// Retrieves the top level window.
	Gtk::Container	* container				= canvas->get_toplevel();
	Gtk::Window		* topLevel				= dynamic_cast< Gtk::Window * >( container );
	
	assert( topLevel != 0 );
	
	
	// Stops refreshs.
	topLevel->get_window()->freeze_updates();
	
	
	// Configures the layout.
	if( isFullScreen )
	{
		topLevel->get_child()->show_all();
		topLevel->unmaximize();
	}
	else
	{
		topLevel->get_child()->hide_all();
		topLevel->maximize();
		
		// We want to see the canvas. So we walk from the canvas to the top level window
		// and show each.
		for( Gtk::Widget * widget = canvas; widget != topLevel; widget = widget->get_parent() )
		{
			widget->show();
		}
	}
	
	
	// Refresh the window again.
	topLevel->get_window()->thaw_updates();	
	
	
	// Updates the current state.
	isFullScreen = ! isFullScreen;
}



void viewAll( myCanvas * canvas )
{
	canvas->viewAll();
}



void helpAbout( Gtk::Window * topLevel )
{
	Gtk::AboutDialog				aboutDialog;
	std::vector< Glib::ustring >	authors;

	authors.push_back( Glib::ustring("Guillaume Brocker") );
	authors.push_back( Glib::ustring("Nicolas Papier") );

	aboutDialog.set_transient_for( *topLevel );
	aboutDialog.set_authors( authors );
	aboutDialog.set_comments( "This programm is a simple demonstration of vgSDK capabilities. It allows you to load meshes (obj, trian, trian2), manipulate them and browse the rendering scene graph." );
	aboutDialog.set_copyright( "Copyright (C) 2008, Guillaume Brocker, Nicolas Papier and Digital trainers SAS." );
	aboutDialog.set_license( "Distributed under the terms of the GNU Library General Public License (LGPL) as published by the Free Software Foundation." );
	aboutDialog.set_website("http://home.gna.org/vgsdk");
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
			canvas->appendToScene(filename);
		}
		else
		{
			vgDebug::get().logWarning( "\"%s\": missing or invalid file path.", filename.c_str() );
		}

		// Moves the match start forward.
		start = result[0].second;
	}
}



void statusbarLogHandler( const gchar *log_domain, GLogLevelFlags log_level, const gchar *message, gpointer user_data )
{
	Gtk::Statusbar		* statusbar( reinterpret_cast<Gtk::Statusbar *>(user_data) );

	statusbar->push( Glib::ustring(message) );
}



} // namespace vgsdkViewerGtk
