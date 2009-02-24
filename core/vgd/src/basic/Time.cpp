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


Time::Time()
: m_current( boost::posix_time::microsec_clock::universal_time() )
{
}



void Time::restart()
{
	m_current = boost::posix_time::microsec_clock::universal_time();
}



const TimeDuration Time::getElapsedTime() const
{
	Time now;

	const TimeDuration duration( *this, now );

	return duration;
}



const TimeDuration Time::operator - ( const Time& t2 ) const
{
	const TimeDuration duration( *this, t2 );

	return duration;
}



} // namespace basic

} // namespace vgd
