// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/Texture1D.hpp"

#include <vgd/basic/Image.hpp>
#include <vgd/node/Texture1D.hpp>
#include <vge/service/Painter.hpp>
#include <vgm/Utilities.hpp>

#include "vgeGL/rc/TSyncAndBindHelper.hpp"
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

	vgeGL::rc::applyUsingSyncAndBind< vgd::node::Texture1D, vgeGL::handler::painter::Texture1D, vgeGL::rc::Texture1D >(
		pGLEngine, pCastedNode, this );
}



void Texture1D::unapply ( vge::engine::Engine*, vgd::node::Node* )
{
}



void Texture1D::setToDefaults()
{
}



/**
 * @todo take care of texture and image format...
 * @todo move to Texture for beiing reused by TextureCube.
 * 
 * @todo ARB NPOT extension
 */
void Texture1D::synchronize(	vgeGL::engine::Engine *pGLEngine, vgd::node::Texture1D *pNode,
										vgeGL::rc::Texture1D *pResource )
{
	// Dirty flag for IImage
	vgd::field::DirtyFlag*	pDFIImage = pNode->getDirtyFlag( pNode->getDFIImage() );
	
	if ( pDFIImage->isValid() )
	{
		return;
	}

	// Get IImage
	bool										isDefined;
	vgd::Shp< vgd::basic::IImage >	pIImage;

	isDefined = pNode->getIImage( pIImage );
	
	// Nothing to do if iimage is not defined.
	if ( !isDefined )
	{
		return;
	}

	// activate the texture unit.
	pResource->active( GL_TEXTURE0_ARB + pNode->getMultiAttributeIndex() );
	
	// Create or recycle resource.
	int32	imageSize	= pIImage->width();
	int32 imagePOT		= vgm::Utilities::nextPower2( imageSize );

	int32		components	= pIImage->components();
	GLenum	format		= convertMyFormat2GL(	pIImage->format()	);
	GLenum	type			= convertMyType2GL(		pIImage->type()	);

	// Check if create(glTexImage) or update(glTexSubImage).
	bool				bUseGLTexImage;
	int32				texSize;

	if ( pResource->isEmpty() )
	{
		// create
		pResource->generate();
		pResource->bind();
		
		bUseGLTexImage = true;
	}
	else
	{
		pResource->bind();
		
		texSize = pResource->getSize();
		
		// FIXME take care of texture and image format.
		if (	texSize >= imagePOT	)
		{
			// same size (at least) between already initialized texture and imagePOT (power of two), recycle(update) texture.
			bUseGLTexImage = false;
		}
		else
		{
			bUseGLTexImage = true;
		}
	}
	
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
	
	// Create Texture1D
	bool		bResize = false;
	
	if ( bUseGLTexImage )
	{
		// border
		bool			bHasBorder;
		vgm::Vec4f	borderValue;
		int32			borderSize;	
		
		bHasBorder	= pNode->getBorder( borderValue );
		borderSize = bHasBorder ? 2 : 0;

		// size
		GLint	maxTexSize	= pGLEngine->getMaxTexSize();

		// image exceed max texture size ?
		if ( imagePOT > maxTexSize )
		{
			texSize	= maxTexSize;
			bResize	= true;
		}
		else
		{
			texSize = imagePOT;
		}
	
		glTexImage1D( GL_TEXTURE_1D,
				0,
				components,
				texSize + borderSize,
				bHasBorder ? 1 : 0,
				format,
				type,
				0
				);
	}
	
	// Rescale image if necessary (boolean value already set if image is too big).
	// Check others cases, that depends to non power of two texture size and wrapping values.
	if ( !bResize )
	{
		// check only if not already set.
		vgd::node::Texture::WrapValueType wrapSValue;
		
		isDefined = pGLEngine->getStateStackTop< 
							vgd::node::Texture1D,
							vgd::node::Texture1D::WrapParameterType,
							vgd::node::Texture1D::WrapValueType >(
																					vgd::node::Texture1D::getFWrap(),
																					vgd::node::Texture1D::WRAP_S,
																					wrapSValue,
																					pNode->getMultiAttributeIndex() );
		assert( isDefined );
							
		if (	wrapSValue == vgd::node::Texture::ONCE	)
		{
			// never resize if wrap*=ONCE.
			
			// apply a scale to texCoord.
		
			// compute scale factors.
			pResource->setScaleFactors(
							static_cast<float>(imageSize)/static_cast<float>(texSize),
							1.f,
							1.f );
		}
		else
		{
			// possible resize if needed (NPOT)
			if ( texSize != imageSize )
			{
				bResize = true;
			}
		}
	}

	// Update texture (with rescale or not).
	assert( !bResize && "Resize texture1D is not yet implemented" );
	
//	if ( bResize )
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
		const void*	pPixels	= pIImage->pixels();

		glTexSubImage1D( GL_TEXTURE_1D,
				0,				// level
				0,				// offset
				imageSize,
				format,
				type,
				pPixels
				);
//	}

	pDFIImage->validate();
}



void Texture1D::bind(	vgeGL::engine::Engine *pGLEngine, vgd::node::Texture1D *pNode,
								vgeGL::rc::Texture1D *pResource  )
{
	// get IImage
	bool										isDefined;
	vgd::Shp< vgd::basic::IImage >	pIImage;
	
	isDefined = pNode->getIImage( pIImage );

	//
	if ( isDefined )
	{
		// active the texture unit.
		pResource->active( GL_TEXTURE0_ARB + pNode->getMultiAttributeIndex() );
		
		// bind texture to the texture unit.
		pResource->bind();
		
		// enable texturing.								// FIXME should be done in VertexShape (for beiing done once).
		pResource->enable();
	}

	Texture::paint( pGLEngine, pNode, pResource ); // FIXME

	// FIXME scale factors could be better done in VertexShape.
	// scaleFactors
	vgm::Vec3f scaleFactors;
	pResource->getScaleFactors( scaleFactors[0], scaleFactors[1], scaleFactors[2] );
	
	vgm::MatrixR scaleMatrix;
	scaleMatrix.setScale( scaleFactors );

	// apply scale to vge.
	vgm::MatrixR& textureMatrix(
		pGLEngine->getTextureMatrix().getTop( pNode->getMultiAttributeIndex() )
			);

	textureMatrix = scaleMatrix * textureMatrix;
	
	// apply scale to vgeGL.
	glMatrixMode( GL_TEXTURE );
	glLoadMatrixf( reinterpret_cast<const float*>( textureMatrix.getValue() ) );
	
	// Validate node
	pNode->getDirtyFlag(pNode->getDFNode())->validate();	
}



} // namespace painter

} // namespace handler

} // namespace vgeGL
