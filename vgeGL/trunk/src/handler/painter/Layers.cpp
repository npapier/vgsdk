// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/Layers.hpp"

#include <vgd/basic/ImageInfo.hpp>
#include <vgd/node/Quad.hpp>
#include <vgd/node/Switch.hpp>
#include <vgd/node/Texture1D.hpp>
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
	
	initializeShaders();

	paint( pGLEngine, pLayers );

	// at this time, it could not be compiled in a display list.
	//vgeGL::rc::applyUsingDisplayList< vgd::node::Layers, Layers >( pEngine, pNode, this );	
}



void Layers::unapply( vge::engine::Engine* , vgd::node::Node* )
{
}



void Layers::setToDefaults()
{
}



void Layers::paint( vgeGL::engine::Engine *pGLEngine, vgd::node::Layers *pLayers )
{
	using vgd::basic::IImage;
	using vgd::basic::ImageInfo;
	using vgd::node::Layers;
	using vgd::node::Texture1D;
	using vgd::node::Texture2D;
	
	vgd::Shp< vgd::node::Switch >				pSwitch;
	vgd::Shp< vgd::node::Quad >				pQuad;
	std::vector< vgd::Shp< Texture2D > >	textures2D;
	std::vector< vgd::Shp< Texture1D > >	textures1D;
	
	// Step 1 : initialization
	if ( pLayers->getRoot().get() == 0 )
	{
		return;
	}
	
	if ( (pLayers->getRoot())->getNumChildren() == 0 )
	{
		// layers not initialized (never call Layers::createLayers(...)).
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

	const int32 numLayers = (pSwitch->getNumChildren() - 1) /2;
	assert( numLayers == pLayers->getNumLayers() );
	textures1D.reserve( numLayers );
	textures2D.reserve( numLayers );
	
	for(	int32	i = 1;
			i != 2*numLayers+1;
			++i )
	{
		vgd::Shp< Texture2D > pTex2D( pSwitch->getChild< Texture2D >(i) );
		assert( pTex2D.get() != 0 && "vgeGL::handler::painter::Layers internal error" );
		textures2D.push_back( pTex2D );
		
		++i;

		vgd::Shp< Texture1D > pTex1D( pSwitch->getChild< Texture1D >(i) );
		assert( pTex1D.get() != 0 && "vgeGL::handler::painter::Layers internal error" );
		textures1D.push_back( pTex1D );
	}

	// STEP 2 : For each layer
	vgd::Shp< vge::service::Painter >	painter(vge::service::Painter::create());

	bool											bScissorHasChanged = false;
	vgd::Shp< vgd::basic::IImage >		pScissor;
	vgd::Shp< Texture2D >					pTex2DForScissor;
	
	bool											bFirstPass = true;

	for(	int32 pass = 0;
			pass < numLayers;
			++pass )
	{
		// *** gets informations on this layer. ***
		vgd::Shp< IImage >					pIImage				= pLayers->getFIImageRO( pass )->getValue();
		
		if (	(pIImage.get() == 0) ||
				(pIImage->isEmpty()) )
		{
			// nothing to do, no or empty image.
			continue;
		}
		
		Layers::ComposeOperatorValueType	composeOperator	= pLayers->gethComposeOperator( pass );
		
		//
		if (composeOperator.getFunction() == Layers::COMPOSE_FUNCTION_NONE)
		{
			// there is an image, but don't draw it.
			continue;
		}

		vgd::field::DirtyFlag *				dirtyFlagImage		= pLayers->getDirtyFlag( pLayers->getDFIImage(pass) );

		// *** configure texture, blend stage, alpha stage, depth stage and shaders ***
		vgd::Shp< Texture2D > pTex2D;
		vgd::Shp< Texture1D > pTex1D;
		
		switch ( composeOperator.getFunction() )
		{
			//case Layers::COMPOSE_FUNCTION_NONE:
			//nothing to do, because this case was already catch.

			case Layers::REPLACE:
			case Layers::INTERPOLATE:
			{
				if ( pIImage->format() == IImage::COLOR_INDEX )
				{
					pTex2D = textures2D[pass];
					pTex1D = textures1D[pass];
					
					pTex2D->setMultiAttributeIndex(0);
					pTex1D->setMultiAttributeIndex(1);

					if ( dirtyFlagImage->isDirty() )
					{
						pTex2D->setIImage( pIImage );
						
						assert( pIImage->paletteSize() > 0 );
						ImageInfo *pImagePalette = new ImageInfo(	pIImage->paletteSize(), 1, 1,
																				pIImage->paletteFormat(), pIImage->paletteType(),
																				pIImage->palettePixels() );

						pTex1D->setIImage( vgd::Shp< ImageInfo >(pImagePalette) );
						
						dirtyFlagImage->validate();
					}
					//else nothing to do

					// REPLACE/INTERPOLATE shared the same shader.
					if ( pScissor.get() != 0 )
					{
						m_pScissorPaletteReplaceShader->use();
						m_pScissorPaletteReplaceShader->setUniform1i( "imageMap", 0 );
						m_pScissorPaletteReplaceShader->setUniform1i( "paletteMap", 1 );
						m_pScissorPaletteReplaceShader->setUniform1i( "scissorMap", 2 );
					}
					else
					{
						m_pPaletteReplaceShader->use();
						m_pPaletteReplaceShader->setUniform1i( "imageMap", 0 );
						m_pPaletteReplaceShader->setUniform1i( "paletteMap", 1 );
					}
				}
				else
				{
					pTex2D = textures2D[pass];
					pTex2D->setMultiAttributeIndex(0);
					
					if ( dirtyFlagImage->isDirty() )
					{
						pTex2D->setIImage( pIImage );
						dirtyFlagImage->validate();
					}
					//else nothing to do
					
					// REPLACE/INTERPOLATE share the shader.
					if ( pScissor.get() != 0 )
					{
						m_pScissorReplaceShader->use();
						m_pScissorReplaceShader->setUniform1i( "imageMap", 0 );
						m_pScissorReplaceShader->setUniform1i( "scissorMap", 1 );
					}
					else
					{
						m_pReplaceShader->use();
						m_pReplaceShader->setUniform1i( "imageMap", 0 );
					}
				}
				
				break;
			}



			case Layers::SCISSOR:
			{
				if ( pIImage->format() == IImage::COLOR_INDEX )
				{
					assert( false && "Scissor layer could not have a palette." );
				}
				else
				{
					pTex2D = textures2D[pass];
					
					if ( dirtyFlagImage->isDirty() )
					{
						pTex2D->setIImage( pIImage );
						dirtyFlagImage->validate();
						
						bScissorHasChanged = true;
					}
					//else nothing to do

					pTex2DForScissor = pTex2D;
					pScissor = pIImage;
					
					continue;
				}
				break;
			}



//			case Layers::MODULATE:
//				if ( dirtyFlagImage->isDirty() || bScissorHasChanged )								FIXME: todo
//				{
//					pTex2D->setIImage( pIImage );
//					dirtyFlagImage->validate();
//				}
//				//else nothing to do
//				
//				pTex2D->setFunction( vgd::node::Texture::FUN_REPLACE );
//				glEnable( GL_BLEND );
//				glBlendFunc( GL_ZERO, GL_SRC_COLOR );
//				break;

			default:
				assert( false && "Unknown ComposeOperator function." );
		}

		//glPushAttrib( GL_ALL_ATTRIB_BITS );				// FIXME : OPTME minimize number of push/pop and on what attributes
		
		//pGLEngine->getTextureMatrix().pushAll();
		pGLEngine->getTextureMatrix().push(0);
		pGLEngine->getTextureMatrix().push(1);		
		pGLEngine->getTextureMatrix().push(2);

		// udpate TEXTURE2D
		if ( pTex2D.get() != 0 )
		{
			// update TEXTURE2D
			// FIXME i do this because texture with options ONCE change the texture matrix and never restore it !!!
			//pGLEngine->getTextureMatrix().push(0);
			pGLEngine->evaluate( painter, pTex2D.get(), true );
			//pGLEngine->getTextureMatrix().pop(0);
		}
		
		// udpate TEXTURE1D
		if ( pTex1D.get() != 0 )
		{
			//pGLEngine->getTextureMatrix().push(1);		
			pGLEngine->evaluate( painter, pTex1D.get(), true );
			//pGLEngine->getTextureMatrix().pop(1);
		}

		if ( pScissor.get() != 0 )
		{
			assert(pTex2DForScissor.get() != 0 );
						
			if ( pIImage->format() == IImage::COLOR_INDEX )
			{
				pTex2DForScissor->setMultiAttributeIndex(2);
			}
			else
			{
				pTex2DForScissor->setMultiAttributeIndex(1);
			}
				
			//pGLEngine->getTextureMatrix().pushAll();					
			pGLEngine->evaluate( painter, pTex2DForScissor.get(), true );
			//pGLEngine->getTextureMatrix().popAll();
		}

		// Enable/disable opengl part for the mask.
		bool bMask = composeOperator.hasMask() || (pScissor.get() != 0);

		// ALPHA
		GLboolean	alphaTest;
		GLint			alphaFunc, alphaRef;
		glGetBooleanv( GL_ALPHA_TEST,			&alphaTest );
		glGetIntegerv( GL_ALPHA_TEST_FUNC,	&alphaFunc );
		glGetIntegerv( GL_ALPHA_TEST_REF,	&alphaRef );

		if ( bMask )
		{
			glEnable( GL_ALPHA_TEST );
			glAlphaFunc( GL_NOTEQUAL, 0.f );
		}

		// DEPTH
		GLboolean	depthMask;
		GLint			depthFunc;
		glGetBooleanv( GL_DEPTH_WRITEMASK,	&depthMask );
		glGetIntegerv( GL_DEPTH_FUNC,			&depthFunc );
		
		// configure pass
		if ( bFirstPass )
		{
			// this is the first pass
			glDepthMask( GL_TRUE );
			bFirstPass = false;
		}
		else
		{
			// this is not the first pass.
			glDepthMask( GL_FALSE );
			glDepthFunc( GL_EQUAL );
		}

		// BLEND
		GLboolean	blendEnabled;
		GLint			blendSrc, blendDst;

		glGetBooleanv( GL_BLEND,		&blendEnabled );
		glGetIntegerv( GL_BLEND_SRC,	&blendSrc );
		glGetIntegerv( GL_BLEND_DST,	&blendDst );
		
		// configure opengl state.
		if ( composeOperator.getFunction() == Layers::INTERPOLATE )
		{
			glEnable( GL_BLEND );
			glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
		}

		// draw proxy geometry.
		pGLEngine->evaluate( painter, pQuad.get(), true );
		
		pGLEngine->getTextureMatrix().pop(0);
		pGLEngine->getTextureMatrix().pop(1);		
		pGLEngine->getTextureMatrix().pop(2);
		//pGLEngine->getTextureMatrix().popAll();

		// restore
		// Restore alpha
		if ( alphaTest )
		{
			glEnable( GL_ALPHA_TEST );
		}
		else
		{
			glDisable( GL_ALPHA_TEST );
		}
		
		glAlphaFunc( alphaFunc, alphaRef );
		
		// Restore depth
		glDepthMask( depthMask );
		glDepthFunc( depthFunc );

		// Restore blend
		if ( blendEnabled )
		{
			glEnable( GL_BLEND );
		}
		else
		{
			glDisable( GL_BLEND );
		}

		glBlendFunc( blendSrc, blendDst );
		
		//glPopAttrib();																												// FIXME optme
	} // end for each layer
	
	glo::GLSLShader::useFixedPaths();
	
	// Validate node
	pLayers->getDirtyFlag(pLayers->getDFNode())->validate();
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



void Layers::initializeShaders()
{
	if ( m_shadersAlreadyInitialized )
	{
		return;
	}
	
	// ** REPLACE **
	m_pReplaceShader			= new glo::GLSLShader();

	const char *pReplace = "\
uniform sampler2D imageMap; \
 \
void main(void) \
{ \
	vec4	imageColor		= texture2D(imageMap, gl_TexCoord[0].st); \
 \
	gl_FragColor = imageColor; \
}";

	m_pReplaceShader->addShader( pReplace, glo::GLSLShader::FRAGMENT, true );
	
	// ** PALETTE_REPLACE **
	m_pPaletteReplaceShader	= new glo::GLSLShader();
	
	const char *pPaletteReplace = "\
uniform sampler2D imageMap; \
uniform sampler1D paletteMap; \
 \
void main(void) \
{ \
	vec4	imageColor		= texture2D(imageMap, gl_TexCoord[0].st); \
	vec4	paletteColor	= texture1D(paletteMap, imageColor.x); \
 \
	gl_FragColor = paletteColor; \
}";

	m_pPaletteReplaceShader->addShader( pPaletteReplace, glo::GLSLShader::FRAGMENT, true );

	// ** SCISSOR REPLACE **
	m_pScissorReplaceShader			= new glo::GLSLShader();

	const char *pScissorReplace = "\
uniform sampler2D imageMap; \
uniform sampler2D scissorMap; \
 \
void main(void) \
{ \
	vec4	imageColor		= texture2D(imageMap, gl_TexCoord[0].st); \
 \
	vec4	scissorColor	= texture2D(scissorMap, gl_TexCoord[0].st); \
 \
	gl_FragColor = vec4(imageColor.rgb, min(scissorColor.r, imageColor.a) ); \
}";

	m_pScissorReplaceShader->addShader( pScissorReplace, glo::GLSLShader::FRAGMENT, true );

	// ** SCISSOR PALETTE_REPLACE **
	m_pScissorPaletteReplaceShader	= new glo::GLSLShader();
	
	const char *pScissorPaletteReplace = "\
uniform sampler2D imageMap; \
uniform sampler1D paletteMap; \
 \
uniform sampler2D scissorMap; \
 \
void main(void) \
{ \
	vec4	imageColor		= texture2D(imageMap, gl_TexCoord[0].st); \
	vec4	paletteColor	= texture1D(paletteMap, imageColor.x); \
 \
	vec4	scissorColor	= texture2D(scissorMap, gl_TexCoord[0].st); \
 \
	gl_FragColor = vec4(paletteColor.rgb, min(scissorColor.r, paletteColor.a));\
}";

	m_pScissorPaletteReplaceShader->addShader( pScissorPaletteReplace, glo::GLSLShader::FRAGMENT, true );

	//
	m_shadersAlreadyInitialized = true;
}



bool Layers::m_shadersAlreadyInitialized = false;

glo::GLSLShader *Layers::m_pReplaceShader						= 0;
glo::GLSLShader *Layers::m_pPaletteReplaceShader			= 0;

glo::GLSLShader *Layers::m_pScissorReplaceShader			= 0;
glo::GLSLShader *Layers::m_pScissorPaletteReplaceShader	= 0;

} // namespace painter

} // namespace handler

} // namespace vgeGL
