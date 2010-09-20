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
 * @brief Reads the file and stores it in the returned vector.
 *
 * @return an empty vector if an error occurs, otherwise a vector with the data.
 */
VGIO_API vgd::Shp< std::vector< char > > readFile( const std::string filePath );

/**
 * @brief	Load a file.
 *
 * @param	filePath	the file path to load.
 *
 * @return true if successful, false otherwise and a smart pointer on node if sucessful.
 */
VGIO_API std::pair< bool, vgd::Shp< vgd::node::Group > > load( std::string filePath );


/**
 * @brief	Get the correct loader by filename.
 *
 * @param	filename	the filename to load.
 *
 * @return	the correct loader.
 */
VGIO_API vgd::Shp< vgio::ILoader > getLoaderByFilename( std::string filename );


/**
 * @brief	Load a crypted image.
 *
 * @param	filePath	the file path to load..
 */
VGIO_API vgd::Shp< vgd::basic::Image > loadCryptedImage( std::string filePath, std::string key );



} // namespace vgio

#endif //#ifndef _VGIO_HELPERS_HPP