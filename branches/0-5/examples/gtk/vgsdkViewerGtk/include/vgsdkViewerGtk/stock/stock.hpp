// VGSDK - Copyright (C) 2008, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include <gtkmm/stock.h>


namespace vgsdkViewerGtk
{

namespace stock
{



/**
 * @name	Stock Icon Identifiers
 */
//@{
extern "C" Gtk::StockID	SINGLE_VIEW;		///< Defines the stock identifier for the single-view icon.
extern "C" Gtk::StockID	MULTI_VIEW_SIDED;	///< Defines the stock identifier for the multi-view-sided icon.
extern "C" Gtk::StockID	MULTI_VIEW_SQUARED;	///< Defines the stock identifier for the multi-view-squared icon.
extern "C" Gtk::StockID	RESOLUTION;			///< Defines the stock identifier for the resolution icon.
//@}



/**
 * @brief	Initializes the sock icons.
 *
 * Should get called after GTK initialization and before any stock icon usage.
 */
void initialize();



} // namespace stock

} // namespace vgsdkViewerGtk
