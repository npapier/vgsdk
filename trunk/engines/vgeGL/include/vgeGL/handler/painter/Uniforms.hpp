// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_HANDLER_PAINTER_UNIFORMS_HPP
#define _VGEGL_HANDLER_PAINTER_UNIFORMS_HPP

#include <vge/handler/painter/SingleAttribute.hpp>
#include "vgeGL/vgeGL.hpp"

namespace vgd { namespace node { struct Uniforms; } }

namespace vgeGL { namespace engine { struct Engine; } }



namespace vgeGL
{

namespace handler
{

namespace painter
{



/**
 * @brief Implements painting service for Uniforms node
 */
struct VGEGL_API Uniforms : public vge::handler::painter::SingleAttribute
{
	META_HANDLER_HPP( Uniforms  );

	const TargetVector getTargets() const;

	void apply	( vge::engine::Engine*, vgd::node::Node* );
	void unapply( vge::engine::Engine*, vgd::node::Node* );

	void setToDefaults();
};



} // namespace painter

} // namespace handler

} // namespace vgeGL

#endif //#ifndef _VGEGL_HANDLER_PAINTER_UNIFORMS_HPP
