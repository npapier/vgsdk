// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/engine/SceneManager.hpp"

#include <vgDebug/Global.hpp>
#include <vgeGL/technique/Main.hpp>
#include <vgeGL/technique/ProcessEvent.hpp>



namespace vgeGL
{

namespace engine
{



SceneManager::SceneManager( vgd::Shp< vgeGL::engine::Engine > pEngine ) :
	::vge::engine::SceneManager	(	pEngine	),
	m_GLEngine							(	pEngine	),
	m_bCallInitialize					(	false		)
{
}



void SceneManager::initialize()
{
	m_bCallInitialize = true;
}



void SceneManager::paint( const vgm::Vec2i size, const bool bUpdateBoundingBox )
{
	::vge::engine::SceneManager::paint( size, bUpdateBoundingBox );

	vgeGL::technique::Main main;
	getEngine()->resetEval();
	main.apply( getEngine().get(), getNodeCollector().getTraverseElements() );
}



void SceneManager::resize( const vgm::Vec2i )
{
}



void SceneManager::onEvent( vgd::Shp<vgd::event::Event> event )
{
	vgeGL::technique::ProcessEvent processEvent;
	
	getEngine()->resetEval();	
	processEvent.apply( getEngine().get(), getNodeCollector().getTraverseElements(), event );

	//vgDebug::get().logDebug("SceneManager::onEvent:%s", typeid(*event.get()).name() );
}



vgd::Shp< vgeGL::engine::Engine > SceneManager::getGLEngine()
{
	return ( m_GLEngine );
}



} // namespace engine

} // namespace vgeGL
