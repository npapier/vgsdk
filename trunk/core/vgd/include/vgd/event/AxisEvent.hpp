// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGD_EVENT_AXISEVENT_HPP_
#define _VGD_EVENT_AXISEVENT_HPP_

#include "vgd/vgd.hpp"
#include "vgd/event/Event.hpp"



namespace vgd
{

namespace event
{



/**
 * @brief	Implements an event that notifies about axis positions (like analog controls of a joystick).
 * 			The axis position is normalized so values are always in the range [-1, 1].
 */
struct VGD_API AxisEvent : public Event
{
	/**
	 * @brief	Constructor
	 *
	 * @param	source			a pointer to the source device
	 * @param	buttonStates	states of the buttons
	 * @param	index			axis' index
	 * @param	value			axis' value (must be in the range [-1, 1])
	 *
	 * @pre		(value >= -1.f) && (value <= 1.f)
	 */
	AxisEvent( Source * source, const ButtonStateSet & buttonStates, const int index, const float value );

	/**
	 * @name	Accessors
	 */
	//@{
	/**
	 * @brief	Retrieves the index of the axis.
	 *
	 * @return	the axis' index
	 */
	const int getIndex() const;

	/**
	 * @brief	Retrieves the value of the axis.
	 *
	 * @remark	Values are always in the range [-1, 1].
	 *
	 * @return	the axis' value
	 */
	const float getValue() const;
	//@}


	/**
	 * @name	Overrides
	 */
	//@{
	void accept( vgd::event::EventVisitor & eventVisitor );
	//@}


private:

	const int	m_index;	///< The index of the axis
	const float	m_value;	///< The value of the xais
};


} // namespace event

} // namespace vgd



#endif /*_VGD_EVENT_AXISEVENT_HPP_*/
