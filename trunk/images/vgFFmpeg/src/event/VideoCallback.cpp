// VGSDK - Copyright (C) 2009, 2010, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#include "vgFFmpeg/event/VideoCallback.hpp"

#include <vgd/basic/Image.hpp>
#include <vgd/event/TimerEvent.hpp>
#include <vgd/node/Group.hpp>
#include <vgd/node/Quad.hpp>
#include <vgd/node/Texture2D.hpp>
#include <vgd/visitor/helpers.hpp>

//#define ENABLED_VIDEO_DEBUG


namespace vgFFmpeg
{


static const std::string	GROUP_NODE_NAME("VideoPlayback");
static const std::string	TEX2D_NODE_NAME("VideoPlayback.frame");
static const std::string	QUAD_NODE_NAME("VideoPlayback.shape");




VideoCallback::VideoCallback( const std::string& pathFilename )
:	m_output( NO_OUTPUT ),
	m_videoOver(false),
	m_replayWaitingTime(1)
{
	setVideo( pathFilename );

	setExecutionDuration( 0 );
	setTDuration( 0 );

	setTDirection( FORWARD );
	setTLoopMode( ONCE );
	setTLoopCount( 0 );
}



vgd::Shp< vgd::node::Group > VideoCallback::setVideoPlaybackInTexture2D()
{
	using vgd::node::Group;
	using vgd::node::Quad;
	using vgd::node::Texture2D;

	vgd::Shp< Group >		group	= Group::create( GROUP_NODE_NAME );
	vgd::Shp< Texture2D >	tex2D	= Texture2D::create( TEX2D_NODE_NAME );
	vgd::Shp< Quad >		quad	= Quad::create( QUAD_NODE_NAME );

	group->addChilds( tex2D, quad );

	tex2D->setWrap( Texture2D::WRAP_S, Texture2D::CLAMP_TO_EDGE );
	tex2D->setWrap( Texture2D::WRAP_T, Texture2D::CLAMP_TO_EDGE );
	tex2D->setFilter( Texture2D::MIN_FILTER, Texture2D::LINEAR );
	tex2D->setFilter( Texture2D::MAG_FILTER, Texture2D::LINEAR );
	tex2D->sethFunction( Texture2D::FUN_MODULATE );

	quad->initializeTexUnits( 1, vgd::basic::TOP_LEFT, false /* cw */ );

	setNode( group );
	m_output = TEXTURE2D;

	updateAspectRatio();

	return group;
}



void VideoCallback::apply( const vgd::Shp< vgd::event::TimerEvent > event )
{
	// Tests if there is an ouput defined
	if ( m_output == NO_OUTPUT )
	{
		return;
	}

	// Tests if video is over and video restart has been requested
	if ( m_videoOver.isValid() )
	{
		vgAssert( m_video->isOver() );
		if ( m_videoOver.getElapsedTime() > getReplayWaitingTime() )
		{
#ifdef ENABLED_VIDEO_DEBUG
			vgLogDebug2( "Video is over since %i ms. Calls restart()", m_videoOver.getElapsedTime().ms() );
#endif
			m_video->restart();
			m_videoOver.setInvalid();
		}
		else
		{
			return;
		}
	}
	//else nothing to do

	// Tests if video is in paused
	if ( m_video->isPaused() )
	{
		// Schedules a refresh
		event->scheduleRefreshForced(); // @todo improves to be not refreshing in pause(): to have a refresh when returning onto the overview
		return;
	}


	// @todo takes care of t to play video at the real speed
	//const float t = getTf();

	update( event );
}



void VideoCallback::setVideo( const std::string & pathFilename )
{
	vgLogDebug2("VideoCallback::setVideo( %s )", pathFilename.c_str() );

	m_video = vgd::makeShp( new vgFFmpeg::Video( pathFilename ) );

#ifdef ENABLED_VIDEO_DEBUG
	const int64 frameRate		= static_cast<int64>( m_video->getFrameRate() );
	const int64 timePerFrame	= static_cast<int>( 1000/frameRate );

	vgLogDebug2("frameRate=%i i/s", frameRate );
	vgLogDebug2("timePerFrame=%i ms", timePerFrame );
#endif

	setFrequency( m_video->getFrameRate() * 1.1f );
	updateAspectRatio();
}


void VideoCallback::setReplayWaitingTime( const int duration )
{
	m_replayWaitingTime = duration;
}


const int VideoCallback::getReplayWaitingTime() const
{
	return m_replayWaitingTime;
}


void VideoCallback::update( const vgd::Shp< vgd::event::TimerEvent > event )
{
	const bool mustScheduleRefreshForced = update();
	if ( mustScheduleRefreshForced )
	{
		event->scheduleRefreshForced();
	}
}


const bool VideoCallback::update()
{
	bool mustScheduleRefreshForced = false;

	const int64 frameRate		= static_cast<int64>( m_video->getFrameRate() );
	const int64 timePerFrame	= static_cast<int>( 1000/frameRate );

	// Buffering
	doVideoStreamBuffering( 1 );

	// Retrieves texture node
	using vgd::node::Texture2D;
	using vgd::node::Group;
	vgd::Shp< Group >		group	= vgd::dynamic_pointer_cast< Group >( getNode() );
	vgd::Shp< Texture2D >	texture	= vgd::visitor::findFirstByName< Texture2D >( group, TEX2D_NODE_NAME );
	if ( !texture )
	{
		vgAssertN( false, "No texture for video" );
		return false;
	}

	// Process the next image
	while( true )
	{
		vgd::Shp< ImageFrame > imageFrame = m_video->getImage();

		if ( !imageFrame )
		{
			if ( m_video->isOver() )
			{
				vgLogDebug2(  "update(): Video %s is over.", m_video->getPathFilename().c_str() );
				if ( getTLoopMode() == LOOP )
				{
					m_videoOver.restart();
				}
				else
				{
#ifdef ENABLED_VIDEO_DEBUG
					vgLogDebug2(  "update(): Video %s is over. Calls pause().", m_video->getPathFilename().c_str() );
#endif
					m_video->pause();
				}
				//setExecutionDuration(1); // sets execution duration to 1ms to end this callback
				break;
			}
			else
			{
#ifdef ENABLED_VIDEO_DEBUG
				vgLogDebug( "Need buffering" );
				vgLogDebug2( "beforeBuffering:getImageQueueSize()=%i", m_video->getImageQueueSize() );
#endif
				doVideoStreamBuffering( 1 );
#ifdef ENABLED_VIDEO_DEBUG
				vgLogDebug2( "afterBuffering:getImageQueueSize()=%i", m_video->getImageQueueSize() );
#endif
				continue;
			}
		}
		else
		{
			const int64 deltaAllowed = timePerFrame/2;

			const int64 imageTime	= imageFrame->getPosition();
			const int64 currentTime	= getVideo()->getPlayingElapsedTime();

			const int64 difference = currentTime - imageTime;
			if ( difference > 0 )
			{
				// image behind
				if ( difference < deltaAllowed )
				{
#ifdef ENABLED_VIDEO_DEBUG
					vgLogDebug3("image behind:show(currentTime,imageTime)=%i,%i", (int)currentTime, (int)imageTime );
#endif
					texture->setImage( imageFrame->getImage() );
					mustScheduleRefreshForced = true;
					break;
				}
				else
				{
#ifdef ENABLED_VIDEO_DEBUG
					vgLogDebug3("image behind:skip(currentTime,imageTime)=%i,%i", (int)currentTime, (int)imageTime );
#endif
					continue;
				}
			}
			else
			{
				// image ahead
				if ( -difference < deltaAllowed )
				{
#ifdef ENABLED_VIDEO_DEBUG
					vgLogDebug3("image ahead:show(currentTime,imageTime)=%i,%i", (int)currentTime, (int)imageTime );
#endif
					texture->setImage( imageFrame->getImage() );
					mustScheduleRefreshForced = true;
					break;
				}
				else
				{
#ifdef ENABLED_VIDEO_DEBUG
					vgLogDebug3("image ahead:wait(currentTime,imageTime)=%i,%i", (int)currentTime, (int)imageTime );
#endif
					SDL_Delay( -difference );
#ifdef ENABLED_VIDEO_DEBUG
					const int64 newCurrentTime	= getVideo()->getPlayingElapsedTime();
					vgLogDebug3("image ahead:showAfterWait(currentTime,imageTime)=%i,%i", (int)newCurrentTime, (int)imageTime );
#endif
					texture->setImage( imageFrame->getImage() );
					mustScheduleRefreshForced = true;
					break;
				}
			}
		}
	}

	return mustScheduleRefreshForced;
}



void VideoCallback::doVideoStreamBuffering( const int bufferInSecond )
{
	if ( !m_video ) return;

	while ( m_video->getImageQueueSize() < m_video->getFrameRate() * bufferInSecond )
	{
		// Reads/decodes a new packet from video stream
		const bool processPacketRetVal = m_video->processPacket();
		if ( !processPacketRetVal )
		{
#ifdef ENABLED_VIDEO_DEBUG
			vgLogDebug( "update:processPacket() fails. EOF ?" );
			vgLogDebug2( "update:begin:getImageQueueSize()=%i", m_video->getImageQueueSize() );
#endif
			break;
		}
	}
	//vgLogDebug2( "update:begin:getImageQueueSize()=%i", m_video->getImageQueueSize() );
}



void VideoCallback::updateAspectRatio()
{
	using vgd::node::Group;
	using vgd::node::Quad;

	vgd::Shp< Group >	group	= vgd::dynamic_pointer_cast< Group >( getNode() );

	if( group && m_video )
	{
		vgd::Shp< Quad >	quad = vgd::visitor::findFirstByName< Quad >( group, QUAD_NODE_NAME );

		if ( quad )
		{
			quad->initializeGeometry(1.f, (float) m_video->getHeight() / m_video->getWidth() );
		}
	}
	// Else, nothing to do.
}



void VideoCallback::beginExecution( const vgd::Shp< vgd::event::TimerEvent > event )
{
	// Buffering
	vgLogDebug("VideoCallback::beginExecution()");
	doVideoStreamBuffering( 1 );

	const bool mustScheduleRefreshForced = update();
	if ( mustScheduleRefreshForced )
	{
		// Schedules a refresh
		event->scheduleRefreshForced();
	}
}



void VideoCallback::endExecution( const vgd::Shp< vgd::event::TimerEvent > event )
{
	if ( m_output == TEXTURE2D )
	{
		assert( getNode() );

		using vgd::node::Group;

		vgd::Shp< Group > videoOutputGroup	= vgd::dynamic_pointer_cast< Group >( getNode() );
		vgd::Shp< Group > container			= videoOutputGroup->getParent();

		if ( container )
		{
			container->removeChild( videoOutputGroup );
		}
		// else nothing to do

		// Schedules a refresh
		event->scheduleRefreshForced();
	}
}


} // namespace vgFFmpeg

