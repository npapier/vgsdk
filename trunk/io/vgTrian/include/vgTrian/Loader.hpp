// VGSDK - Copyright (C) 2004, 2007, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGTRIAN_LOADER_HPP
#define _VGTRIAN_LOADER_HPP

#include "vgTrian/vgTrian.hpp"

#include <vgio/ILoader.hpp>
#include <vgio/LoaderRegistry.hpp>

#include <fstream>
#include <sstream>
#include <string>
#include <utility>

#include <vector>


namespace vgTrian
{



/**
 * @brief Support of .trian/.trian2 files
 * 
 * @todo computeNormals for trian file (see vgd::node::VertexShape). 
 * @todo Support of vgd::node::TriSet
 * @todo Uses boost::filesystem
 * 
 * @todo remove char* and use std::string instead
 */
struct VGTRIAN_API Loader : public vgio::ILoader
{
	META_LOADER_HPP( vgTrian::Loader )
	
	/**
	 * @brief Loads a mesh from .trian (in ascii).
	 * 
	 * Create vertex, edge tables, but don't create normals(nor neighbours).
	 *
	 * @param pathFilename	the name of file to read.
	 * @param bCCW		true to specify conter-clockwise ordering for triangle
	 * 
	 * @return true if successful, false otherwise and a smart pointer on node if sucessful.
	 * 
	 * @deprecated Uses loadTrian method that creates a TriSet node.
	 */
	std::pair< bool, vgd::Shp< vgd::node::VertexShape > > loadTrian( const char *pathFilename, const bool bCCW = false );

	/**
	 * @brief Loads a mesh from .trian (in ascii).
	 * 
	 * Create vertex, edge tables, but don't create normals(nor neighbours).
	 *
	 * @param pathFilename	the name of file to read.
	 * @param bCCW		true to specify conter-clockwise ordering for triangle
	 * 
	 * @return true if successful, false otherwise and a smart pointer on node if sucessful.
	 * 
	 * @todo create TriSet(with neighbours) insteed of VertexShape.
	 */
	std::pair< bool, vgd::Shp< vgd::node::TriSet > > loadTrian( const std::string& pathFilename, const bool bCCW = false );

	/**
	 * @brief Saves a triset in a .trian (in ascii).
	 * 
	 * @param triset			the shape to save
	 * @param pathFilename	the name of file to read.
	 * @param bCCW		true to specify conter-clockwise ordering for triangle
	 * 
	 * @return true if successful, false otherwise.
	 * 
	 * @todo Support of neighbours
	 */
	const bool saveTrian( vgd::Shp< vgd::node::TriSet > triset, const std::string& pathFilename, const bool bCCW = true );

	/**
	 * @brief Load a model from file.
	 * 
	 * @return a pair bool/group. true if the scene succefully create. The group representing the whole scene graph.
	 */	
	std::pair< bool, vgd::Shp< vgd::node::Group > > load( const std::string filePath, const bool bCCW = false );

	/**
	 * @brief Load a model from a file in memory.
	 * 
	 * @return a pair bool/group. true if the scene succefully create. The group representing the whole scene graph.
	 */
	std::pair< bool, vgd::Shp< vgd::node::Group > > load( const std::string filePath, vgd::Shp< std::vector< char > > outBuffer, const bool bCCW = false );

	/**
	 * @brief Load a model from a file in memory and the list of image already load in memory.
	 * 
	 * @return a pair bool/group. true if the scene succefully create. The group representing the whole scene graph.
	 */
	std::pair< bool, vgd::Shp< vgd::node::Group > > load( const std::string filePath, vgd::Shp< std::vector< char > > outBuffer, std::map< std::string, vgd::Shp< vgd::basic::Image > > imageMap, const bool bCCW = false );


	/**
	 * @brief Same as load function.
	 *
	 * @todo	remove it and only use load function.
	 */
	// * param useCache		true to use cache system for image
	std::pair< bool, vgd::Shp< vgd::node::Group > >	loadTrian2( const char *pathFilename, bool bCCW = false );
	//, const bool useCache = false );


	virtual vgd::Shp< vgio::ILoader > clone();

private:
	/**
	 * @name Used by loadTrian2.
	 */
	//@{

	/**
	 * @brief Loads a mesh from .trian2 (in ascii) : stringstream already initilized from one of the load method.
	 * 
	 * Create vertex, edge tables...., but don't create normals(nor neighbours).
	 *
	 * @param group	group to save the mesh.
	 *
	 * @return true if successful, false otherwise.
	 * 
	 * @remark Experimental format (files .trian2 are created by 3DSMax vgsdkExporter plugins).
	 * 
	 * @todo create TriSet(with neighbours) insteed of VertexShape.
	 */	
	bool loadTrian2( vgd::Shp< vgd::node::Group > group );

	vgd::Shp< vgd::node::Switch >		loadMaterials	();
	
	void								loadTextureMaps( vgd::Shp< vgd::node::Group > group );

	vgd::Shp< vgd::node::VertexShape >	loadMesh		( std::string meshName );
	
	vgd::Shp< vgd::node::Material >		loadWireColor	( std::string nodeName );



	std::stringstream	m_fp;

//	bool				m_useCache;			///< true to use cache system for image, false otherwise

	/**
	 * @brief Path for the file.
	 */
	std::string			m_path; 
	
	//@}

	std::map< std::string, vgd::Shp< vgd::basic::Image > > m_imageMap;
};



} // namespace vgTrian

#endif //#ifndef _VGTRIAN_LOADER_HPP
