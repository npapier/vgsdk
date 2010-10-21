// VGSDK - Copyright (C) 2010, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include "vgio/Media.hpp"



namespace vgio
{



Media::CryptoKeyContainer Media::m_cryptoKeys;



void Media::addCryptoKey( const std::string & strKey )
{
	CryptoKeyType	key;

	key.resize( strKey.size() );
	std::copy( strKey.begin(), strKey.end(), key.begin() );
	addCryptoKey( key );
}



void Media::addCryptoKey( const CryptoKeyType & key )
{
	if( ! hasCryptoKey(key) )
	{
		m_cryptoKeys.push_back( key );
	}
}



const bool Media::hasCryptoKey( const CryptoKeyType & key )
{
	return std::find(m_cryptoKeys.begin(), m_cryptoKeys.end(), key) != m_cryptoKeys.end();
}



const bool Media::load( const boost::filesystem::path & path, std::vector< char > & buffer ) const
{
	// Opens the input stream.
	vgd::Shp< std::istream >	in = open(path);
	
	if( !in )
	{
		buffer.resize(0);
		return false;
	}
	

	// Loads the stream content.
	in->seekg( 0, std::ios::end );
	buffer.resize( in->tellg() );
	in->seekg( 0, std::ios::beg );
	in->read( &buffer[0], buffer.size() );

	if( in->fail() )
	{
		buffer.resize(0);
		return false;
	}


	// Job's done.
	return true;
}



} // namespace vgio
