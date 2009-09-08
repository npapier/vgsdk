// VGSDK - Copyright (C) 2009, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGSDKTESTGTK_VGTEST_TESTMANIPULATOR_HPP
#define _VGSDKTESTGTK_VGTEST_TESTMANIPULATOR_HPP

#include <vgUI/BasicManipulator.hpp>
#include <vgTest/convenience.hpp>

#include "vgsdkTestGtk/vgTest/CustomPerformanceTest.hpp"
#include "vgsdkTestGtk/vgTest/myBase.hpp"

/**
 * @brief Canvas and UI stuff.
 */
namespace vgsdkTestGtk
{

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

	void setType(const vgsdkTestGtk::vgTest::testType t);
	void setScreenShotName(const std::string s);
	void setBase(vgTest::myBase *l);
	void setCustomPerf(const vgd::Shp<vgsdkTestGtk::vgTest::CustomPerformanceTest> customPerf);

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
	vgsdkTestGtk::vgTest::testType							m_type;
	vgsdkTestGtk::vgTest::myBase							*m_base;
	std::string												m_screenShotName;
	bool													m_perf;
	bool													m_screenShot;
	vgd::Shp<vgsdkTestGtk::vgTest::CustomPerformanceTest>	m_customPerf;

	uint						m_minDuration;
	uint						m_maxDuration;
	uint						m_averageDuration;
};


} // namespace vgTest

} //namespace vgsdkTestGtk

#endif // #ifndef _VGSDKTESTGTK_VGTEST_TESTMANIPULATOR_HPP