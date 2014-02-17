// VGSDK - Copyright (C) 2008, 2009, 2011, 2012, 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

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

		// SCREENSHOT
		if ( buttonID == 's' && buttonState == KeyboardButtonEvent::DOWN )
		{
			getCanvas()->scheduleScreenshot();
		}
		// VIDEO CAPTURE
		else if ( buttonID == ' ' && buttonState == KeyboardButtonEvent::DOWN )
		{
			const bool isVideoCaptureEnabled = getCanvas()->isVideoCaptureEnabled();
			// Starts or stops the capture
			getCanvas()->setVideoCapture( !isVideoCaptureEnabled );
		}
	}

	return false;
}



} // namespace event

} // namespace vgUI
