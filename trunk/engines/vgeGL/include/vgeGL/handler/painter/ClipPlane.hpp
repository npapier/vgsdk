// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_HANDLER_PAINTER_CLIPPLANE_HPP
#define _VGEGL_HANDLER_PAINTER_CLIPPLANE_HPP

#include <vge/handler/painter/MultiAttribute.hpp>
#include "vgeGL/vgeGL.hpp"

namespace vgd { namespace node { struct ClipPlane; } }

namespace vgeGL 
{
	namespace engine	{ struct Engine;		}
}



namespace vgeGL
{

namespace handler
{

namespace painter
{



/**
 * @brief Handler for ClipPlane node.
 */
struct VGEGL_API ClipPlane : public vge::handler::painter::MultiAttribute
{
	META_HANDLER_HPP( ClipPlane );

	const TargetVector getTargets() const;

	void apply( vge::engine::Engine*, vgd::node::Node* );
	void unapply( vge::engine::Engine*, vgd::node::Node* );

	void setToDefaults();

	void paint( vgeGL::engine::Engine*, vgd::node::ClipPlane* );
};



} // namespace painter

} // namespace handler

} // namespace vgeGL

#endif //#ifndef _VGEGL_HANDLER_PAINTER_CLIPPLANE_HPP
