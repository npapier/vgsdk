// VGSDK - Copyright (C) 2008, Clement Forest.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Clement Forest
// Author Guillaume Brocker

#ifndef _VGOBJ_LOADER_HPP
#define _VGOBJ_LOADER_HPP

#include <utility>

#include <vgio/ILoader.hpp>
#include "vgObj/vgObj.hpp"
#include <vgio/LoaderRegistry.hpp>
#include <vgio/Media.hpp>

namespace vgd
{
	template<class T> struct Shp;

	namespace node
	{
		struct Group;
		struct Material;
		struct Switch;
		struct TriSet;
		struct VertexShape;
	}
}



namespace vgObj
{

/**
 * @brief vgSdk loader for the .obj files.
 *
 * See vgObj namespace for mor info on the .obj format.
 *
 * For now, only triangle and quad geometry are supported. No texturing.
 *
 * @todo add support for lines and textures.
 */
struct VGOBJ_API Loader : public vgio::ILoader
{
	META_LOADER_HPP( vgObj::Loader )


	/**
	 * @brief Loads a vgsdk mesh from .obj (in ascii).
	 * 
	 * @return a pair bool/group. true if the scene succefully create. The group representing the whole scene graph.
	 */	
	virtual std::pair< bool, vgd::Shp< vgd::node::Group > > load( const std::string filePath, const bool bCCW = false );

	/**
	 * @brief Loads a vgsdk mesh from .obj (in ascii).
	 * 
	 * @return a pair bool/group. true if the scene succefully create. The group representing the whole scene graph.
	 */
		virtual std::pair< bool, vgd::Shp< vgd::node::Group > > load( const std::string filePath, vgd::Shp< std::vector< char > > outBuffer, const bool bCCW = false );

	/**
	 * @brief Load a model from a file in memory and the list of image already loaded in memory.
	 * 
	 * @return a pair bool/group. true if the scene succefully create. The group representing the whole scene graph.
	 */
	virtual std::pair< bool, vgd::Shp< vgd::node::Group > > load( const std::string filePath, vgd::Shp< std::vector< char > > outBuffer, std::map< std::string, vgd::Shp< vgd::basic::Image > > imageMap, const bool bCCW = false );


	virtual vgd::Shp< ILoader > clone();

protected:

	std::pair< bool, vgd::Shp< vgd::node::Group > > load( const vgio::Media & media, const std::string & filePath, const bool bCCW );

	/**
	 * @brief Load obj object from the given istream.
	 */
	std::pair< bool, vgd::Shp< vgd::node::VertexShape > > loadObj( std::istream & in, vgd::Shp< vgd::node::Group > group, const bool bCCW );


	/**
	 * @brief Empty constructor.
	 *
	 * To register this loader, the application must link with
	 * vgEgg. To force this link, we usually create a dummy loader in
	 * the application. However, if the loader does not have any
	 * constructor nor any variable member, the creation is removed in
	 * release mode by the compiler as an optimization, and the link
	 * with vgEgg is not done. This creator is here to prevent this
	 * optimisation to be done.
	 */
public:
	Loader();

};



} // namespace vgsdkViewer


#endif // _VGOBJ_LOADER_HPP
