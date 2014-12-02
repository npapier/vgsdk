//// VGSDK - Copyright (C) 2004, 2007, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#include "vgeGLBase/handler/painter/Texture1D.hpp"
//
//#include <vgd/node/Texture1D.hpp>
//#include <vge/service/Painter.hpp>
//
//#include "vgeGLBase/rc/TSynchronizeHelper.hpp"
//#include "vgeGLBase/rc/Texture1D.hpp"
//
//
//
//namespace vgeGLBase
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
//	assert( dynamic_cast< vgeGLBase::engine::Engine* >(pEngine) != 0 );
//	vgeGLBase::engine::Engine *pGLEngine = static_cast< vgeGLBase::engine::Engine* >(pEngine);
//
//	assert( dynamic_cast< vgd::node::Texture1D* >(pNode) != 0 );
//	vgd::node::Texture1D *pCastedNode = static_cast< vgd::node::Texture1D* >(pNode);
//
//	vgeGLBase::rc::applyUsingSynchronize< vgeGLBase::rc::Texture1D >( pGLEngine, pCastedNode, this );
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
//void Texture1D::synchronize(	vgeGLBase::engine::Engine *pGLEngine, vgd::node::Texture1D *pNode,
//								vgeGLBase::rc::Texture1D *pResource )
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
//} // namespace vgeGLBase
//