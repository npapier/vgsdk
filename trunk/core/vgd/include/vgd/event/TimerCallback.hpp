// VGSDK - Copyright (C) 2009, 2010, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_EVENT_TIMERCALLBACK_HPP
#define _VGD_EVENT_TIMERCALLBACK_HPP

#include "vgd/Shp.hpp"
#include "vgd/basic/Time.hpp"
#include "vgd/basic/TimeDuration.hpp"

namespace vgd { namespace event { struct TimerEvent; } }
namespace vgd { namespace node { struct Node; } }



namespace vgd
{

namespace event
{



struct TimerCallback;

/**
 * @brief Base functor to overload TimerCallback::apply() method
 */
struct VGD_API ApplyFunctor
{
	virtual void apply( const vgd::Shp< vgd::event::TimerEvent > event, vgd::event::TimerCallback * timerCallbackSource )=0;
};


/**
 * @brief Callback triggered by timer event.
 *
 * @ingroup g_time
 *
 * @todo stop() => call stop() follow by getTimerEventProcessor()->remove( callback );
 *
 * @todo isCallable(), isActive or isPlaying()
 * @todo functor
 * @todo delay()
 * @todo pause()
 * @todo start(), stop(), rewind(), skip(), advance()
 */
struct TimerCallback
{
	/**
	 * @name Constructor and destructor
	 */
	//@{

	/**
	 * @brief	Default constructor
	 *
	 * @post getNode() == 0
	 *
	 * @post getExecutionDuration().seconds() == 1
	 * @post getFrequency() == 25
	 */
	VGD_API TimerCallback();

	/**
	 * @brief	Constructor storing a node reference for future usage in apply method.
	 *
	 * @param node			a shared pointer on the node to store
	 *
	 * @pre node != 0
	 *
	 * @post getNode() != 0
	 *
	 * @post getExecutionDuration().seconds() == 1
	 * @post getFrequency() == 25
	 */
	VGD_API TimerCallback( vgd::Shp< vgd::node::Node > node );

	/**
	 * @brief	Virtual destructor
	 */
	VGD_API virtual ~TimerCallback();
	//@}


	/**
	 * @name Node accessor
	 */
	//@{

	/**
	 * @brief Retrieves the node reference stored by this callback
	 *
	 * @return the node reference stored by this callback
	 */
	VGD_API vgd::Shp< vgd::node::Node > getNode();

	/**
	 * @brief Sets the node reference stored by this callback
	 *
	 * @param node	the node to store
	 */
	VGD_API void setNode( vgd::Shp< vgd::node::Node > node );

	//@}


	/**
	 * @name Methods to overload TimerCallback::apply()
	 */
	//@{

	/**
	 * @brief Retrieves the apply functor stored by this callback
	 *
	 * @return the apply functor stored by this callback
	 */
	VGD_API vgd::Shp< ApplyFunctor > getApplyFunctor();

	/**
	 * @brief Sets the apply functor stored by this callback
	 *
	 * @param applyFunctor	the apply functor to store
	 */
	VGD_API void setApplyFunctor( vgd::Shp< ApplyFunctor > applyFunctor );

	//@}


	/**
	 * @name Callback implementation
	 */
	//@{

	/**
	 * @brief Implements the internal part of timer callback
	 *
	 * This callback method is called by TimerEventProcessor class when it receives a time event.
	 *
	 * @param event		the event that has triggered the callback execution
	 * @return true to stop futur execution of this callback, false to continue.
	 */
	VGD_API const bool operator() ( const vgd::Shp< vgd::event::TimerEvent > event );

	/**
	 * @brief Implements the user part of the timer callback
	 *
	 * @param event		the event that has triggered the callback execution
	 *
	 * @remarks To customize this callback, use setApplyFunctor() or override this method
	 */
	VGD_API virtual void apply( const vgd::Shp< vgd::event::TimerEvent > event );

	/**
	 * @brief Implements the user part of the first execution of the timer callback
	 *
	 * @param event		the event that has triggered the callback execution
	 *
	 * By default, this method does nothing. Overriddes this method to customize this callback.
	 */
	VGD_API virtual void beginExecution( const vgd::Shp< vgd::event::TimerEvent > event ) {}

	/**
	 * @brief Implements the user part of the last execution of the timer callback
	 *
	 * @param event		the event that has triggered the callback execution
	 *
	 * By default, this method does nothing. Overriddes this method to customize this callback.
	 */
	VGD_API virtual void endExecution( const vgd::Shp< vgd::event::TimerEvent > event ) {}

	//@}



	/**
	 * @name Parametrization methods
	 */
	//@{

	/**
	 * @brief Sets the life duration of callback execution
	 *
	 * @param duration	the life duration of callback execution
	 *
	 * @remarks Uses a null duration, constructed using TimeDuration(), to set an infinite life duration of callback execution.
	 */
	VGD_API void setExecutionDuration( const vgd::basic::TimeDuration duration );

	/**
	 * @brief Returns the life duration of callback execution
	 *
	 * @return the life duration of callback execution
	 */
	VGD_API const vgd::basic::TimeDuration getExecutionDuration() const;


	/**
	 * @brief Sets frequency of callback execution in hertz.
	 *
	 * Sets the desired number of execution per seconds.
	 */
	VGD_API void setFrequency( const float frequency );

	/**
	 * @brief Returns the frequency of callback execution in hertz.
	 *
	 * @return the frequency of callback execution in hertz.
	 *
	 * @see setFrequency
	 */
	VGD_API const float getFrequency() const;

	//@}


	/**
	 * @name T parameter
	 *
	 * This parameter is a time parameter normalized between [0,1]. 
	 * Typical usage is to implement a function of time in apply() to do animation.
	 *
	 * Its default behavior is :
	 * - it is set to 0 at the first execution of the callback
	 * - next it increases linearly
	 * - and finally reach 1 after 1 seconds.
	 *
	 * This behavior, therefore the callback animation, could be customized using setTDuration() , setTDirection(), setTLoopMode() and setTLoopCount().
	 */
	//@{

	/**
	 * @brief Returns the t parameter
	 *
	 * @return a value between 0 and 1.
	 */
	VGD_API const float getTf();

	/**
	 * @brief Returns the t parameter value
	 *
	 * @return a value between 0 and 1.
	 */
	VGD_API const double getTd();


	/**
	 * @brief Sets the duration
	 *
	 * This value represents the time needed for the t parameter to reach 1 from zero.
	 */
	VGD_API void setTDuration( const vgd::basic::TimeDuration duration );

	/**
	 * @brief Returns the duration
	 */
	VGD_API const vgd::basic::TimeDuration getTDuration() const;


	/**
	 * @brief Defines the different direction of the t parameter
	 */
	enum TDirection
	{
		FORWARD,	///< the t parameter increases with time, i.e. moves from 0 to 1
		BACKWARD,	///< the t parameter decreases with time, i.e. moves from 1 to 0
	};

	/**
	 * @brief Sets the direction
	 *
	 * This value defines if the t parameter increases or decreases with time.
	 *
	 * @param direction	the desired direction
	 *
	 * @see TDirection
	 */
	VGD_API void setTDirection( const TDirection direction );

	/**
	 * @brief Returns the direction
	 */
	VGD_API const TDirection getTDirection() const;


	/**
	 * @brief Defines the different loop modes of the t parameter
	 */
	enum TLoopMode
	{
		ONCE,	///< moves from 0 to 1 one time
		LOOP,	///< repeats move from 0 to 1
		SWING	///< repeats move from 0 to 1, then 1 to 0
	};

	/**
	 * @brief Sets the loop mode
	 *
	 * @param mode	the loop mode
	 *
	 * @see TLoopMode
	 */
	VGD_API void setTLoopMode( const TLoopMode mode );

	/**
	 * @brief Returns the loop mode
	 */
	VGD_API const TLoopMode getTLoopMode() const;


	/**
	 * @brief Sets the loop count
	 *
	 * @param count	the number of time the loop should be executed.
	 *
	 * @remarks a loop count sets to zero means the loop would be execute forever
	 */
	VGD_API void setTLoopCount( const uint count );

	/**
	 * @brief Returns the loop count
	 */
	VGD_API const uint getTLoopCount() const;

	//@}


protected:

	vgd::Shp< vgd::node::Node >	m_node;				///< the node reference stored by this callback.
	vgd::Shp< ApplyFunctor >	m_applyFunctor;		///< a functor to overload apply()

	/**
	 * @name Callback parameterization
	 */
	//@{
	vgd::basic::TimeDuration	m_executionDuration;
	float						m_frequency;
	// @}

	/**
	 * @name T parameter data
	 */
	//@{
	vgd::basic::TimeDuration	m_tDuration;
	TDirection					m_tDirection;
	TLoopMode					m_tLoopMode;
	uint						m_tLoopCount;
	//@}

	// details
	vgd::basic::Time m_firstExecution;	///<  the time point of the first call of this callback
	vgd::basic::Time m_lastExecution;	///<  the time point of the last call of this callback

	vgd::basic::TimeDuration	m_elapsedTimeFrom0;
	double						m_lastTValue;
};



} // namespace event

} // namespace vgd

#endif // #ifndef _VGD_EVENT_TIMERCALLBACK_HPP
