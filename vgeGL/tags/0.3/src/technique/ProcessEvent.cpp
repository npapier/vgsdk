// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/technique/ProcessEvent.hpp"

#include <vgd/node/Dragger.hpp>
#include <vge/engine/Engine.hpp>
#include <vge/service/ProcessEvent.hpp>



namespace vgeGL
{

namespace technique
{


const std::string ProcessEvent::getFProcessEvent()
{
	return ( "f_processEvent" );
}



void ProcessEvent::apply(	vge::engine::Engine *pEngine, vge::visitor::TraverseElementVector* pTraverseElements,
									vgd::Shp<vgd::event::Event> event )
{
	vgd::Shp< vge::service::Service > processEvent = vge::service::ProcessEvent::create();

	prepareEval();
	//pEngine->resetEval();

	// Initialize engine with technique parameters.
	if ( !pEngine->isField( getFProcessEvent() ) )
	{
		pEngine->addField( new FProcessEventType( getFProcessEvent() ) );
	}
	
	vgd::field::EditorRW< FProcessEventType > eventInEngine =
			pEngine->getFieldRW< FProcessEventType >( getFProcessEvent() );
			
	eventInEngine->setValue( event );
	eventInEngine.release();
	
	// First pass
	beginPass();
	glPushAttrib( GL_ALL_ATTRIB_BITS );

	vge::visitor::TraverseElementVector::const_iterator i, iEnd;
	for(	i = pTraverseElements->begin(), iEnd = pTraverseElements->end();
			i != iEnd;
			++i )
	{
		pEngine->evaluate( processEvent, i->first, i->second );
	}

	glPopAttrib();
	endPass();
	
	//
	finishEval();
}



} // namespace technique

} // namespace vgeGL
