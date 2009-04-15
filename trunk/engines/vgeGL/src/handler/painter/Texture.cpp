// VGSDK - Copyright (C) 2004, 2007, 2008, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/Texture.hpp"

#include <glo/Texture.hpp>
#include <vgd/basic/Image.hpp>
#include <vgd/field/DirtyFlag.hpp>
#include <vgd/node/Texture.hpp>
#include <vgDebug/Global.hpp>
#include <vgm/VectorOperations.hpp>

#include "vgeGL/engine/Engine.hpp"



namespace vgeGL
{

namespace handler
{

namespace painter
{



void Texture::setToDefaults()
{}



void Texture::paint(vgeGL::engine::Engine *pEngine, vgd::node::Texture *pNode, glo::Texture *pResource )
{
	paintParams(	pEngine, pNode, pResource );
	paintEnv(		pEngine, pNode, pResource );
}



void Texture::paintParams(vgeGL::engine::Engine *pEngine, vgd::node::Texture *pNode, glo::Texture *pResource )
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
				m_wrapParameter[ wrapIter->first ],
				m_wrapValue[ wrapIter->second ]
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
				m_filterParameter[ filterIter->first ],
				m_filterValue[ filterIter->second ]
				);
	}	
	filter.release();

	// MIPMAP
	bool bMipmap;
	bool bDefined = pNode->getMipmap( bMipmap );

	if ( bDefined )
	{
		if ( isGL_SGIS_generate_mipmap() )
		{
			#ifdef _DEBUG
			vgDebug::get().logDebug("vgeGL.Texture: GL_SGIS_generate_mipmap detected and used.");
			#endif

			pResource->parameter(
				GL_GENERATE_MIPMAP, bMipmap );
		}
		else
		{
			#ifdef _DEBUG
			vgDebug::get().logDebug("vgeGL.Texture: GL_SGIS_generate_mipmap not detected, try software mipmap later.");
			#endif
		}
	}

	// BORDER_COLOR
	vgm::Vec4f v4;
	bDefined = pNode->getBorderColor( v4 );

	if ( bDefined )
	{
		pResource->parameter(
			GL_TEXTURE_BORDER_COLOR, v4.getValue() );
	}
}



void Texture::paintEnv( vgeGL::engine::Engine *pEngine, vgd::node::Texture *pNode, glo::Texture *pResource )
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
	}

	// FUNCTION
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
				m_functionValue[ functionIter->second ]
				);
	}	
	function.release();
	
	// COMBINE
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
}



void Texture::synchronize(	vgeGL::engine::Engine * pGLEngine, vgd::node::Texture * pNode,
							::glo::Texture * pTexture )
{
	TexInfo	texInfo;

	State	state = preSynchronize( pGLEngine, pNode, pTexture, texInfo );

	if ( state  == NOIIMAGE_VALIDATED )
	{
		// Nothing to do

		// // Disables texturing
		// pTexture->disable();

		return;
	}
	else if ( state == IIMAGE_VALIDATED )
	{
		// No synchronization, just uses the texture

		// Activates the desired texture unit
		pGLEngine->activeTexture( pNode );

		//Binds texture to the texture unit
		pTexture->bind();

		// Texturing is enabled lazily in shape handlers (pTexture->enable()).

		// Updates engine state about texture
		typedef vgeGL::engine::GLSLState::TexUnitState TexUnitState;

		vgd::Shp< TexUnitState > texUnitState( new TexUnitState(pNode, pTexture) );
		pGLEngine->getGLSLState().setTexture( pNode->getMultiAttributeIndex(), texUnitState );

		// Updates texture parameters ?
		synchronizeParametersAndEnv( pGLEngine, pNode, pTexture );
	}
	else
	{
		assert( state == NEW_IIMAGE );

		computeTexInfo( pGLEngine, pNode, pTexture, texInfo );

		// Allocates texture object
		const bool newTexture = pTexture->isEmpty();

		if ( newTexture )
		{
			// Creates texture object
			pTexture->generate();
		}
		// else nothing to do texture already created

		// Activates the desired texture unit
		pGLEngine->activeTexture( pNode );

		// Binds the texture object
		pTexture->bind();

		// Texturing is enabled lazily in shape handlers ( pTexture->enable();)

		// Updates engine state about texture
		typedef vgeGL::engine::GLSLState::TexUnitState TexUnitState;

		vgd::Shp< TexUnitState > texUnitState( new TexUnitState(pNode, pTexture) );
		pGLEngine->getGLSLState().setTexture( pNode->getMultiAttributeIndex(), texUnitState );

		const bool isCompatible = isTextureCompatible( pGLEngine, pNode, pTexture, texInfo );

		// Creates n-dimensionnal texture
		if ( newTexture || !isCompatible )
		{
			// Specifies texture image
			glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

			// Specifies a texture image
			// @todo Support of level-of-detail number
			pTexture->texImage(	0,	 // level
								texInfo.internalFormat,
								texInfo.texSize[0] + texInfo.borderSize,
								texInfo.texSize[1] + texInfo.borderSize,
								texInfo.texSize[2] + texInfo.borderSize,
								texInfo.borderSize,
								texInfo.format,
								texInfo.type	);
		}
		// else nothing to do

		// Updates texture parameters ?
		synchronizeParametersAndEnv( pGLEngine, pNode, pTexture );

		// Updates texture image
		texSubImage( pGLEngine, pNode, pTexture, texInfo );
	}

	// Validates node
	vgd::field::DirtyFlag* pDFNode = pNode->getDirtyFlag( pNode->getDFNode() );
	pDFNode->validate();

	assert( pNode->getDirtyFlag(pNode->getDFIImages())->isValid() );
	assert( pNode->getDirtyFlag(pNode->getDFParameters())->isValid() );
	assert( pNode->getDirtyFlag(pNode->getDFEnvironmentParameters())->isValid() );
	assert( pDFNode->isValid() );
}



void Texture::texSubImage(	vgeGL::engine::Engine *pGLEngine, vgd::node::Texture *pNode,
							glo::Texture *pTexture,
							TexInfo& texInfo )
{
	using vgd::node::Texture;

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
		const void*	pixels = texInfo.iimage->pixels();
		
		pTexture->texSubImage(	0,				// level
								0, 0, 0, 		// offset
								texInfo.texSize[0], texInfo.texSize[1], texInfo.texSize[2],
								texInfo.format, texInfo.type, 
								pixels );
	}

	vgd::field::DirtyFlag * pDFIImages = pNode->getDirtyFlag( pNode->getDFIImages() );
	pDFIImages->validate();
}



Texture::State Texture::preSynchronize(	vgeGL::engine::Engine *pGLEngine, vgd::node::Texture *pNode, ::glo::Texture *pTexture,
										TexInfo& texInfo )
{
	// Creates the return value
	State state;

	// Tests if 'iimage' field is valid
	vgd::field::DirtyFlag * pDFIImages = pNode->getDirtyFlag( pNode->getDFIImages() );

	// Gets texture.iimage
	const bool imageFieldDefined = 	pNode->getIImages( vgd::node::Texture::DEFAULT_IIMAGES, texInfo.iimage );

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
		state = NEW_IIMAGE;
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

	// Updates border property
	bool		borderValue		= false;
	const bool	isBorderDefined	= pNode->getBorder( borderValue );

	texInfo.borderSize = borderValue ? 1 : 0;

	// Updates image properties
	texInfo.imageSize		= image->getSize3i();
	texInfo.imageSizePOT	= vgm::nextPower2( texInfo.imageSize );
	
	// Computes texture dimension
	texInfo.texDimension = pNode->gethTextureDimension();
	assert( texInfo.texDimension == 1 || texInfo.texDimension == 2 || texInfo.texDimension == 3 );

	// @todo chooseInternalFormat( m_pIImage->format(), m_pIImage->type(), texture->getHints() ).
	texInfo.internalFormat	= static_cast< GLint >( image->components() );
	texInfo.format			= convertMyFormat2GL( image->format() );
	texInfo.type			= convertMyType2GL	( image->type()	);

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
			vgDebug::get().logDebug("Texture: Unsupported texture dimension (!= 1, 2, 3, 6)");
			assert( false && "Unsupported texture dimension (!= 1, 2, 3, 6)" );
	}
}



const bool Texture::isTextureCompatible(	vgeGL::engine::Engine *pGLEngine, vgd::node::Texture *pNode, ::glo::Texture * pTexture,
											const TexInfo& texInfo )
{
	const bool isTexSizeCompatible = isTextureSizeCompatible( pTexture, texInfo );
	// @todo checks format, type and internalFormat

	const bool isCompatible = isTexSizeCompatible;
	
	return isCompatible;
}



const bool Texture::isTextureSizeCompatible( ::glo::Texture * pTexture, const TexInfo& texInfo )
{
	// Retrieves texture size
	vgm::Vec3i texSize;
	const GLint texBorder = pTexture->getSize( texSize[0], texSize[1], texSize[2] );

	bool isCompatible =	( texInfo.texSize == texSize ) &&
						( texInfo.borderSize == texBorder );

	return isCompatible;
}



void Texture::synchronizeParametersAndEnv(	vgeGL::engine::Engine *pGLEngine, vgd::node::Texture *pNode,
											::glo::Texture *pTexture )
{
	// TEXTURE PARAMETERS
	vgd::field::DirtyFlag* pDFParameters = pNode->getDirtyFlag( pNode->getDFParameters() );	

	if ( pDFParameters->isDirty() )
	{
		// Activates the desired texture unit
		pGLEngine->activeTexture( pNode );

		// Apply texture parameters
		paintParams( pGLEngine, pNode, pTexture );

		// Validates DF
		pDFParameters->validate();
	}
	// else nothing to do

	// TEXTURE ENVIRONMENT PARAMETERS
	vgd::field::DirtyFlag* pDFEnvironmentParameters = pNode->getDirtyFlag( pNode->getDFEnvironmentParameters() );

	if ( pDFEnvironmentParameters->isDirty() )
	{
		// Activates the desired texture unit
		pGLEngine->activeTexture( pNode );

		// Apply texture parameters
		paintEnv( pGLEngine, pNode, pTexture );

		// Validates DF
		pDFEnvironmentParameters->validate();
	}
	// else nothing to do

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



GLint Texture::m_functionValue[] = {

		GL_REPLACE,
		GL_MODULATE, 
		GL_DECAL,
		GL_BLEND,
		GL_ADD,
		GL_COMBINE

};



GLenum Texture::m_combineParameter[] = {
	
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
