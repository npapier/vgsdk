// VGSDK - Copyright (C) 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/basic/Time.hpp"

#include "vgd/basic/TimeDuration.hpp"



namespace vgd
{

namespace basic
{


Time::Time( const bool initializeUsingUTCTime )
: m_current( initializeUsingUTCTime ?
				boost::posix_time::microsec_clock::universal_time() : 
				boost::posix_time::not_a_date_time )
{
}



void Time::restart()
{
	m_current = boost::posix_time::microsec_clock::universal_time();
}



const TimeDuration Time::getElapsedTime() const
{
	assert( isValid() && "Time is invalid." );

	Time now;

	const TimeDuration duration( *this, now );

	return duration;
}



const TimeDuration Time::operator - ( const Time& t2 ) const
{
	assert( isValid() && "Time is invalid." );
	assert( t2.isValid() && "Time is invalid." );

	const TimeDuration duration( *this, t2 );

	return duration;
}



const bool Time::isValid() const
{
	const bool retVal = m_current.is_not_a_date_time();

	return !retVal;
}



const bool Time::isInvalid() const
{
	const bool retVal = m_current.is_not_a_date_time();

	return retVal;
}



void Time::setInvalid()
{
	m_current = boost::posix_time::ptime( boost::posix_time::not_a_date_time );
}



const bool Time::operator < ( const Time & t2 ) const
{
	assert( isValid() && "Time is invalid." );
	assert( t2.isValid() && "Time is invalid." );

	return m_current < t2.m_current;
}


const bool Time::operator <= ( const Time & t2 ) const
{
	assert( isValid() && "Time is invalid." );
	assert( t2.isValid() && "Time is invalid." );

	return m_current <= t2.m_current;
}


const bool Time::operator > ( const Time & t2 ) const
{
	assert( isValid() && "Time is invalid." );
	assert( t2.isValid() && "Time is invalid." );

	return m_current > t2.m_current;
}


const bool Time::operator >= ( const Time & t2 ) const
{
	assert( isValid() && "Time is invalid." );
	assert( t2.isValid() && "Time is invalid." );

	return m_current >= t2.m_current;
}


const bool Time::operator == ( const Time & t2 ) const
{
	assert( isValid() && "Time is invalid." );
	assert( t2.isValid() && "Time is invalid." );

	return m_current == t2.m_current;
}


const bool Time::operator != ( const Time & t2 ) const
{
	assert( isValid() && "Time is invalid." );
	assert( t2.isValid() && "Time is invalid." );

	return m_current != t2.m_current;
}



} // namespace basic

} // namespace vgd
