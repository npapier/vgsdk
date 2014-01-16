// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgGTK/node/ColladaSettings.hpp"

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



ColladaSettings::ColladaSettings() :
m_geometryVBox(),
m_geometryHBox1(),
m_geometryHBox2(),
m_miscHBox(),
m_geometryFrame( "Geometry settings" ),
m_textureFrame( "Texture settings" ),
m_miscFrame( "Other settings" ),
m_exportLevelCombo(),
m_applyGeometricalTransformation( "Apply geometrical transformation" ),
m_triangulate( "Triangulate" ),
m_invertPrimitiveOrientation( "Invert primitives orientation" ),
m_encrypt( "Encrypt" ),
m_reflective( "Reflective" ),
m_bump( "Bump" ),
m_specular( "Specular" ),
m_textureSizeLabel( "Maximum texture Size:" )
{
	m_applyGeometricalTransformation.toggled();
	
	m_textureSize.set_increments( 1, 1 );
	m_textureSize.set_range( 1, 32768 );
	m_textureSize.set_value( 8192 );

	m_exportLevelCombo.append_text( "Geometry only" );
	m_exportLevelCombo.append_text( "Material" );
	m_exportLevelCombo.append_text( "Texture" );
	m_exportLevelCombo.set_active( 2 );
	
	m_miscHBox.pack_start( m_exportLevelCombo, Gtk::PACK_EXPAND_PADDING, 5 );
	m_miscHBox.pack_start( m_encrypt, Gtk::PACK_EXPAND_PADDING, 5 );

	m_geometryHBox1.pack_start( m_applyGeometricalTransformation, Gtk::PACK_EXPAND_PADDING, 5 );
	m_geometryHBox1.pack_start( m_triangulate, Gtk::PACK_EXPAND_PADDING, 5 );
	m_geometryHBox2.pack_start( m_invertPrimitiveOrientation, Gtk::PACK_EXPAND_PADDING, 5 );
	
	m_textureHBox1.pack_start( m_textureSizeLabel, Gtk::PACK_EXPAND_PADDING, 5 );
	m_textureHBox1.pack_start( m_textureSize, Gtk::PACK_EXPAND_PADDING, 5 );
	m_textureHBox2.pack_start( m_reflective, Gtk::PACK_EXPAND_PADDING, 5 );
	m_textureHBox2.pack_start( m_bump, Gtk::PACK_EXPAND_PADDING, 5 );
	m_textureHBox2.pack_start( m_specular, Gtk::PACK_EXPAND_PADDING, 5 );

	m_miscHBox.set_border_width(10);

	m_geometryVBox.pack_start( m_geometryHBox1, Gtk::PACK_EXPAND_PADDING, 5 );
	m_geometryVBox.pack_start( m_geometryHBox2, Gtk::PACK_EXPAND_PADDING, 5 );

	m_textureVBox.pack_start( m_textureHBox1, Gtk::PACK_EXPAND_PADDING, 5 );
	m_textureVBox.pack_start( m_textureHBox2, Gtk::PACK_EXPAND_PADDING, 5 );

	m_geometryFrame.add( m_geometryVBox );
	m_textureFrame.add( m_textureVBox );
	m_miscFrame.add( m_miscHBox );

	pack_start( m_geometryFrame, Gtk::PACK_EXPAND_WIDGET, 5 );
	pack_start( m_textureFrame, Gtk::PACK_EXPAND_WIDGET, 5 );
	pack_start( m_miscFrame, Gtk::PACK_EXPAND_WIDGET, 5 );


	//disable unimplemented:
	m_encrypt.set_sensitive( false );
	m_reflective.set_sensitive( false );
	m_bump.set_sensitive( false );
	m_specular.set_sensitive( false );
}



vgOpenCOLLADA::Settings ColladaSettings::getSettings()
{
	bool applyGeometricalTransformation = m_applyGeometricalTransformation.get_active();
	bool triangulate = m_triangulate.get_active();
	bool invertPrimitiveOrientation = m_invertPrimitiveOrientation.get_active();
	bool encrypt = m_encrypt.get_active();
	bool reflective = m_reflective.get_active();
	bool bump = m_bump.get_active();
	bool specular = m_specular.get_active();
	int textureSize = (int)m_textureSize.get_value();

	vgOpenCOLLADA::LEVEL exportLevel;

	int rowNumber = m_exportLevelCombo.get_active_row_number();
	switch( rowNumber )
	{
		case 0:
			exportLevel = vgOpenCOLLADA::GEOMETRY;
			break;
		case 1:
			exportLevel = vgOpenCOLLADA::MATERIAL;
			break;
		case 2:
			exportLevel = vgOpenCOLLADA::TEXTURE;
			break;
		default:
			exportLevel = vgOpenCOLLADA::TEXTURE;
			break;
	}

	vgOpenCOLLADA::Settings settings( applyGeometricalTransformation, triangulate, invertPrimitiveOrientation, 
		encrypt, reflective, bump, specular, textureSize, exportLevel );

	return settings;
}



} // namespace node

} // namespace vgGTK
