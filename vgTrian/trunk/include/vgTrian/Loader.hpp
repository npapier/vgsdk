// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGTRIAN_LOADER_H
#define _VGTRIAN_LOADER_H

#include "vgTrian/vgTrian.hpp"

#include <fstream>
#include <utility>
#include <vgd/node/Group.hpp>
#include <vgd/node/Material.hpp>
#include <vgd/node/Switch.hpp>
#include <vgd/node/VertexShape.hpp>



namespace vgTrian
{



struct VGTRIAN_API Loader
{
	/**
	 * @brief Loads a mesh from .trian (in ascii).
	 * 
	 * Create vertex, edge tables, but don't create normals(nor neighbours).
	 *
	 * @param pathFilename the name of file to read.
	 * 
	 * @return true if successful, false otherwise and a smart pointer on node if sucessful.
	 * 
	 * @todo create TriSet(with neighbours) insteed of VertexShape.
	 */
	std::pair< bool, vgd::Shp< vgd::node::VertexShape > >
			loadTrian( const char *pathFilename, bool bCCW = false );

	/**
	 * @brief Loads a mesh from .trian2 (in ascii).
	 * 
	 * Create vertex, edge tables...., but don't create normals(nor neighbours).
	 *
	 * @param pathFilename the name of file to read.
	 * 
	 * @return true if successful, false otherwise.
	 * 
	 * @remark Experimental format (files .trian2 are created by 3DSMax vgsdkExporter plugins).
	 * 
	 * @todo create TriSet(with neighbours) insteed of VertexShape.
	 */
	std::pair< bool, vgd::Shp< vgd::node::Group > >	
		loadTrian2( const char *pathFilename, bool bCCW = false );

private:
	/**
	 * @name Used by loadTrian2.
	 */
	//@{
	
	vgd::Shp< vgd::node::Switch >			loadMaterials	();
	
	void											loadTextureMaps( vgd::Shp< vgd::node::Group > group );

	vgd::Shp< vgd::node::VertexShape >	loadMesh			( std::string meshName );
	
	vgd::Shp< vgd::node::Material >		loadWireColor	( std::string nodeName );
	
	
	
	std::ifstream		m_fp;

	/**
	 * @brief Path for the file.
	 */
	std::string			m_path; 
	
	//@}
};



} // namespace vgTrian

#endif //#ifndef _VGTRIAN_LOADER_H
