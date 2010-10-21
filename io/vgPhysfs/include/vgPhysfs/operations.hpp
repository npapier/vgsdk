// VGSDK - Copyright (C) 2010, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGPHYSFS_OPERATIONS_HPP_
#define _VGPHYSFS_OPERATIONS_HPP_

#include <vector>
#include <boost/filesystem/path.hpp>

#include "vgPhysfs/vgPhysfs.hpp"



namespace vgPhysfs
{


/**
 * @brief	Transforms the given path to remove encryption information.
 */
VGPHYSFS_API const std::string getDecryptedPath( const std::string & );

/**
 * @brief	Transforms the given path to remove encryption information.
 */
VGPHYSFS_API const boost::filesystem::path getDecryptedPath( const boost::filesystem::path & );

/**
 * @brief	Transforms the given path to add encryption information.
 */
VGPHYSFS_API const std::string getEncryptedPath( const std::string & );

/**
 * @brief	Transforms the given path to add encryption information.
 */
VGPHYSFS_API const boost::filesystem::path getEncryptedPath( const boost::filesystem::path & );

/**
 * @brief	Tells if the given stream contains crypted data.
 */
VGPHYSFS_API const bool isEncrypted( std::istream & in );

/**
 * @brief	Tells if the given path contains the encryption extension.
 */
VGPHYSFS_API const bool isEncryptedPath( const std::string & );

/**
 * @brief	Tells if the given path contains the encryption extension.
 */
VGPHYSFS_API const bool isEncryptedPath( const boost::filesystem::path & );

/**
 * @brief	Decrypts the given input buffer to the given output buffer using the blowfish algorithm.
 */
VGPHYSFS_API const bool decrypt( const std::vector< char > & key, const std::vector< char > & inBuffer, std::vector< char > & outBuffer );

/**
 * @brief	Loads crypted data from the given intput stream in the the input buffer and decrypts into the given output buffer using the blowfish algorithm.
 *
 * @remark	The inBuffer will receive a copy of the crypted data in order to allow later decryption tries if the one done at loadin failes.
 */
VGPHYSFS_API const bool decrypt( const std::vector< char > & key, std::istream & inStream, std::vector< char > & inBuffer, std::vector< char > & outBuffer );

/**
 * @brief	Encrypts the given input buffer into the given output buffer using the blowfish algorithm.
 */
VGPHYSFS_API void encrypt( const std::vector< char > & key, const std::vector< char > & inBuffer, std::vector< char > & outBuffer );

/**
 * @brief	Encrypts the given input buffer into the given output stream using the blowfish algorithm.
 */
VGPHYSFS_API void encrypt( const std::vector< char > & key, const std::vector< char > & inBuffer, std::ostream & outStream );



} // namespace vgPhysfs



#endif // _VGPHYSFS_OPERATIONS_HPP_