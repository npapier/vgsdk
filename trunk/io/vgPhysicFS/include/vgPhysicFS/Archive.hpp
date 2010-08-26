// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGPHYSICFS_ARCHIVE_HPP
#define _VGPHYSICFS_ARCHIVE_HPP

#include "vgPhysicFS/vgPhysicFS.hpp"

#include <vgd/Shp.hpp>

#include <physfs.h>
#include <string>
#include <vector>

namespace vgPhysicFS
{

/**
 * @brief Open and extract compressed files.
 */
struct VGPHYSICFS_API Archive 
{
	/**
	 * @brief	Open an archive.
	 *
	 * @param filePath	Path of the archive to open.
	 */
	Archive( std::string filePath );

	~Archive();

	/**
	 * @brief	Get a list of all file in directory.
	 *
	 * @param directory	Directory to retrieve file list (default = root dir).
	 */
	std::vector< std::string > getFileList( std::string directory = "" );

	/**
	 * @brief	Get a list of all file in directory.
	 *
	 * @return	List of all directories.
	 */
	std::vector< std::string > getDirectoryList();

	/**
	 * @brief	Check if file exists.
	 *
	 * @param filename	Path of the archive to open.
	 */
	bool fileExists( std::string filename );

	/**
	 * @brief	Get a file with its name.
	 *
	 * @param filename	filename to open.
	 *
	 * @param buffer	buffer of the file.
	 *
	 * @param write		open mode (true to write, false to read).
	 */
	void getFile( std::string filename, vgd::Shp< std::vector< char > > buffer, bool write = false );

	/**
	 * @brief	Close current file.
	 */
	void closeFile();

private:
	std::string		m_filePath;
	PHYSFS_file*	m_currentFile;
};

} // namespace vgPhysicFS

#endif //#ifndef _VGPHYSICFS_ARCHIVE_HPP
