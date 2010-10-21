// VGSDK - Copyright (C) 2010, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include "vgio/FileSystem.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <boost/filesystem/operations.hpp>
#include <vgPhysfs/operations.hpp>



namespace vgio
{



const bool FileSystem::exists( const boost::filesystem::path & path ) const
{
	if( boost::filesystem::exists(path) )
	{
		return true;
	}
	else
	{
		return boost::filesystem::exists( vgPhysfs::getEncryptedPath(path) );
	}
}



vgd::Shp< std::istream > FileSystem::open( const boost::filesystem::path & path ) const
{
	const boost::filesystem::path	clearPath( path );

	if( boost::filesystem::exists(clearPath) )
	{
		return vgd::Shp< std::istream >( new std::ifstream(clearPath.file_string().c_str(), std::ios::binary) );
	}
	else
	{
		const boost::filesystem::path	cryptedPath = vgPhysfs::getEncryptedPath( clearPath );

		// Ensures a crypted file exists.
		if( !boost::filesystem::exists(cryptedPath) )
		{
			std::cerr << "Unable to find eithed clear or crypted version of " << clearPath << std::endl;
			return vgd::Shp< std::istream >();
		}


		// Ensures there is at least one crypto key.
		CryptoKeyContainer::const_iterator	i = m_cryptoKeys.begin();

		if( i == m_cryptoKeys.end() )
		{
			std::cerr << "Unable to open the crypted file " << clearPath << " because no key is available " << std::endl;
			return vgd::Shp< std::istream >();
		}


		// Tryes the first key.
		std::ifstream		inStream( cryptedPath.file_string().c_str(), std::ios::binary );
		std::vector< char >	cryptBuffer;
		std::vector< char > clearBuffer;
		bool				decrypted;

		decrypted = vgPhysfs::decrypt( *i, inStream, cryptBuffer, clearBuffer );
		

		// If the first key failed, tries other keys.
		if( !decrypted )
		{
			for(; i != m_cryptoKeys.end(); ++i)
			{
				if( vgPhysfs::decrypt(*i, cryptBuffer, clearBuffer) )
				{
					break;
				}
			}
		}


		// If the decryption failed, then reset data and warn about the problem.
		if( i == m_cryptoKeys.end() )
		{
			std::cerr << "Unable to decrypt " << cryptedPath << std::endl;
			return vgd::Shp< std::istream >();
		}


		// Builds a string stream with the clear buffer data.
		// @todo Optimization by reducing the number of data copies...
		std::string	strBuffer;

		strBuffer.resize( clearBuffer.size() );
		std::copy( clearBuffer.begin(), clearBuffer.end(), strBuffer.begin() );

		return vgd::Shp< std::istream >( new std::istringstream(strBuffer) );
	}
}



} // namespace vgio
