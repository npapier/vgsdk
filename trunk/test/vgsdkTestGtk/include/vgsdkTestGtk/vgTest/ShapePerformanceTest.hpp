// VGSDK - Copyright (C) 2009, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGSDKTESTGTK_VGTEST_SHAPEPERFORMANCETEST_HPP
#define _VGSDKTESTGTK_VGTEST_SHAPEPERFORMANCETEST_HPP

#include <vgd/node/VertexShape.hpp>
#include <vgd/Shp.hpp>

#include "vgsdkTestGtk/vgTest/CustomPerformanceTest.hpp"
#include "vgsdkTestGtk/vgTest/TestManipulator.hpp"

namespace vgsdkTestGtk
{

namespace vgTest
{

/**
 * @brief Provide function called at the begining/end of the test end before and after each paint in shape performance tests
 */
struct ShapePerformanceTest : public CustomPerformanceTest
{
	ShapePerformanceTest(vgsdkTestGtk::vgTest::TestManipulator *canvas);

	void begin();

	void end();

	void prePaint();

	void postPaint();

private:
	vgd::Shp< vgd::node::VertexShape > m_shape;
	vgsdkTestGtk::vgTest::TestManipulator	*m_canvas;

};
} //namespace vgTest

} //namespace vgsdkTestGtk

#endif // #ifndef _VGSDKTESTGTK_VGTEST_SHAPEPERFORMANCETEST_HPP