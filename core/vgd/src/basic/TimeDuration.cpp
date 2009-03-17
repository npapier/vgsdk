// VGSDK - Copyright (C) 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/basic/TimeDuration.hpp"

#include "vgd/basic/Time.hpp"



namespace vgd
{

namespace basic
{


TimeDuration::TimeDuration( const Time& t1, const Time& t2 )
: m_duration( t2.m_current - t1.m_current )
{
}


TimeDuration::TimeDuration( const int milliSeconds )
: m_duration( boost::posix_time::milliseconds( milliSeconds ) )
{
}


TimeDuration::TimeDuration( const int hours, const int minutes, const int seconds, const int milliSeconds )
: m_duration( hours, minutes, seconds )
{
	if ( milliSeconds != 0 )
	{
		m_duration = m_duration + boost::posix_time::milliseconds( milliSeconds );
	}
}



const uint64 TimeDuration::hours() const
{
	return m_duration.hours();
}


const uint64 TimeDuration::h() const
{
	return hours();
}


const uint64 TimeDuration::minutes() const
{
	return m_duration.minutes();
}


const uint64 TimeDuration::m() const
{
	return minutes();
}


const uint64 TimeDuration::seconds() const
{
	return m_duration.total_seconds();
}


const uint64 TimeDuration::s() const
{
	return seconds();
}


const uint64 TimeDuration::milliSeconds() const
{
	return m_duration.total_milliseconds();
}


const uint64 TimeDuration::ms() const
{
	return milliSeconds();
}



TimeDuration TimeDuration::operator + ( const TimeDuration& t2 ) const
{
	TimeDuration retVal(*this);

	retVal.m_duration += t2.m_duration;

	return retVal;
}



TimeDuration TimeDuration::operator - ( const TimeDuration& t2 ) const
{
	TimeDuration retVal(*this);

	retVal.m_duration -= t2.m_duration;

	return retVal;
}



const bool TimeDuration::operator < ( const TimeDuration & duration ) const
{
	return m_duration < duration.m_duration;
}


const bool TimeDuration::operator <= ( const TimeDuration & duration ) const
{
	return m_duration <= duration.m_duration;
}


const bool TimeDuration::operator > ( const TimeDuration & duration ) const
{
	return m_duration > duration.m_duration;
}


const bool TimeDuration::operator >= ( const TimeDuration & duration ) const
{
	return m_duration >= duration.m_duration;
}


const bool TimeDuration::operator == ( const TimeDuration & duration ) const
{
	return m_duration == duration.m_duration;
}


const bool TimeDuration::operator != ( const TimeDuration & duration ) const
{
	return m_duration != duration.m_duration;
}



} // namespace basic

} // namespace vgd
