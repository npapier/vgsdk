// VGSDK - Copyright (C) 2010, Guillaume Brocker, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include "vgsdkViewerGtk/Properties.hpp"

#include <gtkmm/button.h>
#include <gtkmm/image.h>
#include <gtkmm/label.h>
#include <gtkmm/stock.h>

#include "vgsdkViewerGtk/myCanvas.hpp"



namespace vgsdkViewerGtk
{



Properties::Properties()
{
	Gtk::HBox	* header	= Gtk::manage( new Gtk::HBox() );
	Gtk::Label	* label		= Gtk::manage( new Gtk::Label() );
	Gtk::Button	* close		= Gtk::manage( new Gtk::Button() );

	label->set_markup( "<b>Properties</b>" );
	label->set_alignment( 0, 0.5 );

	close->set_image( *Gtk::manage(new Gtk::Image(Gtk::Stock::CLOSE, Gtk::ICON_SIZE_SMALL_TOOLBAR)) );
	close->set_relief( Gtk::RELIEF_NONE );
	close->signal_clicked().connect( sigc::mem_fun(&m_signalClose, &sigc::signal<void>::emit) );

	header->add( *label );
	header->pack_end( *close, Gtk::PACK_SHRINK );

	pack_start( *header, Gtk::PACK_SHRINK );
	add( m_notebook );
}



void Properties::setCanvas( myCanvas & canvas )
{
	m_notebook.setCanvas( canvas );
}



sigc::signal< void > & Properties::signalClose()
{
	return m_signalClose;
}



} // namespace vgsdkViewerGtk
