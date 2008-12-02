// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgUI/event/CaptureEventProcessor.hpp"

#include <vgd/event/KeyboardButtonEvent.hpp>
#include <vgDebug/convenience.hpp>
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
			if ( getCanvas()->isVideoCaptureEnabled() == false )
			{
				vgLogDebug( "Starts the video capture" );
				vgLogStatus( "Starts the video capture" );
				getCanvas()->setVideoCapture();
			}
		}
		else if ( buttonID == 'b' && buttonState == KeyboardButtonEvent::DOWN )
		{
			if ( getCanvas()->isVideoCaptureEnabled() )
			{
				vgLogDebug( "Stops the video capture" );
				vgLogStatus( "Stops the video capture" );
				getCanvas()->setVideoCapture( false );

				// Flushs the video
				getCanvas()->m_video.save( "../var/vgsdk/videos/", "video", true );
				getCanvas()->m_video.clear();
			}
		}
		else if ( buttonID == 'c' && buttonState == KeyboardButtonEvent::DOWN )
		{
			if ( getCanvas()->isVideoCaptureEnabled() )
			{
				vgLogDebug( "Cancels the video capture" );
				vgLogStatus( "Cancels the video capture" );
				getCanvas()->setVideoCapture( false );

				// Removes the video
				getCanvas()->m_video.clear();
			}
		}
	}

	return false;
}



} // namespace event

} // namespace vgUI
