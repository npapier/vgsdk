// VGSDK - Copyright (C) 2009, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGTEST_SHAPEPERFORMANCETEST_HPP
#define _VGTEST_SHAPEPERFORMANCETEST_HPP

#include "vgTest/CustomPerformanceTest.hpp"

#include <vgd/Shp.hpp>
#include <vgd/node/VertexShape.hpp>
#include "vgTest/TestManipulator.hpp"

namespace vgTest
{


/**
 * @brief Provide function called at the begining/end of the test end before and after each paint in shape performance tests
 */
struct ShapePerformanceTest : public CustomPerformanceTest
{
	ShapePerformanceTest(vgTest::TestManipulator *canvas);

	void begin();

	void end();

	void prePaint();

	void postPaint();

private:
	vgd::Shp< vgd::node::VertexShape > m_shape;
	vgTest::TestManipulator	*m_canvas;

};
} //namespace vgTest

#endif // #ifndef _VGTEST_SHAPEPERFORMANCETEST_HPP