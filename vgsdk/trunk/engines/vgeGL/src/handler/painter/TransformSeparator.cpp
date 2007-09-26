// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/TransformSeparator.hpp"

#include <glo/Texture.hpp>
#include <vgd/field/DirtyFlag.hpp>
#include <vgd/node/TransformSeparator.hpp>
#include <vge/service/Painter.hpp>
#include <vge/service/ProcessEvent.hpp>

#include "vgeGL/engine/Engine.hpp"



namespace vgeGL
{

namespace handler
{

namespace painter
{



META_HANDLER_CPP( TransformSeparator );



const vge::service::List TransformSeparator::getServices() const
{
	vge::service::List list;
	list.push_back( vgd::Shp<vge::service::Service>( new vge::service::Painter ) );
	list.push_back( vgd::Shp<vge::service::Service>( new vge::service::ProcessEvent) );

	return ( list );
}



const vge::handler::Handler::TargetVector TransformSeparator::getTargets() const
{
	vge::handler::Handler::TargetVector targets;

	targets.push_back( vgd::node::TransformSeparator::getClassIndexStatic() );

	return ( targets );
}



void TransformSeparator::apply ( vge::engine::Engine* pEngine, vgd::node::Node *pNode )
{
	//assert( dynamic_cast< vgeGL::engine::Engine* >(pEngine) != 0 );
	//vgeGL::engine::Engine *pGLEngine = static_cast< vgeGL::engine::Engine* >(pEngine);

	assert( dynamic_cast< vgd::node::TransformSeparator* >(pNode) != 0 );
	vgd::node::TransformSeparator *pCastedNode = static_cast< vgd::node::TransformSeparator* >(pNode);

	// Push.
	vge::handler::TransformSeparator::apply( pEngine, pCastedNode );
	
	// Validate node
	pNode->getDirtyFlag(pNode->getDFNode())->validate();	
}



void TransformSeparator::unapply ( vge::engine::Engine* pEngine, vgd::node::Node* pNode )
{
	assert( dynamic_cast< vgeGL::engine::Engine* >(pEngine) != 0 );
	vgeGL::engine::Engine *pGLEngine = static_cast< vgeGL::engine::Engine* >(pEngine);

	assert( dynamic_cast< vgd::node::TransformSeparator* >(pNode) != 0 );
	vgd::node::TransformSeparator *pCastedNode = static_cast< vgd::node::TransformSeparator* >(pNode);

	// Software pop()
	vge::handler::TransformSeparator::unapply( pEngine, pCastedNode );

	// Restore matrix in OpenGL.
	const int8 mask	( pCastedNode->getMask() );
	
	if ( mask & vgd::node::TransformSeparator::TEXTURE_MATRIX_BIT )
	{
		for(	uint32	i		= 0,
							iMax	= pEngine->getMaxTexUnits();
				i < iMax;
				++i )
		{
			const vgm::MatrixR& matrix	( 
				pEngine->getTextureMatrix().getTop( i ) 
					);
		
			// Update OpenGL
			pGLEngine->activeTexture( i );
			glMatrixMode( GL_TEXTURE );
			glLoadMatrixf( reinterpret_cast<const float*>( matrix.getValue() ) );
		}
	}
	
	if ( mask & vgd::node::TransformSeparator::PROJECTION_MATRIX_BIT )
	{
		const vgm::MatrixR& matrix ( 
			pEngine->getProjectionMatrix().getTop()
			 );
		
		// Update OpenGL
		glMatrixMode( GL_PROJECTION );
		glLoadMatrixf( reinterpret_cast<const float*>( matrix.getValue() ) );
	}

	if ( mask & vgd::node::TransformSeparator::GEOMETRICAL_MATRIX_BIT )
	{
		const vgm::MatrixR& matrix ( 
			pEngine->getGeometricalMatrix().getTop()
			 );

		// Update OpenGL
		glMatrixMode( GL_MODELVIEW );
		glLoadMatrixf( reinterpret_cast<const float*>( matrix.getValue() ) );
	}
}



/**
 * @todo What to set/unset in this method ?
 */
void TransformSeparator::setToDefaults()
{
}



} // namespace painter

} // namespace handler

} // namespace vgeGL
