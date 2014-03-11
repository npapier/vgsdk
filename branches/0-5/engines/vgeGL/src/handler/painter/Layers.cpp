// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/Layers.hpp"

#include <vgd/basic/ImageInfo.hpp>
#include <vgd/node/Quad.hpp>
#include <vgd/node/Switch.hpp>
#include <vgd/node/Texture1D.hpp>
#include <vgd/node/Texture2D.hpp>
#include <vgd/node/TextureMatrixTransform.hpp>
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

	// STEP 1 : initialization pSwitch, pQuad & numLayers
	assert( pLayers->getRoot() != 0 );
	if ( pLayers->getRoot()->getNumChildren() <= 1 )
	{
		// layers not initialized (never call Layers::createLayers(...)).
		return;
	}

	// get nodes.
	vgd::Shp< vgd::node::Switch >	pSwitch( vgd::dynamic_pointer_cast<vgd::node::Switch>(pLayers->getRoot()) );
	assert( pSwitch != 0 && "vgeGL::handler::painter::Layers internal error" );

	vgd::Shp< vgd::node::Quad >		pQuad(	pSwitch->getChild< vgd::node::Quad >(0) );
	assert( pQuad && "vgeGL::handler::painter::Layers internal error" );

	const int32 numLayers = (pSwitch->getNumChildren() - 2) / 2;
	assert( numLayers == pLayers->getNumLayers() );
	
	// STEP 2 : texture transformation
	using vgd::node::TextureMatrixTransform;
	
	vgd::Shp< TextureMatrixTransform > pTexMatrixTransform = pSwitch->getChild< TextureMatrixTransform >(1);

	vgd::field::DirtyFlag*	dfTransformation= pLayers->getDirtyFlag( pLayers->getDFTransformation() );

	if ( dfTransformation->isDirty() )
	{
		vgm::MatrixR matrix = pLayers->gethMatrix();
		
		pTexMatrixTransform->setMatrix( matrix );

		dfTransformation->validate();
	}

	// STEP 2bis : For each layer
	bool								bFirstPass = true;
	vgd::Shp< vgd::basic::IImage >		pScissor;
	vgd::Shp< Texture2D >				pTex2DForScissor;

	for(	int32 pass = 0;
			pass < numLayers;
			++pass )
	{
		// *** gets informations on this layer. ***
		
		// IMAGE
		vgd::Shp< IImage >	pIImage	= pLayers->getFIImageRO( pass )->getValue();
		
		if (	(pIImage == 0) ||
				(pIImage->isEmpty()) )
		{
			// nothing to do, no or empty image.
			continue;
		}
		
		// COMPOSE_OPERATOR
		Layers::ComposeOperatorValueType	composeOperator	= pLayers->gethComposeOperator( pass );
		
		if (composeOperator.getFunction() == Layers::COMPOSE_FUNCTION_NONE)
		{
			// there is an image, but don't draw it.
			continue;
		}

		// INTERNAL
		vgd::field::DirtyFlag*	dirtyFlagImage( pLayers->getDirtyFlag( pLayers->getDFIImage(pass) ) );
		vgd::Shp< Texture2D >	pTex2D( pSwitch->getChild< Texture2D >(2*pass+2) );
		vgd::Shp< Texture1D >	pTex1D( pSwitch->getChild< Texture1D >(2*pass+3) );
		assert( pTex1D != 0 );
		assert( pTex2D != 0 );

		// Configure dirtyFlagImage, pTex*
		// ouput pScissor and pTex2DForScissor
		const bool isAScissorPass = configure(	pIImage, composeOperator,
												dirtyFlagImage, pTex2D, pTex1D,
												pScissor, pTex2DForScissor );

		if ( isAScissorPass )
		{
			// current pass is on a SCISSOR, no more work must be done.
			continue;
		}

		// *** configure texture, blend stage, alpha stage, depth stage and shaders ***
		configureShaders(	pIImage, dirtyFlagImage,
							composeOperator,
							pScissor, pTex2DForScissor );
							
		// FIXME
		glPushAttrib( GL_ALL_ATTRIB_BITS );				// FIXME : OPTME minimize number of push/pop and on what attributes
		
		// configure glstate
		configureGLState( bFirstPass, composeOperator, pScissor );
				
		// UPDATE TEXTURE
		//pGLEngine->getTextureMatrix().pushAll();
		// FIXME i do this because texture with options ONCE change the texture matrix and never restore it !!!
		pGLEngine->getTextureMatrix().push(0);
		pGLEngine->getTextureMatrix().push(1);
		pGLEngine->getTextureMatrix().push(2);
		
		vgd::Shp< vgd::basic::IImage > iimage;
		bool imageInTex2D = pTex2D->getImage( iimage );
		bool imageInTex1D = pTex1D->getImage( iimage ); 

		// painter
		vgd::Shp< vge::service::Painter >	painter(vge::service::Painter::create());

		if ( imageInTex1D )
		{
			pGLEngine->evaluate( painter, pTex1D.get(), true );
		}

		if ( imageInTex2D )
		{
			pGLEngine->evaluate( painter, pTex2D.get(), true );

			// FIXME optme only evaluate it one time ? and only if != identity ?
			pGLEngine->evaluate( painter, pTexMatrixTransform.get(), true );
			assert( pTex2D->getMultiAttributeIndex() == pTexMatrixTransform->getMultiAttributeIndex() );
		}
		
		if ( pScissor != 0 )
		{
			// FIXME OPTME could be done only the first time ?
			
			// A scissor is current.
			assert( pTex2DForScissor != 0 );
						
			if ( pIImage->format() == IImage::COLOR_INDEX )
			{
				pTex2DForScissor->setMultiAttributeIndex(2);
			}
			else
			{
				pTex2DForScissor->setMultiAttributeIndex(1);
			}

			pGLEngine->evaluate( painter, pTex2DForScissor.get(), true );
		}



		// draw proxy geometry.
		pGLEngine->evaluate( painter, pQuad.get(), true );
		
		pGLEngine->getTextureMatrix().pop(0);
		pGLEngine->getTextureMatrix().pop(1);		
		pGLEngine->getTextureMatrix().pop(2);
		//pGLEngine->getTextureMatrix().popAll();
		
		// FIXME
		glPopAttrib();																												// FIXME optme
	} // end for each layer
	
	glo::GLSLProgram::useFixedPaths();
	
	// Validate node
	pLayers->getDirtyFlag(pLayers->getDFNode())->validate();
}



const bool Layers::configure(	vgd::Shp< vgd::basic::IImage > pIImage,
								vgd::node::Layers::ComposeOperatorValueType composeOperator,
								vgd::field::DirtyFlag*	dirtyFlagImage,
								vgd::Shp< vgd::node::Texture2D > pTex2D, vgd::Shp< vgd::node::Texture1D >	pTex1D,
								vgd::Shp< vgd::basic::IImage >& pScissor, vgd::Shp< vgd::node::Texture2D >& pTex2DForScissor )
{
	using vgd::basic::ImageInfo;
	using vgd::node::Layers;
	
	bool isAScissorPass = false;

	switch ( composeOperator.getFunction() )
	{
		//case Layers::COMPOSE_FUNCTION_NONE:
		//nothing to do, because this case was already catch.

		case Layers::REPLACE:
		case Layers::INTERPOLATE:
		{
			if ( pIImage->format() == ImageInfo::COLOR_INDEX )
			{
				if ( dirtyFlagImage->isDirty() )
				{
					pTex2D->setMultiAttributeIndex(0);
					pTex2D->setImage( pIImage );
					
					assert( pIImage->paletteSize() > 0 );
					ImageInfo *pImagePalette = new ImageInfo(	pIImage->paletteSize(), 1, 1,
																pIImage->paletteFormat(), pIImage->paletteType(),
																pIImage->palettePixels() );

					pTex1D->setMultiAttributeIndex(1);
					pTex1D->setImage( vgd::Shp< ImageInfo >(pImagePalette) );
					
					dirtyFlagImage->validate();
				}
				//else nothing to do
			}
			else
			{
				if ( dirtyFlagImage->isDirty() )
				{
					pTex2D->setMultiAttributeIndex(0);
					pTex2D->setImage( pIImage );
					dirtyFlagImage->validate();
				}
				//else nothing to do
			}
			break;
		}


		case Layers::SCISSOR:
		{
			if ( pIImage->format() == ImageInfo::COLOR_INDEX )
			{
				assert( false && "Scissor layer could not have a palette." );									// FIXME
			}
			else
			{
				if ( dirtyFlagImage->isDirty() )
				{
					pTex2D->setImage( pIImage );
					dirtyFlagImage->validate();
				}
				//else nothing to do

				pTex2DForScissor	= pTex2D;
				pScissor			= pIImage;

				isAScissorPass = true;
			}
		}
		break;

		default:
			assert( false && "Unknown ComposeOperator function." );
	}
	
	return ( isAScissorPass );
}



void Layers::configureShaders(	vgd::Shp< vgd::basic::IImage > pIImage, vgd::field::DirtyFlag*	dirtyFlagImage,
								vgd::node::Layers::ComposeOperatorValueType composeOperator,
								vgd::Shp< vgd::basic::IImage >& pScissor, vgd::Shp< vgd::node::Texture2D >& pTex2DForScissor )
{
	using vgd::basic::IImage;
	using vgd::basic::ImageInfo;	
	using vgd::node::Layers;
	
	switch ( composeOperator.getFunction() )
	{
		//case Layers::COMPOSE_FUNCTION_NONE:
		//nothing to do, because this case was already catch.

		case Layers::REPLACE:
		case Layers::INTERPOLATE:
		{
			if ( pIImage->format() == IImage::COLOR_INDEX )
			{
				// REPLACE/INTERPOLATE shared the same shader.
				if ( pScissor != 0 )
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
				// REPLACE/INTERPOLATE share the shader.
				if ( pScissor != 0 )
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

//		case Layers::SCISSOR:

		default:
			assert( false && "Unknown ComposeOperator function." );
	}
}



void Layers::configureGLState(	bool& bFirstPass,
								vgd::node::Layers::ComposeOperatorValueType composeOperator,
								vgd::Shp< vgd::basic::IImage > pScissor )
{
	// Enable/disable opengl part for the mask.
	bool bMask = composeOperator.hasMask() || (pScissor.get() != 0);
		
	if ( bMask )
	{
		glEnable( GL_ALPHA_TEST );
		glAlphaFunc( GL_NOTEQUAL, 0.f );
	}

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

	// configure opengl state.
	if ( composeOperator.getFunction() == vgd::node::Layers::INTERPOLATE )
	{
		glEnable( GL_BLEND );
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	}
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
	m_pReplaceShader			= new glo::GLSLProgram();

	const char *pReplace = "\
uniform sampler2D imageMap; \
 \
void main(void) \
{ \
	vec4	imageColor		= texture(imageMap, gl_TexCoord[0].st); \
 \
	gl_FragColor = imageColor; \
}";

	m_pReplaceShader->addShader( pReplace, glo::GLSLProgram::FRAGMENT, true );
	
	// ** PALETTE_REPLACE **
	m_pPaletteReplaceShader	= new glo::GLSLProgram();
	
	const char *pPaletteReplace = "\
uniform sampler2D imageMap; \
uniform sampler1D paletteMap; \
 \
void main(void) \
{ \
	vec4	imageColor		= texture(imageMap, gl_TexCoord[0].st); \
	vec4	paletteColor	= texture(paletteMap, imageColor.x); \
 \
	gl_FragColor = paletteColor; \
}";

	m_pPaletteReplaceShader->addShader( pPaletteReplace, glo::GLSLProgram::FRAGMENT, true );

	// ** SCISSOR REPLACE **
	m_pScissorReplaceShader			= new glo::GLSLProgram();

	const char *pScissorReplace = "\
uniform sampler2D imageMap; \
uniform sampler2D scissorMap; \
 \
void main(void) \
{ \
	vec4	imageColor		= texture(imageMap, gl_TexCoord[0].st); \
 \
	vec4	scissorColor	= texture(scissorMap, gl_TexCoord[0].st); \
 \
	gl_FragColor = vec4(imageColor.rgb, min(scissorColor.r, imageColor.a) ); \
}";

	m_pScissorReplaceShader->addShader( pScissorReplace, glo::GLSLProgram::FRAGMENT, true );

	// ** SCISSOR PALETTE_REPLACE **
	m_pScissorPaletteReplaceShader	= new glo::GLSLProgram();
	
	const char *pScissorPaletteReplace = "\
uniform sampler2D imageMap; \
uniform sampler1D paletteMap; \
 \
uniform sampler2D scissorMap; \
 \
void main(void) \
{ \
	vec4	imageColor		= texture(imageMap, gl_TexCoord[0].st); \
	vec4	paletteColor	= texture(paletteMap, imageColor.x); \
 \
	vec4	scissorColor	= texture(scissorMap, gl_TexCoord[0].st); \
 \
	gl_FragColor = vec4(paletteColor.rgb, min(scissorColor.r, paletteColor.a));\
}";

	m_pScissorPaletteReplaceShader->addShader( pScissorPaletteReplace, glo::GLSLProgram::FRAGMENT, true );

	//
	m_shadersAlreadyInitialized = true;
}



void Layers::destroyShaders()
{
	if ( m_pReplaceShader != 0 )
	{
		delete m_pReplaceShader;
		m_pReplaceShader = 0;
	}

	if ( m_pPaletteReplaceShader != 0 )
	{
		delete m_pPaletteReplaceShader;
		m_pPaletteReplaceShader = 0;		
	}

	if ( m_pScissorReplaceShader != 0 )
	{
		delete m_pScissorReplaceShader;
		m_pScissorReplaceShader = 0;		
	}

	if ( m_pScissorPaletteReplaceShader != 0 )
	{
		delete m_pScissorPaletteReplaceShader;
		m_pScissorPaletteReplaceShader = 0;		
	}
}



bool Layers::m_shadersAlreadyInitialized = false;

glo::GLSLProgram *Layers::m_pReplaceShader					= 0;
glo::GLSLProgram *Layers::m_pPaletteReplaceShader			= 0;

glo::GLSLProgram *Layers::m_pScissorReplaceShader			= 0;
glo::GLSLProgram *Layers::m_pScissorPaletteReplaceShader	= 0;


//			case Layers::MODULATE:
//				if ( dirtyFlagImage->isDirty() || bScissorHasChanged )								FIXME: todo
//				{
//					pTex2D->setImage( pIImage );
//					dirtyFlagImage->validate();
//				}
//				//else nothing to do
//				
//				pTex2D->setFunction( vgd::node::Texture::FUN_REPLACE );
//				glEnable( GL_BLEND );
//				glBlendFunc( GL_ZERO, GL_SRC_COLOR );
//				break;







		// FIXME must be done for all texunits.
		// push TEXTURE_xD
//		GLboolean	isTexture1D, isTexture2D;
//		glGetBooleanv( GL_TEXTURE_1D, &isTexture1D );
//		glGetBooleanv( GL_TEXTURE_2D, &isTexture2D );

//		// push ALPHA
//		GLboolean	alphaTest;
//		GLint		alphaFunc, alphaRef;
//		glGetBooleanv( GL_ALPHA_TEST,		&alphaTest );
//		glGetIntegerv( GL_ALPHA_TEST_FUNC,	&alphaFunc );
//		glGetIntegerv( GL_ALPHA_TEST_REF,	&alphaRef );

//		// push DEPTH
//		GLboolean	depthMask;
//		GLint		depthFunc;
//		glGetBooleanv( GL_DEPTH_WRITEMASK,	&depthMask );
//		glGetIntegerv( GL_DEPTH_FUNC,		&depthFunc );

//		// push BLEND
//		GLboolean	blendEnabled;
//		GLint		blendSrc, blendDst;
//
//		glGetBooleanv( GL_BLEND,		&blendEnabled );
//		glGetIntegerv( GL_BLEND_SRC,	&blendSrc );
//		glGetIntegerv( GL_BLEND_DST,	&blendDst );




//		// pop TEXTURE_xD
//		if ( isTexture1D )
//		{
//			glEnable( GL_TEXTURE_1D );
//		}
//		else
//		{
//			glDisable( GL_TEXTURE_1D );
//		}
//
//		if ( isTexture2D )
//		{
//			glEnable( GL_TEXTURE_2D );
//		}
//		else
//		{
//			glDisable( GL_TEXTURE_2D );
//		}
//
//		// pop ALPHA
//		if ( alphaTest )
//		{
//			glEnable( GL_ALPHA_TEST );
//		}
//		else
//		{
//			glDisable( GL_ALPHA_TEST );
//		}
//		
//		glAlphaFunc( alphaFunc, alphaRef );
//		
//		// pop DEPTH
//		glDepthMask( depthMask );
//		glDepthFunc( depthFunc );
//
//		// Pop BLEND
//		if ( blendEnabled )
//		{
//			glEnable( GL_BLEND );
//		}
//		else
//		{
//			glDisable( GL_BLEND );
//		}
//
//		glBlendFunc( blendSrc, blendDst );











} // namespace painter

} // namespace handler

} // namespace vgeGL
