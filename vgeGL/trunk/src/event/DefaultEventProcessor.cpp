// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/event/DefaultEventProcessor.hpp"


#include "vgeGL/engine/SceneManager.hpp"
#include "vgeGL/technique/ProcessEvent.hpp"



namespace vgeGL
{
	
namespace event
{

DefaultEventProcessor::DefaultEventProcessor( ::vgeGL::engine::SceneManager *sceneManager ) :
	EventProcessor( sceneManager )
{
}



const bool DefaultEventProcessor::onEvent( vgd::Shp<vgd::event::Event> event )
{
	vgeGL::technique::ProcessEvent processEvent;
	
	m_sceneManager->getEngine()->resetEval();	
	processEvent.apply(
		m_sceneManager->getEngine().get(),
		m_sceneManager->getNodeCollector().getTraverseElements(),
		event );

	//vgDebug::get().logDebug("SceneManager::onEvent:%s", typeid(*event.get()).name() );
	
	return ( false );
}


} // namespace event

} // namespace vgeGL
	