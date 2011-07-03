// VGSDK - Copyright (C) 2009, 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Philippe Sengchanpheng

#include "vgd/basic/Time.hpp"

#include "vgd/basic/TimeDuration.hpp"



namespace vgd
{

namespace basic
{


Time::Time( const bool initializeUsingUTCTime )
:	m_current( initializeUsingUTCTime ?
				boost::posix_time::microsec_clock::universal_time() : 
				boost::posix_time::not_a_date_time ),
	m_pauseTime( boost::posix_time::not_a_date_time ),
	m_pauseDuration()
{
}



void Time::restart()
{
	m_current		=	boost::posix_time::microsec_clock::universal_time();

	// reset pause duration
	m_pauseDuration =	boost::posix_time::time_duration();
	m_pauseTime		=	boost::posix_time::not_a_date_time;
}



void Time::pause()
{
	assert( m_pauseTime.is_not_a_date_time() && "Already in pause mode. Must call resume() before recalling pause()." );
	m_pauseTime = boost::posix_time::microsec_clock::universal_time();
}



void Time::resume()
{
	assert( !m_pauseTime.is_not_a_date_time() && "Must call pause() before resume()." );

	boost::posix_time::ptime	now	=	boost::posix_time::microsec_clock::universal_time();
	m_pauseDuration					+=	now - m_pauseTime;
	m_pauseTime						=	boost::posix_time::not_a_date_time;
}



const TimeDuration Time::getElapsedTime() const
{
	assert( isValid() && "Time is invalid." );

	Time rightNow;

	const TimeDuration duration( *this, rightNow );

	// temporary pause duration, if we're still paused
	boost::posix_time::time_duration	currentPauseDuration(0,0,0,0);
	if( !m_pauseTime.is_not_a_date_time() )
	{
		boost::posix_time::ptime	now	=	boost::posix_time::microsec_clock::universal_time();
		currentPauseDuration			=	now - m_pauseTime;
	}

	// remove pause duration
	const TimeDuration correctedDuration( duration.milliSeconds() - m_pauseDuration.total_milliseconds() - currentPauseDuration.total_milliseconds() );
	return correctedDuration;
}



const bool Time::isPaused() const
{
	return !m_pauseTime.is_not_a_date_time();
}



const TimeDuration Time::operator - ( const Time& t2 ) const
{
	assert( isValid() && "Time is invalid." );
	assert( t2.isValid() && "Time is invalid." );

	const TimeDuration duration( *this, t2 );

	return duration;
}



Time Time::operator + ( const TimeDuration& t2 ) const
{
	Time retVal( *this );

	retVal.m_current += t2.m_duration;

	return retVal;
}



Time Time::operator - ( const TimeDuration& t2 ) const
{
	Time retVal( *this );

	retVal.m_current -= t2.m_duration;

	return retVal;
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
