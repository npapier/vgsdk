// VGSDK - Copyright (C) 2009, 2010, Nicolas Papier.
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



namespace vgFFmpeg
{


static const std::string	GROUP_NODE_NAME("VideoPlayback");
static const std::string	TEX2D_NODE_NAME("VideoPlayback.frame");
static const std::string	QUAD_NODE_NAME("VideoPlayback.shape");




VideoCallback::VideoCallback( const std::string& pathFilename )
:	m_video( new vgFFmpeg::Video( pathFilename ) ),
	m_output( NO_OUTPUT )
{
	setExecutionDuration( 0 );
	// @todo
	//setFrequency( 20 );
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

	// @todo takes care of t to play video at the real speed
	//const float t = getTf();

	update( event );
}



void VideoCallback::setVideo( const std::string & pathFilename )
{
	m_video = vgd::makeShp( new vgFFmpeg::Video( pathFilename ) );
	updateAspectRatio();
}



void VideoCallback::update( const vgd::Shp< vgd::event::TimerEvent > event )
{
	// Decodes the next frame	
	const bool retVal = m_video->next();

	if ( retVal )
	{
		// Retrieves the frame image
		using vgd::basic::Image;
		vgd::Shp< Image > image( new Image( m_video->getCurrent() ) );
		//vgd::basic::ImageUtilities::setAlpha( image.get(), 1.f );

		// Updates texture2D
		using vgd::node::Texture2D;
		using vgd::node::Group;

		vgd::Shp< Group >		group	= vgd::dynamic_pointer_cast< Group >( getNode() );
		vgd::Shp< Texture2D >	texture	= vgd::visitor::findFirstByName< Texture2D >( group, TEX2D_NODE_NAME );

		if ( texture )
		{
			texture->setImage( image );
		}

		event->scheduleRefreshForced();
	}
}



void VideoCallback::updateAspectRatio()
{
	using vgd::node::Group;
	using vgd::node::Quad;

	vgd::Shp< Group >	group	= vgd::dynamic_pointer_cast< Group >( getNode() );

	if( group && m_video )
	{
		vgd::Shp< Quad >	quad = vgd::visitor::findFirstByName< Quad >( group, QUAD_NODE_NAME );
		
		quad->initializeGeometry(1.f, (float) m_video->getHeight() / m_video->getWidth() );
	}
	// Else, nothing to do.
}



void VideoCallback::beginExecution()
{
	//update( event ); // @todo 
}



void VideoCallback::endExecution()
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
	}
}



} // namespace vgFFmpeg
