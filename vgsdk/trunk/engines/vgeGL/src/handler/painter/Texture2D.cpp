// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/Texture2D.hpp"

#include <GL/glu.h>

#include <vgd/basic/Image.hpp>
#include <vgd/node/Texture2D.hpp>
#include <vge/service/Painter.hpp>

#include "vgeGL/rc/TSynchronizeHelper.hpp"
#include "vgeGL/rc/Texture2D.hpp"


namespace vgeGL
{

namespace handler
{

namespace painter
{



META_HANDLER_CPP( Texture2D );



const vge::handler::Handler::TargetVector Texture2D::getTargets() const
{
	vge::handler::Handler::TargetVector targets;

	targets.push_back( vgd::node::Texture2D::getClassIndexStatic() );

	return ( targets );
}



void Texture2D::apply ( vge::engine::Engine* pEngine, vgd::node::Node *pNode )
{
	assert( dynamic_cast< vgeGL::engine::Engine* >(pEngine) != 0 );
	vgeGL::engine::Engine *pGLEngine = static_cast< vgeGL::engine::Engine* >(pEngine);

	assert( dynamic_cast< vgd::node::Texture2D* >(pNode) != 0 );
	vgd::node::Texture2D *pCastedNode = static_cast< vgd::node::Texture2D* >(pNode);

	vgeGL::rc::applyUsingSynchronize< vgd::node::Texture2D, vgeGL::handler::painter::Texture2D, vgeGL::rc::Texture2D >(
		pGLEngine, pCastedNode, this );
}



void Texture2D::unapply ( vge::engine::Engine* , vgd::node::Node* )
{
}



void Texture2D::setToDefaults()
{
}



void Texture2D::synchronize(	vgeGL::engine::Engine*	pGLEngine, vgd::node::Texture2D* pNode,
								vgeGL::rc::Texture2D*	pResource )
{
	// Switch to the specified tex unit and creates rc/tex
	const bool bImageAndTextureSynchronized = preSynchronize( pGLEngine, pNode, pResource );

	// Updates texture parameters
	synchronizeParameters( pGLEngine, pNode, pResource );

	if ( !bImageAndTextureSynchronized )
	{
		// Updates texture image
		texSubImage( pGLEngine, pNode, pResource );
	}

	assert( pNode->getDirtyFlag(pNode->getDFIImages())->isValid() );
	assert( pNode->getDirtyFlag(pNode->getDFParameters())->isValid() );
	assert( pNode->getDirtyFlag(pNode->getDFNode())->isValid() );
}



void Texture2D::texSubImage(	vgeGL::engine::Engine *pGLEngine, vgd::node::Texture2D *pNode,
								vgeGL::rc::Texture2D *pResource )
{
	using vgd::node::Texture;
	using vgd::node::Texture2D;	
	
	// Rescale image if necessary (boolean value already set if image is too big).
	// Check others cases, that depends to non power of two texture size and wrapping values.
	if ( !m_bResize )
	{
		// check only if not already set.
		Texture::WrapValueType wrapSValue;
		Texture::WrapValueType wrapTValue;
		
		bool isDefined = pGLEngine->getStateStackTop< Texture2D, Texture2D::WrapParameterType, Texture2D::WrapValueType >(
																		Texture2D::getFWrap(),
																		Texture2D::WRAP_S,
																		wrapSValue,
																		pNode->getMultiAttributeIndex() );
		assert( isDefined );
							
		isDefined = pGLEngine->getStateStackTop< Texture2D,	Texture2D::WrapParameterType, Texture2D::WrapValueType >(
																		Texture2D::getFWrap(),
																		Texture2D::WRAP_T,
																		wrapTValue,
																		pNode->getMultiAttributeIndex() );
		assert( isDefined );

		if (	(wrapSValue == Texture::ONCE) &&
				(wrapTValue == Texture::ONCE) )
		{
			// never resize if wrap*=ONCE.
			
			// apply a scale to texCoord.
		
			// compute scale factors.
			pResource->setScaleFactors(
							static_cast<float>(m_imageSize[0])/static_cast<float>(m_texSize[0]),
							static_cast<float>(m_imageSize[1])/static_cast<float>(m_texSize[1]),
							1.f );
		}
		else
		{
			// possible resize if needed (NPOT)
			if (	(m_texSize[0]	!= m_imageSize[0]) ||
					(m_texSize[1]	!= m_imageSize[1]) )
			{
				m_bResize= true;
			}
		}
	}

	// Updates texture (with rescale or not).
	if ( m_bResize )
	{
		// RESCALE IMAGE
		vgDebug::get().logDebug("Texture2D: Performance warning : Image (%i, %i) used as texture is resized (%i,%i)",
			m_pIImage->width(), m_pIImage->height(),
			m_texSize[0], m_texSize[1] );

		vgd::basic::Image newImage(	m_pIImage->components(), 
									m_texSize[0], m_texSize[1], 1,
									m_pIImage->format(), m_pIImage->type() );

		const void*	pixels		= m_pIImage->pixels();
		void*		newPixels	= newImage.editPixels();
	
		int retValScale;
		retValScale = gluScaleImage(
			m_format,					// src
			m_imageSize[0], m_imageSize[1],
			m_type,
			pixels,
			
			m_texSize[0], m_texSize[1],// dst
			m_type,
			newPixels
			);
			
		newImage.editPixelsDone();

		assert( retValScale == 0 );

		glTexSubImage2D( GL_TEXTURE_2D,
				0,				// level
				0, 0,			// offset
				m_texSize[0], m_texSize[1],
				m_format,
				m_type,
				newPixels
				);
	}
	else
	{
		// DON'T RESCALE IMAGE
		const void*	pPixels	= m_pIImage->pixels();

		glTexSubImage2D( GL_TEXTURE_2D,
				0,				// level
				0, 0,			// offset
				m_imageSize[0], m_imageSize[1],
				m_format,
				m_type,
				pPixels
				);
	}
	
	m_pDFIImages->validate();
}



} // namespace painter

} // namespace handler

} // namespace vgeGL
