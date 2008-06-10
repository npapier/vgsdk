// VGSDK - Copyright (C) 2008, Nicolas Papier.
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
extern "C" Gtk::StockID	MULTI_VIEW;	///< Defines the stock identifier for the multi-view icon.
//@}



/**
 * @brief	Initializes the sock icons.
 *
 * Should get called after GTK initialization and before any stock icon usage.
 */
void initialize();



} // namespace stock

} // namespace vgsdkViewerGtk
