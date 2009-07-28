// VGSDK - Copyright (C) 2009, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGTEST_TESTMANIPULATOR_HPP
#define _VGTEST_TESTMANIPULATOR_HPP

#include <vgUI/BasicManipulator.hpp>
#include "vgTest/myBase.hpp"
#include "vgTest/convenience.hpp"
#include "vgTest/CustomPerformanceTest.hpp"
//#include <glibmm/ustring.h>

/**
 * @brief Canvas and UI stuff.
 */
namespace vgTest
{

/**
 * @brief Canvas for tests.
 */
struct TestManipulator : public vgUI::BasicManipulator
{
	/**
	 * @name Construction and initialisation.
	 */
	//@{
	/**
	 * @brief Constructor.
	 */
	TestManipulator();
	~TestManipulator();

	void setType(vgTest::testType t);
	void setScreenShotName(std::string s);
	void setBase(vgTest::myBase *l);
	void setCustomPerf(vgd::Shp<vgTest::CustomPerformanceTest> customPerf);

	/**
	 * @brief	Constructs a BasicManipulator with its own OpenGL context, but that share OpenGL objects with another(s) Canvas.
	 *
	 * @param	parent	a pointer to the parent window.
	 */
	TestManipulator( Canvas * pSharedCanvas );
	//@}

	/**
	 * @brief Function paint.
	 */
	void paint(const vgm::Vec2i size, const bool bUpdateBoundingBox);
	//@}

private :
	vgTest::testType							m_type;
	vgTest::myBase								*m_base;
	std::string									m_screenShotName;
	bool										m_perf;
	bool										m_screenShot;
	vgd::Shp<vgTest::CustomPerformanceTest>		m_customPerf;
};


} // namespace vgTest

#endif // #ifndef _VGTEST_TESTMANIPULATOR_HPP