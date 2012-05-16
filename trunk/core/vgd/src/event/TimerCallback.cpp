// VGSDK - Copyright (C) 2009, 2010, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/event/TimerCallback.hpp"

#include <algorithm>
#include <glm/gtx/compatibility.hpp>
#include <limits>
#include "vgd/event/TimerEvent.hpp"
#include "vgm/Utilities.hpp"



namespace vgd
{

namespace event
{



TimerCallback::TimerCallback()
:	//m_node

	m_executionDuration( 1000 ),
	m_frequency( 25.f ),

	m_tDuration(1000),
	m_tDirection( FORWARD ),
	m_tLoopMode( ONCE ),
	m_tLoopCount(std::numeric_limits<uint>::max()),

	m_firstExecution( false ),
	m_lastExecution( false ),
	//m_elapsedTimeFrom0,
	m_lastTValue(0.f)
{
}



TimerCallback::TimerCallback( vgd::Shp< vgd::node::Node > node )
:	m_node( node ),

	m_executionDuration( 1000 ),
	m_frequency( 25.f ),

	m_tDuration(1000),
	m_tDirection( FORWARD ),
	m_tLoopMode( ONCE ),
	m_tLoopCount(std::numeric_limits<uint>::max()),

	m_firstExecution( false ),
	m_lastExecution( false ),
	//m_elapsedTimeFrom0,
	m_lastTValue(0.f)
{
}



TimerCallback::~TimerCallback()
{
}



vgd::Shp< vgd::node::Node > TimerCallback::getNode()
{
	return m_node;
}



void TimerCallback::setNode( vgd::Shp< vgd::node::Node > node )
{
	m_node = node;
}



const bool TimerCallback::operator() ( const vgd::Shp< vgd::event::TimerEvent > event )
{
	if ( m_firstExecution.isInvalid() )
	{
		// This is the first call of this callback
		m_firstExecution.restart();

		//
		m_lastExecution		= m_firstExecution;
		m_elapsedTimeFrom0	= m_firstExecution.getElapsedTime();
		beginExecution( event );
		apply( event );
	}
	else
	{
		const vgd::basic::TimeDuration duration = m_lastExecution.getElapsedTime();

		if ( duration.ms() >= (1000.f / getFrequency()) )
		{
			//
			m_lastExecution.restart();
			m_elapsedTimeFrom0 = m_firstExecution.getElapsedTime();
			apply( event );
		}
		// else nothing to do
	}

	// Takes care of execution duration
	const bool retVal = (getExecutionDuration() == vgd::basic::TimeDuration()) ?
		false :														// executes this callback forever
		m_firstExecution.getElapsedTime() > getExecutionDuration();	// stops execution if conditions are reached

	if ( retVal )
	{
		// This is the last execution of this callback
		endExecution( event );
	}

	return retVal;
}


void TimerCallback::setExecutionDuration( const vgd::basic::TimeDuration duration )
{
	m_executionDuration = duration;
}


const vgd::basic::TimeDuration TimerCallback::getExecutionDuration() const
{
	return m_executionDuration;
}


void TimerCallback::setFrequency( const float frequency )
{
	m_frequency = frequency;
}


const float TimerCallback::getFrequency() const
{
	return m_frequency;
}


const float TimerCallback::getTf()
{
	return static_cast< float >( getTd() );
}


const double TimerCallback::getTd()
{
	// Initializes begin and end for T param
	double beginT, endT;
	if ( getTDirection() == FORWARD )
	{
		beginT	= 0.f;
		endT	= 1.f;
	}
	else
	{
		assert( getTDirection() == BACKWARD );

		beginT	= 1.f;
		endT	= 0.f;
	}

	// Evaluates t value
	double value = 0.f;

	if ( getTLoopMode() == ONCE )
	{
		if ( m_elapsedTimeFrom0.ms() > getTDuration().ms() )
		{
			return m_lastTValue;
		}
		else
		{
			value = vgm::Utilities::linearInterpolation(
				0.f,					static_cast< float >(beginT),
				getTDuration().ms(),	static_cast< float >(endT),
				static_cast< float >( m_elapsedTimeFrom0.ms() ) );

			value = glm::saturate( value );
		}
	}
	else if ( getTLoopMode() == LOOP || getTLoopMode() == SWING )
	{
		const uint loopDuration = getTDuration().ms();
		const uint loopCount	= m_elapsedTimeFrom0.ms() / loopDuration;

		if ( loopCount < m_tLoopCount /* don't use getTLoopCount(), because it could returned 0 instead of numeric_limits<>::max() */ )
		{
			float moduloTInMS = static_cast< float >( m_elapsedTimeFrom0.ms() % loopDuration );

			if ( getTLoopMode() == SWING )
			{
				if ( moduloTInMS <= loopDuration / 2 )
				{
					value = vgm::Utilities::linearInterpolation(
						0.f,				beginT,
						loopDuration / 2,	endT,
						moduloTInMS );
				}
				else
				{
					value = vgm::Utilities::linearInterpolation(
						loopDuration /2,	endT,
						loopDuration,		beginT,
						moduloTInMS );
				}
			}
			else
			{
				value = vgm::Utilities::linearInterpolation(
					0.f,			beginT,
					loopDuration,	endT,
					moduloTInMS );
			}
			value = glm::saturate( value );
		}
		else
		{
			return m_lastTValue;
		}
	}
	else
	{
		assert( false );
	}

	m_lastTValue = value;

	return m_lastTValue;
}



void TimerCallback::setTDuration( const vgd::basic::TimeDuration duration )
{
	m_tDuration = duration;
}


const vgd::basic::TimeDuration TimerCallback::getTDuration() const
{
	return m_tDuration;
}


void TimerCallback::setTDirection( const TDirection direction )
{
	m_tDirection = direction;
}


const TimerCallback::TDirection TimerCallback::getTDirection() const
{
	return m_tDirection;
}


void TimerCallback::setTLoopMode( const TLoopMode mode )
{
	m_tLoopMode = mode;
}


const TimerCallback::TLoopMode TimerCallback::getTLoopMode() const
{
	return m_tLoopMode;
}


void TimerCallback::setTLoopCount( const uint count )
{
	if ( count == 0 )
	{
		m_tLoopCount = std::numeric_limits<uint>::max();
	}
	else
	{
		m_tLoopCount = count;
	}
}


const uint TimerCallback::getTLoopCount() const
{
	if ( m_tLoopCount == std::numeric_limits<uint>::max() )
	{
		return 0;
	}
	else
	{
		return m_tLoopCount;
	}
}



} // namespace event

} // namespace vgd
