// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgPhysfs/Archive.hpp"

#include <vgd/basic/FilenameExtractor.hpp>

namespace vgPhysfs
{



Archive::Archive( std::string filePath ) :
m_filePath( filePath )
{
	PHYSFS_init(NULL);

	PHYSFS_addToSearchPath( filePath.c_str(), 1);
}



Archive::~Archive()
{
	PHYSFS_deinit();
}



std::vector< std::string > Archive::getFileList( std::string directory )
{
	char** list = PHYSFS_enumerateFiles( directory.c_str() );
	int i = 0;
	std::vector< std::string > fileList;
	while( list[i] )
	{
		// Retrieves the extension of the given filename.
		vgd::basic::FilenameExtractor	extractor(list[i] );
		std::string						extension = extractor.getExtension();

		if( extension.compare( "" ) != 0 ) //is not a directory
		{
			fileList.push_back( list[i] );
		}
		i++;
	}

	return fileList;
}



std::vector< std::string > Archive::getDirectoryList()
{
	std::vector< std::string > directoryList;
	directoryList.push_back( "" ); //adds root directory

	char** list = PHYSFS_enumerateFiles( "" );
	int i = 0;

	while( list[i] )
	{
		// Retrieves the extension of the given filename.
		vgd::basic::FilenameExtractor	extractor(list[i] );
		std::string						extension = extractor.getExtension();

		if( extension.compare( "" ) == 0 ) //is not a directory		
		{
			directoryList.push_back( list[i] );
		}
		i++;
	}	

	return directoryList;
}



bool Archive::fileExists( std::string filename )
{
	int exists = PHYSFS_exists( filename.c_str() );

	if( exists == 1 )
	{
		return true;
	}

	return false;
}



void Archive::getFile( std::string filename, vgd::Shp< std::vector< char > > buffer, bool write )
{
	//close last file before opening a new one.
	if( m_currentFile )
	{
		PHYSFS_close( m_currentFile );
	}
	
	if( write )
	{
		m_currentFile = PHYSFS_openWrite( filename.c_str() );
	}
	else
	{
		m_currentFile = PHYSFS_openRead( filename.c_str() );
	}


	//buffer.reset( new std::vector< char > );
	buffer->resize( PHYSFS_fileLength( m_currentFile ) );
	int length_read = PHYSFS_read( m_currentFile, &(*buffer)[0], 1, PHYSFS_fileLength( m_currentFile ));
	//length_read = ( ( length_read + 7 ) &~7 ); //lenght must be a multiple of 8

	buffer->resize( length_read );
}



void Archive::closeFile()
{
	PHYSFS_close( m_currentFile );
}



} // namespace vgPhysfs
