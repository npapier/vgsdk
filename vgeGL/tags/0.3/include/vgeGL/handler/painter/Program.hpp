// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_HANDLER_PAINTER_PROGRAM_H
#define _VGEGL_HANDLER_PAINTER_PROGRAM_H

#include "vgeGL/vgeGL.hpp"

#include <vge/handler/painter/MultiAttribute.hpp>

namespace vgd
{
	namespace node
	{
		struct Program;
	}
}

namespace vgeGL
{
	namespace engine
	{
		struct Engine;
	}
}



namespace vgeGL
{
	
namespace handler
{

namespace painter
{

/**
 * @brief Send render commands for the Program.
 */
struct VGEGL_API Program : public vge::handler::painter::MultiAttribute
{
	META_HANDLER_HPP( Program  );

	const TargetVector	getTargets()	const;

	void	apply				( vge::engine::Engine*, vgd::node::Node* );
	void	unapply			( vge::engine::Engine*, vgd::node::Node* );
	
	void	setToDefaults	();
	
	void synchronize	( vgeGL::engine::Engine* pGLEngine, vgd::node::Program* pNode, vgeGL::rc::GLSLShader* pGLResource );
	void bind			( vgeGL::engine::Engine* pGLEngine, vgd::node::Program* pNode, vgeGL::rc::GLSLShader* pGLResource );
};



} // namespace painter

} // namespace handler

} // namespace vgeGL

#endif //#ifndef _VGEGL_HANDLER_PAINTER_PROGRAM_H
