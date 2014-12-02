//// VGSDK - Copyright (C) 2010, Maxime Peresson.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Maxime Peresson
//
//#include "vgio/ArchiveLoader.hpp"
//
//#include <algorithm>
//
//#include <vgAlg/actions/Decrypt.hpp>
//#include <vgd/basic/FilenameExtractor.hpp>
//
//
//#include <vgio/helpers.hpp>
//
//
//namespace vgio
//{
//META_LOADER_CPP( vgio::ArchiveLoader, "vgarch" )
//
//
//ArchiveLoader::ArchiveLoader() :
//m_encryptionKey( "vgsdkViewerGTK" )
//{
//}
//
//
//
//ArchiveLoader::ArchiveLoader( std::string encryptionKey ) :
//m_encryptionKey( encryptionKey )
//{
//}
//
//
//
//std::pair< bool, vgd::Shp< vgd::node::Group > > ArchiveLoader::load( const std::string filePath, const bool bCCW )
//{
//	std::pair< bool, vgd::Shp< vgd::node::Group > > retVal;
//	retVal.first = true;
//	m_root = vgd::node::Group::create( filePath );
//	retVal.second = m_root;
//
//	m_compression.reset( new vgPhysfs::Archive( filePath ) );
//
//	m_directoryList = m_compression->getDirectoryList();
//	loadImages();
//
//	std::vector< std::string > fileList = m_compression->getFileList();
//	for( int i = 0; i < fileList.size(); ++i )
//	{
//		std::string pathFilename = fileList[ i ];
//
//		// Retrieves the extension of the given filename.
//		vgd::basic::FilenameExtractor	extractor( pathFilename.c_str() );
//		std::string						extension = extractor.getExtension();
//		std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower); //to lowercase;
//
//		vgd::Shp< std::vector< char > > inBuffer( new std::vector< char > );
//		m_compression->getFile( pathFilename, inBuffer );
//
//		if ( extension.compare( ".crypt" ) == 0 )
//		{
//			vgd::Shp< std::vector< char > > outBuffer( new std::vector< char > );
//
//			vgAlg::actions::Decrypt decrypt;
//			decrypt.setInitialize( m_encryptionKey, inBuffer, outBuffer );
//			decrypt.execute();
//
//			inBuffer = outBuffer;
//			pathFilename = pathFilename.substr( 0, pathFilename.size() - 6 ); //remove ".crypt" extension
//		}
//
//		vgd::Shp< vgio::ILoader > loader = vgio::getLoaderByFilename( pathFilename );
//
//		if( loader )
//		{	
//			std::pair< bool, vgd::Shp< vgd::node::Group > > retModel;
//			retModel = loader->load( pathFilename.c_str(), inBuffer, m_imageMap );
//			if( retModel.first )
//			{
//				m_root->addChild( retModel.second );
//			}
//			else
//			{
//				retVal.first = false;
//				return retVal;
//			}
//		}
//	}
//
//	return retVal;
//}
//
//
//std::pair< bool, vgd::Shp< vgd::node::Group > > ArchiveLoader::load( const std::string filePath, vgd::Shp< std::vector< char > > outBuffer, const bool bCCW )
//{
//	std::pair< bool, vgd::Shp< vgd::node::Group > > retVal;
//
//	assert( false && "Can't load archived file from memory." );
//
//	return retVal;
//}
//
//
//std::pair< bool, vgd::Shp< vgd::node::Group > > ArchiveLoader::load( const std::string filePath, vgd::Shp< std::vector< char > > outBuffer, std::map< std::string, vgd::Shp< vgd::basic::Image > > imageMap, const bool bCCW )
//{
//	std::pair< bool, vgd::Shp< vgd::node::Group > > retVal;
//
//	assert( false && "Can't load archived file from memory." );
//
//	return retVal;
//}
//
//
//void ArchiveLoader::loadImages()
//{
//	for( int i = 0; i < m_directoryList.size(); ++i )
//	{
//		std::vector< std::string > fileList = m_compression->getFileList( m_directoryList[ i ] );
//		for( int j = 0; j < fileList.size(); ++j )
//		{
//			// Retrieves the extension of the given filename.
//			vgd::basic::FilenameExtractor	extractor( fileList[ j ].c_str() );
//			std::string						extension = extractor.getExtension();
//			std::string						fileName = fileList[ j ];
//
//			std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower); //to lowercase;
//			if( extension.compare( ".jpg" ) == 0 || extension.compare( ".png" ) == 0 || extension.compare( ".crypt" ) == 0 || extension.compare( ".crypt" ) == 0 )
//			{
//				std::string pathFilename = m_directoryList[ i ] + "/" + fileList[ j ];
//				vgd::Shp< std::vector< char > > inBuffer( new std::vector< char > );
//				m_compression->getFile( pathFilename, inBuffer );
//
//				if( extension.compare( ".crypt" ) == 0 || extension.compare( ".crypt" ) == 0 ) //decrypt img
//				{
//					vgd::Shp< std::vector< char > > outBuffer( new std::vector< char > );
//
//					vgAlg::actions::Decrypt decrypt;
//					decrypt.setInitialize( m_encryptionKey, inBuffer, outBuffer );
//					decrypt.execute();
//
//					inBuffer = outBuffer;
//
//					fileName = fileName.substr( 0, fileName.size() - 6 ); //remove ".crypt" extension
//				}
//
//				void *pixel = &(*inBuffer)[0];
//
//				vgd::Shp< vgd::basic::Image > img = vgd::Shp< vgd::basic::Image >( new vgd::basic::Image( fileName, pixel, inBuffer->size() ) );
//				m_imageMap[ fileList[ j ] ] = img;
//			}
//		}
//	}
//}
//
//
//
//vgd::Shp< vgio::ILoader > ArchiveLoader::clone()
//{
//	return vgd::Shp< vgio::ILoader >( new ArchiveLoader );
//}
//
//
//
//} // namespace vgio
//
