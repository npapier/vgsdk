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
 * @brief	Decrypts the given source file to the given destination file using the blowfish algorithm.
 */
VGPHYSFS_API const bool decrypt( const std::vector< unsigned char > & key, const boost::filesystem::path & inPath, const boost::filesystem::path & outPath );

/**
 * @brief	Decrypts the given source file to the given destination buffer using the blowfish algorithm.
 */
VGPHYSFS_API const bool decrypt( const std::vector< unsigned char > & key, const boost::filesystem::path & inPath, std::vector< unsigned char > & outBuffer );
 
/**
 * @brief	Encrypts the given source file to the given destination file using the blowfish algorithm.
 */
VGPHYSFS_API const bool encrypt( const std::vector< unsigned char > & key, const boost::filesystem::path & inPath, const boost::filesystem::path & outPath );



} // namespace vgPhysfs



#endif // _VGPHYSFS_OPERATIONS_HPP_