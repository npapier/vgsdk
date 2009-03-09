// VGSDK - Copyright (C) 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGD_EVENT_SIZEEVENT_HPP
#define _VGD_EVENT_SIZEEVENT_HPP

#include <vgm/Vector.hpp>

#include "vgd/event/Event.hpp"


namespace vgd
{

namespace event
{



/**
 * @brief	Defines the event class for size change notifications.
 */
struct VGD_API SizeEvent : public Event
{
	/**
	 * @brief	Constructor.
	 * 
	 * @param	source			a pointer to event source
	 * @param	buttonStates	a reference to the button state set
	 * @param	size			the size information
	 */
	SizeEvent( Source * source, const ButtonStateSet & buttonStates, const vgm::Vec2i & size );
	
	/**
	 * @brief	Destructor.
	 */
	virtual ~SizeEvent();

	/**
	 * @brief	Retrives the size.
	 */
	const vgm::Vec2i & getSize() const;

	/**
	 * @name Overridden method
	 */
	//@{
	void accept( vgd::event::EventVisitor& eventVisitor );
	//@}


private:

	vgm::Vec2i	m_size;	///< The size.
};



} // namespace event

} // namespace vgd

#endif // _VGD_EVENT_SIZEEVENT_HPP
