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




} // namespace vgio
