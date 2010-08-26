// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGIO_LOADER_HPP
#define _VGIO_LOADER_HPP

#include <utility>
#include <string>
#include <vector>
#include <map>

#include "vgio/vgio.hpp"

namespace vgd
{
	template<class T> struct Shp;

	namespace basic
	{
		struct Image;
	}
	
	namespace node
	{
		struct Group;
		struct Material;
		struct Switch;
		struct TriSet;
		struct VertexShape;
	}
}



namespace vgio
{

/**
 * @brief vgsdk interface for model loader.
 */
struct VGIO_API ILoader
{
	/**
	 * @brief Load a model from file.
	 * 
	 * @return a pair bool/group. true if the scene succefully create. The group representing the whole scene graph.
	 */	
	virtual std::pair< bool, vgd::Shp< vgd::node::Group > > load( const std::string filePath, const bool bCCW = false ) = 0;

	/**
	 * @brief Load a model from a file in memory.
	 * 
	 * @return a pair bool/group. true if the scene succefully create. The group representing the whole scene graph.
	 */
	virtual std::pair< bool, vgd::Shp< vgd::node::Group > > load( const std::string filePath, vgd::Shp< std::vector< char > > outBuffer, const bool bCCW = false ) = 0;

	/**
	 * @brief Load a model from a file in memory and the list of image already load in memory.
	 * 
	 * @return a pair bool/group. true if the scene succefully create. The group representing the whole scene graph.
	 */
	virtual std::pair< bool, vgd::Shp< vgd::node::Group > > load( const std::string filePath, vgd::Shp< std::vector< char > > outBuffer, std::map< std::string, vgd::Shp< vgd::basic::Image > > imageMap, const bool bCCW = false ) = 0;


	virtual vgd::Shp< ILoader > clone() = 0;

};



} // namespace vgio


#endif // _VGIO_LOADER_HPP
