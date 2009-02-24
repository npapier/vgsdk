// VGSDK - Copyright (C) 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_EVENT_TIMERCALLBACK_HPP
#define _VGD_EVENT_TIMERCALLBACK_HPP

#include "vgd/Shp.hpp"
#include "vgd/basic/Time.hpp"

namespace vgd { namespace event { struct TimerEvent; } }
namespace vgd { namespace node { struct Node; } }



namespace vgd
{

namespace event
{



/**
 * @brief Callback triggered by timer event.
 */
struct VGD_API TimerCallback
{
	/**
	 * @brief	Default constructor
	 *
	 * @post getNode() == 0
	 */
	TimerCallback();

	/**
	 * @brief	Constructor storing a node reference for future usage in apply method.
	 *
	 * @param node	a shared pointer on the node to store
	 *
	 * @pre node != 0
	 * @post getNode() != 0
	 */
	TimerCallback( vgd::Shp< vgd::node::Node > node );

	/**
	 * @brief	Virtual destructor
	 */
	virtual ~TimerCallback();



	/**
	 * @brief Retrieves the node reference stored by this callback
	 *
	 * @return the node reference stored by this callback
	 */
	vgd::Shp< vgd::node::Node > getNode();



	/**
	 * @brief Implements the callback
	 *
	 * This callback method is called each time a timer send an event and all requirements are satisfied (see mustBeApplied method).
	 *
	 * @param event			the event that has triggered the callback execution
	 */
	virtual void apply( const vgd::Shp< vgd::event::TimerEvent > event )=0;

	//* @param normalizedTime	a value representing a value between 0 and 1 representing the
	//mustBeApplied


private:


	vgd::Shp< vgd::node::Node > m_node;	///< the node reference stored by this callback.

//	vgd::basic::Time m_lastExecution;	///<  the time point of the last call of this callback
};



} // namespace event

} // namespace vgd

#endif // #ifndef _VGD_EVENT_TIMERCALLBACK_HPP
