// VGSDK - Copyright (C) 2004, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_HANDLER_PAINTER_CLEARFRAMEBUFFER_HPP
#define _VGEGL_HANDLER_PAINTER_CLEARFRAMEBUFFER_HPP

#include "vgeGL/vgeGL.hpp"
#include <vge/handler/painter/SingleAttribute.hpp>
#include "vgeGL/engine/Engine.hpp"

namespace vgd
{
	namespace node
	{
		struct ClearFrameBuffer;
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
		struct DisplayList;
	}
}



namespace vgeGL
{

namespace handler
{

namespace painter
{



/**
 * @brief Send render commands for the frame buffer.
 */
struct VGEGL_API ClearFrameBuffer : public vge::handler::painter::SingleAttribute
{
	META_HANDLER_HPP( ClearFrameBuffer );

	const TargetVector					getTargets()	const;

	void	apply	( vge::engine::Engine*, vgd::node::Node* );
	void	unapply	( vge::engine::Engine*, vgd::node::Node* );

	void	setToDefaults();
	
	void	paint	( vgeGL::engine::Engine*, vgd::node::ClearFrameBuffer* );

	static void applyBufferUsagePolicy( const vge::engine::BufferUsagePolicy policy, vgd::Shp< glo::FrameBufferObject > fbo );
};



} // namespace painter

} // namespace handler

} // namespace vgeGL

#endif //#ifndef _VGEGL_HANDLER_PAINTER_CLEARFRAMEBUFFER_HPP
