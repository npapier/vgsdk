// VGSDK - Copyright (C) 2004, 2007, 2008, 2009, 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/Texture.hpp"

#include <glo/Texture.hpp>
#include <vgd/basic/Image.hpp>
#include <vgd/field/DirtyFlag.hpp>
#include <vgd/node/Texture.hpp>
#include <vgDebug/convenience.hpp>
#include <vgm/VectorOperations.hpp>

#include "vgeGL/engine/Engine.hpp"



namespace vgeGL
{

namespace handler
{

namespace painter
{



namespace
{

const GLenum convertInternalFormatToGLInternalFormat( const vgd::node::Texture::InternalFormatValueType internalFormat, const GLenum defaultGLInternalFormat )
{
	using vgd::node::Texture;

	if ( internalFormat == Texture::DEPTH_COMPONENT_16 )
	{
		return GL_DEPTH_COMPONENT16;
	}
	else if ( internalFormat == Texture::DEPTH_COMPONENT_24 )
	{
		return GL_DEPTH_COMPONENT24;
	}
	else if ( internalFormat == Texture::DEPTH_COMPONENT_32 )
	{
		return GL_DEPTH_COMPONENT32;
	}
	else if ( internalFormat == Texture::DEPTH_COMPONENT_32F )
	{
		return GL_DEPTH_COMPONENT32F;
	}
	else if ( internalFormat == Texture::RGB_16F )
	{
		return GL_RGB16F;
	}
	else if ( internalFormat == Texture::RGB_32F )
	{
		return GL_RGB32F;
	}
	else if ( internalFormat == Texture::RGBA_16F )
	{
		return GL_RGBA16F;
	}
	else if ( internalFormat == Texture::RGBA_32F )
	{
		return GL_RGBA32F;
	}	
	else if ( internalFormat == Texture::LUMINANCE_16F )
	{
		return GL_LUMINANCE16F_ARB; // @todo GL_R16 ?
	}
	else if ( internalFormat == Texture::LUMINANCE_32F )
	{
		return GL_LUMINANCE32F_ARB;
	}
	else if ( internalFormat == Texture::LUMINANCE_ALPHA_16F )
	{
		return GL_LUMINANCE_ALPHA16F_ARB;
	}
	else if ( internalFormat == Texture::LUMINANCE_ALPHA_32F )
	{
		return GL_LUMINANCE_ALPHA32F_ARB;
	}	
	else if ( internalFormat ==  Texture::AUTOMATIC )
	{
		return defaultGLInternalFormat;
	}
	else
	{
		assert( false && "Unexpected value in convertInternalFormatToGLInternalFormat()" );
		return GL_DEPTH_COMPONENT;
	}
}

}



void Texture::setToDefaults()
{}



void Texture::paint(vgeGL::engine::Engine *pEngine, vgd::node::Texture *pNode, glo::Texture *pResource )
{
	paintParams(	pEngine, pNode, pResource );
	//paintEnv(		pEngine, pNode, pResource );
}



void Texture::paintParams( vgeGL::engine::Engine *pEngine, vgd::node::Texture *pNode, glo::Texture *pResource )
{
	using vgd::node::Texture;

	// WRAP
	vgd::field::EditorRO< Texture::FWrapType > wrap = pNode->getFieldRO<Texture::FWrapType>(pNode->getFWrap());

	Texture::FWrapType::const_iterator wrapIter;
	Texture::FWrapType::const_iterator wrapEnd;
	
	for(	wrapIter = wrap->begin(),
			wrapEnd	= wrap->end();

			wrapIter != wrapEnd;

			++wrapIter
			)
	{
		pResource->parameter(
				m_wrapParameter[ wrapIter->first.value() - Texture::WRAP_S ],
				m_wrapValue[ wrapIter->second.value() - Texture::REPEAT ]
				);
	}
	wrap.release();

	// FILTER
	vgd::field::EditorRO< Texture::FFilterType > filter = pNode->getFieldRO<Texture::FFilterType>(pNode->getFFilter());
	
	Texture::FFilterType::const_iterator filterIter;
	Texture::FFilterType::const_iterator filterEnd;
	
	for(	filterIter = filter->begin(),
			filterEnd	= filter->end();
			
			filterIter != filterEnd;
			
			++filterIter
			)
	{
		pResource->parameter(
				m_filterParameter[ filterIter->first.value() - Texture::MIN_FILTER ],
				m_filterValue[ filterIter->second.value() - Texture::NEAREST ]
				);
	}
	filter.release();

	// MIPMAP
	if ( pNode->hasMipmap() )
	{
		bool bMipmap;
		pNode->getMipmap( bMipmap );

		if ( isGL_SGIS_generate_mipmap() )
		{
			#ifdef _DEBUG
			vgLogDebug("vgeGL.Texture: GL_SGIS_generate_mipmap detected and used.");
			#endif

			pResource->setAutomaticMipmapGenerationEnabled( bMipmap );
		}
		else
		{
			#ifdef _DEBUG
			vgLogDebug("vgeGL.Texture: GL_SGIS_generate_mipmap not detected, try software mipmap later.");
			#endif
		}
	}

/*	// BORDER_COLOR
	vgm::Vec4f v4;
	bDefined = pNode->getBorderColor( v4 );

	if ( bDefined )
	{
		pResource->parameter(
			GL_TEXTURE_BORDER_COLOR, v4.getValue() );
	}*/
}



/*void Texture::paintEnv( vgeGL::engine::Engine *pEngine, vgd::node::Texture *pNode, glo::Texture *pResource )
{
	using vgd::node::Texture;

	// ENV_COLOR
	vgm::Vec4f v4;
	bool bDefined = pNode->getEnvColor( v4 );
	
	if ( bDefined )
	{
		pResource->env( 
			GL_TEXTURE_ENV_COLOR,
			v4.getValue() );
	}*/

	// FUNCTION
/*// @todo
	vgd::field::EditorRO< Texture::FFunctionType > function = pNode->getFieldRO<Texture::FFunctionType>(pNode->getFFunction());
	
	Texture::FFunctionType::const_iterator functionIter;
	Texture::FFunctionType::const_iterator functionEnd;
	
	for(	functionIter = function->begin(),
			functionEnd	= function->end();
			
			functionIter != functionEnd;
			
			++functionIter
			)
	{
		pResource->env(
				GL_TEXTURE_ENV_MODE,
				m_functionValue[ functionIter->second ] - Texture::FUN_REPLACE
				);
	}	
	function.release();*/

	/*// COMBINE
	vgd::field::EditorRO< Texture::FCombineType > combine = pNode->getFieldRO<Texture::FCombineType>(pNode->getFCombine());
	
	Texture::FCombineType::const_iterator combineIter;
	Texture::FCombineType::const_iterator combineEnd;
	
	for(	combineIter = combine->begin(),
			combineEnd	= combine->end();
			
			combineIter != combineEnd;
			
			++combineIter
			)
	{
		pResource->env(
				m_combineParameter[ combineIter->first ],
				m_combineValue[ combineIter->second ]
				);
	}
	combine.release();
	
	// SOURCE
	vgd::field::EditorRO< Texture::FSourceType > source = pNode->getFieldRO<Texture::FSourceType>(pNode->getFSource());
	
	Texture::FSourceType::const_iterator sourceIter;
	Texture::FSourceType::const_iterator sourceEnd;
	
	for(	sourceIter = source->begin(),
			sourceEnd	= source->end();
			
			sourceIter != sourceEnd;
			
			++sourceIter
			)
	{
		pResource->env(
				m_sourceParameter[ sourceIter->first ],
				m_sourceValue[ sourceIter->second ]
				);
	}
	source.release();

	// OPERAND
	vgd::field::EditorRO< Texture::FOperandType > operand = pNode->getFieldRO<Texture::FOperandType>(pNode->getFOperand());
	
	Texture::FOperandType::const_iterator operandIter;
	Texture::FOperandType::const_iterator operandEnd;
	
	for(	operandIter = operand->begin(),
			operandEnd	= operand->end();
			
			operandIter != operandEnd;
			
			++operandIter
			)
	{
		pResource->env(
				m_operandParameter[ operandIter->first ],
				m_operandValue[ operandIter->second ]
				);
	}
	operand.release();

	// SCALE
	vgd::field::EditorRO< Texture::FScaleType > scale = pNode->getFieldRO<Texture::FScaleType>(pNode->getFScale());
	
	Texture::FScaleType::const_iterator scaleIter;
	Texture::FScaleType::const_iterator scaleEnd;
	
	for(	scaleIter = scale->begin(),
			scaleEnd	= scale->end();
			
			scaleIter != scaleEnd;
			
			++scaleIter
			)
	{
		pResource->env(
				m_scaleParameter[ scaleIter->first ],
				scaleIter->second
				);
	}
	scale.release();
}*/



void Texture::synchronize(	vgeGL::engine::Engine * engine, vgd::node::Texture * node,
							::glo::Texture * texture )
{
	if ( engine->isTextureMappingEnabled() == false )
	{
		// Texture mapping is disabled, so do nothing
		// Validates node
		vgd::field::DirtyFlag* pDFNode = node->getDirtyFlag( node->getDFNode() );
		pDFNode->validate();
		return;
	}

	TexInfo	texInfo;

	State state = preSynchronize( engine, node, texture, texInfo );

	const uint texUnit = node->getMultiAttributeIndex();

	if ( state == NOIIMAGE_DIRTY )
	{
		// Nothing to do
		// Validates dirty flags (see the end of this method)
	}
	else if ( state == NOIIMAGE_VALIDATED )
	{
		// Nothing to do
		return;
	}
	else if ( state == IIMAGE_VALIDATED )
	{
		// No synchronization, just uses the texture

		// Activates the desired texture unit
		engine->activeTexture( node );

		//Binds texture to the texture unit
		texture->bind();

		// Texturing is enabled lazily in shape handlers (texture->enable()).

// @todo share with else
		// Updates engine state
		using vgeGL::engine::GLSLState;
		typedef GLSLState::TexUnitState TexUnitState;

		GLSLState& glslState = engine->getGLSLState();

		vgd::Shp< TexUnitState > texUnitState( glslState.getTexture( texUnit ) );
		if ( texUnitState )
		{
			// Updates the existing texture unit state
			texUnitState->setTextureNode( node );
		}
		else
		{
			// Creates the new texture unit state
			texUnitState.reset( new GLSLState::TexUnitState(node, texture) );
			glslState.setTexture( texUnit, texUnitState );
		}
//

		// Updates texture parameters ?
		synchronizeParametersAndEnv( engine, node, texture );
	}
	else
	{
		assert( state == IIMAGE_DIRTY );

		computeTexInfo( engine, node, texture, texInfo );

		// Allocates texture object
		const bool newTexture = texture->isEmpty();

		if ( newTexture )
		{
			// Creates texture object
			texture->generate();
		}
		// else nothing to do texture already created

		// Activates the desired texture unit
		engine->activeTexture( node );

		// Binds the texture object
		texture->bind();

		// Texturing is enabled lazily in shape handlers ( texture->enable();)

// @todo share with if (IIMAGE_VALIDATED)
		// Updates engine state
		using vgeGL::engine::GLSLState;
		typedef GLSLState::TexUnitState TexUnitState;

		GLSLState& glslState = engine->getGLSLState();

		vgd::Shp< TexUnitState > texUnitState( glslState.getTexture( texUnit ) );
		if ( texUnitState )
		{
			// Updates the existing texture unit state
			texUnitState->setTextureNode( node );
		}
		else
		{
			// Creates the new texture unit state
			texUnitState.reset( new GLSLState::TexUnitState(node, texture) );
			glslState.setTexture( texUnit, texUnitState );
		}
//

		const bool isCompatible = isTextureCompatible( engine, node, texture, texInfo );

		// Creates n-dimensionnal texture
		if ( newTexture || !isCompatible )
		{
			// Specifies texture image
			glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

			// Specifies a texture image
			// @todo Support of level-of-detail number
			texture->texImage(	0,	 // level
								texInfo.internalFormat,
								texInfo.texSize[0] /*+ texInfo.borderSize*/,
								texInfo.texSize[1] /*+ texInfo.borderSize*/,
								texInfo.texSize[2] /*+ texInfo.borderSize*/,
								0 /*texInfo.borderSize*/,
								texInfo.format,
								texInfo.type );
		}
		// else nothing to do

		// Updates texture parameters ?
		synchronizeParametersAndEnv( engine, node, texture );

		// Updates texture image
		texSubImage( engine, node, texture, texInfo );
	}

	// Validates node
	vgd::field::DirtyFlag* pDFNode = node->getDirtyFlag( node->getDFNode() );
	pDFNode->validate();

	//assert( node->getDirtyFlag(node->getDFIImages())->isValid() );
	//assert( node->getDirtyFlag(node->getDFParameters())->isValid() );
	//assert( node->getDirtyFlag(node->getDFEnvironmentParameters())->isValid() );
	assert( pDFNode->isValid() );
}



void Texture::texSubImage(	vgeGL::engine::Engine *pGLEngine, vgd::node::Texture *pNode,
							glo::Texture *pTexture,
							TexInfo& texInfo )
{
	const void*	pixels = texInfo.iimage->pixels();
	if ( pixels == 0 )
	{
		// IImage contains no data, then do nothing
		return;
	}

	// Tests if rescaling incoming image must be done and updates texture
	if ( texInfo.resizeForTex )
	{
		// RESCALE IMAGE
		vgDebug::get().logDebug("vgeGL.Texture: Performance warning : Incoming image size %i %i %i used as texture is resized %i %i %i.",
								texInfo.imageSize[0], texInfo.imageSize[1], texInfo.imageSize[2],
								texInfo.texSize[0], texInfo.texSize[1], texInfo.texSize[2] );

		// Creates a copy of the incoming image
		using vgd::basic::Image;

//		Image newImage(	(*texInfo.iimage.get()) );
// or
		vgd::Shp< vgd::basic::IImage > iimage = texInfo.iimage;
		Image newImage(	iimage->width(), iimage->height(), iimage->depth(),
						iimage->format() == Image::COLOR_INDEX ? Image::LUMINANCE : iimage->format(),
						iimage->type(),
						iimage->pixels() );

		newImage.scale( texInfo.texSize, Image::FILTER_SCALE_MITCHELL /*Image::FILTER_SCALE_BOX */ );
		//@todo options for lower-quality filter during rescaling
		//@todo use vgITK::Image to really support any image type

		const void * newPixels = newImage.pixels();

		pTexture->texSubImage(	0,			// level
								0, 0, 0,	// offset
								texInfo.texSize[0], texInfo.texSize[1], texInfo.texSize[2],
								texInfo.format, texInfo.type,
								newPixels );
	}
	else
	{
		// DON'T RESCALE IMAGE
		pTexture->texSubImage(	0,				// level
								0, 0, 0, 		// offset
								texInfo.texSize[0], texInfo.texSize[1], texInfo.texSize[2],
								texInfo.format, texInfo.type, 
								pixels );
	}

	/*vgd::field::DirtyFlag * pDFIImages = pNode->getDirtyFlag( pNode->getDFIImages() );
	pDFIImages->validate();*/
}



Texture::State Texture::preSynchronize(	vgeGL::engine::Engine *pGLEngine, vgd::node::Texture *pNode, ::glo::Texture *pTexture,
										TexInfo& texInfo )
{
	// Creates the return value
	State state;

	// Tests if 'iimage' field is valid
	//vgd::field::DirtyFlag * pDFIImages = pNode->getDirtyFlag( pNode->getDFIImages() );
	vgd::field::DirtyFlag * pDFIImages = pNode->getDirtyFlag( pNode->getDFNode() ); // @todo DFIImages()

	// Gets texture.iimage
	//const bool imageFieldDefined = 	pNode->getIImages( vgd::node::Texture::DEFAULT_IIMAGES, texInfo.iimage );
	const bool imageFieldDefined = pNode->hasImage();
	if ( imageFieldDefined )
	{
		pNode->getImage( texInfo.iimage );
	}

	const bool noImage =	!imageFieldDefined				||
							( texInfo.iimage == 0 )			||
							( (texInfo.iimage != 0 ) && (texInfo.iimage->isEmpty()) );

	// Computes current state
	if ( pDFIImages->isValid() )
	{
		if ( noImage )
		{
			state = NOIIMAGE_VALIDATED;
		}
		else
		{
			state = IIMAGE_VALIDATED;
		}
	}
	else
	{
		if ( noImage )
		{
			state = NOIIMAGE_DIRTY;
		}
		else
		{
			state = IIMAGE_DIRTY;
		}
	}
	
	return state;
}



void Texture::computeTexInfo( vgeGL::engine::Engine *pGLEngine, vgd::node::Texture *pNode, ::glo::Texture * pTexture, TexInfo& texInfo )
{
	assert( texInfo.iimage != 0 );

	computeTexImageParams(	pNode, pTexture, texInfo );
	clampTexImageSize(		pGLEngine, pTexture, texInfo );
}



void Texture::computeTexImageParams( vgd::node::Texture *pNode, ::glo::Texture * pTexture, TexInfo& texInfo )
{
	// Pre-conditions
	assert( pNode != 0 );
	assert( pTexture != 0 );

	assert( texInfo.iimage != 0 );
	assert( texInfo.iimage->isEmpty() == false );

	// Alias on image
	vgd::Shp< vgd::basic::IImage >& image = texInfo.iimage;

/*	// Updates border property
	bool		borderValue		= false;
	const bool	isBorderDefined	= pNode->getBorder( borderValue );

	texInfo.borderSize = borderValue ? 1 : 0;*/

	// Updates image properties
	texInfo.imageSize		= image->getSize3i();
	texInfo.imageSizePOT	= vgm::nextPower2( texInfo.imageSize );
	
	// Computes texture dimension
	texInfo.texDimension = pNode->gethTextureDimension();
	assert( texInfo.texDimension == 1 || texInfo.texDimension == 2 || texInfo.texDimension == 3 );

	boost::tie(texInfo.internalFormat, texInfo.format ) = chooseFormats( image, pNode );
	texInfo.type										= convertMyType2GL( image->type() );

	// Takes care of POT/NPOT image (by using GL_ARB_texture_non_power_of_two or by resizing incoming image)
	// @todo Support of GL_ARB_texture_rectangle
	if ( texInfo.imageSize != texInfo.imageSizePOT )
	{
		// NPOT image
		#ifdef _DEBUG
		//vgDebug::get().logDebug("vgeGL.Texture: Incoming image size %i %i %i (npot)", 
		//						texInfo.imageSize[0], texInfo.imageSize[1], texInfo.imageSize[2] );
		#endif

		if ( isGL_ARB_texture_non_power_of_two() )
		{
			#ifdef _DEBUG
			//vgDebug::get().logDebug("vgeGL.Texture: GL_ARB_texture_non_power_of_two is supported and used.");
			#endif
			texInfo.texSize			= texInfo.imageSize;
			texInfo.resizeForTex	= false;
		}
		else
		{
			#ifdef _DEBUG
			vgDebug::get().logDebug("vgeGL.Texture: Incoming image size %i %i %i (npot)", 
									texInfo.imageSize[0], texInfo.imageSize[1], texInfo.imageSize[2] );
			vgDebug::get().logDebug("vgeGL.Texture: Incoming image must be resized.");
			#endif

			texInfo.texSize			= texInfo.imageSizePOT;
			texInfo.resizeForTex	= true;
		}
	}
	else
	{
		// POT image
		#ifdef _DEBUG
		//vgDebug::get().logDebug("vgeGL.Texture: Incoming image size %i %i %i (pot)",
		//						texInfo.imageSize[0], texInfo.imageSize[1], texInfo.imageSize[2] );
		#endif

		texInfo.texSize			= texInfo.imageSizePOT; //  texInfo.imageSize == texInfo.imageSizePOT
		texInfo.resizeForTex	= false;
	}
}



void Texture::clampTexImageSize( vgeGL::engine::Engine *pGLEngine, ::glo::Texture * pTexture, TexInfo& texInfo )
{
	// Computes texture size limit
	GLint maxTexSize;

	if ( texInfo.texDimension == 3 )
	{
		maxTexSize = pGLEngine->getMax3DTexSize();
	}
	else if ( texInfo.texDimension == 6 )
	{
		maxTexSize = pGLEngine->getMaxCubeMapTexSize();
	}
	else
	{
		assert( texInfo.texDimension == 1 || texInfo.texDimension == 2 );
		maxTexSize = pGLEngine->getMaxTexSize();
	}

	// Computes the clamp
	switch ( texInfo.texDimension )
	{
		case 3:
			if ( texInfo.texSize[2] > maxTexSize )
			{
				texInfo.texSize[2]		= maxTexSize;
				texInfo.resizeForTex	= true;
			}
			// else nothing to do

		case 6:
		case 2:
			if ( texInfo.texSize[1] > maxTexSize )
			{
				texInfo.texSize[1]		= maxTexSize;
				texInfo.resizeForTex	= true;
			}
			// else nothing to do

		case 1:
			if ( texInfo.texSize[0] > maxTexSize )
			{
				texInfo.texSize[0]		= maxTexSize;
				texInfo.resizeForTex	= true;
			}
			// else nothing to do
			break;

		default:
			texInfo.texSize.null();
			vgLogDebug("Texture: Unsupported texture dimension (!= 1, 2, 3, 6)");
			assert( false && "Unsupported texture dimension (!= 1, 2, 3, 6)" );
	}
}



const bool Texture::isTextureCompatible(	vgeGL::engine::Engine *pGLEngine, vgd::node::Texture *pNode, ::glo::Texture * pTexture,
											const TexInfo& texInfo )
{
	const bool isTexSizeCompatible = isTextureSizeCompatible( pTexture, texInfo );

	const bool isTexInternalFormatCompatible = (texInfo.internalFormat == pTexture->getInternalFormat());

	// @todo checks format and type.

	const bool isCompatible = isTexSizeCompatible && isTexInternalFormatCompatible;

	return isCompatible;
}



const bool Texture::isTextureSizeCompatible( ::glo::Texture * pTexture, const TexInfo& texInfo )
{
	// Retrieves texture size
	vgm::Vec3i texSize;
	/*const GLint texBorder = */pTexture->getSize( texSize[0], texSize[1], texSize[2] );

	bool isCompatible =	( texInfo.texSize == texSize ) /*&&
						( texInfo.borderSize == texBorder )*/;

	return isCompatible;
}



void Texture::synchronizeParametersAndEnv(	vgeGL::engine::Engine *pGLEngine, vgd::node::Texture *pNode,
											::glo::Texture *pTexture )
{
	// TEXTURE PARAMETERS
	//vgd::field::DirtyFlag* pDFParameters = pNode->getDirtyFlag( pNode->getDFParameters() );	 // @todo DFParameters
	vgd::field::DirtyFlag* pDFParameters = pNode->getDirtyFlag( pNode->getDFNode() );

	if ( pDFParameters->isDirty() )
	{
		// Activates the desired texture unit
		pGLEngine->activeTexture( pNode );

		// Apply texture parameters
		paintParams( pGLEngine, pNode, pTexture );

		// Validates DF
		//pDFParameters->validate();
	}
	// else nothing to do

	/*// TEXTURE ENVIRONMENT PARAMETERS
	//vgd::field::DirtyFlag* pDFEnvironmentParameters = pNode->getDirtyFlag( pNode->getDFEnvironmentParameters() ); // @todo DFEnvironmentParameters
	vgd::field::DirtyFlag* pDFEnvironmentParameters = pNode->getDirtyFlag( pNode->getDFNode() );

	if ( pDFEnvironmentParameters->isDirty() )
	{
		// Activates the desired texture unit
		pGLEngine->activeTexture( pNode );

		// Apply texture parameters
		//paintEnv( pGLEngine, pNode, pTexture );

		// Validates DF
		pDFEnvironmentParameters->validate();
	}
	// else nothing to do*/

/*	// TEXTURE SCALE (see Scale factors in ::glo::Texture)
	//@todo scale factors could be better done in VertexShape ?
	vgm::Vec3f scaleFactors;
	pTexture->getScaleFactors( scaleFactors[0], scaleFactors[1], scaleFactors[2] );

	if ( scaleFactors != vgm::Vec3f(1.f, 1.f, 1.f) )
	{
		// applies scale to vge
		vgm::MatrixR& textureMatrix( pGLEngine->getTextureMatrix().getTop( pNode->getMultiAttributeIndex() ) );

		textureMatrix.scale( scaleFactors );

		// applies scale to vgeGL
		texInfo.activeTexture( pNode );

		glMatrixMode( GL_TEXTURE );
		glLoadMatrixf( reinterpret_cast<const float*>( textureMatrix.getValue() ) );
	}*/
}



const boost::tuple< GLint, GLenum > Texture::chooseFormats( vgd::Shp< vgd::basic::IImage > iimage, vgd::node::Texture * texture )
{
	// Adapts internal/external format of texture depending of its usage (see Texture.usage)
	vgd::node::Texture::UsageValueType usage = texture->getUsage();

	if ( usage.value() == vgd::node::Texture::SHADOW )
	{
		// Texture is used for shadow
		assert( iimage->components() == 1 && "Texture.usage == SHADOW, but Texture.image.components != 1" );

		const vgd::node::Texture::InternalFormatValueType internalFormat = texture->getInternalFormat();
		const GLenum internalFormatGL = convertInternalFormatToGLInternalFormat( internalFormat, GL_DEPTH_COMPONENT );

// @todo test if internalFormat is a depth format
		return boost::make_tuple( internalFormatGL, GL_DEPTH_COMPONENT );
	}
	else
	{
		assert( usage.value() == vgd::node::Texture::IMAGE && "Unexpected value for usage field." );

		const GLint		components	= iimage->components();
		const GLenum	format		= convertMyFormat2GL( iimage->format() );

		const vgd::node::Texture::InternalFormatValueType internalFormat = texture->getInternalFormat();

		const GLenum internalFormatGL = convertInternalFormatToGLInternalFormat( internalFormat, components );

		return boost::make_tuple( internalFormatGL, format );
	}
}



GLenum Texture::convertMyFormat2GL( const vgd::basic::IImage::Format format )
{
	GLenum glformat;
	
	switch ( format )
	{
		case vgd::basic::IImage::RGB:
			glformat = GL_RGB;
			break;

		case vgd::basic::IImage::RGBA:
			glformat = GL_RGBA;
			break;

		case vgd::basic::IImage::BGR:
			glformat = GL_BGR_EXT;
			break;

		case vgd::basic::IImage::BGRA:
			glformat = GL_BGRA_EXT;
			break;

		case vgd::basic::IImage::LUMINANCE:
		case vgd::basic::IImage::COLOR_INDEX:
			glformat = GL_LUMINANCE;
			break;
			
		case vgd::basic::IImage::LUMINANCE_ALPHA:
			glformat = GL_LUMINANCE_ALPHA;
			break;

		default:
			assert(false && "Unknown or unsupported format." );
			glformat = GL_RGBA;
	}

	return ( glformat );
}



GLenum Texture::convertMyType2GL( const vgd::basic::IImage::Type type )
{
	GLenum gltype;

	switch ( type )
	{
		case vgd::basic::IImage::UINT8:
			gltype = GL_UNSIGNED_BYTE;
			break;

		case vgd::basic::IImage::INT8:
			gltype = GL_BYTE;
			break;

		case vgd::basic::IImage::UINT16:
			gltype = GL_UNSIGNED_SHORT;
			break;

		case vgd::basic::IImage::INT16:
			gltype = GL_SHORT;
			break;

		case vgd::basic::IImage::UINT32:
			gltype = GL_UNSIGNED_INT;
			break;

		case vgd::basic::IImage::INT32:
			gltype = GL_INT;
			break;

		case vgd::basic::IImage::FLOAT:
			gltype = GL_FLOAT;
			break;

		case vgd::basic::IImage::NO_TYPE:
		case vgd::basic::IImage::DOUBLE:
		default:
			assert(false && "Unknown or unsupported type.");
			gltype = GL_UNSIGNED_BYTE;
	}
	
	return ( gltype );
}

		

GLenum Texture::m_wrapParameter[] = {
	GL_TEXTURE_WRAP_S,
	GL_TEXTURE_WRAP_T,
	GL_TEXTURE_WRAP_R 
};



GLint Texture::m_wrapValue[] = {

	GL_REPEAT,
	GL_CLAMP,
	GL_CLAMP_TO_EDGE,	// GL 1.2
	GL_CLAMP_TO_BORDER,	// GL 1.3
	GL_MIRRORED_REPEAT,	// GL 1.4
	GL_CLAMP,			// ONCE @todo FIXME Should be GL_CLAMP_TO_BORDER, but this prevent the maximum intensity texel to be rendered !!!
};



GLenum Texture::m_filterParameter[] = {
	GL_TEXTURE_MIN_FILTER,
	GL_TEXTURE_MAG_FILTER
};



GLint Texture::m_filterValue[] = {

	GL_NEAREST,
	GL_LINEAR,

	GL_NEAREST_MIPMAP_NEAREST,
	GL_LINEAR_MIPMAP_NEAREST,
	GL_NEAREST_MIPMAP_LINEAR,
	GL_LINEAR_MIPMAP_LINEAR
	
};



/*GLint Texture::m_functionValue[] = {

		GL_REPLACE,
		GL_MODULATE, 
		GL_DECAL,
		GL_BLEND,
		GL_ADD,
		GL_COMBINE

};*/



/*GLenum Texture::m_combineParameter[] = {
	
	GL_COMBINE_RGB,
	GL_COMBINE_ALPHA

};



GLint Texture::m_combineValue[] = {

	GL_REPLACE,
	GL_MODULATE,
	GL_ADD,
	GL_ADD_SIGNED,
	GL_INTERPOLATE,
	GL_SUBTRACT,
	GL_DOT3_RGB,
	GL_DOT3_RGBA

};



GLenum Texture::m_sourceParameter[] = {
	
	GL_SRC0_RGB,
	GL_SRC1_RGB,
	GL_SRC2_RGB,
	
	GL_SRC0_ALPHA,
	GL_SRC1_ALPHA,
	GL_SRC2_ALPHA
	
};



GLint Texture::m_sourceValue[] = {
	
	GL_CONSTANT,
	GL_PRIMARY_COLOR,
	GL_PREVIOUS,
	GL_TEXTURE,
	GL_TEXTURE0,
	GL_TEXTURE1,
	GL_TEXTURE2,
	GL_TEXTURE3,
	GL_TEXTURE4,
	GL_TEXTURE5,
	GL_TEXTURE6,
	GL_TEXTURE7,
	GL_TEXTURE8,
	GL_TEXTURE9,
	GL_TEXTURE10,
	GL_TEXTURE11,
	GL_TEXTURE12,
	GL_TEXTURE13,
	GL_TEXTURE14,
	GL_TEXTURE15,
	GL_TEXTURE16,
	GL_TEXTURE17,
	GL_TEXTURE18,
	GL_TEXTURE19,
	GL_TEXTURE20,
	GL_TEXTURE21,
	GL_TEXTURE22,
	GL_TEXTURE23,
	GL_TEXTURE24,
	GL_TEXTURE25,
	GL_TEXTURE26,
	GL_TEXTURE27,
	GL_TEXTURE28,
	GL_TEXTURE29,
	GL_TEXTURE30,
	GL_TEXTURE31

};



GLenum Texture::m_operandParameter[] = {

	GL_OPERAND0_RGB,
	GL_OPERAND1_RGB,
	GL_OPERAND2_RGB,
	
	GL_OPERAND0_ALPHA,
	GL_OPERAND1_ALPHA,
	GL_OPERAND2_ALPHA
	
};



GLint Texture::m_operandValue[] = {

	GL_SRC_COLOR,
	GL_ONE_MINUS_SRC_COLOR,
	GL_SRC_ALPHA,
	GL_ONE_MINUS_SRC_ALPHA

};



GLenum Texture::m_scaleParameter[] = {
	
	GL_RGB_SCALE,
	GL_ALPHA_SCALE

};
*/


/* 	// Rescale image if necessary (boolean value already set if image is too big).
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
			pTexture->setScaleFactors(
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
 */



} // namespace painter

} // namespace handler

} // namespace vgeGL
