// VGSDK - Copyright (C) 2009, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGTEST_SHAPE_HPP
#define _VGTEST_SHAPE_HPP

#include <boost/algorithm/string.hpp>
#include <boost/assign/list_of.hpp>
#include <gtest/gtest.h>
#include <map>

#include <sbf/path.hpp>
#include <string>
#include <vgd/node/Sphere.hpp>
#include <vgd/node/VertexShape.hpp>
#include <vgd/ScopedPtr.hpp>
#include <vgd/Shp.hpp>
#include <vgTest/convenience.hpp>

#include <vector>

#include "Fixtures.hpp"
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
TEST_P(VgTestShape, PerformanceShapeTest)
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
		vgTest::moveTo(base->getScreenShotPath() + base->getDatedScreenShotName(), base->getReferencePath() + base->getScreenShotName());
	}
	else
	{
		if (!boost::filesystem::exists(base->getReferencePath()))
		{
			FAIL() << "REFERENCE FILE IS NOT CREATED";
		}

		int diff = vgTest::compare(base->getReferencePath() + base->getScreenShotName(), base->getScreenShotPath() + base->getDatedScreenShotName(), base->getDifferencePath() + base->getDatedScreenShotName());
		EXPECT_EQ( diff, 0 );

		base->getLog()->add("PixelDiff", diff);

		if (diff > 0)
		{
			base->getLog()->add("ImagePath", base->getImagesPath(true));
		}
		else
		{
			base->getLog()->add("ImagePath", base->getImagesPath(false));
		}
	}

	//base->getLog()->addToGtest();
	PutInGtestReport(base)
}

/**
* @brief Test if it crash when we add a static object
*/
static vgd::Shp<vgd::node::Sphere> objStatic = vgd::node::Sphere::create("sphere");
TEST_F(VgTestShape, StaticShapeTest)
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
		vgTest::moveTo(base->getScreenShotPath() + base->getDatedScreenShotName(), base->getReferencePath() + base->getScreenShotName());
	}
	else
	{
		if (!boost::filesystem::exists(base->getReferencePath()))
		{
			FAIL() << "REFERENCE FILE IS NOT CREATED";
		}		
		
		int diff = vgTest::compare(base->getReferencePath() + base->getScreenShotName(), base->getScreenShotPath() + base->getDatedScreenShotName(), base->getDifferencePath() + base->getDatedScreenShotName());
		EXPECT_EQ( diff, 0 );

		base->getLog()->add("PixelDiff", diff);

		if (diff > 0)
		{
			base->getLog()->add("ImagePath", base->getImagesPath(true));
		}
		else
		{
			base->getLog()->add("ImagePath", base->getImagesPath(false));
		}
	}
	
	//base->getLog()->addToGtest();
	PutInGtestReport(base)
}

#endif // #ifndef _VGTEST_SHAPE_HPP
