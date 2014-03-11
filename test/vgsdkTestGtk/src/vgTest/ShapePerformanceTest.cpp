// VGSDK - Copyright (C) 2009, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgsdkTestGtk/vgTest/ShapePerformanceTest.hpp"

namespace vgsdkTestGtk
{

namespace vgTest
{

ShapePerformanceTest::ShapePerformanceTest(vgsdkTestGtk::vgTest::TestManipulator *canvas)
{
	m_canvas = canvas;
}

void ShapePerformanceTest::begin()
{
	using vgd::node::VertexShape;

	vgd::visitor::predicate::ByKindOfType < VertexShape > predicate;
	m_shape = vgd::visitor::findFirst< VertexShape >( m_canvas->getRoot(), predicate );
}

void ShapePerformanceTest::end()
{

}

void ShapePerformanceTest::prePaint()
{
	m_shape->getFVertexRW();
}

void ShapePerformanceTest::postPaint()
{

}

} //namespace vgTest

} //namespace vgsdkTestGtk

