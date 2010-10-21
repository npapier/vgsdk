// VGSDK - Copyright (C) 2010, Guillaume Brocker.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGIO_FILESYSTEM_HPP_
#define _VGIO_FILESYSTEM_HPP_

#include "vgio/vgio.hpp"
#include "vgio/Media.hpp"



namespace vgio
{



/**
 * @brief	Implements a media that offers access to the native file system.
 */
struct VGIO_API FileSystem : public Media
{
	/**
	 * @name	Overrides
	 */
	//@{
	const bool exists( const boost::filesystem::path & ) const;
	vgd::Shp< std::istream > open( const boost::filesystem::path & ) const;
	//@}
};



} // namespace vgio



#endif // _VGIO_FILESYSTEM_HPP_
