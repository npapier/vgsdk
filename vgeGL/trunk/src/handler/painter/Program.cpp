//// VGSDK - Copyright (C) 2004, IRCAD.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#include "vgeGL/handler/painter/Program.hpp"
//
//#include <vgd/node/Program.hpp>
//#include <vge/service/Painter.hpp>
//#include "vgeGL/rc/GLSLShader.hpp"
//#include "vgeGL/rc/TSyncAndBindHelper.hpp"
//
//
//
//namespace vgeGL
//{
//
//namespace handler
//{
//
//namespace painter
//{
//
//META_HANDLER_CPP( Program );
//
//
//
//const vge::handler::Handler::TargetVector Program::getTargets() const
//{
//	TargetVector targets;
//	
//	targets.reserve( 1 );
//	targets.push_back( vgd::node::Program::getClassIndexStatic() );
//
//	return ( targets );
//}
//
//
//
//void Program::apply ( vge::engine::Engine* pEngine, vgd::node::Node *pNode )
//{
//	assert( dynamic_cast< vgeGL::engine::Engine* >(pEngine) != 0 );
//	vgeGL::engine::Engine *pGLEngine = static_cast< vgeGL::engine::Engine* >(pEngine);
//
//	assert( dynamic_cast< vgd::node::Program* >(pNode) != 0 );
//	vgd::node::Program *pCastedNode = static_cast< vgd::node::Program* >(pNode);
//
//	applyUsingSyncAndBind< vgd::node::Program, vgeGL::handler::painter::Program, vgeGL::rc::GLSLShader >( 
//			pGLEngine, pCastedNode, this 
//			);
//}
//
//
//
//void Program::unapply ( vge::engine::Engine* engine, vgd::node::Node* pNode )
//{
//}
//
//
//
//void Program::setToDefaults()
//{
//}
//
//
//
//void Program::synchronize( vgeGL::engine::Engine* pGLEngine, vgd::node::Program* pNode, vgeGL::rc::GLSLShader* pGLResource )
//{
//	if ( pGLResource->isEmpty() )
//	{
//	}
//	else
//	{
//	}
//}
//
//
//
//void Program::bind( vgeGL::engine::Engine* pGLEngine, vgd::node::Program* pNode, vgeGL::rc::GLSLShader* pGLResource )
//{
//}
//
//
//} // namespace painter
//
//} // namespace handler
//
//} // namespace vgeGL
