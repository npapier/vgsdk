// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgGTK/node/ExportColladaDialog.hpp"

#include <gtkmm/stock.h>



namespace vgGTK
{

namespace node
{



ExportColladaDialog::ExportColladaDialog()
:	Gtk::Dialog( "Collada Export Settings" )
{
	m_exportCollada.set_border_width( 12 );

	add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK );
	add_button( Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL );
	get_vbox()->add( m_exportCollada );
}



vgOpenCOLLADA::exporter::ExportSettings ExportColladaDialog::getExportSettings()
{
	return m_exportCollada.getExportSettings();
}



} // namespace node

} // namespace vgGTK
