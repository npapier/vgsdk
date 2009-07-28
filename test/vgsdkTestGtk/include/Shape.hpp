// VGSDK - Copyright (C) 2009, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGTEST_SHAPE_HPP
#define _VGTEST_SHAPE_HPP

#include <gtest/gtest.h>
#include <boost/algorithm/string.hpp>
#include <vgd/ScopedPtr.hpp>
#include <vgd/Shp.hpp>

#include <vgd/node/VertexShape.hpp>
#include <vgd/node/Sphere.hpp>
#include <sbf/path.hpp>

#include <vector>
#include <boost/assign/list_of.hpp>

#include "vgTest/myBase.hpp"
#include "vgTest/myCanvas.hpp"
#include "vgTest/convenience.hpp"
#include "vgTest/ShapePerformanceTest.hpp"

#include "Fixtures.hpp"

/**
* @brief VgTestShape testsuite
*/


/**
* @brief Test performance with different complexity
*/
TEST_P(VgTestShape, PerformanceShapeTest)
{
	RecordProperty("Description", "Test performance with different complexity");
	
	vgTest::Performance perf = GetParam();

	vgd::Shp<vgd::node::Sphere> obj = vgd::node::Sphere::create("sphere");
	RecordProperty("Shape", "sphere");

	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::string filename = vgTest::getImageName(test_info->name());

	// prerun Gtk
	vgd::ScopedPtr< vgTest::myBase > base( new vgTest::myBase(filename, vgTest::SCREENSHOT_PERFORMANCE) );
	
	vgd::Shp<vgTest::ShapePerformanceTest> customPerf(new vgTest::ShapePerformanceTest(base->getCanvas()));
	base->getCanvas()->setCustomPerf(customPerf);

	// prepare scene
	obj->initializeGeometry(perf.getLevel());
	RecordProperty("GeometryLevel", perf.getLevel());

	obj->setDeformableHint(perf.getDeformableHint());

	RecordProperty("DeformableHintValue", perf.getDeformableHintToString().c_str());

	obj->setBoundingBoxUpdatePolicy(perf.getBoundingBox());
	RecordProperty("BoundingBoxUpdatePolicyValue", perf.getBoundingBoxToString().c_str());

	base->addObject( obj );

	base->getCanvas()->viewAll();

	// run GTK
	base->run();

	int f = base->getFrame();
	int d = base->getDuration();
	int fps = base->getFps();

	RecordProperty("Frame", f);
	RecordProperty("Duration", d);
	RecordProperty("Fps", fps);

	if (vgTest::getCreateReference())
	{
		vgTest::moveTo(base->getScreenShotPath(), base->getReferencePath());
	}
	else
	{
		int diff = vgTest::compare(base->getReferencePath(), base->getScreenShotPath(), base->getDifferencePath());
		EXPECT_EQ( diff, 0 );

		RecordProperty("PixelDiff", diff);

		if (diff > 0)
		{
			RecordProperty("ImagePath", base->getImagesPath(true).c_str());
		}
		else
		{
			RecordProperty("ImagePath", base->getImagesPath(false).c_str());
		}
	}
}

/**
* @brief Test if it crash when we add a static object
*/
static vgd::Shp<vgd::node::Sphere> objStatic = vgd::node::Sphere::create("sphere");
TEST_F(VgTestShape, StaticShapeTest)
{
	RecordProperty("Description", "Test if it crash when we add a static object");
	
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::string filename = vgTest::getImageName(test_info->name());

	//static vgd::Shp<vgd::node::Sphere> objStatic = vgd::node::Sphere::create("sphere");
	RecordProperty("Shape", "sphere");

	// prerun Gtk
	vgd::ScopedPtr< vgTest::myBase > base( new vgTest::myBase(filename, vgTest::SCREENSHOT) );

	// prepare scene
	objStatic->initializeGeometry();
	base->addObject( objStatic );

	base->getCanvas()->viewAll();

	// run GTK
	base->run();
	
	if (vgTest::getCreateReference())
	{
		vgTest::moveTo(base->getScreenShotPath(), base->getReferencePath());
	}
	else
	{
		int diff = vgTest::compare(base->getReferencePath(), base->getScreenShotPath(), base->getDifferencePath());
		EXPECT_EQ( diff, 0 );

		RecordProperty("PixelDiff", diff);

		if (diff > 0)
		{
			RecordProperty("ImagePath", base->getImagesPath(true).c_str());
		}
		else
		{
			RecordProperty("ImagePath", base->getImagesPath(false).c_str());
		}
	}
}

#endif // #ifndef _VGTEST_SHAPE_HPP
