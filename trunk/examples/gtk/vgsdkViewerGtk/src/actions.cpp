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
	Gtk::FileFilter			colladaFilter;
	Gtk::FileFilter			objFilter;

	allFilter.set_name( "All supported files" );
	allFilter.add_pattern( "*.trian" );
	allFilter.add_pattern( "*.trian2" );
	allFilter.add_pattern( "*.DAE" );
	allFilter.add_pattern( "*.obj" );

	trianFilter.set_name( "Trian files (*.trian, *.trian2)" );
	trianFilter.add_pattern( "*.trian" );
	trianFilter.add_pattern( "*.trian2" );

	colladaFilter.set_name( "All collada files (*.DAE)" );
	colladaFilter.add_pattern( "*.DAE" );

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
	if( result == Gtk::RESPONSE_OK )
	{
		// Clears the canvas if requested.
		if( clearScene )
		{
			canvas->clearScene();
		}

		// Submits the choosen files to the canvas and refresh the whole thing.
		canvas->appendToScene( chooser.get_filenames() );
		canvas->refresh();
	}
}



void fileReload( myCanvas * canvas )
{
	canvas->reloadScene();
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
	aboutDialog.set_comments( "This programm is a simple demonstration of vgSDK capabilities. It allows you to load and manipulate trian and trian2 meshes." );
	aboutDialog.set_copyright( "Copyright (C) 2008, Guillaume Brocker, Nicolas Papier." );
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
