// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/Layers.hpp"

#include <vgd/node/Quad.hpp>
#include <vgd/node/Switch.hpp>
#include <vgd/node/Texture2D.hpp>
#include <vge/service/Painter.hpp>

#include "vgeGL/rc/TDisplayListHelper.hpp"



namespace vgeGL
{

namespace handler
{

namespace painter
{



META_HANDLER_CPP( Layers );



const vge::handler::Handler::TargetVector Layers::getTargets() const
{
	TargetVector targets;
	
	targets.push_back( vgd::node::Layers::getClassIndexStatic() );

	return ( targets );
}



void Layers::apply( vge::engine::Engine* pEngine, vgd::node::Node *pNode )
{
	assert( dynamic_cast< vgeGL::engine::Engine* >(pEngine) != 0 );
	vgeGL::engine::Engine *pGLEngine = static_cast< vgeGL::engine::Engine* >(pEngine);

	assert( dynamic_cast< vgd::node::Layers* >(pNode) != 0 );
	vgd::node::Layers *pLayers = static_cast< vgd::node::Layers* >(pNode);
	
	paint( pGLEngine, pLayers );
	
	//vgeGL::rc::applyUsingDisplayList< vgd::node::Layers, Layers >( pEngine, pNode, this ); FIXME
}



void Layers::unapply ( vge::engine::Engine* engine, vgd::node::Node* pNode )
{
}



void Layers::setToDefaults()
{
}



void Layers::paint( vgeGL::engine::Engine *pGLEngine, vgd::node::Layers *pLayers )
{
	vgd::Shp< vgd::node::Switch >							pSwitch;
	vgd::Shp< vgd::node::Quad >							pQuad;
	std::vector< vgd::Shp< vgd::node::Texture2D > >	textures;
	
	if ( pLayers->getRoot().get() == 0 )
	{
		return;
	}
	
	if ( (pLayers->getRoot())->getNumChildren() == 0 )
	{
		// layers not initialized (never call vgd::node::Layers::createLayers(...)).
		return;
	}

	// get nodes.
	pSwitch	= vgd::dynamic_pointer_cast<vgd::node::Switch>(pLayers->getRoot());
	if (	pSwitch.get() == 0 )
	{
		assert( false && "vgeGL::handler::painter::Layers internal error" );
		return;
	}

	pQuad		= pSwitch->getChild< vgd::node::Quad >(0);
	assert( pQuad.get() && "vgeGL::handler::painter::Layers internal error" );

	const int32 numLayers = pLayers->getNumLayers();	
	assert( pSwitch->getNumChildren() - 1 == numLayers && "Must have one texture node for each layer" );
	textures.reserve( numLayers );
	
	for(	int32	i = 1;
			i != numLayers+1;
			++i )
	{
		vgd::Shp< vgd::node::Texture2D > pTex( pSwitch->getChild< vgd::node::Texture2D >(i) );
		assert( pTex.get() != 0 && "vgeGL::handler::painter::Layers internal error" );
		
		textures.push_back( pTex );
	}

	// For each layer
	vgd::Shp< vge::service::Painter >	painter;
	vgd::Shp< vgd::basic::IImage >		pScissor;
	// sets to true if a previously encountered scissor has changed.
	bool											bScissorHasChanged( false );

	painter		= vge::service::Painter::create();

	bool bFirstPass = true;
	
	for(	int32 i = 0;
			i < numLayers;
			++i )
	{
		// *** gets informations on this layer. ***
		vgd::field::EditorRO< vgd::node::Layers::FIImageType >	editorImageRO;
		vgd::Shp< vgd::basic::IImage >									pImage;
		vgd::node::Layers::ComposeOperatorValueType					composeOperator;
		
		editorImageRO		= pLayers->getFIImageRO( i );
		pImage				= editorImageRO->getValue();
		composeOperator	= pLayers->gethComposeOperator( i );

		vgd::field::DirtyFlag *dirtyFlagImage = pLayers->getDirtyFlag( pLayers->getDFIImage(i) );
		
		// alpha
		float alpha;
		alpha = composeOperator.getAlpha();
		
		uint8	ui8Alpha;
		ui8Alpha	= static_cast< uint8 >( alpha * 255.f );
		
		//
		vgd::Shp< vgd::node::Texture2D > pTex( textures[i] );

		//
		if (	(pImage.get() == 0) ||
				(pImage->isEmpty())
				)
		{
			// nothing to do, no or empty image.
			continue;
		}

		// *** configure texture, blend stage, alpha stage and depth stage ***
		glPushAttrib( GL_ALL_ATTRIB_BITS );																		// FIXME : OPTME minimize number of push/pop and on what attributes
		
		switch ( composeOperator.getFunction() )
		{
			case vgd::node::Layers::COMPOSE_FUNCTION_NONE:
				glPopAttrib();
				// there is an image, but don't draw it.
				continue;



			case vgd::node::Layers::REPLACE:
				if ( dirtyFlagImage->isDirty() || bScissorHasChanged )
				{
					pTex->setIImage( pImage );
					dirtyFlagImage->validate();
				}
				//else nothing to do
				
				pTex->setFunction( vgd::node::Texture2D::FUN_REPLACE );				
				break;



			case vgd::node::Layers::INTERPOLATE:
				if ( dirtyFlagImage->isDirty() || bScissorHasChanged )
				{
					pTex->setIImage( pImage );
					dirtyFlagImage->validate();
				}
				//else nothing to do

				pTex->setFunction( vgd::node::Texture::FUN_REPLACE );
				glEnable( GL_BLEND );
				glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
				break;



			case vgd::node::Layers::SCISSOR:
				if ( dirtyFlagImage->isDirty() )
				{
					bScissorHasChanged = true;
					dirtyFlagImage->validate();					
				}
				//else nothing to do

				pScissor = pImage;
				glPopAttrib();
				// nothing to be drawn.
				continue;



			case vgd::node::Layers::MODULATE:
				if ( dirtyFlagImage->isDirty() || bScissorHasChanged )
				{
					pTex->setIImage( pImage );
					dirtyFlagImage->validate();
				}
				//else nothing to do
				
				pTex->setFunction( vgd::node::Texture::FUN_REPLACE );
				glEnable( GL_BLEND );
				glBlendFunc( GL_ZERO, GL_SRC_COLOR );
				break;

			default:
				assert( false && "Unknown ComposeOperator function." );
		}
		
		// Enable/disable opengl part for the mask.
		bool bMask;
		bMask =	composeOperator.hasMask() ||
					(pScissor.get() != 0);

		if ( bMask )
		{
			glEnable( GL_ALPHA_TEST );
			glAlphaFunc( GL_NOTEQUAL, 0.f );
		}
		
		// Scissor mask
		//std::vector< uint8 > alphaChannel;		
		vgd::Shp< vgd::basic::Image > pCopyImage;

		if ( bScissorHasChanged )
		{
			pCopyImage = vgd::Shp< vgd::basic::Image >( new vgd::basic::Image(*pImage) ); // FIXME optme.
			
			//
			applyScissorMask( pScissor, pImage );
		}

		// render
		if ( bFirstPass )
		{
			// this is the first pass
			glDepthMask( GL_TRUE );
		}
		else
		{
			// this is not the first pass.
			glDepthFunc( GL_EQUAL );
			glDepthMask( GL_FALSE );
		}

		// FIXME i do this because texture with options ONCE change the texture matrix and never restore it !!!
		pGLEngine->getTextureMatrix().push(0);
		pGLEngine->evaluate( painter, pTex.get(), true );
		pGLEngine->getTextureMatrix().pop(0);

		// restore alpha channel of image if needed FIXME ???????????????????????????????????????????????????????????????????????????????????
		if ( pCopyImage.get() != 0 )
		{
			(*pImage) = (*pCopyImage);
			//		if ( alphaChannel.size() != 0 )
			//		{
			//			std::vector< uint8 >::iterator iAlphaChannel;
			//			iAlphaChannel = alphaChannel.begin();
			//		
			//			uint8*			iImage = static_cast<uint8*>(pImage->editPixels());
			//			for(	uint8	*iEnd = iImage + pImage->width()*pImage->height()*4;
			//					iImage != iEnd;
			//					)
			//			{
			//				iImage += 3;
			//				
			//				(*iImage) = (*iAlphaChannel);
			//				
			//				++iAlphaChannel;
			//				++iImage;
			//			}
			//			pImage->editPixelsDone();
			//		}
		}
		
		// draw proxy geometry.
		pGLEngine->evaluate( painter, pQuad.get(), true );
		
		bFirstPass = false;

		// restore
		glPopAttrib();
	} // end for each layer
}



void Layers::applyScissorMask( vgd::Shp< vgd::basic::IImage > pScissor, vgd::Shp< vgd::basic::IImage > pImage )
{
	using vgd::basic::IImage;
	
	assert(	(pScissor->format() == IImage::RGBA) ||
				(pScissor->format() == IImage::BGRA) ||
				(pScissor->format() == IImage::LUMINANCE_ALPHA) );

	assert( pScissor->format() == pImage->format() );
	
	assert( pScissor->type() == IImage::UINT8 );
	assert( pImage->type() == IImage::UINT8 );	

	assert( pScissor->width() == pImage->width() );
	assert( pScissor->height() == pImage->height() );

	// scan image
	const uint8*	iScissor = static_cast<const uint8*>(pScissor->pixels());
	uint8*			iImage	= static_cast<uint8*>(pImage->editPixels());
	
	switch ( pImage->format() )
	{
		case IImage::RGBA:
		case IImage::BGRA:
		{	
			for(	uint8	*iEnd = iImage + pImage->width()*pImage->height()*4;
					iImage != iEnd;
					)
			{
				if (	(iScissor[0] == 0) &&
						(iScissor[1] == 0) &&
						(iScissor[2] == 0)
						)
				{
					iImage += 3;
					(*iImage) = 0;
					++iImage;
				}
				else
				{
					iImage	+= 4;
				}
				
				iScissor += 4;
			}
			pImage->editPixelsDone();
		}
		break;
		
		case IImage::LUMINANCE_ALPHA:
		{
			for(	uint8	*iEnd = iImage + pImage->width()*pImage->height()*2;
					iImage != iEnd;
					)
			{
				if (	iScissor[0] == 0 )
				{
					++iImage;
					(*iImage) = 0;
					++iImage;
				}
				else
				{
					iImage	+= 2;
				}
				
				iScissor += 2;
			}
			pImage->editPixelsDone();
		}
		break;

		default:
			assert( false && "Internal error" );
	}
}



//					tex2D->setFunction( vgd::node::Texture::FUN_DECAL );
				/*tex2D->setFunction( vgd::node::Texture::FUN_COMBINE );
			
				tex2D->setCombine( vgd::node::Texture::RGB, vgd::node::Texture::INTERPOLATE );
				tex2D->setCombine( vgd::node::Texture::ALPHA, vgd::node::Texture::INTERPOLATE );
				
				tex2D->setSource( vgd::node::Texture::RGB0, vgd::node::Texture::TEXTURE );
				tex2D->setSource( vgd::node::Texture::ALPHA0, vgd::node::Texture::TEXTURE );
				
				tex2D->setSource( vgd::node::Texture::RGB1, vgd::node::Texture::PREVIOUS );
				tex2D->setSource( vgd::node::Texture::ALPHA1, vgd::node::Texture::PREVIOUS );
				
				tex2D->setSource( vgd::node::Texture::RGB2, vgd::node::Texture::CONSTANT );
				tex2D->setSource( vgd::node::Texture::ALPHA2, vgd::node::Texture::CONSTANT );
				
				tex2D->setOperand( vgd::node::Texture::RGB0, vgd::node::Texture::ONE_MINUS_SRC_COLOR );
				tex2D->setOperand( vgd::node::Texture::RGB1, vgd::node::Texture::SRC_COLOR );
				tex2D->setOperand( vgd::node::Texture::RGB2, vgd::node::Texture::SRC_COLOR );						

				tex2D->setOperand( vgd::node::Texture::ALPHA0, vgd::node::Texture::ONE_MINUS_SRC_ALPHA );
				tex2D->setOperand( vgd::node::Texture::ALPHA1, vgd::node::Texture::SRC_ALPHA );
				tex2D->setOperand( vgd::node::Texture::ALPHA2, vgd::node::Texture::SRC_ALPHA );
				*/

} // namespace painter

} // namespace handler

} // namespace vgeGL
