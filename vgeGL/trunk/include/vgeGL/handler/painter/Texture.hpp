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
 * @todo Optimize convertMy*2GL() using a table.
 */
struct VGEGL_API Texture : public vge::handler::painter::MultiAttribute
{
	void	setToDefaults	();
	
	void	paint				( vgeGL::engine::Engine*, vgd::node::Texture*, glo::Texture* );



protected:
	/**
	 * @brief Convert IImage format to the OpenGL equivalent format.
	 */
	GLenum convertMyFormat2GL( vgd::basic::IImage::Format format ) const;
	
	/**
	 * @brief Convert IImage type to the OpenGL equivalent type.
	 */
	GLenum convertMyType2GL( vgd::basic::IImage::Type type ) const;



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
