// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgUI/event/CaptureEventProcessor.hpp"

#include <vgd/event/KeyboardButtonEvent.hpp>
#include "vgUI/Canvas.hpp"



namespace vgUI
{

namespace event
{



CaptureEventProcessor::CaptureEventProcessor( ::vgUI::Canvas * canvas )
:	EventProcessor( canvas )
{}



const bool CaptureEventProcessor::onEvent( vgd::Shp< vgd::event::Event > event )
{
	using vgd::event::KeyboardButtonEvent;

	KeyboardButtonEvent * keyboardButtonEvent = dynamic_cast< KeyboardButtonEvent * >( event.get() );

	// Tests if incoming event is a keyboard button event
	if ( keyboardButtonEvent )
	{
		const uint							buttonID	= keyboardButtonEvent->getButtonID();
		const KeyboardButtonEvent::State	buttonState	= keyboardButtonEvent->getState();
		if ( buttonID == 's' && buttonState == KeyboardButtonEvent::DOWN )
		{
			getCanvas()->scheduleScreenshot();
		}
		else if ( buttonID == 'v' && buttonState == KeyboardButtonEvent::DOWN )
		{
			getCanvas()->setVideoCapture();
		}
		else if ( buttonID == 'b' && buttonState == KeyboardButtonEvent::DOWN )
		{
			getCanvas()->setVideoCapture( false );
		}
	}

	return false;
}



} // namespace event

} // namespace vgUI
