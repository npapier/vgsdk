// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGWX_EVENT_HELPERS_H
#define _VGWX_EVENT_HELPERS_H

#include <vgd/event/ButtonStateSet.hpp>
#include <vgd/event/detail/GlobalButtonStateSet.hpp>
#include <vgd/event/KeyboardButtonEvent.hpp>

#include "vgWX/vgWX.hpp"



namespace vgWX
{
	
namespace event
{

//template< typename wxEventType >
//vgd::event::ButtonStateSet makeModifiersButtonStates( wxEventType& event )
//{
//	vgd::event::ButtonStateSet bss;
//	
//	if ( event.ControlDown() )
//	{
//		bss.setDown( vgd::event::KeyboardButtonEvent::KEY_CONTROL );
//	}
//
//	if ( event.ShiftDown() )
//	{
//		bss.setDown( vgd::event::KeyboardButtonEvent::KEY_SHIFT );
//	}
//		
//	if ( event.AltDown() )
//	{
//		bss.setDown( vgd::event::KeyboardButtonEvent::KEY_ALT );
//	}
//	
//	return ( bss );
//}



template< typename wxEventType >
void updateModifiersOfGlobalButtonStates( wxEventType& event )
{
	using vgd::event::KeyboardButtonEvent;
	using vgd::event::detail::GlobalButtonStateSet;
	
	GlobalButtonStateSet::update( KeyboardButtonEvent::KEY_CONTROL, event.ControlDown() );

	GlobalButtonStateSet::update( KeyboardButtonEvent::KEY_SHIFT, event.ShiftDown() );
	
	GlobalButtonStateSet::update( KeyboardButtonEvent::KEY_ALT, event.AltDown() );
}


} // namespace event

} // namespace vgWX

#endif //#ifndef _VGWX_EVENT_HELPERS_H
