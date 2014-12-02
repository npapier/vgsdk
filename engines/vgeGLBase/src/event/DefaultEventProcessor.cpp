//// VGSDK - Copyright (C) 2004, 2006, 2008, 2009, 2014, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#include "vgeGLBase/event/DefaultEventProcessor.hpp"
//
//#include "vgeGLBase/engine/Engine.hpp"
//#include "vgeGLBase/engine/SceneManager.hpp"
//#include "vgeGLBase/technique/ProcessEvent.hpp"
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
//DefaultEventProcessor::DefaultEventProcessor( ::vgeGLBase::engine::SceneManager *sceneManager ) 
//:	EventProcessor( sceneManager )
//{}
//
//
//
//const bool DefaultEventProcessor::onEvent( vgd::Shp<vgd::event::Event> event )
//{
//	// onEvent() is called only when isEnabled() returns true.
//	vgAssert( isEnabled() );
//
//	// Do a picking if the incoming event is a mouse [or keyboard ] button event. Picking computation is used by Dragger
//
//	//using vgd::event::KeyboardButtonEvent; @todo add location2 in KeyboardButtonEvent to be able to do a picking
//	//const KeyboardButtonEvent	* keyboardButtonEvent = dynamic_cast<KeyboardButtonEvent*>(event.get());
//
//	using vgd::event::MouseButtonEvent;
//	const MouseButtonEvent		* mouseButtonEvent    = dynamic_cast<MouseButtonEvent*>(event.get());
//
//	const bool doAPicking = /*(keyboardButtonEvent != 0) ||*/ (mouseButtonEvent != 0);
//	if ( doAPicking )
//	{
//		const vgm::Vec2i location( mouseButtonEvent->getLocation() );
//		const vgeGLBase::basic::Hit * hit = getSceneManager()->castRayForHit( location[0], location[1] );
//
//		// Initialize engine with picking informations.
//		vgd::Shp< vgeGLBase::engine::Engine > glEngine = getSceneManager()->getGLEngine();
//		if ( !glEngine->isField( "DefaultEventProcessor.hit" ) )	glEngine->addField( new FHitType( getFHit() ) );
//
//		vgd::field::EditorRW< FHitType > hitInEngine = glEngine->getFieldRW< FHitType >( getFHit() );
//		if ( hit )
//		{
//			hitInEngine->setValue( vgd::makeShp(new vgeGLBase::basic::Hit(*hit)) );
//		}
//		else
//		{
//			hitInEngine->setValue( vgd::makeShp(new vgeGLBase::basic::Hit()) );
//		}
//	}
//	else
//	{
//		/// @todo OPTME : Always update node collector ?
//		getSceneManager()->updateNodeCollector();
//	}
//
//	// Propagate the incoming event into scene graph for processing
//	vgeGLBase::technique::ProcessEvent processEvent;
//	processEvent.setEvent( event );
//
//	processEvent.setParameters(
//		getSceneManager()->getGLEngine().get(),
//		getSceneManager()->getNodeCollector().getTraverseElements() );
//
//	processEvent.apply(
//		getSceneManager()->getGLEngine().get(),
//		getSceneManager()->getNodeCollector().getTraverseElements() );
//
//	//vgLogDebug("SceneManager::onEvent:%s", typeid(*event.get()).name() );
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