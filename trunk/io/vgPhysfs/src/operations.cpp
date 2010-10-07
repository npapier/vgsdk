// VGSDK - Copyright (C) 2010, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include <fstream>
#include <vector>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <vgDebug/convenience.hpp>

#include "vgPhysfs/BlowFish.hpp"
#include "vgPhysfs/operations.hpp"



namespace vgPhysfs
{



const bool decrypt( const std::vector< unsigned char > & key, const boost::filesystem::path & inPath, const boost::filesystem::path & outPath )
{
	std::vector< unsigned char >	buffer;

	if( decrypt(key, inPath, buffer) )
	{
		std::ofstream	out( outPath.file_string().c_str(), std::ios::trunc|std::ios::binary );

		out.write( reinterpret_cast< char * >(&buffer[0]), buffer.size() );
		return out.fail() == false;
	}
	else
	{
		return false;
	}
}



const bool decrypt( const std::vector< unsigned char > & key, const boost::filesystem::path & inPath, std::vector< unsigned char > & outBuffer )
{
	const std::string	inStrPath = inPath.file_string();
	
	
	// Ensures the path exists.
	if( !boost::filesystem::exists(inPath) )
	{
		vgLogError2( "%s is not a valid path.", inStrPath.c_str() );
		return false;
	}
	
	
	// Opens the files
	std::ifstream	in( inStrPath.c_str(), std::ifstream::in | std::ifstream::binary );
	
	if( !in )
	{
		vgLogError2( "Unable to open file %s", inStrPath.c_str() );
		return false;
	}
	
	
	// Do the decryption.
	CBlowFish	blowFish( const_cast< unsigned char * >(&key[0]), key.size() );
		
	in.seekg( 0, std::ios::end );
	outBuffer.resize( in.tellg(), 0 );
	in.seekg( 0, std::ios::beg );
	
	in.read( (char*)&outBuffer[0], outBuffer.size() );
	blowFish.Decrypt( &outBuffer[0], outBuffer.size() );


	// Find the stopper (the ASCII EOT character, i.e. 0x04) and removes it.
	for( int i = outBuffer.size()-1; i > 0; --i )
	{
		if( outBuffer[i] == 0x04 )
		{
			outBuffer.resize( i );
			break;
		}
	}
	
	return true;
}
 


const bool encrypt( const std::vector< unsigned char > & key, const boost::filesystem::path & inPath, const boost::filesystem::path & outPath )
{
	const std::string	inStrPath = inPath.file_string();
	const std::string	outStrPath = outPath.file_string();
	
	
	// Ensures the path exists.
	if( !boost::filesystem::exists(inPath) )
	{
		vgLogError2( "%s is not a valid path.", inStrPath.c_str() );
		return false;
	}
	
	
	// Opens the files
	std::ifstream	in( inStrPath.c_str(), std::ifstream::in | std::ifstream::binary );
	std::ofstream	out( outStrPath.c_str(), std::ios::trunc | std::ios::binary );
	
	if( !in )
	{
		vgLogError2( "Unable to open file %s", inStrPath.c_str() );
		return false;
	}
	
	if( !out )
	{
		vgLogError2( "Unable to create output file %s", outStrPath.c_str() );
		return false;
	}
	
	
	// Do the encryption.
	CBlowFish						blowFish( const_cast< unsigned char * >(&key[0]), key.size() );
	std::vector< unsigned char >	buffer;
	unsigned int					fileSize;
	unsigned int					bufferSize;
	
	// Gets the file size.
	in.seekg( 0, std::ios::end );
	fileSize = in.tellg();
	in.seekg( 0, std::ios::beg );
	
	// Computes the buffer size (it must be a multiple of 8) and create space for a stopper.
	if( fileSize % 8 )
	{
		bufferSize = (fileSize / 8 + 1) * 8;
	}
	else
	{
		bufferSize = fileSize + 8;
	}
	
	// Resizes the data buffer and places the stopper (the ASCII EOT character, i.e. 0x04).
	buffer.resize( bufferSize, 0 );
	buffer[fileSize] = 0x04;

	// Loads, encrypts and saves encrypted data.
	in.read( (char*)&buffer[0], fileSize );
	blowFish.Encrypt( &buffer[0], buffer.size() );
	out.write( (char*)&buffer[0], buffer.size() );

	return true;
}



} // namespace vgPhysfs
