// VGSDK - Copyright (C) 2004-2006, 2008, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGD_EVENT_EVENTVISITOR_HPP
#define _VGD_EVENT_EVENTVISITOR_HPP

#include "vgd/vgd.hpp"



namespace vgd
{

namespace event
{

struct AxisEvent;
struct HatEvent;
struct JoystickButtonEvent;
struct KeyboardButtonEvent;
struct Location2Event;
struct MouseButtonEvent;
struct Motion3Event;
struct MouseWheelEvent;
struct SizeEvent;
struct TimerEvent;


/**
 * @brief Visitor interface for Event classes
 */
struct VGD_API EventVisitor
{
	/**
	 * @brief Virtual destructor
	 */
	virtual ~EventVisitor();

	virtual void apply( const vgd::event::AxisEvent				*pAxisEvent				)=0;
	virtual void apply( const vgd::event::HatEvent				*pHatEvent				)=0;
	virtual void apply( const vgd::event::JoystickButtonEvent	*pJoystickButtonEvent	)=0;
	virtual void apply( const vgd::event::KeyboardButtonEvent	*pKeyboardButtonEvent	)=0;
	virtual void apply( const vgd::event::Location2Event		*pLocation2Event 		)=0;
	virtual void apply( const vgd::event::MouseButtonEvent		*pMouseButtonEvent		)=0;
	virtual void apply( const vgd::event::Motion3Event			*pMotion3Event			)=0;
	virtual void apply( const vgd::event::MouseWheelEvent		*pMouseWheelEvent		)=0;
	virtual void apply( const vgd::event::SizeEvent				*pSizeEvent				)=0;
	virtual void apply( const vgd::event::TimerEvent			*pTimerEvent			)=0;
};



} // namespace event

} // namespace vgd

#endif //#ifndef _VGD_EVENT_EVENTVISITOR_HPP
