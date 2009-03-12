// VGSDK - Copyright (C) 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_BASIC_TIME_HPP
#define _VGD_BASIC_TIME_HPP

#include "vgd/vgd.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>

namespace vgd { namespace basic { struct TimeDuration; } }

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
	 * @brief Returns the elapsed time between the time point of this object  and the call of this method.
	 *
	 * @pre isValid() == true
	 *
	 * @return the duration time object.
	 */
	const TimeDuration getElapsedTime() const;

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
	boost::posix_time::ptime	m_current; ///< The UTC time
};



} // namespace basic

} // namespace vgd

#endif //#ifndef _VGD_BASIC_TIME_HPP
