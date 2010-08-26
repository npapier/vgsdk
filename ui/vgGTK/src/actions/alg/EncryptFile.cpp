// VGSDK - Copyright (C) 2010, Nicolas Papier and Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgGTK/actions/alg/EncryptFile.hpp"

#include <gtkmm/filechooserdialog.h>
#include <gtkmm/stock.h>
#include <gtkmm.h>

#include <vgAlg/actions/Encrypt.hpp>

#include <fstream>

namespace vgGTK
{

namespace actions
{

namespace alg
{


EncryptFile::EncryptFile()
{

}



EncryptFile::~EncryptFile()
{

}



void EncryptFile::execute()
{
	Gtk::FileChooserDialog	openChooser( "File to encrypt", Gtk::FILE_CHOOSER_ACTION_OPEN );
	Gtk::FileFilter			openAllFilter;
	Gtk::FileFilter			openDaeFilter;
	Gtk::FileFilter			openTrianFilter;
	Gtk::FileFilter			openImgFilter;

	openAllFilter.set_name( "All supported file (*.DAE, *.trian2, *.png, *.jpg)" );
	openAllFilter.add_pattern( "*.DAE" );
	openAllFilter.add_pattern( "*.trian2" );
	openAllFilter.add_pattern( "*.png" );
	openAllFilter.add_pattern( "*.jpg" );
	
	openDaeFilter.set_name( "COLLADA file (*.DAE)" );
	openDaeFilter.add_pattern( "*.DAE" );

	openTrianFilter.set_name( "Trian2 file (*.trian2)" );
	openTrianFilter.add_pattern( "*.trian2" );

	openImgFilter.set_name( "Image file (*.png, *.jpg)" );
	openImgFilter.add_pattern( "*.png" );
	openImgFilter.add_pattern( "*.jpg" );

	openChooser.add_filter( openAllFilter );
	openChooser.add_filter( openDaeFilter );
	openChooser.add_filter( openTrianFilter );
	openChooser.add_filter( openImgFilter );
	openChooser.add_button( Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL );
	openChooser.add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK );
	openChooser.set_do_overwrite_confirmation( false );


	Gtk::FileChooserDialog	saveChooser( "Save encrypted file as..", Gtk::FILE_CHOOSER_ACTION_SAVE );
	Gtk::FileFilter			saveDaeFilter;
	Gtk::FileFilter			saveTrianFilter;
	Gtk::FileFilter			saveJpgFilter;
	Gtk::FileFilter			savePngFilter;

	saveDaeFilter.set_name( "COLLADA Encrypted file (*.VGDAE)" );
	saveDaeFilter.add_pattern( "*.VGDAE" );

	saveTrianFilter.set_name( "Trian2 Encrypted file (*.VGtrian2)" );
	saveTrianFilter.add_pattern( "*.VGtrian2" );

	saveJpgFilter.set_name( "Jpg Encrypted file (*.VGjpg)" );
	saveJpgFilter.add_pattern( "*.VGjpg" );

	savePngFilter.set_name( "PNG Encrypted file (*.VGpng)" );
	savePngFilter.add_pattern( "*.VGpng" );

	saveChooser.add_filter( saveDaeFilter );
	saveChooser.add_filter( saveTrianFilter );
	saveChooser.add_filter( saveJpgFilter );
	saveChooser.add_filter( savePngFilter );

	saveChooser.add_button( Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL );
	saveChooser.add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK );
	saveChooser.set_do_overwrite_confirmation( true );

	const int result = openChooser.run();
	if( result == Gtk::RESPONSE_OK )
	{
		std::string originalFile = openChooser.get_filename();
		std::string encryptedFile;
		openChooser.hide();

		const int result = saveChooser.run();
		if( result == Gtk::RESPONSE_OK )
		{
			Gtk::Dialog keyDialog( "Set encryption key", true );
			keyDialog.add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK );
			keyDialog.add_button( Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL );

			Gtk::Entry keyEntry;
			keyEntry.set_text( "vgsdkViewerGTK" );
			Gtk::Label keylabel( "Key:" );

			keyDialog.get_vbox()->pack_start( keylabel, Gtk::PACK_EXPAND_PADDING, 5 );
			keyDialog.get_vbox()->pack_start( keyEntry, Gtk::PACK_EXPAND_PADDING, 5 );
			keyDialog.get_vbox()->show_all();

			const int keyResponse = keyDialog.run();
			if( keyResponse == Gtk::RESPONSE_OK )
			{
				std::string key = keyEntry.get_text();
				encryptedFile = saveChooser.get_filename();

				std::ifstream inFile;
				inFile.open( originalFile.c_str(), std::ifstream::in | std::ifstream::binary );
				bool b = inFile.good();
				inFile.seekg (0, std::ios::end);
				int length = inFile.tellg();
				inFile.seekg (0, std::ios::beg);

				std::vector< char > inBuffer;
				inBuffer.resize( length );
				inFile.read( &inBuffer[0], length );
				
				vgd::Shp< std::vector< char > > outBuffer( new std::vector< char > );
				vgAlg::actions::Encrypt encrypt;

				encrypt.setInitialize( key, inBuffer, outBuffer );
				encrypt.execute();

				std::ofstream outFile( encryptedFile.c_str(), std::ios::trunc | std::ios::binary );
				for( int i = 0; i < outBuffer->size(); ++i )
				{
					outFile << (*outBuffer)[i];
				}
				outFile.close();
				inFile.close();
			}
		}
	}	
}


} // namespace alg

} // namespace actions

} // namespace vgGTK
