// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include "vgsdkViewerGtk/stock/stock.hpp"

#include <gtkmm/iconfactory.h>



namespace vgsdkViewerGtk
{

namespace stock
{



#include "vgsdkViewerGtk/stock/multi-view-16.xpm"
#include "vgsdkViewerGtk/stock/multi-view-24.xpm"



Gtk::StockID	MULTI_VIEW("vgsdkViewerGtk::stock::MULTI_VIEW");



void initialize()
{
	// Creates an icon set with our icons.
	Gtk::IconSet	iconSet;
	Gtk::IconSource	iconSource;
	
	iconSource.set_pixbuf( Gdk::Pixbuf::create_from_xpm_data(multi_view_16_xpm) );
	iconSource.set_size( Gtk::IconSize(16) );
	iconSet.add_source( iconSource );
	
	iconSource.set_pixbuf( Gdk::Pixbuf::create_from_xpm_data(multi_view_24_xpm) );
	iconSource.set_size( Gtk::IconSize(24) );
	iconSet.add_source( iconSource );
	
	
	// Creates an icon factory for our icon sets.
	Glib::RefPtr< Gtk::IconFactory >	iconFactory = Gtk::IconFactory::create();
	
	iconFactory->add( MULTI_VIEW, iconSet );
	iconFactory->add_default();
}



} // namespace stock

} // namespace vgsdkViewerGtk
