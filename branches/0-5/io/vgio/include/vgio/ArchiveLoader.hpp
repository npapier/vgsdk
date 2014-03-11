// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGIO_ARCHIVELOADER_HPP
#define _VGIO_ARCHIVELOADER_HPP

#include "vgio/vgio.hpp"

#include <vgd/basic/Image.hpp>
#include <vgd/Shp.hpp>
#include <vgd/node/Group.hpp>
#include <vgio/ILoader.hpp>
#include <vgio/LoaderRegistry.hpp>
#include <vgPhysfs/Archive.hpp>

#include <vector>

namespace vgio
{



/**
 * @brief Support of .vgarch files
 *
 * @ingroup g_archCrypto
 * 
 */
struct VGIO_API ArchiveLoader : public ILoader
{
	META_LOADER_HPP( vgio::ArchiveLoader )
	
	ArchiveLoader();

	ArchiveLoader( std::string encryptionKey );

	/**
	 * @brief Load a model from file.
	 * 
	 * @return a pair bool/group. true if the scene succefully create. The group representing the whole scene graph.
	 */	
	virtual std::pair< bool, vgd::Shp< vgd::node::Group > > load( const std::string filePath, const bool bCCW = false );

	/**
	 * @brief Load a model from a file in memory.
	 * 
	 * @return a pair bool/group. true if the scene succefully create. The group representing the whole scene graph.
	 */
	virtual std::pair< bool, vgd::Shp< vgd::node::Group > > load( const std::string filePath, vgd::Shp< std::vector< char > > outBuffer, const bool bCCW = false );

	/**
	 * @brief Load a model from a file in memory and the list of image already load in memory.
	 * 
	 * @return a pair bool/group. true if the scene succefully create. The group representing the whole scene graph.
	 */
	virtual std::pair< bool, vgd::Shp< vgd::node::Group > > load( const std::string filePath, vgd::Shp< std::vector< char > > outBuffer, std::map< std::string, vgd::Shp< vgd::basic::Image > > imageMap, const bool bCCW = false );

	virtual vgd::Shp< ILoader > clone();

private:
	/**
	 * @brief Loads all images of the archive in memory
	 */
	void loadImages();

	vgd::Shp< vgPhysfs::Archive >							m_compression;
	vgd::Shp< vgd::node::Group >							m_root;
	std::vector< std::string >								m_directoryList;
	std::map< std::string, vgd::Shp< vgd::basic::Image > >	m_imageMap;

	std::string												m_encryptionKey;
};



} // namespace vgio

#endif //#ifndef _VGIO_ARCHIVELOADER_HPP
