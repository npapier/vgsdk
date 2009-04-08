// VGSDK - Copyright (C) 2008, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgUI/event/CaptureEventProcessor.hpp"

#include <sstream>
#include <locale>
#include "boost/date_time/local_time/local_time.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>

#include <sbf/Module.hpp>
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
				// Stops the capture
				vgLogDebug( "Stops the video capture" );
				vgLogStatus( "Stops the video capture" );
				getCanvas()->setVideoCapture( false );

				// Computes directory name
				namespace bfs = boost::filesystem;
				using namespace boost::local_time;
				using namespace boost::posix_time;

				std::stringstream ss;
				time_facet * outputFacet = new time_facet(); 
				ss.imbue( std::locale(std::locale::classic(), outputFacet) );
				// Monday-29-02-2009_14h30m12s
				outputFacet->format("%A-%d-%m-%Y_%Hh%Mm%Ss");
				ss << second_clock::local_time();

				sbf::Module module;
				const bfs::path path = module.getPath( sbf::Module::Var, bfs::path("videos") / ss.str() );
				const std::string strPath = path.file_string();

				// Flushs the video
				getCanvas()->m_video.mkdirs( strPath );
				getCanvas()->m_video.save( strPath, "video", true );
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
