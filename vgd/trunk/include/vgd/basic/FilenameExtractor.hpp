// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_BASIC_FILENAMEEXTRACTOR_H
#define _VGD_BASIC_FILENAMEEXTRACTOR_H

#include "vgd/vgd.hpp"

#include <string>



namespace vgd
{
	
namespace basic
{

struct VGD_API FilenameExtractor
{
	/**
	 * @brief Constructor that take a filename with or without a path.
	 * 
	 * @param pathFilename		absolute or relative path to a file.
	 * 
	 * @remarks All '\' are converted to '/'.
	 */
	FilenameExtractor( std::string pathFilename );
	
	/**
	 * @brief Extract the filename extension.
	 */
	std::string getExtension() const;

	/**
	 * @brief Extract the filename with his extension.
	 */
	std::string getFilename() const;	
	
	/**
	 * @brief Extract the path to the file.
	 */
	std::string getPath() const;
	
	/**
	 * @brief Return the filename with the path.
	 */
	std::string getPathFilename() const;

	
	
private:

	std::string		m_pathFilename;
};



} // namespace basic

} // namespace vgd

#endif //#ifndef _VGD_BASIC_FILENAMEEXTRACTOR_H
