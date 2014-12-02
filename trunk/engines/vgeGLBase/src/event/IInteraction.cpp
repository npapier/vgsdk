//// VGSDK - Copyright (C) 2004, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#include "vgeGL/event/IInteraction.hpp"
//
//#include "vgeGL/engine/SceneManager.hpp"
//
//
//
//namespace vgeGL
//{
//	
//namespace event
//{
//
//
//
//IInteraction::IInteraction( ::vgeGL::engine::SceneManager *sceneManager )
//:	EventProcessor( sceneManager )
//{
//}
//
//
//
//const bool IInteraction::onEvent( vgd::Shp<vgd::event::Event> event )
//{
//	// onEvent() is called only when isEnabled() returns true.
//	assert( isEnabled() );
//
//	event->accept( *this );	
//	
//	return false;
//}
//
//
//
//} // namespace event
//
//} // namespace vgeGL
//