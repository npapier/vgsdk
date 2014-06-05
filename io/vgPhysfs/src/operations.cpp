// VGSDK - Copyright (C) 2010, 2011, 2014, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include <cassert>
#include <vector>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

#include <vgDebug/helpers.hpp>

#include "vgPhysfs/Blowfish.hpp"
#include "vgPhysfs/operations.hpp"



namespace vgPhysfs
{



struct StreamHeader
{
	char	signature[8];
	int64	dataSize;
};

static const std::string	encryptedExtension(".encrypted");
static const std::string	headerSignature("vgBlow01");
static const std::string	bufferSignature("vgBuffer");



const std::string getDecryptedPath( const std::string & path )
{
	return getDecryptedPath( boost::filesystem::path(path) ).string();
}



const boost::filesystem::path getDecryptedPath( const boost::filesystem::path & path )
{
	if( path.extension() == encryptedExtension )
	{
		return boost::filesystem::path(path).replace_extension();
	}
	else
	{
		return path;
	}
}



const std::string getEncryptedPath( const std::string & path )
{
	return getEncryptedPath( boost::filesystem::path(path) ).string();
}



const boost::filesystem::path getEncryptedPath( const boost::filesystem::path & path )
{
	const std::string	extension = path.extension().string();

	if( extension != encryptedExtension )
	{
		//boost::filesystem::path	result( path );
		//result.replace_extension( extension + encryptedExtension ); // Ticket Boost 5118
		boost::filesystem::path	result( path.string()+encryptedExtension );
		return result;
	}
	else
	{
		return path;
	}
}



const bool isEncrypted( std::istream & in )
{
	assert( in.good() );

	// Reads the header.
	unsigned int	headerIndex;
	unsigned int	dataIndex;
	StreamHeader	header;

	headerIndex = in.tellg();
	in.read( (char*) &header, sizeof(header) );
	dataIndex = in.tellg();
	
	// Ensures that the whole header has been read.
	if( (dataIndex - headerIndex) != sizeof(header) )
	{
		return false;
	}

	// Ensures the signature is good.
	if( ! std::equal(headerSignature.begin(), headerSignature.end(), header.signature) )
	{
		return false;
	}
	
	// Ensures the whole data load is present.
	unsigned int	endIndex;

	in.seekg( static_cast< int >(header.dataSize), std::ios::cur );
	endIndex = in.tellg();
	if( (endIndex - dataIndex) != header.dataSize )
	{
		return false;
	}


	// Restore the stream read position.
	in.seekg( headerIndex, std::ios::beg );


	// Passed all test successfully.
	return true;
}



const bool isEncryptedPath( const std::string & path )
{
	return isEncryptedPath( boost::filesystem::path(path) );
}



const bool isEncryptedPath( const boost::filesystem::path & path )
{
	return path.extension() == encryptedExtension;
}



const bool decrypt( const std::vector< char > & key, const std::vector< char > & inBuffer, std::vector< char > & outBuffer )
{
	// Ensures the input buffer size is a multiple of 8 and can container the stopper and the signature.
	const unsigned int inSize = inBuffer.size();

	if( inSize % 8 != 0 || inSize < 16 )
	{
		vgLogError( "Unable to decrypt data: input buffer has not a valid size." );
		outBuffer.resize( 0 );
		return false;
	}


	// Decrypts
	CBlowFish		blowFish( reinterpret_cast< unsigned char * >(const_cast< char * >(&key[0])), key.size() );
	unsigned int	outSize = inSize;

	outBuffer.resize( outSize );
	std::copy( inBuffer.begin(), inBuffer.end(), outBuffer.begin() );
	blowFish.Decrypt( reinterpret_cast< unsigned char * >(&outBuffer[0]), outSize );

	// Checks the signature and removes the signature.
	if( !std::equal(bufferSignature.begin(), bufferSignature.end(), &outBuffer[outSize-8]) )
	{
		vgLogError( "Unable to decrypt data: data is inappropriated or key is invalid." );
		outBuffer.resize( 0 );
		return false;
	}
	else
	{
		outBuffer.resize( outSize - 8 );
		outSize = outBuffer.size();
	}


	// Find the stopper (the ASCII EOT character, i.e. 0x04) and removes it with trailing bytes.
	const char	* begin		= &outBuffer[0] + outSize - 8;
	const char	* end		= &outBuffer[0] + outSize;
	const char	* stopper	= std::find( begin, end, 0x04 );

	if( stopper != end )
	{
		outBuffer.resize( outSize - (end-stopper) );
		return true;
	}
	else
	{
		vgLogDebug( "Unable to decrypt data: malformed data." );
		outBuffer.resize( 0 );
		return false;
	}

	return false;
}



const bool decrypt( const std::vector< char > & key, std::istream & inStream, std::vector< char > & inBuffer, std::vector< char > & outBuffer )
{
	assert( inStream.good() );

	// Reads and checks the data signature.
	StreamHeader	header;

	inStream.read( (char*)&header, sizeof(StreamHeader) );
	if( !std::equal(headerSignature.begin(), headerSignature.end(), header.signature) )
	{
		vgLogError( "Unable to decrypt data: stream does not containe valid data." );
		inBuffer.resize( 0 );
		outBuffer.resize( 0 );
		return false;
	}

	// Get the encrypted data size and reads the data.
	inBuffer.resize( static_cast< size_t >(header.dataSize) );
	inStream.read( &inBuffer[0], inBuffer.size() );

	if( inStream.fail() )
	{
		vgLogError( "Unable to decrypt data: error while reading data from stream." );
		inBuffer.resize( 0 );
		outBuffer.resize( 0 );
		return false;
	}

	// Do the decryption.
	return decrypt( key, inBuffer, outBuffer );
}




void encrypt( const std::vector< char > & key, const std::vector< char > & inBuffer, std::vector< char > & outBuffer )
{
	// Computes the output buffer size (it must be a multiple of 8) and create space for a stopper and signature.
	const unsigned int	inSize	= inBuffer.size();
	unsigned int		outSize	= 0;

	if( inSize % 8 )
	{
		outSize = (inSize / 8 + 1) * 8 + 8;
	}
	else
	{
		outSize = inSize + 8 + 8;
	}
		

	// Resizes the output buffer, places the stopper (the ASCII EOT character, i.e. 0x04) and the signature.
	outBuffer.resize( outSize, 0 );
	outBuffer[inSize] = 0x04;
	std::copy( bufferSignature.begin(), bufferSignature.end(), &outBuffer[outSize-8] );


	// Encrypts data.
	CBlowFish	blowFish( reinterpret_cast< unsigned char * >(const_cast< char * >(&key[0])), key.size() );

	std::copy( inBuffer.begin(), inBuffer.end(), outBuffer.begin() );
	blowFish.Encrypt( reinterpret_cast< unsigned char * >(&outBuffer[0]), outBuffer.size() );
}



void encrypt( const std::vector< char > & key, const std::vector< char > & inBuffer, std::ostream & outStream )
{
	assert( outStream.good() );

	std::vector< char >	outBuffer;
	unsigned int		outSize;

	// Encrypts data.
	encrypt( key, inBuffer, outBuffer );
	outSize = outBuffer.size();

	// Writes file content.
	StreamHeader	header;

	std::copy( headerSignature.begin(), headerSignature.end(), header.signature );
	header.dataSize = outSize;

	outStream.write( (char*)&header, sizeof(StreamHeader) );
	outStream.write( &outBuffer[0], outBuffer.size() );
}
 


} // namespace vgPhysfs
