// VGSDK - Copyright (C) 2009, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgTest/TestManipulator.hpp"

#include <vgeGL/engine/Engine.hpp>
#include <vgd/basic/Image.hpp>
#include <vgd/basic/Time.hpp>
#include <vgd/basic/TimeDuration.hpp>

#include "vgTest/ShapePerformanceTest.hpp"

namespace vgTest
{

TestManipulator::TestManipulator() 
:	m_type( vgTest::NOTHING ),
	m_screenShotName(""),
	m_perf( false ),
	m_screenShot( false )
{
	//vgUI::BasicManipulator::BasicManipulator();
}

TestManipulator::TestManipulator( Canvas * pSharedCanvas )
:	vgUI::BasicManipulator( pSharedCanvas ), 
	m_type( vgTest::NOTHING ), 
	m_screenShotName (""), 
	m_perf( false ),
	m_screenShot( false )
{
}

TestManipulator::~TestManipulator()
{
}

void TestManipulator::setType(vgTest::testType t)
{
	m_type = t;
}

void TestManipulator::setScreenShotName(std::string s)
{
	m_screenShotName = s;
}

void TestManipulator::setBase(vgTest::myBase *l)
{
	m_base = l;
}

void TestManipulator::setCustomPerf(vgd::Shp<vgTest::CustomPerformanceTest> customPerf)
{
	m_customPerf = customPerf;
}

//
// Overriden from BasicManipulator
//
void TestManipulator::paint(const vgm::Vec2i size, const bool bUpdateBoundingBox)
{
	if (m_type == vgTest::SCREENSHOT || m_type == vgTest::SCREENSHOT_PERFORMANCE)
	{
		if (m_screenShot == false)
		{
			scheduleScreenshot(m_screenShotName);
			m_screenShot = true;
		}

		vgUI::BasicManipulator::paint(size, bUpdateBoundingBox);

		if (m_type == vgTest::SCREENSHOT_PERFORMANCE && m_perf == false)
		{
		
			if ( m_customPerf )
			{
				m_customPerf->begin();
			}

			vgd::basic::Time time;
			
		#ifdef _DEBUG
			const uint testDuration = 1000;
		#else
			const uint testDuration = 1000;
		#endif

			vgd::basic::TimeDuration endTime(time.getElapsedTime().milliSeconds() + testDuration);

			int frame = 0;
			while ( time.getElapsedTime() < endTime )
			{
				if ( m_customPerf )
				{
					m_customPerf->prePaint();
				}

				vgUI::BasicManipulator::paint(size, bUpdateBoundingBox);

				if ( m_customPerf )
				{
					m_customPerf->postPaint();
				}

				frame++;
			}

			// @todo num of triangles => MTS
			uint duration = time.getElapsedTime().milliSeconds();
			m_base->getLog()->add("Duration", duration);
			m_base->getLog()->add("Frame", frame);
			m_base->getLog()->add("Fps", frame / (duration / 1000));

			m_perf = true;

			if ( m_customPerf )
			{
				m_customPerf->end();
			}
		}
		// else nothing

		m_base->setQuit(true);
	}
	else
	{
		vgUI::BasicManipulator::paint(size, bUpdateBoundingBox);
		m_base->setQuit(true);
	}
}
} // namespace vgTest
