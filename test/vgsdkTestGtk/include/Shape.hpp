// VGSDK - Copyright (C) 2009, 2012, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson
// Author Guillaume Brocker

#ifndef _VGTEST_SHAPE_HPP
#define _VGTEST_SHAPE_HPP

#include <boost/algorithm/string.hpp>
#include <boost/assign/list_of.hpp>
#include <map>

#include <string>
#include <vgd/node/Sphere.hpp>
#include <vgd/node/VertexShape.hpp>
#include <vgd/ScopedPtr.hpp>
#include <vgd/Shp.hpp>
#include <vgTest/convenience.hpp>

#include <vector>

#include "Fixtures.hpp"
#include <gtest.hpp>
#include "vgsdkTestGtk/vgTest/convenience.hpp"
#include "vgsdkTestGtk/vgTest/myBase.hpp"
#include "vgsdkTestGtk/vgTest/myCanvas.hpp"
#include "vgsdkTestGtk/vgTest/ShapePerformanceTest.hpp"



/**
* @brief VgTestShape testsuite
*/


/**
* @brief Test performance with different complexity
*/
TEST_P(VgTestShape, DISABLED_PerformanceShapeTest)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::string filename = vgTest::getImageName(test_info->name());

	// prerun Gtk
	vgd::ScopedPtr< vgsdkTestGtk::vgTest::myBase > base( new vgsdkTestGtk::vgTest::myBase(filename, vgsdkTestGtk::vgTest::SCREENSHOT_PERFORMANCE) );	
	
	base->getLog()->add("Description", "Test performance with different complexity");
	
	vgsdkTestGtk::vgTest::Performance perf = GetParam();

	vgd::Shp<vgd::node::Sphere> obj = vgd::node::Sphere::create("sphere");
	base->getLog()->add("Shape", "sphere");
	
	vgd::Shp<vgsdkTestGtk::vgTest::ShapePerformanceTest> customPerf(new vgsdkTestGtk::vgTest::ShapePerformanceTest(base->getCanvas()));
	base->getCanvas()->setCustomPerf(customPerf);

	// prepare scene
	obj->initializeGeometry(perf.getLevel());
	base->getLog()->add("GeometryLevel", perf.getLevel());

	obj->setDeformableHint(perf.getDeformableHint());

	base->getLog()->add("DeformableHintValue", perf.getDeformableHintToString());

	obj->setBoundingBoxUpdatePolicy(perf.getBoundingBox());
	base->getLog()->add("BoundingBoxUpdatePolicyValue", perf.getBoundingBoxToString());

	base->addObject( obj );

	base->getCanvas()->viewAll();

	// run GTK
	base->run();

	if (vgsdkTestGtk::vgTest::getCreateReference())
	{
		base->moveToReference();
	}
	else
	{
		// do the test
		base->compareScreenShots();
	}

	base->getLog()->addToGtest();
}

/**
* @brief Test if it crash when we add a static object
*/
static vgd::Shp<vgd::node::Sphere> objStatic = vgd::node::Sphere::create("sphere");
TEST_F(VgTestShape, DISABLED_StaticShapeTest)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::string filename = vgTest::getImageName(test_info->name());

	// prerun Gtk
	vgd::ScopedPtr< vgsdkTestGtk::vgTest::myBase > base( new vgsdkTestGtk::vgTest::myBase(filename, vgsdkTestGtk::vgTest::SCREENSHOT) );

	base->getLog()->add("Description", "Test if it crash when we add a static object");

	base->getLog()->add("Shape", "sphere");

	// prepare scene
	objStatic->initializeGeometry();
	base->addObject( objStatic );

	base->getCanvas()->viewAll();

	// run GTK
	base->run();
	
	if (vgsdkTestGtk::vgTest::getCreateReference())
	{
		base->moveToReference();
	}
	else
	{
		// do the test
		base->compareScreenShots();
	}
	
	base->getLog()->addToGtest();
}

#endif // #ifndef _VGTEST_SHAPE_HPP
