// VGSDK - Copyright (C) 2004, 2006, 2008, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/event/DefaultEventProcessor.hpp"

#include "vgeGL/engine/Engine.hpp"
#include "vgeGL/engine/SceneManager.hpp"
#include "vgeGL/technique/ProcessEvent.hpp"



namespace vgeGL
{

namespace event
{



DefaultEventProcessor::DefaultEventProcessor( ::vgeGL::engine::SceneManager *sceneManager ) 
:	EventProcessor( sceneManager )
{}



const bool DefaultEventProcessor::onEvent( vgd::Shp<vgd::event::Event> event )
{
	// onEvent() is called only when isEnabled() returns true.
	assert( isEnabled() );

	/// @todo OPTME : Always update node collector ?
	getSceneManager()->updateNodeCollector();

	// Propagate the incoming event into scene graph for processing
	vgeGL::technique::ProcessEvent processEvent;
	processEvent.setEvent( event );

	processEvent.setParameters(
		getSceneManager()->getGLEngine().get(),
		getSceneManager()->getNodeCollector().getTraverseElements() );

	processEvent.apply(
		getSceneManager()->getGLEngine().get(),
		getSceneManager()->getNodeCollector().getTraverseElements() );

	//vgLogDebug("SceneManager::onEvent:%s", typeid(*event.get()).name() );

	return false;
}



} // namespace event

} // namespace vgeGL
