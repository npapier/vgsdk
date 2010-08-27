// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgio/helpers.hpp"

#include <fstream>

#include <vgAlg/actions/Decrypt.hpp>
#include <vgio/LoaderRegistry.hpp>

#include <vgd/basic/FilenameExtractor.hpp>
#include <vgd/basic/Image.hpp>
#include <vgDebug/convenience.hpp>

namespace vgio
{



std::pair< bool, vgd::Shp< vgd::node::Group > > load( std::string filePath )
{
	std::pair< bool, vgd::Shp< vgd::node::Group > > retVal;

	// Retrieves the extension of the given filename.
	vgd::basic::FilenameExtractor	extractor( filePath.c_str() );
	std::string						extension = extractor.getExtension();
	std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower); //to lowercase;

	vgd::Shp< vgio::ILoader > loader;

	if ( extension.compare( ".crypt" ) == 0 ) //load crypted file ==> from memory
	{
		//Get file in memory.
		std::ifstream inFile;
		vgd::Shp< std::vector< char > > inBuffer( new std::vector< char > );
		inFile.open( filePath.c_str(), std::ifstream::in | std::ifstream::binary );

		if( inFile.good() )
		{
			inFile.seekg (0, std::ios::end);
			int length = inFile.tellg();
			inFile.seekg (0, std::ios::beg);

			inBuffer->resize( length );
			inFile.read( &(*inBuffer)[0], length );
		}
		else
		{
			retVal.first = false;
			return retVal;
		}
		
		vgd::Shp< std::vector< char > > outBuffer( new std::vector< char > );
		vgAlg::actions::Decrypt decrypt;
		decrypt.setInitialize( "vgsdkViewerGTK", (*inBuffer.get()), outBuffer );
		decrypt.execute();

		filePath = extractor.getPath() + "/" + extractor.getFilenameWithoutExtension();
		loader = getLoaderByFilename( filePath );

		if( loader )
		{
			retVal = loader->load( filePath, outBuffer );
		}
		else
		{
			retVal.first = false;
		}
	}
	else //load from file
	{
		loader = getLoaderByFilename( filePath );

		if( loader )
		{
			retVal = loader->load( filePath );
		}
		else
		{
			retVal.first = false;
		}
	}

	return retVal;
}



vgd::Shp< vgio::ILoader > getLoaderByFilename( std::string filename )
{
	vgd::Shp< vgio::ILoader > retVal;
	
	// Retrieves the extension of the given filename.
	vgd::basic::FilenameExtractor	extractor( filename.c_str() );
	std::string						extension = extractor.getExtension();

	std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower); //to lowercase;

	// Get the right loader, depending on the found extension.
	//@todo modifying train and obj loader to respect ILoader Interface.
	if ( /* extension.compare( ".trian" ) == 0 || */extension.compare( ".trian2" ) == 0 )
	{
		retVal = LoaderRegistry::getLoaderRegistry()->getLoader( "trian");
	}
	else if ( extension.compare( ".dae" ) == 0 )
	{
		retVal = LoaderRegistry::getLoaderRegistry()->getLoader( "collada");
	}
	else if( extension.compare( ".obj" ) == 0 )
	{
		//retVal = LoaderRegistry::getLoaderRegistry()->getLoader( "obj");
		vgDebug::get().logWarning( "Unknown file extension in %s.", filename.c_str() );
	}
	else if( extension.compare( ".vgarch" ) == 0 )
	{
		retVal = LoaderRegistry::getLoaderRegistry()->getLoader( "vgarch");
	}
	else
	{
		vgDebug::get().logWarning( "Unknown file extension in %s.", filename.c_str() );
	}

	return retVal;
}



vgd::Shp< vgd::basic::Image > loadCryptedImage( std::string filePath, std::string key )
{
	vgd::Shp< vgd::basic::Image > img;
	vgd::Shp< std::vector< char > > inBuffer( new std::vector< char > );

	std::ifstream inFile;
	inFile.open( filePath.c_str(), std::ifstream::in | std::ifstream::binary );
	if( inFile.good() )
	{
		inFile.seekg (0, std::ios::end);
		int length = inFile.tellg();
		inFile.seekg (0, std::ios::beg);

		inBuffer->resize( length );
		inFile.read( &(*inBuffer)[0], length );

		vgd::Shp< std::vector< char > > outBuffer( new std::vector< char > );

		vgAlg::actions::Decrypt decrypt;
		decrypt.setInitialize( key, (*inBuffer.get()), outBuffer );
		decrypt.execute();

		inBuffer = outBuffer;
		
		void *pixel = &(*inBuffer)[0];

		img = vgd::Shp< vgd::basic::Image >( new vgd::basic::Image( filePath, pixel, inBuffer->size() ) );
	}
	else
	{
		assert( false && "Unable to load image file" );
	}
	return img;
}



} // namespace vgio