// VGSDK - Copyright (C) 2008, Clement Forest.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Clement Forest
// Author Guillaume Brocker

#ifndef _VGOBJ_LOADER_HPP
#define _VGOBJ_LOADER_HPP

#include <utility>

#include "vgObj/vgObj.hpp"

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
struct VGOBJ_API Loader
{
	/**
	 * @brief Loads a vgsdk mesh from .obj (in ascii).
	 *
	 * @param pathFilename the name of file to read.
	 * @param bCCW Counter Clock Wise computation of normals.
	 *
	 * @return true if successful, false otherwise.
	 */
	std::pair< bool, vgd::Shp< vgd::node::VertexShape > >	loadObj( const char *pathFilename, bool bCCW = false );
};



} // namespace vgsdkViewer


#endif // _VGOBJ_LOADER_HPP
