//// VGSDK - Copyright (C) 2004, 2007, 2008, 2010, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#include "vgeGLBase/technique/ProcessEvent.hpp"
//
//#include <vge/pass/ForEach.hpp>
//#include <vge/service/ProcessEvent.hpp>
//
//#include "vgeGLBase/engine/Engine.hpp"
//
//
//
//namespace vgeGLBase
//{
//
//namespace technique
//{
//
//
//
//void ProcessEvent::setEvent( vgd::Shp< vgd::event::Event > event )
//{
//	m_event = event;
//}
//
//
//
//vgd::Shp< vgd::event::Event > ProcessEvent::getEvent() const
//{
//	return m_event;
//}
//
//
//
//void ProcessEvent::apply( vgeGLBase::engine::Engine * engine, vge::visitor::TraverseElementVector* traverseElements )
//{
//	vgd::Shp< vge::service::Service > processEvent = vge::service::ProcessEvent::create();
//
//	prepareEval( engine, traverseElements );
//
//	// Initialize engine with technique parameters
//	if ( !engine->isField( getFProcessEvent() ) )
//	{
//		engine->addField( new FProcessEventType( getFProcessEvent() ) );
//	}
//
//	using vgd::field::EditorRW;
//	EditorRW< FProcessEventType > eventInEngine = engine->getFieldRW< FProcessEventType >( getFProcessEvent() );
//
//	eventInEngine->setValue( getEvent() );
//	eventInEngine.release();
//
//	// The pass
//	setPassDescription("ProcessEvent:apply()");
//
//	evaluatePass( ::vgd::makeShp( new vge::pass::ForEach ), processEvent );
//
//	//
//	finishEval();
//}
//
//
//
//const std::string ProcessEvent::getFProcessEvent()
//{
//	return "f_processEvent";
//}
//
//
//
//} // namespace technique
//
//} // namespace vgeGLBase
//