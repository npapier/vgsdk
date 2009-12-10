// VGSDK - Copyright (C) 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_HANDLER_PAINTER_TEXGENEYELINEAR_HPP
#define _VGEGL_HANDLER_PAINTER_TEXGENEYELINEAR_HPP

#include "vgeGL/handler/painter/TexGen.hpp"

namespace vgd { namespace node { struct TexGenEyeLinear; } }



namespace vgeGL
{

namespace handler
{

namespace painter
{



/**
 * @brief Handler for TexGenEyeLinear node
 */
struct VGEGL_API TexGenEyeLinear : public vgeGL::handler::painter::TexGen
{
	META_HANDLER_HPP( TexGenEyeLinear );

	const TargetVector getTargets() const;

	void apply( vge::engine::Engine*, vgd::node::Node* );
	void unapply( vge::engine::Engine*, vgd::node::Node* );

	void setToDefaults();

	void paint( vgeGL::engine::Engine*, vgd::node::TexGenEyeLinear* );
};



} // namespace painter

} // namespace handler

} // namespace vgeGL

#endif //#ifndef _VGEGL_HANDLER_PAINTER_TEXGENEYELINEAR_HPP
