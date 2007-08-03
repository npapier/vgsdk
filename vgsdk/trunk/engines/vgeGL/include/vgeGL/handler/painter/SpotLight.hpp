// VGSDK - Copyright (C) 2004, 2006, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_HANDLER_PAINTER_SPOTLIGHT_HPP
#define _VGEGL_HANDLER_PAINTER_SPOTLIGHT_HPP

#include "vgeGL/vgeGL.hpp"
#include "vgeGL/handler/painter/PointLight.hpp"

namespace vgd
{
	namespace node
	{
		struct SpotLight;
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
 * @brief Send render commands for the spot light.
 */
struct VGEGL_API SpotLight : public vgeGL::handler::painter::PointLight
{
	META_HANDLER_HPP( SpotLight );

	const TargetVector getTargets()	const;

	void	apply	( vge::engine::Engine*, vgd::node::Node* );
	void	unapply	( vge::engine::Engine*, vgd::node::Node* );

	void	setToDefaults();	
	
	void	paint(	vgeGL::engine::Engine *pEngine, vgd::node::SpotLight *pSpotLight );
};



} // namespace painter

} // namespace handler

} // namespace vgeGL

#endif //#ifndef _VGEGL_HANDLER_PAINTER_SPOTLIGHT_HPP
