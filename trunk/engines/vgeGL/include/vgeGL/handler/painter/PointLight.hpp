// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_HANDLER_PAINTER_POINTLIGHT_HPP
#define _VGEGL_HANDLER_PAINTER_POINTLIGHT_HPP

#include "vgeGL/vgeGL.hpp"

#include "vgeGL/handler/painter/Light.hpp"

namespace vgd
{
	namespace node
	{
		struct PointLight;
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
 * @brief Send render commands for the PointLight node.
 */
struct VGEGL_API PointLight : public vgeGL::handler::painter::Light
{
	META_HANDLER_HPP( PointLight );

	const TargetVector					getTargets()	const;

	void	apply		( vge::engine::Engine*, vgd::node::Node* );
	void	unapply	( vge::engine::Engine*, vgd::node::Node* );

	void	setToDefaults();	
	
	void	paint(	vgeGL::engine::Engine *pEngine, vgd::node::PointLight *pPointLight );
};



} // namespace painter

} // namespace handler

} // namespace vgeGL

#endif //#ifndef _VGEGL_HANDLER_PAINTER_POINTLIGHT_HPP
