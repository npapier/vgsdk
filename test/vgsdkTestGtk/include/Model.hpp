// VGSDK - Copyright (C) 2009, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGTEST_MODEL_HPP
#define _VGTEST_MODEL_HPP

#include <gtest/gtest.h>
#include <boost/algorithm/string.hpp>

#include <vgd/ScopedPtr.hpp>
#include <vgd/Shp.hpp>

#include "vgTest/myBase.hpp"
#include "vgTest/myCanvas.hpp"
#include "vgTest/convenience.hpp"

#include "Fixtures.hpp"

/**
* @brief VgTestModel testsuite
*/

/**
* @brief Compare a generated image and a reference image
*/
TEST_P(VgTestModel, CompareTest)
{	
	std::string desc = "Compare a generated image and a reference image.<br/> Object:";
	desc += GetParam();
	RecordProperty("Description", desc.c_str());
	
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::string filename = vgTest::getImageName(test_info->name());

	vgd::ScopedPtr< vgTest::myBase > base( new vgTest::myBase(filename, vgTest::SCREENSHOT) );
	RecordProperty("Object", GetParam().c_str());

	// prepare scene
	base->addObject(GetParam());

	//run GTK
	base->run();

	if (vgTest::getCreateReference())
	{
		vgTest::moveTo(base->getScreenShotPath(), base->getReferencePath());
	}
	else
	{
		// do the test
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
* @brief Test performance with different model
*/
TEST_P(VgTestModel, PerformanceModelTest)
{
	std::string desc = "Test performance with different model.<br/> Object:";
	desc += GetParam();
	RecordProperty("Description", desc.c_str());	
	
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::string filename = vgTest::getImageName(test_info->name());

	vgd::ScopedPtr< vgTest::myBase > base( new vgTest::myBase(filename, vgTest::SCREENSHOT_PERFORMANCE) );
	RecordProperty("Object", GetParam().c_str());

	// prepare scene
	base->addObject(GetParam());

	//run GTK
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
* @brief Compare a generated image and a reference image
*/
//TEST_F(VgTestModel, FailCompareTest)
//{	
//	RecordProperty("Description", "Compare a generated image and a fake reference image ==> MUST FAIL");
//	
//	const ::testing::TestInfo* const test_info =
//	  ::testing::UnitTest::GetInstance()->current_test_info();
//
//	std::string filename = vgTest::getImageName(test_info->name());
//
//	vgd::ScopedPtr< vgTest::myBase > base( new vgTest::myBase(filename, vgTest::SCREENSHOT) );
//	RecordProperty("Object", "cavite.obj");
//
//	// prepare scene
//	base->addObject("cavite.obj");
//
//	//run GTK
//	base->run();
//
//
//	// do the test
//	int diff = vgTest::compare(base->getReferencePath(), base->getScreenShotPath(), base->getDifferencePath());
//	EXPECT_EQ( diff, 0 );
//
//	RecordProperty("PixelDiff", diff);
//
//	if (diff > 0)
//	{
//		RecordProperty("ImagePath", base->getImagesPath(true).c_str());
//	}
//	else
//	{
//		RecordProperty("ImagePath", base->getImagesPath(false).c_str());
//	}
//}



#endif // #ifndef _VGTEST_MODEL_HPP