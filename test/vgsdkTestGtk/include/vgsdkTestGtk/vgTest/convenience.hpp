// VGSDK - Copyright (C) 2009, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGSDKTESTGTK_VGTEST_CONVENIENCE_HPP
#define _VGSDKTESTGTK_VGTEST_CONVENIENCE_HPP

#include <iostream>
#include <vector>
#include <vgd/node/VertexShape.hpp>

#include "vgsdkTestGtk/vgTest/Performance.hpp"

/**
 * @brief Useful testing stuff
 */
namespace vgsdkTestGtk
{
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
	 * @brief Return a vector of all possibility of performance object
	 */
	std::vector<vgsdkTestGtk::vgTest::Performance> getPerformance(	std::vector<int> level, 
														std::vector<vgd::node::VertexShape::DeformableHintValueType> deformableHint, 
														std::vector<vgd::node::VertexShape::BoundingBoxUpdatePolicyValueType> boundingBoxPolicy);

	} //namespace vgTest

} //namespace vgsdkTestGtk

#endif // #ifndef _VGSDKTESTGTK_VGTEST_CONVENIENCE_HPP
