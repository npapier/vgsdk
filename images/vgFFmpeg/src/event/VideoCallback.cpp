// VGSDK - Copyright (C) 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgFFmpeg/event/VideoCallback.hpp"

#include <vgd/basic/Image.hpp>



namespace vgFFmpeg
{



VideoCallback::VideoCallback(	const std::string& pathFilename,
								vgd::Shp< vgd::node::Texture2D > node )
:	TimerCallback( node ),
	m_video( new vgFFmpeg::Video( pathFilename ) )
{
	// @todo
	setExecutionDuration( 1000 * 60 * 5 ); // 5mn
	//setFrequency( 20 );
	setTDuration( 1000 * 60 * 5 );

	setTDirection( FORWARD );
	setTLoopMode( ONCE );
	setTLoopCount( 0 );
}


void VideoCallback::apply( const vgd::Shp< vgd::event::TimerEvent > event )
{
	// @todo takes care of t to play video at the real speed
	const float t = getTf();

	const bool retVal = m_video->next();
	if ( retVal )
	{
		using vgd::basic::Image;

		vgd::Shp< Image > image( new Image( m_video->getCurrent() ) );
		//vgd::basic::ImageUtilities::setAlpha( image.get(), 1.f );

		// Updates node
		vgd::Shp< vgd::node::Texture2D > node;
		node = vgd::dynamic_pointer_cast< vgd::node::Texture2D >( getNode() );
		node->setImage( image );
	}
}



} // namespace vgFFmpeg
