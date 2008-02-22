// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_HANDLER_PAINTER_DIRECTIONALLIGHT_HPP
#define _VGEGL_HANDLER_PAINTER_DIRECTIONALLIGHT_HPP

#include "vgeGL/vgeGL.hpp"

namespace vgd
{
	namespace node
	{
		struct DirectionalLight;
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

#include "vgeGL/handler/painter/Light.hpp"



namespace vgeGL
{
	
namespace handler
{

namespace painter
{


/**
 * @brief Send render commands for the directional light.
 */
struct VGEGL_API DirectionalLight : public vgeGL::handler::painter::Light
{
	META_HANDLER_HPP( DirectionalLight );

	const TargetVector					getTargets()	const;

	void	apply		( vge::engine::Engine*, vgd::node::Node* );
	void	unapply	( vge::engine::Engine*, vgd::node::Node* );

	void	setToDefaults();	
	
	void	paint(	vgeGL::engine::Engine *pEngine, vgd::node::DirectionalLight *pDirectionalLight );
};



} // namespace painter

} // namespace handler

} // namespace vgeGL

#endif //#ifndef _VGEGL_HANDLER_PAINTER_DIRECTIONALLIGHT_HPP
