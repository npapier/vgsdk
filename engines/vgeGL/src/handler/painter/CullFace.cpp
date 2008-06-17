// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/CullFace.hpp"

#include <vgd/node/CullFace.hpp>
#include <vgDebug/convenience.hpp>
#include "vgeGL/rc/TDisplayListHelper.hpp"



namespace vgeGL
{

namespace handler
{

namespace painter
{



META_HANDLER_CPP( CullFace );



const vge::handler::Handler::TargetVector CullFace::getTargets() const
{
	TargetVector targets;

	targets.reserve( 1 );
	targets.push_back( vgd::node::CullFace::getClassIndexStatic() );

	return targets;
}



void CullFace::apply( vge::engine::Engine * engine, vgd::node::Node * node )
{
//	assert( dynamic_cast< vgeGL::engine::Engine* >(engine) != 0 );
//	vgeGL::engine::Engine *pGLEngine = static_cast< vgeGL::engine::Engine* >(engine);

//	assert( dynamic_cast< vgd::node::CullFace* >(node) != 0 );
//	vgd::node::CullFace *pCastedNode = static_cast< vgd::node::CullFace* >(node);

	vgeGL::rc::applyUsingDisplayList< vgd::node::CullFace, CullFace >( engine, node, this );
}



void CullFace::unapply ( vge::engine::Engine*, vgd::node::Node* )
{
}



void CullFace::setToDefaults()
{
	glDisable( GL_CULL_FACE );
}



void CullFace::paint( vgeGL::engine::Engine *, vgd::node::CullFace * node )
{
	// MODE
	vgd::node::CullFace::ModeValueType value = node->getMode();

	if ( value == vgd::node::CullFace::DISABLED )
	{
		glDisable( GL_CULL_FACE );
	}
	else
	{
		glEnable( GL_CULL_FACE );

		if ( value == vgd::node::CullFace::BACK )
		{
			glCullFace( GL_BACK );
		}
		else if ( value == vgd::node::CullFace::FRONT )
		{
			glCullFace( GL_FRONT );
		}
		else if ( value == vgd::node::CullFace::FRONT_AND_BACK )
		{
			glCullFace( GL_FRONT_AND_BACK );
		}
		else
		{
			vgLogDebug( "Unexpected value for CullFace.mode" );
		}
	}

	// Validates node df
	node->getDirtyFlag(node->getDFNode())->validate();
}



} // namespace painter

} // namespace handler

} // namespace vgeGL
