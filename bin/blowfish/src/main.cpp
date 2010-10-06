// VGSDK - Copyright (C) 2010, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include <string>
#include <vector>
#include <boost/filesystem/path.hpp>
#include <vgDebug/convenience.hpp>
#include <vgPhysfs/operations.hpp>




void showUsage( const char * program )
{
	vgLogMessage( "This program encrypts or decrypts files using the blowfish algorithm." );
	vgLogMessage2( "%s <encrypt|decrypt> <key> <file> [file...]", program );
}



int main( int argc, char ** argv )
{
	// Checks that all required arguments are passed
	if( argc < 4 )
	{
		vgLogMessage( "Missing arguments. Usage :" );
		showUsage( "blowfish" /*argv[0]*/ );
		return 0;
	}
	
	// Gets all arguments
	typedef std::vector< boost::filesystem::path > PathContainer;
	
	std::string						command( argv[1] );
	std::vector< unsigned char >	key;
	PathContainer					files;

	key.resize( strlen(argv[2]) );
	std::copy( argv[2], argv[2]+key.size(), key.begin() );
	
	for( int i = 3; i < argc; ++i )
	{
		files.push_back( boost::filesystem::path(argv[i]) );
	}
	
	// Process the command.
	if( command == "encrypt" )
	{
		for( PathContainer::const_iterator i = files.begin(); i != files.end(); ++i )
		{
			vgPhysfs::encrypt( key, *i, i->file_string()+".encrypted" );
		}
	}
	else if( command == "decrypt" )
	{
		for( PathContainer::const_iterator i = files.begin(); i != files.end(); ++i )
		{
			boost::filesystem::path	out = *i;
			
			if( out.extension() == ".encrypted" )
			{
				out.replace_extension();
			}
			else
			{
				out = out.file_string() + ".decrypted";
			}
			
			vgPhysfs::decrypt( key, *i, out );
		}
	}
	else
	{
		vgLogMessage( "Unknown command." );
		showUsage( "blowfish" /*argv[0]*/ );
	}
	
	return 0;
}