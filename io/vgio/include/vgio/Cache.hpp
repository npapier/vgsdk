// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGIO_CACHE_HPP
#define _VGIO_CACHE_HPP

#include <vge/rc/TManager.hpp>

#include "vgio/vgio.hpp"

namespace vgd
{

	template<class T> struct Shp;
	namespace basic { struct IImage; }
}



namespace vgio
{



/**
 * @brief Cache system
 *
 * @todo Converts to template
 */
struct VGIO_API ImageCache
	: public vge::rc::TManager< std::string, vgd::basic::IImage > // @todo moves TManager to vgd
{
	/**
	 * @brief Constructor
	 *
	 * @param name 		name of the manager
	 */
	ImageCache( const std::string name );

	static vgd::Shp< vgd::basic::IImage > load( const std::string pathFilename );

	static vgd::Shp< ImageCache > getInstance();

private:

	static vgd::Shp< ImageCache > m_imageCache;
};



} // namespace vgio

#endif //#ifndef _VGIO_CACHE_HPP
