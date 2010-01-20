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
	 * @param node				node to update with video frame
	 */
	VideoCallback(	const std::string& pathFilename,
					vgd::Shp< vgd::node::Texture2D > node );

protected:
	/**
	 * @brief Updates the vgsdk node with a video frame
	 */
	void apply( const vgd::Shp< vgd::event::TimerEvent > event );

private:
	vgd::Shp< vgFFmpeg::Video > m_video;
};



} // namespace vgFFmpeg

#endif // #ifndef _VGFFMPEG_VIDEOCALLBACK_HPP
