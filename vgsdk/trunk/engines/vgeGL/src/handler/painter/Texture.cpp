// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/Texture.hpp"

#include <glo/Texture.hpp>
#include <vgd/field/DirtyFlag.hpp>
#include <vgd/node/Texture.hpp>
#include <vgm/Utilities.hpp>
#include <vgm/Vector.hpp>

#include "vgeGL/engine/Engine.hpp"



namespace vgeGL
{

namespace handler
{

namespace painter
{



void Texture::setToDefaults()
{
}



void Texture::paint(vgeGL::engine::Engine *, vgd::node::Texture *pNode, glo::Texture *pResource )
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
		pResource->parameter(
			GL_GENERATE_MIPMAP, bMipmap );
	}
	
	// BORDER
	vgm::Vec4f v4;
	bDefined = pNode->getBorder( v4 );
	
	if ( bDefined )
	{
		pResource->parameter(
			GL_TEXTURE_BORDER_COLOR, v4.getValue() );
	}

	// ENV_COLOR
	bDefined = pNode->getEnvColor( v4 );
	
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



const bool Texture::preSynchronize(	vgeGL::engine::Engine *pGLEngine, vgd::node::Texture *pNode,
									::glo::Texture *pTexture )
{
	// activate the desired texture unit.
	pTexture->active( GL_TEXTURE0_ARB + pNode->getMultiAttributeIndex() );

	// Tests if 'iimage' field is valid ?
	m_pDFIImages = pNode->getDirtyFlag( pNode->getDFIImages() );
	
	if ( m_pDFIImages->isValid() )
	{
		// Nothing to do, because texture is already created and synchronized.
		return true;
	}

	// gets IImage
	const bool imageFieldDefined = 	pNode->getIImages( vgd::node::Texture::DEFAULT_IIMAGES, m_pIImage );

	m_isImageDefined =	imageFieldDefined	&&
						(m_pIImage != 0) &&
						(!m_pIImage->isEmpty());

	if ( !m_isImageDefined )
	{
		// Nothing to do, because iimage is not defined.
		m_pDFIImages->validate();
		return true;
	}

	// updates imageSize and imageSizePOT.
	m_imageSize[0]	= m_pIImage->width();
	m_imageSize[1]	= m_pIImage->height();
	m_imageSize[2]	= m_pIImage->depth();
	
	const int32 textureDimension = pNode->gethTextureDimension();
	assert( textureDimension == 1 || textureDimension == 2 || textureDimension == 3 );

	m_imageSizePOT[0] = vgm::Utilities::nextPower2( m_imageSize[0] );
	m_imageSizePOT[1] = vgm::Utilities::nextPower2( m_imageSize[1] );
	m_imageSizePOT[2] = vgm::Utilities::nextPower2( m_imageSize[2] );

	m_components	= m_pIImage->components();
	m_format		= convertMyFormat2GL( m_pIImage->format() );
	m_type			= convertMyType2GL( m_pIImage->type() );
	
	// Creates or recycles glo::Texture* ?
	bool m_bUseGLTexImage;

	if ( pTexture->isEmpty() )
	{
		// creates
		pTexture->generate();
		pTexture->bind();
		
		m_bUseGLTexImage = true;
	}
	else
	{
		// recycles
		pTexture->bind();
		
		pTexture->getSize( m_texSize[0], m_texSize[1], m_texSize[2] );

		// FIXME take care of texture and image format.
		m_bUseGLTexImage = false;
		
		switch ( textureDimension )
		{
			case 3:
				// same size (at least) between already initialized texture and m_imageSizePOT, so reuses texture.
				m_bUseGLTexImage = m_bUseGLTexImage || (m_imageSizePOT[2] > m_texSize[2]);

			case 2:
				m_bUseGLTexImage = m_bUseGLTexImage || (m_imageSizePOT[1] > m_texSize[1]);
				
			case 1:
				m_bUseGLTexImage = m_bUseGLTexImage || (m_imageSizePOT[0] > m_texSize[0]);			
				break;
		
			default:
				assert( false && "Unsupported texture dimension (!= 1,2,3)" );
		}
	}
	
	// creates n-dimensionnal texture (glTexImageXD)
	if ( m_bUseGLTexImage )
	{
		// border
		vgm::Vec4f	borderValue;
		bool		bHasBorder = pNode->getBorder( borderValue );
		
		int32		borderSize = bHasBorder ? 2 : 0;

		// size
		assert( textureDimension == 1 || textureDimension == 2 || textureDimension == 3 );
		
		GLint maxTexSize;
		
		if ( textureDimension == 3 )
		{
			maxTexSize = pGLEngine->getMax3DTexSize();
		}
		else
		{
			maxTexSize = pGLEngine->getMaxTexSize();
		}

		// image exceed max texture size ?
		switch ( textureDimension )
		{
			case 3:
				if ( m_imageSizePOT[2] > maxTexSize )
				{
					m_texSize[2]	= maxTexSize;
					m_bResize		= true;
				}
				else
				{
					m_texSize[2]	= m_imageSizePOT[2];
					m_bResize		= false;
				}

			case 2:
				if ( m_imageSizePOT[1] > maxTexSize )
				{
					m_texSize[1]	= maxTexSize;
					m_bResize		= true;
				}
				else
				{
					m_texSize[1]	= m_imageSizePOT[1];
					m_bResize		= false;					
				}

			case 1:
				if ( m_imageSizePOT[0] > maxTexSize )
				{
					m_texSize[0]	= maxTexSize;
					m_bResize		= true;
				}
				else
				{
					m_texSize[0]	= m_imageSizePOT[0];
					m_bResize		= false;		
				}
				break;
		
			default:
				m_texSize[0] = m_texSize[1] = m_texSize[2] = 0;
				assert( false && "Unsupported texture dimension (!= 1,2,3)" );
		}

		// Specifies texture image
		glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

		pTexture->texImage(	0,
							m_components,		// @todo internalFormat
							m_texSize[0] + borderSize, m_texSize[1] + borderSize, m_texSize[2] + borderSize,
							bHasBorder ? 1 : 0,
							m_format,
							m_type	);
	}
	
	return false;
}



void Texture::synchronizeParameters(vgeGL::engine::Engine *pGLEngine, vgd::node::Texture *pNode,
									::glo::Texture *pTexture )
{
	if ( m_isImageDefined )
	{
		// bind texture to the texture unit.
		pTexture->bind();
	
		// enable texturing.							// FIXME should be done in VertexShape ? (for beiing done once).
		pTexture->enable();
	}

	// TEXTURE PARAMETERS
	vgd::field::DirtyFlag* pDFParameters = pNode->getDirtyFlag( pNode->getDFParameters() );	

	if ( pDFParameters->isDirty() )
	{
		// Apply texture parameters.
		paint( pGLEngine, pNode, pTexture );
		
		// Validate DF
		pDFParameters->validate();
	}
	// else nothing to do

	
	
	// TEXTURE SCALE (see scaleFactors)
	// FIXME scale factors could be better done in VertexShape ?
	vgm::Vec3f scaleFactors;
	pTexture->getScaleFactors( scaleFactors[0], scaleFactors[1], scaleFactors[2] );
	
	if ( scaleFactors != vgm::Vec3f(1.f, 1.f, 1.f) )
	{
		// apply scale to vge.
		vgm::MatrixR& textureMatrix(
			pGLEngine->getTextureMatrix().getTop( pNode->getMultiAttributeIndex() )
				);

		const bool isIdentity = textureMatrix.isIdentity();
		
		if ( isIdentity )
		{
			textureMatrix.setScale( scaleFactors );
		}
		else
		{
			// FIXME use textureMatrix.scale()
			vgm::MatrixR scaleMatrix;
			scaleMatrix.setScale( scaleFactors );

			textureMatrix = scaleMatrix * textureMatrix;
		}
		
		// apply scale to vgeGL.
		glMatrixMode( GL_TEXTURE );
		glLoadMatrixf( reinterpret_cast<const float*>( textureMatrix.getValue() ) );
	}
	
	// Validate node
	vgd::field::DirtyFlag* pDFNode = pNode->getDirtyFlag( pNode->getDFNode() );	
	pDFNode->validate();
}



GLenum Texture::convertMyFormat2GL( vgd::basic::IImage::Format format )
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



GLenum Texture::convertMyType2GL( vgd::basic::IImage::Type type )
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



} // namespace painter

} // namespace handler

} // namespace vgeGL
