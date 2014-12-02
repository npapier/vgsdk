// VGSDK - Copyright (C) 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/event/TimerCallback.hpp"



namespace vgeGL
{

namespace event
{



TimerCallback::TimerCallback()
:	//vgd::event::TimerCallback(),
	m_sceneManager( 0 )
{
}


TimerCallback::TimerCallback( vgeGL::engine::SceneManager * sceneManager )
:	//vgd::event::TimerCallback(),
	m_sceneManager( sceneManager )
{
}


TimerCallback::TimerCallback( vgd::Shp< vgd::node::Node > node, vgeGL::engine::SceneManager * sceneManager )
:	vgd::event::TimerCallback( node ),
	m_sceneManager( sceneManager )
{
}


vgeGL::engine::SceneManager * TimerCallback::getSceneManager()
{
	return m_sceneManager;
}


} // namespace event

} // namespace vgeGL
