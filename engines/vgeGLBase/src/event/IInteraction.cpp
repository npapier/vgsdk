//// VGSDK - Copyright (C) 2004, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#include "vgeGLBase/event/IInteraction.hpp"
//
//#include "vgeGLBase/engine/SceneManager.hpp"
//
//
//
//namespace vgeGLBase
//{
//	
//namespace event
//{
//
//
//
//IInteraction::IInteraction( ::vgeGLBase::engine::SceneManager *sceneManager )
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
//} // namespace vgeGLBase
//