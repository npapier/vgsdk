// VGSDK - Copyright (C) 2004-2006, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGD_EVENT_MOUSEWHEELEVENT_HPP
#define _VGD_EVENT_MOUSEWHEELEVENT_HPP

#include "vgd/event/Event.hpp"



namespace vgd
{

namespace event
{



/**
 * @brief	Defines a mouse wheel event.
 */
struct VGD_API MouseWheelEvent : public Event
{
	/**
	 * @brief	Defines the possible wheel axis.
	 */
	enum Axis { HORIZONTAL, VERTICAL };
	
	/**
	 * @brief	Constructor
	 * 
	 * @param	source			a pointer to the event source
	 * @param	buttonStates	a reference to the button state set
	 * @param	axis				a wheel axis
	 * @param	delta				a wheel rotation delta
	 */
	MouseWheelEvent( Source *source, const ButtonStateSet& buttonStates, Axis axis, int32 delta );

	/**
	 * @brief	Retrieves the wheel axis.
	 * 
	 * @return	a wheel axis
	 */
	const Axis getAxis() const; 
	
	/**
	 * @brief	Retrieves the wheel rotation delta.
	 * 
	 * @return	a signed integer representing the wheel rotation delta
	 */
	const int32 getDelta() const;

	/**
	 * @name Overridden method
	 */
	//@{
	void accept( vgd::event::EventVisitor& eventVisitor );
	//@}

private:

	/**
	 * @brief	The rotation axis.
	 */
	Axis axis;
	
	/**
	 * @brief	The rotation delta.
	 */
	int32 delta;
};


} // namespace event

} // namespace vgd


#endif // _VGD_EVENT_MOUSEWHEELEVENT_HPP
