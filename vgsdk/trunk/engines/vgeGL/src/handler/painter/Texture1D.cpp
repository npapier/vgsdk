// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/Texture1D.hpp"

#include <vgd/basic/Image.hpp>
#include <vgd/node/Texture1D.hpp>
#include <vge/service/Painter.hpp>

#include "vgeGL/rc/TSynchronizeHelper.hpp"
#include "vgeGL/rc/Texture1D.hpp"


namespace vgeGL
{

namespace handler
{

namespace painter
{



META_HANDLER_CPP( Texture1D );



const vge::handler::Handler::TargetVector Texture1D::getTargets() const
{
	vge::handler::Handler::TargetVector targets;

	targets.push_back( vgd::node::Texture1D::getClassIndexStatic() );

	return ( targets );
}



void Texture1D::apply ( vge::engine::Engine* pEngine, vgd::node::Node *pNode )
{
	assert( dynamic_cast< vgeGL::engine::Engine* >(pEngine) != 0 );
	vgeGL::engine::Engine *pGLEngine = static_cast< vgeGL::engine::Engine* >(pEngine);

	assert( dynamic_cast< vgd::node::Texture1D* >(pNode) != 0 );
	vgd::node::Texture1D *pCastedNode = static_cast< vgd::node::Texture1D* >(pNode);

	vgeGL::rc::applyUsingSynchronize< vgd::node::Texture1D, vgeGL::handler::painter::Texture1D, vgeGL::rc::Texture1D >(
		pGLEngine, pCastedNode, this );
}



void Texture1D::unapply ( vge::engine::Engine*, vgd::node::Node* )
{
}



void Texture1D::setToDefaults()
{
}



void Texture1D::synchronize(	vgeGL::engine::Engine *pGLEngine, vgd::node::Texture1D *pNode,
								vgeGL::rc::Texture1D *pResource )
{
	// Switch to the specified tex unit and creates rc/tex
	const bool bImageAndTextureSynchronized = preSynchronize( pGLEngine, pNode, pResource );
	
	if ( !bImageAndTextureSynchronized )
	{
		// Updates texture image
		texSubImage( pGLEngine, pNode, pResource );
	}
	
	// Updates texture parameters
	synchronizeParameters( pGLEngine, pNode, pResource );
	
	assert( pNode->getDirtyFlag(pNode->getDFIImages())->isValid() );
	assert( pNode->getDirtyFlag(pNode->getDFParameters())->isValid() );
	assert( pNode->getDirtyFlag(pNode->getDFNode())->isValid() );
}



void Texture1D::texSubImage(	vgeGL::engine::Engine *pGLEngine, vgd::node::Texture1D *pNode,
								vgeGL::rc::Texture1D *pResource )
{
	using vgd::node::Texture;
	using vgd::node::Texture1D;
	
	// Rescale image if necessary (boolean value already set if image is too big).
	// Check others cases, that depends to non power of two texture size and wrapping values.
//	if ( !m_bResize )
//	{
//		// check only if not already set.
//		Texture::WrapValueType wrapSValue;
//		
//		bool isDefined = pGLEngine->getStateStackTop< Texture1D, Texture1D::WrapParameterType, Texture1D::WrapValueType >(
//																	Texture1D::getFWrap(),
//																	Texture1D::WRAP_S,
//																	wrapSValue,
//																	pNode->getMultiAttributeIndex() );
//		assert( isDefined );
//							
//		if ( wrapSValue == Texture::ONCE )
//		{
//			// never resize if wrap*=ONCE.
//			
//			// apply a scale to texCoord.
//		
//			// compute scale factors.
//			pResource->setScaleFactors(
//							static_cast<float>(m_imageSize[0])/static_cast<float>(m_texSize[0]),
//							1.f,
//							1.f );
//		}
//		else
//		{
//			// possible resize if needed (NPOT)
//			if ( m_texSize[0] != m_imageSize[0] )
//			{
//				m_bResize = true;
//			}
//		}
//	}

	// Update texture (with rescale or not).
	assert( !m_bResize && "Resize texture1D is not yet implemented" );
	
//	if ( m_bResize )
//	{
//		// RESCALE IMAGE
//		vgDebug::get().logDebug("Texture1D: Performance warning : Image (%i, %i) used as texture is resized (%i,%i)",
//			pIImage->width(), pIImage->height(),
//			texSize[0], texSize[1] );
//
//		vgd::basic::Image newImage(	pIImage->components(), texSize[0], texSize[1], 1, pIImage->format(), pIImage->type() );
//
//		const void*	pixels	= pIImage->pixels();
//		void*		newPixels	= newImage.editPixels();
//	
//		int retValScale;
//		retValScale = gluScaleImage(
//			format,					// src
//			imageSize[0], imageSize[1],
//			type,
//			pixels,
//			
//			texSize[0], texSize[1],// dst
//			type,
//			newPixels
//			);
//			
//		newImage.editPixelsDone();
//
//		assert( retValScale == 0 );
//
//		glTexSubImage2D( GL_TEXTURE_2D,
//				0,				// level
//				0, 0,			// offset
//				texSize[0], texSize[1],
//				format,
//				type,
//				newPixels
//				);
//	}
//	else
//	{
		// DON'T RESCALE IMAGE
		const void*	pPixels	= m_pIImage->pixels();

		glTexSubImage1D( GL_TEXTURE_1D,
				0,				// level
				0,				// offset
				m_imageSize[0],
				m_format,
				m_type,
				pPixels
				);
//	}

	m_pDFIImages->validate();
}



} // namespace painter

} // namespace handler

} // namespace vgeGL
