//// VGSDK - Copyright (C) 2004, 2007, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#include "vgeGL/handler/painter/Texture2D.hpp"
//
//#include <vgd/node/Texture2D.hpp>
//#include <vge/service/Painter.hpp>
//
//#include "vgeGL/rc/TSynchronizeHelper.hpp"
//#include "vgeGL/rc/Texture2D.hpp"
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
//
//
//META_HANDLER_CPP( Texture2D );
//
//
//
//const vge::handler::Handler::TargetVector Texture2D::getTargets() const
//{
//	vge::handler::Handler::TargetVector targets;
//
//	targets.push_back( vgd::node::Texture2D::getClassIndexStatic() );
//
//	return ( targets );
//}
//
//
//
//void Texture2D::apply ( vge::engine::Engine* pEngine, vgd::node::Node *pNode )
//{
//	assert( dynamic_cast< vgeGL::engine::Engine* >(pEngine) != 0 );
//	vgeGL::engine::Engine *pGLEngine = static_cast< vgeGL::engine::Engine* >(pEngine);
//
//	assert( dynamic_cast< vgd::node::Texture2D* >(pNode) != 0 );
//	vgd::node::Texture2D *pCastedNode = static_cast< vgd::node::Texture2D* >(pNode);
//
//	vgeGL::rc::applyUsingSynchronize< vgeGL::rc::Texture2D >( pGLEngine, pCastedNode, this );
//}
//
//
//
//void Texture2D::unapply ( vge::engine::Engine* , vgd::node::Node* )
//{
//}
//
//
//
//void Texture2D::setToDefaults()
//{
//}
//
//
//
//void Texture2D::synchronize(	vgeGL::engine::Engine*	pGLEngine, vgd::node::Texture2D* pNode,
//								vgeGL::rc::Texture2D*	pResource )
//{
//	Texture::synchronize( pGLEngine, pNode, pResource );
//}
//
//
//
//} // namespace painter
//
//} // namespace handler
//
//} // namespace vgeGL
//