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

	/**
	 * @brief Determines whether the cache is enabled.
	 *
	 * @return true if cache is enabled, false otherwise
	 */
	const bool isEnabled() const;

	/**
	 * @brief Enables or disables the cache depending on the value of the parameter isEnabled.
	 *
	 * @param isEnabled		true when the cache must be enabled, false otherwise
	 */
	void setEnabled( const bool enabled = true );



	static vgd::Shp< vgd::basic::IImage > load( const std::string pathFilename );

	static vgd::Shp< ImageCache > getInstance();



private:

	static vgd::Shp< ImageCache >	m_imageCache;
	bool							m_isEnabled;			///< true to use cache system for image, false otherwise
};



} // namespace vgio

#endif //#ifndef _VGIO_CACHE_HPP
