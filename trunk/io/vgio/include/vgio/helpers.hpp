// VGSDK - Copyright (C) 2010, 2012, 2013, Nicolas Papier, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGIO_HELPERS_HPP
#define _VGIO_HELPERS_HPP

#include "vgio/vgio.hpp"

#include <vgio/ILoader.hpp>
#include <vgd/Shp.hpp>



namespace vgio
{


/**
 * @brief Read the given 3d file.
 *
 * The file is read using the good loader based on the file extension.
 * Support :
 *  - .trian and .trian2
 *  - .obj (file format first developed by Wavefront Technologies)
 *  - .vgarch (vgsdk archive format).
 *  - .dae (collada), .blend (blender), .3ds (3ds Max) and any format supported by assimp (see http://assimp.sourceforge.net/main_features_formats.html).
 *
 * File loaded could be encrypt using blowfish (.crypt file) or not.
 *
 * @param filePath	the file path to load
 * @param key		the key used to decrypt the file to load (if needed)
 *
 * @return true if successful, false otherwise and a smart pointer on node if sucessful.
 *
 * @ingroup g_io
 */
VGIO_API std::pair< bool, vgd::Shp< vgd::node::Group > > load( const std::string filePath, const std::string key = "vgsdkViewer" );


// @todo loadImage() load image (encrypt or not).

/**
 * @brief Read the given encrypted image.
 *
 * @param filePath	the file path to load
 * @param key		the key used to decrypt the file to load (if needed)
 *
 * @ingroup g_io
 */
VGIO_API vgd::Shp< vgd::basic::Image > loadCryptedImage( const std::string filePath, const std::string key = "vgsdkViewer" );



/**
 * @brief	Get the correct loader for the given \c filename.
 *
 * @param	filename	the filename to load
 *
 * @return	the correct loader or an empty shared pointer.
 *
 * @ingroup g_ioHelpers
 */
VGIO_API vgd::Shp< vgio::ILoader > getLoaderByFilename( const std::string filename );



/**
 * @brief Reads the file and stores it in the returned vector.
 *
 * @return an empty vector if an error occurs, otherwise a vector with the data.
 *
 * @ingroup g_ioHelpers
 */
VGIO_API vgd::Shp< std::vector<char> > readFile( const std::string filePath );



/**
 * @name Read/write raw data into file
 *
 * @todo compressRaw(), uncompressRaw()
 */
//@{

/**
 * @brief Reads the file and initializes the given string with it.
 *
 * @param filePath		name of file to load
 * @param oData			data read are assign to this string
 * @return true if successful, false otherwise.
 *
 * @todo append data to oData
 * @ingroup g_ioHelpers
 */
VGIO_API const bool readFile(const std::string filePath, std::string& oData);


/**
 * @brief Writes the given data into file filePath.
 *
 * @param filePath		name of file to create. If file already exists, then its contents is deleted.
 * @param data			data to be written
 *
 * @ingroup g_ioHelpers
 */
VGIO_API void writeFile( const std::string filePath, const std::string& data );

/**
 * @brief Writes the given data into file filePath.
 *
 * @param filePath		name of file to create. If file already exists, then its contents is deleted.
 * @param data			data to be written
 * @param dataSize		size of the buffer given by data parameter
 *
 * @ingroup g_ioHelpers
 */
VGIO_API void writeFile( const std::string filePath, const char * data, const uint dataSize );

//@}


} // namespace vgio

#endif //#ifndef _VGIO_HELPERS_HPP
