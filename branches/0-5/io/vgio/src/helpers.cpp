// VGSDK - Copyright (C) 2010, 2012, Maxime Peresson, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson
// Author Nicolas Papier

#include "vgio/helpers.hpp"

#include <fstream>

#include <vgAlg/actions/Decrypt.hpp>
#include <vgio/LoaderRegistry.hpp>

#include <vgd/basic/FilenameExtractor.hpp>
#include <vgd/basic/Image.hpp>

#include <vgDebug/helpers.hpp>



namespace vgio
{



std::pair< bool, vgd::Shp< vgd::node::Group > > load( const std::string filePath, const std::string key )
{
	std::pair< bool, vgd::Shp< vgd::node::Group > > retVal;
	retVal.first = false;

	// Retrieves the extension of the given filename.
	vgd::basic::FilenameExtractor	extractor( filePath );
	std::string						extension = extractor.getLowerCaseExtension();

	vgd::Shp< vgio::ILoader > loader;

	if ( extension.compare( ".crypt" ) == 0 ) //load crypted file ==> from memory
	{
		vgd::Shp< std::vector< char > > inBuffer = readFile( filePath );

		if( !inBuffer->empty() )
		{
			vgd::Shp< std::vector< char > > outBuffer( new std::vector< char > );

			vgAlg::actions::Decrypt decrypt;
			decrypt.setInitialize( key, inBuffer, outBuffer );
			decrypt.execute();

			const std::string newFilePath = extractor.getPath() + "/" + extractor.getFilenameWithoutExtension();
			loader = getLoaderByFilename( newFilePath );

			if( loader )
			{
				retVal = loader->load( newFilePath, outBuffer );
			}
			// else nothing to do
		}
		else
		{
			vgAssertN( false, "Unable to load file %s", filePath.c_str() );
		}
	}
	else //load from file
	{
		loader = getLoaderByFilename( filePath );

		if( loader )
		{
			retVal = loader->load( filePath );
		}
		// else nothing to do
	}

	return retVal;
}



vgd::Shp< vgd::basic::Image > loadCryptedImage( const std::string filePath, const std::string key )
{
	using vgd::basic::Image;
	vgd::Shp< Image > image;

	// Reads raw data of image
	vgd::Shp< std::vector< char > > inBuffer = readFile( filePath );

	if( !inBuffer->empty()  )
	{
		// Decrypt image
		vgd::Shp< std::vector< char > > outBuffer( new std::vector< char > );

		vgAlg::actions::Decrypt decrypt;
		decrypt.setInitialize( key, inBuffer, outBuffer );
		decrypt.execute();

		void *pixel = &(*outBuffer)[0];

		image = vgd::makeShp( new Image( filePath, pixel, outBuffer->size() ) );
	}
	else
	{
		vgAssertN( false, "Unable to load encrypt image %s", filePath.c_str() );
	}

	return image;
}


vgd::Shp< vgio::ILoader > getLoaderByFilename( const std::string filename )
{
	vgd::Shp< vgio::ILoader > retVal;

	// Retrieves the extension of the given filename.
	vgd::basic::FilenameExtractor	extractor( filename );
	const std::string				extension( extractor.getLowerCaseExtension() );

	// Get the right loader, depending on the found extension.
	//@todo modifying trian and obj loader to respect ILoader Interface.
	if ( extension.compare( ".trian2" ) == 0 )
	{
		retVal = LoaderRegistry::getLoaderRegistry()->getLoader("trian2");
	}
	else if ( extension.compare( ".trian" ) == 0 )
	{
		retVal = LoaderRegistry::getLoaderRegistry()->getLoader("trian");
	}
	else if( extension.compare( ".obj" ) == 0 )
	{
		retVal = LoaderRegistry::getLoaderRegistry()->getLoader("obj");
	}
	else if( extension.compare( ".vgarch" ) == 0 )
	{
		retVal = LoaderRegistry::getLoaderRegistry()->getLoader("vgarch");
	}
	else
	{
		retVal = LoaderRegistry::getLoaderRegistry()->getLoader("openAssetImport");
	}

	return retVal;
}



vgd::Shp< std::vector< char > > readFile( const std::string filePath )
{
	// Get file in memory
	vgd::Shp< std::vector< char > > retVal( new std::vector< char > );

	std::ifstream inFile( filePath.c_str(), std::ifstream::in | std::ifstream::binary );
	if( inFile.good() )
	{
		// Computes length
		inFile.seekg (0, std::ios::end);
		const int length = inFile.tellg();
		inFile.seekg (0, std::ios::beg);

		// Reads into retVal
		retVal->resize( length );
		inFile.read( &(*retVal)[0], length );

		if ( inFile.fail() )
		{
			retVal->resize(0);
		}
	}

	return retVal;
}



} // namespace vgio
