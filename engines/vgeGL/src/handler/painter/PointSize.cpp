// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/PointStyle.hpp"

#include <vgd/node/PointStyle.hpp>
#include <vgDebug/convenience.hpp>
#include "vgeGL/rc/TDisplayListHelper.hpp"



namespace vgeGL
{

namespace handler
{

namespace painter
{



META_HANDLER_CPP( PointStyle );



const vge::handler::Handler::TargetVector PointStyle::getTargets() const
{
	TargetVector targets;

	targets.reserve( 1 );
	targets.push_back( vgd::node::PointStyle::getClassIndexStatic() );

	return targets;
}



void PointStyle::apply( vge::engine::Engine * engine, vgd::node::Node * node )
{
//	assert( dynamic_cast< vgeGL::engine::Engine* >(engine) != 0 );
//	vgeGL::engine::Engine *pGLEngine = static_cast< vgeGL::engine::Engine* >(engine);

//	assert( dynamic_cast< vgd::node::PointStyle* >(node) != 0 );
//	vgd::node::PointStyle *pCastedNode = static_cast< vgd::node::PointStyle* >(node);

	vgeGL::rc::applyUsingDisplayList< vgd::node::PointStyle, PointStyle >( engine, node, this );
}



void PointStyle::unapply ( vge::engine::Engine*, vgd::node::Node* )
{
}



void PointStyle::setToDefaults()
{
	glEnable( GL_POINT_SMOOTH );
	glPointSize( 1.f );
}



void PointStyle::paint( vgeGL::engine::Engine *, vgd::node::PointStyle * node )
{
	// SIZE
	if ( node->hasSize() )
	{
		vgd::node::PointStyle::SizeValueType size;
		node->getSize( size );

		glPointSize( size );
	}

	// Validates node df
	node->getDirtyFlag(node->getDFNode())->validate();
}



} // namespace painter

} // namespace handler

} // namespace vgeGL
