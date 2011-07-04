// VGSDK - Copyright (C) 2009, 2010, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Philippe Sengchanpheng

#ifndef _VGD_BASIC_TIME_HPP
#define _VGD_BASIC_TIME_HPP

#include <boost/date_time/posix_time/posix_time.hpp>
#include "vgd/basic/TimeDuration.hpp"


/**
 * @defgroup g_time Time
 */



namespace vgd
{

namespace basic
{


/**
 * @brief Interface for time point manipulation
 *
 * @ingroup g_time
 */
struct VGD_API Time
{
	/**
	 * @brief Default constructor using the current UTC time.
	 *
	 * @param initializeUsingUTCTime	true to initialize this point time using UTC time, false to create an invalid point time (see isValid()).
	 */
	Time( const bool initializeUsingUTCTime = true );



	/**
	 * @name Measure time duration
	 */
	//@{

	/**
	 * @brief Reinitializes this time point using the current UTC time.
	 */
	void restart();

	/**
	 * @brief Pause the time point.
	 */
	void pause();

	/**
	 * @brief Resume the time point from its paused state.
	 */
	void resume();


	/**
	 * @brief Returns the elapsed time between the time point of this object  and the call of this method.
	 *
	 * @pre isValid() == true
	 *
	 * @return the duration time object.
	 */
	const TimeDuration getElapsedTime() const;


	/**
	 * @brief Checks if the time point is paused or not.
	 */
	const bool isPaused() const;

	//@}



	/**
	 * @brief Returns the difference between two times.
	 *
	 * @param t2	the second time
	 *
	 * @pre isValid() and t2.isValid() 
	 *
	 * @return the duration time object, i.e. t2 - (*this)
	 */
	const TimeDuration operator - ( const Time& t2 ) const;



	/**
	 * @name Arithmetic operator
	 */
	//@{

	/**
	 * @brief Returns a point time adding a time duration
	 */
	Time operator + ( const TimeDuration& t2 ) const;

	/**
	 * @brief Returns a point time substracting duration
	 */
	Time operator - ( const TimeDuration& t2 ) const;

	//@}



	/**
	 * @name Validity accessors
	 */
	//@{

	/**
	 * @brief Tests if this time point is valid.
	 *
	 * @return true if this time point is valid, false otherwise.
	 */
	const bool isValid() const;

	/**
	 * @brief Tests if this time point is invalid.
	 *
	 * @return true if this time point is invalid, false otherwise.
	 */
	const bool isInvalid() const;

	/**
	 * @brief Invalidates the time point.
	 */
	void setInvalid();

	//@}


	/**
	 * @name Comparison operators
	 *
	 * @pre isValid() and t2.isValid() 
	 */
	//@{
	const bool operator < ( const Time & t2 ) const;
	const bool operator <= ( const Time & t2 ) const;
	const bool operator > ( const Time & t2 ) const;
	const bool operator >= ( const Time & t2 ) const;
	const bool operator == ( const Time & t2 ) const;
	const bool operator != ( const Time & t2 ) const;
	//@}


private:
	friend struct TimeDuration;
	boost::posix_time::ptime			m_current;			///< The UTC time
	boost::posix_time::ptime			m_pauseTime;		///< The time when pause was hit
	boost::posix_time::time_duration	m_pauseDuration;	///< Total pause duration
};



} // namespace basic

} // namespace vgd

#endif //#ifndef _VGD_BASIC_TIME_HPP
