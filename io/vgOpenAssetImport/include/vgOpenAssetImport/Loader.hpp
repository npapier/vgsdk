// VGSDK - Copyright (C) 2012, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGOPENASSETIMPORT_LOADER_HPP
#define _VGOPENASSETIMPORT_LOADER_HPP

#include "vgOpenAssetImport/vgOpenAssetImport.hpp"

#include <boost/filesystem.hpp>
#include <vgio/ILoader.hpp>
#include <vgio/LoaderRegistry.hpp>
//#include <vgio/Media.hpp>



namespace vgOpenAssetImport
{

/**
 * @brief vgSDK interface for assimp loader.
 */
struct VGOPENASSETIMPORT_API Loader : public vgio::ILoader
{
	META_LOADER_HPP( vgOpenAssetImport::Loader )

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
	boost::filesystem::path m_pathFilename;
};



} // namespace vgOpenAssetImport


#endif // _VGOPENASSETIMPORT_LOADER_HPP
