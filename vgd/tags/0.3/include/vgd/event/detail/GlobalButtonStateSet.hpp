// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_EVENT_DETAIL_GLOBALBUTTONSTATESET_H
#define _VGD_EVENT_DETAIL_GLOBALBUTTONSTATESET_H

#include "vgd/vgd.hpp"
#include "vgd/event/ButtonStateSet.hpp"



namespace vgd
{
	
namespace event
{

namespace detail
{

/**
 * @brief The global button state.
 * 
 * The global button states permits to ask the state of all button in the whole system.
 * It is updated by each event generator.	
 */
struct VGD_API GlobalButtonStateSet
{
	/**
	 * @brief	Retrieves the global button states.
	 * 
	 * @return	a reference to the global button states
	 */
	static const vgd::event::ButtonStateSet& get();

	/**
	 * @brief	Clear the global button states.
	 * 
	 * @remarks Call get().setUp().
	 */
	static void clear();

	/**
	 * @brief Update the global button states.
	 * 
	 * @param buttonID	a button identifier
	 * @param isDown		true if button is down, false otherwise
	 */
	static void update( const int32 buttonID, const bool isDown );


private:
	/**
	 * @brief	the global button state set
	 */
	static vgd::event::ButtonStateSet	m_states;
};

} // namespace detail

} // namespace event

} // namespace vgd

#endif //#ifndef _VGD_EVENT_DETAIL_GLOBALBUTTONSTATESET_H
