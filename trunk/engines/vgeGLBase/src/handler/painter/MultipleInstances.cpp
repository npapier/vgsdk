//// VGSDK - Copyright (C) 2010, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#include "vgeGLBase/handler/painter/MultipleInstances.hpp"
//
//#include <vgd/node/MultipleInstances.hpp>
//
//#include "vgeGLBase/rc/TDisplayListHelper.hpp"
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
//META_HANDLER_CPP( MultipleInstances );
//
//
//
//const vge::handler::Handler::TargetVector MultipleInstances::getTargets() const
//{
//	TargetVector targets;
//
//	targets.reserve( 1 );
//	targets.push_back( vgd::node::MultipleInstances::getClassIndexStatic() );
//
//	return targets;
//}
//
//
//
//void MultipleInstances::apply( vge::engine::Engine * engine, vgd::node::Node * node )
//{
//	assert( dynamic_cast< vgeGLBase::engine::Engine* >(engine) != 0 );
//	vgeGLBase::engine::Engine *pGLEngine = static_cast< vgeGLBase::engine::Engine* >(engine);
//
//	assert( dynamic_cast< vgd::node::MultipleInstances* >(node) != 0 );
//	vgd::node::MultipleInstances *pCastedNode = static_cast< vgd::node::MultipleInstances* >(node);
//
//	// Updates GLState
//	pGLEngine->getGLState().setMultipleInstances( pCastedNode );
//
//	//
//	//vgeGLBase::rc::applyUsingDisplayList< vgd::node::MultipleInstances, MultipleInstances >( engine, node, this );
//	paint( pGLEngine, pCastedNode );
//}
//
//
//
//void MultipleInstances::unapply ( vge::engine::Engine*, vgd::node::Node* )
//{
//}
//
//
//
//void MultipleInstances::setToDefaults()
//{
//}
//
//
//
//void MultipleInstances::paint( vgeGLBase::engine::Engine * engine, vgd::node::MultipleInstances * multipleInstances )
//{
//	// SHAPE
//	const vgd::Shp< vgd::node::Shape > shape = vgd::dynamic_pointer_cast< vgd::node::Shape >( multipleInstances->getShape() );
//
//	engine->paint( shape );
//
//	// Validates node df
//	multipleInstances->getDirtyFlag(multipleInstances->getDFNode())->validate();
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