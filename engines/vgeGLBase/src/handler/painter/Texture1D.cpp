//// VGSDK - Copyright (C) 2004, 2007, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#include "vgeGL/handler/painter/Texture1D.hpp"
//
//#include <vgd/node/Texture1D.hpp>
//#include <vge/service/Painter.hpp>
//
//#include "vgeGL/rc/TSynchronizeHelper.hpp"
//#include "vgeGL/rc/Texture1D.hpp"
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
//
//
//META_HANDLER_CPP( Texture1D );
//
//
//
//const vge::handler::Handler::TargetVector Texture1D::getTargets() const
//{
//	vge::handler::Handler::TargetVector targets;
//
//	targets.push_back( vgd::node::Texture1D::getClassIndexStatic() );
//
//	return ( targets );
//}
//
//
//
//void Texture1D::apply ( vge::engine::Engine* pEngine, vgd::node::Node *pNode )
//{
//	assert( dynamic_cast< vgeGL::engine::Engine* >(pEngine) != 0 );
//	vgeGL::engine::Engine *pGLEngine = static_cast< vgeGL::engine::Engine* >(pEngine);
//
//	assert( dynamic_cast< vgd::node::Texture1D* >(pNode) != 0 );
//	vgd::node::Texture1D *pCastedNode = static_cast< vgd::node::Texture1D* >(pNode);
//
//	vgeGL::rc::applyUsingSynchronize< vgeGL::rc::Texture1D >( pGLEngine, pCastedNode, this );
//}
//
//
//
//void Texture1D::unapply ( vge::engine::Engine*, vgd::node::Node* )
//{
//}
//
//
//
//void Texture1D::setToDefaults()
//{
//}
//
//
//
//void Texture1D::synchronize(	vgeGL::engine::Engine *pGLEngine, vgd::node::Texture1D *pNode,
//								vgeGL::rc::Texture1D *pResource )
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