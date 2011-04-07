// VGSDK - Copyright (C) 2004, 2007, 2008, 2010, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGTRIAN_TRIANLOADER_HPP
#define _VGTRIAN_TRIANLOADER_HPP

#include <vgBase/Type.hpp>
#include "vgTrian/vgTrian.hpp"

#include <vgio/ILoader.hpp>
#include <vgio/LoaderRegistry.hpp>
#include <vgio/Media.hpp>

#include <fstream>
#include <string>
#include <utility>

#include <vector>


namespace vgTrian
{



/**
 * @brief Reading and writing .trian files
 */
struct VGTRIAN_API TrianLoader : public vgio::ILoader
{
	META_LOADER_HPP( vgTrian::TrianLoader )

	/**
	 * @brief Loads a mesh from .trian (in ascii).
	 * 
	 * Creates a VertexShape with \c vertex and \c vertexIndex fields initialized. Normals are computed.
	 *
	 * @param in		input stream to read
	 * @param group		group to save the mesh
	 * @param bCCW		true to specify conter-clockwise ordering for triangle
	 * 
	 * @return true if successful, false otherwise.
	 *
	 * @todo Support of neighbours
	 */
	const bool loadTrian( std::istream & in, vgd::Shp< vgd::node::Group > group, const bool bCCW );

	/**
	 * @brief Helper method to load a mesh from .trian (in ascii).
	 *
	 * @param pathFilename		the name of file to read
	 * @param bCCW				true to specify conter-clockwise ordering for triangle
	 *
	 * @return the newly construct VertexShape if successful, an empty smart pointer otherwise
	 */
	vgd::Shp< vgd::node::VertexShape > loadTrian( const std::string& pathFilename, const bool bCCW );


	/**
	 * @brief Saves a triset in a .trian (in ascii).
	 * 
	 * @param shape				the shape to save
	 * @param pathFilename		the name of file to read
	 * @param bCCW				true to specify conter-clockwise ordering for triangle
	 * 
	 * @return true if successful, false otherwise.
	 * 
	 * @todo Support of neighbours
	 */
	const bool saveTrian( vgd::Shp< vgd::node::VertexShape > shape, const std::string& pathFilename, const bool bCCW = true );


	// ILoader interface
	std::pair< bool, vgd::Shp< vgd::node::Group > > load( const std::string filePath, const bool bCCW = false );
	std::pair< bool, vgd::Shp< vgd::node::Group > > load( const vgio::Media & media, const std::string & filePath, const bool bCCW = false );
	std::pair< bool, vgd::Shp< vgd::node::Group > > load( const std::string filePath, vgd::Shp< std::vector< char > > buffer, const bool bCCW = false );
	std::pair< bool, vgd::Shp< vgd::node::Group > > vgDEPRECATED( load( const std::string filePath, vgd::Shp< std::vector< char > > buffer, std::map< std::string, vgd::Shp< vgd::basic::Image > > imageMap, const bool bCCW = false ) );
	vgd::Shp< vgio::ILoader > clone();
};



} // namespace vgTrian

#endif //#ifndef _VGTRIAN_LOADER_HPP
