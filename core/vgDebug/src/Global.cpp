// VGSDK - Copyright (C) 2004, 2008, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#include "vgDebug/Global.hpp"

#include "vgDebug/Logging.hpp"



namespace vgDebug
{



ILogging& Global::get()
{
	return ( *m_globalLogger );
}


void Global::set( boost::shared_ptr< ILogging > logger )
{
	assert( logger );

	m_globalLogger = logger;
}


const bool Global::isAssertEnabled()
{
	return m_assertEnabled;
}


void Global::setAssertEnabled( const bool enabled )
{
	m_assertEnabled = enabled;
}


boost::shared_ptr< ILogging >	Global::m_globalLogger( new Logging() );

bool							Global::m_assertEnabled( true );


ILogging& get()
{
	return ( vgDebug::Global::get() );
}


void set( boost::shared_ptr< ILogging > logger )
{
	vgDebug::Global::set( logger );
}


const bool isAssertEnabled()
{
	return vgDebug::Global::isAssertEnabled();
}


void setAssertEnabled( const bool enabled )
{
	vgDebug::Global::setAssertEnabled( enabled );
}


} // namespace vgDebug
