// VGSDK - Copyright (C) 2012, 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGOPENASSETIMPORT_LOADER_HPP
#define _VGOPENASSETIMPORT_LOADER_HPP

#include "vgOpenAssetImport/vgOpenAssetImport.hpp"

#include <boost/filesystem.hpp>
#include <vgio/ILoader.hpp>
#include <vgio/LoaderRegistry.hpp>
#include <vgio/Media.hpp>



namespace vgOpenAssetImport
{

/**
 * @brief vgSDK interface for assimp loader.
 */
struct VGOPENASSETIMPORT_API Loader : public vgio::ILoader
{
	META_LOADER_HPP( vgOpenAssetImport::Loader )

	/**
	 * @name Specialized interface
	 */
	//@{

	/**
	 * @brief Default constructor
	 *
	 * @post m_flags == 0
	 */
	Loader();

	/**
	 * @brief Set the post processing steps.
	 *
	 * @param flags		Optional post processing steps to be executed after a successful import. Provide a bitwise combination of the aiPostProcessSteps flags. 
	 */
	void addPostProcessing( unsigned int flags );
	//@}


	virtual std::pair< bool, vgd::Shp< vgd::node::Group > > load( const std::string filePath, const bool bCCW = false );

	virtual std::pair< bool, vgd::Shp< vgd::node::Group > > load( const std::string filePath, vgd::Shp< std::vector< char > > inputBuffer, const bool bCCW = false );

	virtual std::pair< bool, vgd::Shp< vgd::node::Group > > vgDEPRECATED( load( const std::string filePath, vgd::Shp< std::vector< char > > outBuffer, std::map< std::string, vgd::Shp< vgd::basic::Image > > imageMap, const bool bCCW = false ) );

	std::pair< bool, vgd::Shp< vgd::node::Group > > load( const vgio::Media & media, const std::string & filePath, const bool bCCW );

	virtual vgd::Shp< ILoader > clone();

private:
	boost::filesystem::path	m_pathFilename;
	unsigned int			m_flags;
};



} // namespace vgOpenAssetImport


#endif // _VGOPENASSETIMPORT_LOADER_HPP
