// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgGTK/node/ExportCollada.hpp"

#include <gtkmm/alignment.h>
#include <gtkmm/dialog.h>
#include <gtkmm/label.h>
#include <gtkmm/listviewtext.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/stock.h>



namespace vgGTK
{

namespace node
{



ExportCollada::ExportCollada() :
m_geometryVBox(),
m_geometryHBox1(),
m_geometryHBox2(),
m_miscHBox(),
m_geometryFrame( "Geometry settings" ),
m_miscFrame( "Other settings" ),
m_exportLevelCombo(),
m_applyGeometricalTransformation( "Apply geometrical transformation" ),
m_triangulate( "Triangulate" ),
m_invertPrimitiveOrientation( "Invert primitives orientation" ),
m_encrypt( "Encrypt" )
{
	m_applyGeometricalTransformation.toggled();
	
	m_exportLevelCombo.append_text( "Geometry only" );
	m_exportLevelCombo.append_text( "Material" );
	m_exportLevelCombo.append_text( "Texture" );
	m_exportLevelCombo.set_active( 2 );
	
	m_miscHBox.pack_start( m_exportLevelCombo, Gtk::PACK_EXPAND_PADDING, 5 );
	m_geometryHBox1.pack_start( m_applyGeometricalTransformation, Gtk::PACK_EXPAND_PADDING, 5 );
	m_geometryHBox1.pack_start( m_triangulate, Gtk::PACK_EXPAND_PADDING, 5 );
	m_geometryHBox2.pack_start( m_invertPrimitiveOrientation, Gtk::PACK_EXPAND_PADDING, 5 );
	m_geometryHBox2.pack_start( m_encrypt, Gtk::PACK_EXPAND_PADDING, 5 );
	
	//m_geometryHBox1.set_border_width( 5 );
	//m_geometryHBox2.set_border_width( 5 );

	m_miscHBox.set_border_width(10);

	m_geometryVBox.pack_start( m_geometryHBox1, Gtk::PACK_EXPAND_PADDING, 5 );
	m_geometryVBox.pack_start( m_geometryHBox2, Gtk::PACK_EXPAND_PADDING, 5 );

	m_geometryFrame.add( m_geometryVBox );
	m_miscFrame.add( m_miscHBox );

	pack_start( m_geometryFrame, Gtk::PACK_EXPAND_WIDGET, 5 );
	pack_start( m_miscFrame, Gtk::PACK_EXPAND_WIDGET, 5 );
}



vgOpenCOLLADA::exporter::ExportSettings ExportCollada::getExportSettings()
{
	bool applyGeometricalTransformation = m_applyGeometricalTransformation.get_active();
	bool triangulate = m_triangulate.get_active();
	bool invertPrimitiveOrientation = m_invertPrimitiveOrientation.get_active();
	bool encrypt = m_encrypt.get_active();

	vgOpenCOLLADA::exporter::ExportLevel exportLevel;

	int rowNumber = m_exportLevelCombo.get_active_row_number();
	switch( rowNumber )
	{
		case 0:
			exportLevel = vgOpenCOLLADA::exporter::GEOMETRY;
			break;
		case 1:
			exportLevel = vgOpenCOLLADA::exporter::MATERIAL;
			break;
		case 2:
			exportLevel = vgOpenCOLLADA::exporter::TEXTURE;
			break;
		default:
			exportLevel = vgOpenCOLLADA::exporter::TEXTURE;
			break;
	}

	vgOpenCOLLADA::exporter::ExportSettings exportSettings( applyGeometricalTransformation, triangulate, invertPrimitiveOrientation, encrypt, exportLevel );
	return exportSettings;
}



} // namespace node

} // namespace vgGTK
