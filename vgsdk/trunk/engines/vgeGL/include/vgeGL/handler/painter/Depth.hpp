// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_HANDLER_PAINTER_DEPTH_H
#define _VGEGL_HANDLER_PAINTER_DEPTH_H

#include <vge/handler/painter/SingleAttribute.hpp>

#include "vgeGL/vgeGL.hpp"

namespace vgd
{
	namespace node
	{
		struct Depth;
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
 * @brief Send render commands for the Depth node.
 */
struct VGEGL_API Depth : public vge::handler::painter::SingleAttribute
{
	META_HANDLER_HPP( Depth );

	const TargetVector	getTargets()	const;

	void	apply				( vge::engine::Engine*, vgd::node::Node* );
	void	unapply			( vge::engine::Engine*, vgd::node::Node* );
	
	void	setToDefaults	();
	
	void	paint				( vgeGL::engine::Engine*, vgd::node::Depth* );
	
private:
	static GLenum	m_functionParameter[];
};



} // namespace painter

} // namespace handler

} // namespace vgeGL

#endif //#ifndef _VGEGL_HANDLER_PAINTER_DEPTH_H
