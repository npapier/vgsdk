// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/TextureMatrixTransform.hpp"

#include <glo/Texture.hpp>
#include <vgd/field/DirtyFlag.hpp>
#include <vgd/node/TextureMatrixTransform.hpp>
#include <vge/service/Painter.hpp>

#include "vgeGL/engine/Engine.hpp"



namespace vgeGL
{

namespace handler
{

namespace painter
{



META_HANDLER_CPP( TextureMatrixTransform );



const vge::handler::Handler::TargetVector TextureMatrixTransform::getTargets() const
{
	vge::handler::Handler::TargetVector targets;

	targets.push_back( vgd::node::TextureMatrixTransform::getClassIndexStatic() );

	return ( targets );
}



void TextureMatrixTransform::apply ( vge::engine::Engine* pEngine, vgd::node::Node *pNode )
{
	assert( dynamic_cast< vgeGL::engine::Engine* >(pEngine) != 0 );
	vgeGL::engine::Engine *pGLEngine = static_cast< vgeGL::engine::Engine* >(pEngine);

	assert( dynamic_cast< vgd::node::TextureMatrixTransform* >(pNode) != 0 );
	vgd::node::TextureMatrixTransform *pCastedNode = static_cast< vgd::node::TextureMatrixTransform* >(pNode);
	
	vge::handler::TextureMatrixTransform::apply( pEngine, pCastedNode );
	
	paint( pGLEngine, pCastedNode );
}



void TextureMatrixTransform::unapply ( vge::engine::Engine* , vgd::node::Node* )
{
}



void TextureMatrixTransform::setToDefaults()
{
	glMatrixMode( GL_TEXTURE );
	glLoadIdentity();
}



void TextureMatrixTransform::paint ( vgeGL::engine::Engine *pGLEngine, vgd::node::TextureMatrixTransform *pNode )
{
	// PROJECTION MATRIX
	// Get the transformation.
	int32	indexMultiAttribute;
	
	indexMultiAttribute = pNode->getMultiAttributeIndex();
	
	vgm::MatrixR& 		current(	
			pGLEngine->getTextureMatrix().getTop( indexMultiAttribute ) 
			);

	glo::Texture::active( GL_TEXTURE0_ARB + indexMultiAttribute );
	glMatrixMode( GL_TEXTURE );

	// Update OpenGL.
	glLoadMatrixf( reinterpret_cast<const float*>( current.getValue() ) );
	
	// Validate node
	pNode->getDirtyFlag(pNode->getDFNode())->validate();	
}



} // namespace painter

} // namespace handler

} // namespace vgeGL
