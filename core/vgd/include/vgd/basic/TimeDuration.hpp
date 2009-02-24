// VGSDK - Copyright (C) 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_BASIC_TIMEDURATION_HPP
#define _VGD_BASIC_TIMEDURATION_HPP

#include "vgd/basic/Time.hpp"



namespace vgd
{

namespace basic
{



/**
 * @brief Interface for time duration.
 *
 * @see Time
 */
struct VGD_API TimeDuration
{
	/**
	 * @brief Constructor taking the difference between two times.
	 *
	 * @param t1	first time point
	 * @param t2	second time point
	 *
	 * Constructs the time duration between t1 and t2, i.e. t2 - t1
	 */
	TimeDuration( const Time& t1, const Time& t2 );

	/**
	 * @brief Returns the number of seconds
	 *
	 * @return the duration value in seconds truncating any fractional seconds.
	 */
	const uint seconds() const;
	const uint s() const;

	/**
	 * @brief Returns the number of milliseconds
	 *
	 * @return the duration value in milliseconds truncating any fractional seconds.
	 */
	const uint milliSeconds() const;
	const uint m() const;

private:

	boost::posix_time::time_duration m_duration; ///< The time duration
};



} // namespace basic

} // namespace vgd

#endif //#ifndef _VGD_BASIC_TIMEDURATION_HPP
