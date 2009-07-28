// VGSDK - Copyright (C) 2009, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGTEST_CUSTOMPERFORMANCETEST_HPP
#define _VGTEST_CUSTOMPERFORMANCETEST_HPP

namespace vgTest
{

/**
 * @brief Interface which provide function called at the begining/end of the test end before and after each paint.
 */

struct CustomPerformanceTest
{
	virtual void begin()=0;

	virtual void end()=0;

	virtual void prePaint()=0;

	virtual void postPaint()=0;
};

} //namespace vgTest

#endif // #ifndef _VGTEST_CUSTOMPERFORMANCETEST_HPP
