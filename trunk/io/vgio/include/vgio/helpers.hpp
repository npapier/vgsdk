// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGIO_HELPERS_HPP
#define _VGIO_HELPERS_HPP


#include "vgio/vgio.hpp"

#include <list>
#include <map>

#include <vgio/ILoader.hpp>
#include <vgd/Shp.hpp>


namespace vgio
{


/**
 * @brief	Load a file.
 *
 * @param	filePath	the file path to load.
 *
 * @return true if successful, false otherwise and a smart pointer on node if sucessful.
 */
std::pair< bool, vgd::Shp< vgd::node::Group > > VGIO_API load( std::string filePath );


/**
 * @brief	Get the correct loader by filename.
 *
 * @param	filename	the filename to load.
 *
 * @return	the correct loader.
 */
vgd::Shp< vgio::ILoader > VGIO_API getLoaderByFilename( std::string filename );


/**
 * @brief	Load a crypted image.
 *
 * @param	filePath	the file path to load..
 */
vgd::Shp< vgd::basic::Image > VGIO_API loadCryptedImage( std::string filePath, std::string key );



} // namespace vgio

#endif //#ifndef _VGIO_HELPERS_HPP