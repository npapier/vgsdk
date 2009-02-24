// VGSDK - Copyright (C) 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/basic/TimeDuration.hpp"



namespace vgd
{

namespace basic
{


TimeDuration::TimeDuration( const Time& t1, const Time& t2 )
: m_duration( t2.m_current - t1.m_current )
{
}



const uint TimeDuration::seconds() const
{
	return m_duration.total_seconds();
}



const uint TimeDuration::s() const
{
	return seconds();
}



const uint TimeDuration::milliSeconds() const
{
	return m_duration.total_milliseconds();
}



const uint TimeDuration::m() const
{
	return milliSeconds();
}



} // namespace basic

} // namespace vgd
