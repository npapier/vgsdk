// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/SurroundScale.hpp"

#include <vgd/node/SurroundScale.hpp>
#include <vge/handler/SurroundScale.hpp>
#include <vge/service/Painter.hpp>
#include <vge/service/ProcessEvent.hpp>
#include <vgm/Utilities.hpp>

#include "vgeGL/engine/Engine.hpp"



namespace vgeGL
{

namespace handler
{

namespace painter
{



META_HANDLER_CPP( SurroundScale );



const vge::service::List SurroundScale::getServices() const
{
	vge::service::List list;
	
	list.push_back( vgd::Shp<vge::service::Service>( new vge::service::Painter ) );
	list.push_back( vgd::Shp<vge::service::Service>( new vge::service::ProcessEvent) );

	return ( list );
}



const vge::handler::Handler::TargetVector SurroundScale::getTargets() const
{
	vge::handler::Handler::TargetVector targets;

	targets.push_back( vgd::node::SurroundScale::getClassIndexStatic() );

	return ( targets );
}



void SurroundScale::apply ( vge::engine::Engine* pEngine, vgd::node::Node *pNode )
{
	assert( dynamic_cast< vgeGL::engine::Engine* >(pEngine) != 0 );
	vgeGL::engine::Engine *pGLEngine = static_cast< vgeGL::engine::Engine* >(pEngine);

	assert( dynamic_cast< vgd::node::SurroundScale* >(pNode) != 0 );
	vgd::node::SurroundScale *pCastedNode = static_cast< vgd::node::SurroundScale* >(pNode);
	
	vge::handler::SurroundScale::apply( pEngine, pCastedNode );

	paint( pGLEngine, pCastedNode );
}



void SurroundScale::unapply ( vge::engine::Engine* , vgd::node::Node* )
{
}



/**
 * @todo What to set/unset in this method ?
 */
void SurroundScale::setToDefaults()
{
}



void SurroundScale::paint( vgeGL::engine::Engine *pGLEngine, vgd::node::SurroundScale *pNode )
{
	// GEOMETRICAL MATRIX
	// Get the transformation.
	vgm::MatrixR& 		current(	
		pGLEngine->getGeometricalMatrix().getTop() 
		);

	glMatrixMode( GL_MODELVIEW );

	// Update OpenGL.
	glLoadMatrixf( reinterpret_cast<const float*>( current.getValue() ) );
	
	// Validate node
	pNode->getDirtyFlag(pNode->getDFNode())->validate();	
}



} // namespace painter

} // namespace handler

} // namespace vgeGL
