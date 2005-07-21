// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/Camera.hpp"

#include <vgd/node/Camera.hpp>
#include <vge/service/Painter.hpp>
#include <vge/service/ProcessEvent.hpp>

#include "vgeGL/engine/Engine.hpp"



namespace vgeGL
{

namespace handler
{

namespace painter
{
	


META_HANDLER_CPP( Camera );



const vge::service::List Camera::getServices() const
{
	vge::service::List list;
	
	list.push_back( vgd::Shp<vge::service::Service>( new vge::service::Painter ) );
	list.push_back( vgd::Shp<vge::service::Service>( new vge::service::ProcessEvent) );

	return ( list );
}



const vge::handler::Handler::TargetVector Camera::getTargets() const
{
	vge::handler::Handler::TargetVector targets;

	targets.push_back( vgd::node::Camera::getClassIndexStatic() );

	return ( targets );
}



void Camera::apply ( vge::engine::Engine* pEngine, vgd::node::Node *pNode )
{
	assert( dynamic_cast< vgeGL::engine::Engine* >(pEngine) != 0 );
	vgeGL::engine::Engine *pGLEngine = static_cast< vgeGL::engine::Engine* >(pEngine);

	assert( dynamic_cast< vgd::node::Camera* >(pNode) != 0 );
	vgd::node::Camera *pCastedNode = static_cast< vgd::node::Camera* >(pNode);
	
	vge::handler::Camera::apply( pEngine, pCastedNode );
	
	paint( pGLEngine, pCastedNode );
}



void Camera::unapply ( vge::engine::Engine*, vgd::node::Node*)
{
}


void Camera::setToDefaults()
{
//	glMatrixMode( GL_PROJECTION );
//	glLoadIdentity();
//	
//	glDisable( GL_SCISSOR_TEST );
}



void Camera::paint( vgeGL::engine::Engine *pGLEngine, vgd::node::Camera *pNode )
{
	// PROJECTION MATRIX
	// Get the transformation.
	vgm::MatrixR& 		current(	
		pGLEngine->getProjectionMatrix().getTop() 
		);	

	glMatrixMode( GL_PROJECTION );

	// Update OpenGL.
	glLoadMatrixf( reinterpret_cast<const float*>( current.getValue() ) );



	// VIEWPORT
	bool bDefined;
	vgm::Rectangle2i viewportValue;
	
	bDefined = pNode->getViewport( viewportValue );

	if ( bDefined )
	{
		glViewport(
			viewportValue.x(), viewportValue.y(),
			viewportValue.width(), viewportValue.height()
				);
	}



	// SCISSOR
	vgm::Rectangle2i  scissorValue;
	
	bDefined = pNode->getScissor( scissorValue );

	if ( bDefined )
	{
		glEnable( GL_SCISSOR_TEST );
		
		glScissor(
			scissorValue.x(), scissorValue.y(),
			scissorValue.width(), scissorValue.height()
				);
	}
	else
	{
		glDisable( GL_SCISSOR_TEST );
	}
	
	// Validate node
	pNode->getDirtyFlag(pNode->getDFNode())->validate();
}



} // namespace painter

} // namespace handler

} // namespace vgeGL
