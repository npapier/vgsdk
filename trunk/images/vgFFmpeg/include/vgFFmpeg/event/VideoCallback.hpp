// VGSDK - Copyright (C) 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGFFMPEG_VIDEOCALLBACK_HPP
#define _VGFFMPEG_VIDEOCALLBACK_HPP

#include <vgd/event/TimerCallback.hpp>
#include <vgd/node/Texture2D.hpp>
#include "vgFFmpeg/Video.hpp"



namespace vgFFmpeg
{



/**
 * @brief Callback updating texture node from a video stream.
 *
 * @todo Updates LayerPlan...
 */
struct VGFFMPEG_API VideoCallback : public vgd::event::TimerCallback
{
	/**
	 * @brief Constructs the video callback
	 *
	 * @param pathFilename		name of video file to play
	 */
	VideoCallback( const std::string& pathFilename );



	/**
	 * @name Accessors to playback output
	 */
	//@{

	/**
	 * @brief Sets playback output to texture 2d.
	 *
	 * @return a group node containing a texture node that would be updated by this callback and a quad node filled by the texture.
	 */
	vgd::Shp< vgd::node::Group > setVideoPlaybackInTexture2D();

	//@}


	vgd::Shp< vgFFmpeg::Video > getVideo()				{ return m_video; }
	void setVideo( const std::string& pathFilename )	{ m_video = vgd::makeShp( new vgFFmpeg::Video( pathFilename ) ); }

protected:
	/**
	 * @brief Updates the vgsdk node with a video frame
	 */
	void apply( const vgd::Shp< vgd::event::TimerEvent > event );


	void beginExecution();
	void endExecution();


private:

	void update( const vgd::Shp< vgd::event::TimerEvent > event );

	vgd::Shp< vgFFmpeg::Video > m_video;		///< The video stream

	enum PlayBackOutput
	{
		NO_OUTPUT,
		TEXTURE2D
	};
	PlayBackOutput m_output;
};



} // namespace vgFFmpeg

#endif // #ifndef _VGFFMPEG_VIDEOCALLBACK_HPP
