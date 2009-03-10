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



#include "vgsdkViewerGtk/stock/single-view-16.xpm"
#include "vgsdkViewerGtk/stock/single-view-24.xpm"
#include "vgsdkViewerGtk/stock/multi-view-sided-16.xpm"
#include "vgsdkViewerGtk/stock/multi-view-sided-24.xpm"
#include "vgsdkViewerGtk/stock/multi-view-squared-16.xpm"
#include "vgsdkViewerGtk/stock/multi-view-squared-24.xpm"
#include "vgsdkViewerGtk/stock/resolution-16.xpm"
#include "vgsdkViewerGtk/stock/resolution-24.xpm"



Gtk::StockID	SINGLE_VIEW("vgsdkViewerGtk::stock::SINGLE_VIEW");
Gtk::StockID	MULTI_VIEW_SIDED("vgsdkViewerGtk::stock::MULTI_VIEW_SIDED");
Gtk::StockID	MULTI_VIEW_SQUARED("vgsdkViewerGtk::stock::MULTI_VIEW_SQUARED");
Gtk::StockID	RESOLUTION("vgsdkViewerGtk::stock::RESOLUTION");



const Gtk::IconSource createIconSource( const int size, const char* const* xpmData )
{
	Gtk::IconSource	iconSource;
	
	iconSource.set_pixbuf( Gdk::Pixbuf::create_from_xpm_data(xpmData) );
	iconSource.set_size( Gtk::IconSize(size) );
	
	return iconSource;
}



void initialize()
{
	// Creates all icon sets.
	Gtk::IconSet	singleViewSet;	
	singleViewSet.add_source( createIconSource(16, single_view_16_xpm) );
	singleViewSet.add_source( createIconSource(24, single_view_24_xpm) );
	
	Gtk::IconSet	multiViewSidedSet;	
	multiViewSidedSet.add_source( createIconSource(16, multi_view_sided_16_xpm) );
	multiViewSidedSet.add_source( createIconSource(24, multi_view_sided_24_xpm) );
	
	Gtk::IconSet	multiViewSquaredSet;
	multiViewSquaredSet.add_source( createIconSource(16, multi_view_squared_16_xpm) );
	multiViewSquaredSet.add_source( createIconSource(24, multi_view_squared_24_xpm) );
	
	Gtk::IconSet	resolutionSet;
	resolutionSet.add_source( createIconSource(16, resolution_16_xpm) );
	resolutionSet.add_source( createIconSource(24, resolution_24_xpm) );
	
	
	// Creates an icon factory for our icon sets.
	Glib::RefPtr< Gtk::IconFactory >	iconFactory = Gtk::IconFactory::create();
	
	iconFactory->add( SINGLE_VIEW, singleViewSet );
	iconFactory->add( MULTI_VIEW_SIDED, multiViewSidedSet );
	iconFactory->add( MULTI_VIEW_SQUARED, multiViewSquaredSet );
	iconFactory->add( RESOLUTION, resolutionSet );
	iconFactory->add_default();
}



} // namespace stock

} // namespace vgsdkViewerGtk
