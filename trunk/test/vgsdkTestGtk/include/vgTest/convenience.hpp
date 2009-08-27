// VGSDK - Copyright (C) 2009, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGTEST_CONVENIENCE_HPP
#define _VGTEST_CONVENIENCE_HPP

#include <iostream>
#include <vector>
#include <vgd/node/VertexShape.hpp>

#include "vgTest/Performance.hpp"

/**
 * @brief Useful testing stuff
 */
namespace vgTest
{
enum testType { NOTHING, SCREENSHOT, PERFORMANCE, SCREENSHOT_PERFORMANCE };

static bool createReference = false;

/**
 * @brief Return True if program is executed to create screenshot reference
 */
bool getCreateReference();

/**
 * @brief Set to True if the program is executed to create screenshot reference
 */
void setCreateReference(bool createRef);

/**
 * @brief Move the file to another directory. Used to move screenshot to reference dir.
 */
void moveTo(std::string from, std::string to);

/**
 * @brief Compare two images and generates an image containing their differences (i.e. abs(img1 - img2))
 *
 * @pre Format == RGB
 *		Type == UINT8
 */
int compare(std::string pathRef, std::string pathCap, std::string pathDif);


/**
 * @brief Return a vector of all possibility of performance object
 */
std::vector<vgTest::Performance> getPerformance(	std::vector<int> level, 
													std::vector<vgd::node::VertexShape::DeformableHintValueType> deformableHint, 
													std::vector<vgd::node::VertexShape::BoundingBoxUpdatePolicyValueType> boundingBoxPolicy);

std::string getImageName(std::string filename);
std::string getDatedImageName(std::string filename);

std::list< std::string > createModelList();

} //namespace vgTest

#endif // #ifndef _VGTEST_CONVENIENCE_HPP
