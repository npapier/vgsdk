// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_EVENT_EVENTVISITOR_H
#define _VGD_EVENT_EVENTVISITOR_H

#include "vgd/vgd.hpp"



namespace vgd
{
	
namespace event
{
	
struct KeyboardButtonEvent;
struct MouseButtonEvent;

/**
 * @brief Visitor interface for Event classes
 */
struct VGD_API EventVisitor
{
	virtual void apply( const vgd::event::KeyboardButtonEvent	*pKeyboardButtonEvent	)=0;
	virtual void apply( const vgd::event::MouseButtonEvent		*pMouseButtonEvent 		)=0;
};



} // namespace event

} // namespace vgd

#endif //#ifndef _VGD_EVENT_EVENTVISITOR_H
