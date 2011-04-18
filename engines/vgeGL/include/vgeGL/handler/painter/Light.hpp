// VGSDK - Copyright (C) 2004, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_HANDLER_PAINTER_LIGHT_HPP
#define _VGEGL_HANDLER_PAINTER_LIGHT_HPP

#include <vge/handler/painter/MultiAttribute.hpp>
#include "vgeGL/vgeGL.hpp"

namespace vgd { namespace node { struct Light; } }

namespace vgeGL
{
	namespace engine
	{
		struct Engine;
		struct LightState;
	}

}



namespace vgeGL
{

namespace handler
{

namespace painter
{



/**
 * @brief Send render commands for the Light.
 */
struct VGEGL_API Light : public vge::handler::painter::MultiAttribute
{
	//META_HANDLER_HPP( Light );
	
	void	setToDefaults();

protected:
	void	updateUnitState( vgeGL::engine::Engine * engine, vgd::node::Light * light, vgd::Shp< vgeGL::engine::LightState > lightState );
	void	paint		( vgeGL::engine::Engine*, vgd::node::Light* );
};



} // namespace painter

} // namespace handler

} // namespace vgeGL

#endif //#ifndef _VGEGL_HANDLER_PAINTER_LIGHT_HPP
