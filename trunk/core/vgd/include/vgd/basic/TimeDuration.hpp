// VGSDK - Copyright (C) 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_BASIC_TIMEDURATION_HPP
#define _VGD_BASIC_TIMEDURATION_HPP

#include "vgd/vgd.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>

namespace vgd { namespace basic { struct Time; } }



namespace vgd
{

namespace basic
{

/**
 * @brief Interface for time duration.
 *
 * @ingroup g_time
 */
struct VGD_API TimeDuration
{
	/**
	 * @name Constructors
	 */
	//@{
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
	 * @brief Constructor from a number of milliseconds.
	 *
	 * @param milliSeconds	number of milliseconds
	 */
	TimeDuration( const uint64 milliSeconds = 0 );

	/**
	 * @brief Constructor
	 *
	 * @param hours		number of hours
	 * @param minutes		number of minutes
	 * @param seconds		number of seconds
	 * @param milliSeconds	number of milliseconds
	 */
	TimeDuration( const uint64 hours, const uint64 minutes, const uint64 seconds, const uint64 milliSeconds = 0 );

	//@}


	/**
	 * @name Accessors
	 */
	//@{

	/**
	 * @brief Returns the number of hours
	 *
	 * @return the duration value in hours truncating any fractional hours.
	 */
	const uint64 hours() const;

	/**
	 * @copydoc TimeDuration::hours()
	 */
	const uint64 h() const;

	/**
	 * @brief Returns the number of minutes
	 *
	 * @return the duration value in minutes truncating any fractional minutes.
	 */
	const uint64 minutes() const;

	/**
	 * @copydoc TimeDuration::minutes()
	 */
	const uint64 m() const;

	/**
	 * @brief Returns the number of seconds
	 *
	 * @return the duration value in seconds truncating any fractional seconds.
	 */
	const uint64 seconds() const;

	/**
	 * @copydoc TimeDuration::seconds()
	 */
	const uint64 s() const;

	/**
	 * @brief Returns the number of milliseconds
	 *
	 * @return the duration value in milliseconds truncating any fractional milliseconds.
	 */
	const uint64 milliSeconds() const;

	/**
	 * @copydoc TimeDuration::milliSeconds()
	 */
	const uint64 ms() const;

	//@}


	/**
	 * @name Arithmetic operator
	 */
	//@{

	/**
	 * @brief Adds duration
	 */
	TimeDuration operator + ( const TimeDuration& t2 ) const;

	/**
	 * @brief Substracts duration
	 */
	TimeDuration operator - ( const TimeDuration& t2 ) const;

	//@}


	/**
	 * @name Comparison operators
	 */
	//@{
	const bool operator < ( const TimeDuration & duration ) const;
	const bool operator <= ( const TimeDuration & duration ) const;
	const bool operator > ( const TimeDuration & duration ) const;
	const bool operator >= ( const TimeDuration & duration ) const;
	const bool operator == ( const TimeDuration & duration ) const;
	const bool operator != ( const TimeDuration & duration ) const;
	//@}

private:
	friend struct Time;
	boost::posix_time::time_duration m_duration; ///< The time duration
};



} // namespace basic

} // namespace vgd

#endif //#ifndef _VGD_BASIC_TIMEDURATION_HPP
