// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/handler/painter/Texture.hpp"

#include <glo/Texture.hpp>
#include <vgd/node/Texture.hpp>
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



void Texture::paint(	vgeGL::engine::Engine *pGLEngine, vgd::node::Texture *pNode,
							glo::Texture *pResource )
{
	// WRAP
	vgd::field::EditorRO< vgd::node::Texture::FWrapType > wrap;

	wrap	=	pNode->getFieldRO<vgd::node::Texture::FWrapType>(pNode->getFWrap());
	
	vgd::node::Texture::FWrapType::const_iterator wrapIter;
	vgd::node::Texture::FWrapType::const_iterator wrapEnd;
	
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
	vgd::field::EditorRO< vgd::node::Texture::FFilterType > filter;

	filter	=	pNode->getFieldRO<vgd::node::Texture::FFilterType>(pNode->getFFilter());
	
	vgd::node::Texture::FFilterType::const_iterator filterIter;
	vgd::node::Texture::FFilterType::const_iterator filterEnd;
	
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
	bool bDefined;
	bool bMipmap;
	
	bDefined = pNode->getMipmap( bMipmap );
	
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
	vgd::field::EditorRO< vgd::node::Texture::FFunctionType > function;

	function	=	pNode->getFieldRO<vgd::node::Texture::FFunctionType>(pNode->getFFunction());
	
	vgd::node::Texture::FFunctionType::const_iterator functionIter;
	vgd::node::Texture::FFunctionType::const_iterator functionEnd;
	
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
	vgd::field::EditorRO< vgd::node::Texture::FCombineType > combine;

	combine	=	pNode->getFieldRO<vgd::node::Texture::FCombineType>(pNode->getFCombine());
	
	vgd::node::Texture::FCombineType::const_iterator combineIter;
	vgd::node::Texture::FCombineType::const_iterator combineEnd;
	
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
	vgd::field::EditorRO< vgd::node::Texture::FSourceType > source;

	source	=	pNode->getFieldRO<vgd::node::Texture::FSourceType>(pNode->getFSource());
	
	vgd::node::Texture::FSourceType::const_iterator sourceIter;
	vgd::node::Texture::FSourceType::const_iterator sourceEnd;
	
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
	vgd::field::EditorRO< vgd::node::Texture::FOperandType > operand;

	operand	=	pNode->getFieldRO<vgd::node::Texture::FOperandType>(pNode->getFOperand());
	
	vgd::node::Texture::FOperandType::const_iterator operandIter;
	vgd::node::Texture::FOperandType::const_iterator operandEnd;
	
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
	vgd::field::EditorRO< vgd::node::Texture::FScaleType > scale;

	scale	=	pNode->getFieldRO<vgd::node::Texture::FScaleType>(pNode->getFScale());
	
	vgd::node::Texture::FScaleType::const_iterator scaleIter;
	vgd::node::Texture::FScaleType::const_iterator scaleEnd;
	
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



GLenum Texture::convertMyFormat2GL( vgd::basic::IImage::Format format ) const
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



GLenum Texture::convertMyType2GL( vgd::basic::IImage::Type type ) const
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
	GL_CLAMP_TO_EDGE,		// GL 1.2
	GL_CLAMP_TO_BORDER,	// GL 1.3
	GL_MIRRORED_REPEAT,	// GL 1.4
	GL_CLAMP,				// ONCE
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
