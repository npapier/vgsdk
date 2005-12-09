// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_HANDLER_PAINTER_TEXTURE_H
#define _VGEGL_HANDLER_PAINTER_TEXTURE_H

#include <vgd/basic/IImage.hpp>
#include <vge/handler/painter/MultiAttribute.hpp>

#include "vgeGL/vgeGL.hpp"

namespace glo
{
	struct Texture;
}

namespace vgd
{
	namespace field
	{
		struct DirtyFlag;
	}
	
	namespace node
	{
		struct Texture;
	}
}

namespace vgeGL
{
	namespace engine
	{
		struct Engine;
	}
	
	namespace rc
	{
		struct Texture;
	}
}



namespace vgeGL
{
	
namespace handler
{

namespace painter
{


/**
 * @brief Send render commands for the Texture node
 * 
 * @todo Shared more source code between Texture1D, 2D... (see TexturexD::synchronize(), TexturexD::texSubImage())
 * @todo Support Texture1D resize (for ONCE parameters)
 * @todo Optimize convertMy*2GL() using a table.
 */
struct VGEGL_API Texture : public vge::handler::painter::MultiAttribute
{
	void	setToDefaults();

	void	paint( vgeGL::engine::Engine*, vgd::node::Texture*, glo::Texture* );

	/**
	 * @brief Convert IImage format to the OpenGL equivalent format.
	 */
	static GLenum convertMyFormat2GL( vgd::basic::IImage::Format format );
	
	/**
	 * @brief Convert IImage type to the OpenGL equivalent type.
	 */
	static GLenum convertMyType2GL( vgd::basic::IImage::Type type );
	
	
protected:
	/**
	 * @name Data initialized by preSynchronize()
	 */
	//@{

	vgd::field::DirtyFlag*			m_pDFIImages;
	bool							m_isImageDefined;
	vgd::Shp< vgd::basic::IImage >	m_pIImage;
	
	// the following attributes are only initialized if preSynchronize has returned false
	vgm::Vec3i	m_imageSize;
	vgm::Vec3i	m_imageSizePOT;
	
	int32	m_components;
	GLenum	m_format;
	GLenum	m_type;

	vgm::Vec3i	m_texSize;
	bool		m_bResize;
	//@}

	/**
	 * @brief Switch to the specified tex unit and creates rc/tex
	 * 
	 * @return true when image/texture are synchronized, false if not.
	 * 
	 * @todo takes care of texture and image format...
	 */
	const bool preSynchronize(	vgeGL::engine::Engine *pGLEngine, vgd::node::Texture *pNode,
								::glo::Texture *pTexture );
								
	void synchronizeParameters(	vgeGL::engine::Engine *pGLEngine, vgd::node::Texture *pNode,
								::glo::Texture *pTexture );
								
private:
	static GLenum	m_wrapParameter[];
	static GLint	m_wrapValue[];
	
	static GLenum	m_filterParameter[];
	static GLint	m_filterValue[];
	
	static GLint	m_functionValue[];
	
	static GLenum	m_combineParameter[];
	static GLint	m_combineValue[];
	
	static GLenum	m_sourceParameter[];
	static GLint	m_sourceValue[];
	
	static GLenum	m_operandParameter[];
	static GLint	m_operandValue[];

	static GLenum	m_scaleParameter[];								
};



} // namespace painter

} // namespace handler

} // namespace vgeGL

#endif //#ifndef _VGEGL_HANDLER_PAINTER_TEXTURE_H
