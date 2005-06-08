// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/Separator.hpp"

#include <vgd/node/Separator.hpp>
#include <vge/service/Painter.hpp>
#include <vge/service/ProcessEvent.hpp>

#include "vgeGL/engine/Engine.hpp"



namespace vgeGL
{

namespace handler
{

namespace painter
{



META_HANDLER_CPP( Separator );



const vge::service::List Separator::getServices() const
{
	vge::service::List list;
	
	list.push_back( vgd::Shp<vge::service::Service>( new vge::service::Painter ) );
	list.push_back( vgd::Shp<vge::service::Service>( new vge::service::ProcessEvent) );

	return ( list );
}



const vge::handler::Handler::TargetVector Separator::getTargets() const
{
	vge::handler::Handler::TargetVector targets;

	targets.push_back( vgd::node::Separator::getClassIndexStatic() );

	return ( targets );
}



/**
 * @todo Check overflow in stack.
 */
void Separator::apply ( vge::engine::Engine* pEngine, vgd::node::Node *pNode )
{
	assert( dynamic_cast< vgd::node::Separator* >(pNode) != 0 );
	vgd::node::Separator *pCastedNode = static_cast< vgd::node::Separator* >(pNode);

	// TransformSeparator::apply( pGLEngine, pCastedNode ); FIXME REMOVEME

	// Push OpenGL part.
	glPushAttrib( GL_ALL_ATTRIB_BITS );
	
	//
	// vge::handler::TransformSeparator::apply( pEngine, pCastedNode );  FIXME REMOVEME
	vge::handler::Separator::apply( pEngine, pCastedNode );
}



void Separator::unapply ( vge::engine::Engine* pEngine, vgd::node::Node* pNode )
{
	assert( dynamic_cast< vgd::node::Separator* >(pNode) != 0 );
	vgd::node::Separator *pCastedNode = static_cast< vgd::node::Separator* >(pNode);

	// TransformSeparator::unapply( pGLEngine, pNode );  FIXME REMOVEME

	// Pop OpenGL part.
	glPopAttrib();

	//
	// vge::handler::TransformSeparator::unapply( pEngine, pCastedNode );  FIXME REMOVEME
	vge::handler::Separator::unapply( pEngine, pCastedNode );
}



/**
 * @todo What to set/unset in this method ?
 */
void Separator::setToDefaults()
{
}



} // namespace painter

} // namespace handler

} // namespace vgeGL
