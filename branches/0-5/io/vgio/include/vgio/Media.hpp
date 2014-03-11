// VGSDK - Copyright (C) 2010, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGIO_MEDIA_HPP_
#define _VGIO_MEDIA_HPP_

#include <string>
#include <vector>
#include <boost/filesystem/path.hpp>
#include <vgd/Shp.hpp>

#include "vgio/vgio.hpp"



namespace vgio
{



/**
 * @brief	Provides an abstract interface for accessing files.
 *
 * A media allows to access transparently a file wherever it is on
 * the file system or in an archive, wherever it is crypted or not.
 */
struct VGIO_API Media
{
	typedef std::vector< char >	CryptoKeyType;
	
	/**
	 * @name	Cryptography
	 */
	//@{
	static void addCryptoKey( const std::string & );
	static void addCryptoKey( const CryptoKeyType & );
	static const bool hasCryptoKey( const CryptoKeyType & );
	//@}

	/**
	 * @name	File access
	 */
	//@{
	/**
	 * @brief	Tells if a given path exists on the media.
	 */
	virtual const bool exists( const boost::filesystem::path & ) const = 0;

	/**
	 * @brief	Opens the given path as a file and return the corresponding input stream.
	 */
	virtual vgd::Shp< std::istream > open( const boost::filesystem::path & ) const = 0;
	//@}

	/**
	 * @brief	Loads the given path as file into the given buffer.
	 */
	template< typename C >
	const bool load( const boost::filesystem::path & path, C & buffer ) const
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


protected:

	typedef std::vector< CryptoKeyType >	CryptoKeyContainer;

	static CryptoKeyContainer	m_cryptoKeys;	///< Holds all registered cryptographic keys.
	
};



} // namespace vgio



#endif // _VGIO_MEDIA_HPP_
