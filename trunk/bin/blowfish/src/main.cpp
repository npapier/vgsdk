// VGSDK - Copyright (C) 2010, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include <fstream>
#include <string>
#include <vector>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <vgDebug/convenience.hpp>
#include <vgPhysfs/operations.hpp>




void showUsage( const char * program )
{
	vgLogMessage( "This program encrypts or decrypts files using the blowfish algorithm." );
	vgLogMessage2( "%s <encrypt|decrypt> <key> <input path> {output path}", program );
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
	std::string				command( argv[1] );
	std::vector< char >		key;
	boost::filesystem::path	inPath;
	boost::filesystem::path	outPath;

	key.resize( strlen(argv[2]) );
	std::copy( argv[2], argv[2]+key.size(), key.begin() );

	inPath = boost::filesystem::path( argv[3] );
	if( !boost::filesystem::exists(inPath) )
	{
		vgLogMessage2( "Invalid input path ", inPath.file_string().c_str() );
		return 0;
	}

	if( argc > 4 )
	{
		outPath = boost::filesystem::path( argv[4] );
	}
	

	// Process the command.
	if( command == "encrypt" )
	{
		if( outPath.empty() )
		{
			outPath = vgPhysfs::getEncryptedPath( inPath );
		}

		std::ifstream		in( inPath.file_string().c_str(), std::ios::binary );
		std::vector< char > inBuffer;
		std::ofstream		out( outPath.file_string().c_str(), std::ios::binary|std::ios::trunc );

		in.seekg( 0, std::ios::end );
		inBuffer.resize( in.tellg() );
		in.seekg( 0, std::ios::beg );
		in.read( &inBuffer[0], inBuffer.size() );
		
		vgPhysfs::encrypt( key, inBuffer, out );
	}
	else if( command == "decrypt" )
	{
		if( outPath.empty() )
		{
			outPath = inPath;
	
			if( vgPhysfs::isEncryptedPath(outPath) )
			{
				outPath.replace_extension();
			}
			else
			{
				outPath = outPath.file_string() + ".decrypted";
			}
		}
			
		// Opens the stream and checks if it contains crypted data.
		std::ifstream		in( inPath.file_string().c_str(), std::ios::binary );

		if( ! vgPhysfs::isEncrypted(in) )
		{
			vgLogMessage( "Source file does not contain valid crypted data." );
			return 0;
		}

		// Decrypts and store clear data.
		std::vector< char >	inBuffer;
		std::vector< char > outBuffer;
		
		if( vgPhysfs::decrypt(key, in, inBuffer, outBuffer) )
		{
			std::ofstream	out( outPath.file_string().c_str(), std::ios::binary|std::ios::trunc );

			out.write( &outBuffer[0], outBuffer.size() );
		}
	}
	else
	{
		vgLogMessage( "Unknown command." );
		showUsage( "blowfish" /*argv[0]*/ );
	}
	
	return 0;
}