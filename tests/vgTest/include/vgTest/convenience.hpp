// VGSDK - Copyright (C) 2009, 2011, Maxime Peresson, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson
// Author Nicolas Papier

#ifndef _VGTEST_CONVENIENCE_HPP
#define _VGTEST_CONVENIENCE_HPP

#include <iostream>
#include <list>

#include "vgTest/Logging.hpp"


/**
 * @brief Useful testing stuff
 */
namespace vgTest
{

/**
 * @brief Move the file to another directory. Used to move screenshot to reference directory.
 */
VGTEST_API void moveTo(std::string from, std::string to);

/**
 * @brief Compare two images and generates an image containing their differences (i.e. abs(img1 - img2))
 *
 * @pre Format == RGB
 *		Type == UINT8
 */
VGTEST_API int compare(std::string pathRef, std::string pathCap, std::string pathDif);

/**
 * @brief Create image name based on test name.
 * @param filename		test name
 */
VGTEST_API std::string getImageName(std::string testName);

/**
 * @brief Create image name based on the current running test.
 */
VGTEST_API std::string getImageName();

/**
 * @brief Add current date to image filename
 * @param filename name of the file
 */
VGTEST_API std::string getDatedImageName(std::string filename);

/**
 * @brief Add number to image filename
 * @param filename name of the file
 * @param number number of the file
 */
VGTEST_API std::string getNumberedImageName(std::string filename, int number);

/**
 * @brief Create list of model based on files in local/share/vgTest/
 * @return list of file path
 */
VGTEST_API std::list< std::string > createModelList( std::string dir = "" );


} //namespace vgTest

#endif // #ifndef _VGTEST_CONVENIENCE_HPP
