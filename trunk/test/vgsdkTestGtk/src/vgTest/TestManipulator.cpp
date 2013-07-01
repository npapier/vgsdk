// VGSDK - Copyright (C) 2009, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgsdkTestGtk/vgTest/TestManipulator.hpp"

#include <limits>
#include <vgd/basic/Image.hpp>
#include <vgd/basic/Time.hpp>
#include <vgd/basic/TimeDuration.hpp>
#include <vgeGL/engine/Engine.hpp>

#include "vgsdkTestGtk/vgTest/ShapePerformanceTest.hpp"

namespace vgsdkTestGtk
{

namespace vgTest
{


TestManipulator::TestManipulator()
:	m_type( vgsdkTestGtk::vgTest::NOTHING ), 
	m_base(0),
	m_perf( false ),
	m_screenShot( false ),
	//m_customPerf
	m_minDuration( std::numeric_limits<uint64>::max() ),
	m_maxDuration( std::numeric_limits<uint64>::min() ),
	m_averageDuration( 0 )
{}


TestManipulator::TestManipulator( Canvas * pSharedCanvas )
:	vgUI::BasicManipulator( pSharedCanvas ), 
	m_type( vgsdkTestGtk::vgTest::NOTHING ), 
	m_base(0),
	m_perf( false ),
	m_screenShot( false ),
	//m_customPerf
	m_minDuration( std::numeric_limits<uint64>::max() ),
	m_maxDuration( std::numeric_limits<uint64>::min() ),
	m_averageDuration( 0 )
{}


void TestManipulator::setType(const vgsdkTestGtk::vgTest::testType type)
{
	m_type = type;
}


void TestManipulator::setBase(vgsdkTestGtk::vgTest::myBase *base)
{
	m_base = base;
}


void TestManipulator::setCustomPerf(const vgd::Shp<vgsdkTestGtk::vgTest::CustomPerformanceTest> customPerf)
{
	m_customPerf = customPerf;
}


// Overriden from BasicManipulator
void TestManipulator::paint(const vgm::Vec2i size, const bool bUpdateBoundingBox)
{
	if (m_type == vgsdkTestGtk::vgTest::SCREENSHOT || m_type == vgsdkTestGtk::vgTest::SCREENSHOT_PERFORMANCE)
	{
		if (m_screenShot == false)
		{
			if ( getCreateReference() )
			{
				scheduleScreenshot( m_base->getCountedScreenShotName(), sbf::pkg::Module::get(), "references" );
			}
			else
			{
				scheduleScreenshot( m_base->getCountedDatedScreenShotName(), sbf::pkg::Module::get(), "screenshots" );
			}
			m_screenShot = true;
		}

		vgUI::BasicManipulator::paint(size, bUpdateBoundingBox);

		if (m_type == vgsdkTestGtk::vgTest::SCREENSHOT_PERFORMANCE && m_perf == false)
		{
		
			if ( m_customPerf )
			{
				m_customPerf->begin();
			}

			vgd::basic::Time time;
			const uint64 testDuration = 1000;

			vgd::basic::TimeDuration endTime(time.getElapsedTime().milliSeconds() + testDuration);

			uint64 frame = 0;
			while ( time.getElapsedTime() < endTime )
			{
				if ( m_customPerf )
				{
					m_customPerf->prePaint();
				}

				vgd::basic::Time paintTime;
				vgUI::BasicManipulator::paint(size, bUpdateBoundingBox);
				const uint64 paintDuration = paintTime.getElapsedTime().milliSeconds();

				if (m_minDuration > paintDuration)
				{
					m_minDuration = paintDuration;
				}

				if (m_maxDuration < paintDuration)
				{
					m_maxDuration = paintDuration;
				}
				
				m_averageDuration += paintDuration;


				if ( m_customPerf )
				{
					m_customPerf->postPaint();
				}

				++frame;
			}

			// @todo num of triangles => MTS
			const uint64 duration = time.getElapsedTime().milliSeconds();
			
			float averageDuration = (float)m_averageDuration / frame;

			m_base->getLog()->add("MinRenderDuration", m_minDuration);
			m_base->getLog()->add("MaxRenderDuration", m_maxDuration);
			m_base->getLog()->add("AverageRenderDuration", averageDuration);

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

} //namespace vgsdkTestGtk
