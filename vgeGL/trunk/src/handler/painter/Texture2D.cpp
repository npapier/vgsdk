// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/Texture2D.hpp"

#include <vgd/basic/Image.hpp>
#include <vgd/field/DirtyFlag.hpp>
#include <vgd/node/Texture2D.hpp>
#include <vge/rc/Manager.hpp>
#include <vge/service/Painter.hpp>
#include <vgm/Utilities.hpp>

#include "vgeGL/engine/Engine.hpp"
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

	vge::rc::Manager& rGLManager = pGLEngine->getGLManager();

	// ****** Render ******
	vgd::field::DirtyFlag	*pDFNode;
	vgd::field::DirtyFlag	*pDFIImage;
	vge::rc::IResource 		*pResource;
	vgeGL::rc::Texture2D		*pCastedResource;

	// get dirty flag of node
	pDFNode		= pCastedNode->getDirtyFlag( pCastedNode->getDFNode() );
	pDFIImage	= pCastedNode->getDirtyFlag( pCastedNode->getDFIImage() );

	// lookup the resource.
	pResource			= rGLManager.getAbstract( pNode );
	pCastedResource	= dynamic_cast< vgeGL::rc::Texture2D* >(pResource);
	
	if (	( pCastedResource == 0 ) &&
			( pResource != 0) )
	{
		// There is a resource, but not of the expected type.
		// Dynamic change of handler ?
		// or node that must be process differently (static, dynamic for VertexShape).
		rGLManager.remove( pNode );

		pResource			= 0;
	}

	assert(	(pResource==0 && pCastedResource==0) ||
				(pResource!=0 && pCastedResource!=0)
				 );

	// What to do ?
	if ( pDFIImage->isDirty() )
	{
		// Node is invalidated.
		if ( pCastedResource == 0 )
		{
			// No resource (this is the first evaluation), create it.
			pCastedResource = new vgeGL::rc::Texture2D();
			rGLManager.add( pNode, pCastedResource );
		}
		// else have founded an associated resource, recycle it in create().

		// update resource.
		create( pGLEngine, pCastedNode, pCastedResource );
		use( pGLEngine, pCastedNode, pCastedResource );
		
		// validate.
		pDFIImage->validate();
		pDFNode->validate();
	}
	else
	{
		// No change in node.
		if ( pCastedResource != 0 )
		{
			// Founded an associated resource.
			
			// render
			use( pGLEngine, pCastedNode, pCastedResource );
		}
		else
		{
			// No resource, but already validate !!!
			assert( false && "No resource, but already validate !!!" );
		}
	}
}



void Texture2D::unapply ( vge::engine::Engine* engine, vgd::node::Node* pNode )
{
}



void Texture2D::setToDefaults()
{
}



/**
 * @todo take care of texture and image format...
 * @todo move to Texture for beiing reused by TextureCube.
 * 
 * @todo ARB NPOT extension
 */
void Texture2D::create(	vgeGL::engine::Engine *pGLEngine, vgd::node::Texture2D *pNode,
								vgeGL::rc::Texture2D *pResource )
{
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
	vgm::Vec2i			imageSize;
	vgm::Vec2i			imagePOT;			// POT : power of two.
	
	imageSize[0]	= pIImage->width();
	imageSize[1]	= pIImage->height();

	imagePOT[0]		= vgm::Utilities::nextPower2( imageSize[0] );
	imagePOT[1]		= vgm::Utilities::nextPower2( imageSize[1] );

	int32		components	= pIImage->components();
	GLenum	format		= convertMyFormat2GL( pIImage->format() );
	GLenum	type			= convertMyType2GL( pIImage->type() );

	// Check if create(glTexImage) or update(glTexSubImage).
	bool				bUseGLTexImage;
	vgm::Vec2i		texSize;

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
		if (	(texSize[0] >= imagePOT[0]) &&
				(texSize[1] >= imagePOT[1])
				 )
		{
			// same size (at least) between already initialized texture and imagePOT (power of two), recycle(update) texture.
			bUseGLTexImage = false;
		}
		else
		{
			bUseGLTexImage = true;
		}
	}
	
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // ?????????????????????????????? FIXME

	// Create texture2D
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
		if ( imagePOT[0] > maxTexSize )
		{
			texSize[0]	= maxTexSize;
			bResize		= true;
		}
		else
		{
			texSize[0] = imagePOT[0];
		}
		
		if ( imagePOT[1] > maxTexSize )
		{
			texSize[1]	= maxTexSize;
			bResize		= true;
		}
		else
		{
			texSize[1]	= imagePOT[1];
		}
	
		glTexImage2D( GL_TEXTURE_2D,
				0,
				components,
				texSize[0] + borderSize, texSize[1] + borderSize,
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
		vgd::node::Texture::WrapValueType wrapTValue;
		
		isDefined = pGLEngine->getStateStackTop< 
							vgd::node::Texture2D,
							vgd::node::Texture2D::WrapParameterType,
							vgd::node::Texture2D::WrapValueType >(
																					vgd::node::Texture2D::getFWrap(),
																					vgd::node::Texture2D::WRAP_S,
																					wrapSValue,
																					pNode->getMultiAttributeIndex() );
		assert( isDefined );
							
		isDefined = pGLEngine->getStateStackTop< 
							vgd::node::Texture2D,
							vgd::node::Texture2D::WrapParameterType,
							vgd::node::Texture2D::WrapValueType >(
																					vgd::node::Texture2D::getFWrap(),
																					vgd::node::Texture2D::WRAP_T,
																					wrapTValue,
																					pNode->getMultiAttributeIndex() );
		assert( isDefined );

		if (	(wrapSValue == vgd::node::Texture::ONCE) &&
				(wrapTValue == vgd::node::Texture::ONCE) )
		{
			// never resize if wrap*=ONCE.
			
			// apply a scale to texCoord.
		
			// compute scale factors.
			pResource->setScaleFactors(
							static_cast<float>(imageSize[0])/static_cast<float>(texSize[0]),
							static_cast<float>(imageSize[1])/static_cast<float>(texSize[1]),
							1.f );
		}
		else
		{
			// possible resize if needed (NPOT)
			if (	(texSize[0]	!= imageSize[0]) ||
					(texSize[1]	!= imageSize[1]) )
			{
				bResize = true;
			}
		}
	}

	// Update texture (with recale or not).
	if ( bResize )
	{
		// RESCALE IMAGE
		vgDebug::get().logDebug("Texture2D: Performance warning : Image (%i, %i) used as texture is resized (%i,%i)",
			pIImage->width(), pIImage->height(),
			texSize[0], texSize[1] );

		vgd::basic::Image newImage(	pIImage->components(), texSize[0], texSize[1], 1, pIImage->format(), pIImage->type() );

		const void*	pixels	= pIImage->pixels();
		void*		newPixels	= newImage.editPixels();
	
		int retValScale;
		retValScale = gluScaleImage(
			format,					// src
			imageSize[0], imageSize[1],
			type,
			pixels,
			
			texSize[0], texSize[1],// dst
			type,
			newPixels
			);
			
		newImage.editPixelsDone();

		assert( retValScale == 0 );

		glTexSubImage2D( GL_TEXTURE_2D,
				0,				// level
				0, 0,			// offset
				texSize[0], texSize[1],
				format,
				type,
				newPixels
				);
	}
	else
	{
		// DON'T RESCALE IMAGE
		const void*	pPixels	= pIImage->pixels();

		glTexSubImage2D( GL_TEXTURE_2D,
				0,				// level
				0, 0,			// offset
				imageSize[0], imageSize[1],
				format,
				type,
				pPixels
				);
	}
}



void Texture2D::use(	vgeGL::engine::Engine *pGLEngine, vgd::node::Texture2D *pNode,
							vgeGL::rc::Texture2D *pResource  )
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
	
	
	
	
	
	/* ??? FIXME glTexGeni(	GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR );
	GLfloat plane[] = { 1.0, 1.0, 1.0, 0.0 };
	glTexGenfv(	GL_S, GL_OBJECT_PLANE, plane );
	glEnable(GL_TEXTURE_GEN_S);

	glTexGeni(	GL_T GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR );
	glTexGenfv(	GL_T, GL_OBJECT_PLANE, plane );
	glEnable(GL_TEXTURE_GEN_T);*/

	
	//glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR );
	//glTexGenf(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR );	

	//glEnable(GL_TEXTURE_GEN_S);
	//glEnable(GL_TEXTURE_GEN_T);	
	
//	glTexGenfv(GL_S,GL_SPHERE_MAP,0);
//	glTexGenfv(GL_T,GL_SPHERE_MAP,0);
//	glEnable(GL_TEXTURE_GEN_S);
//	glEnable(GL_TEXTURE_GEN_T);
}



} // namespace painter

} // namespace handler

} // namespace vgeGL
