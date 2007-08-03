// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_HANDLER_PAINTER_LIGHT_H
#define _VGEGL_HANDLER_PAINTER_LIGHT_H

#include "vgeGL/vgeGL.hpp"

namespace vgd
{
namespace node
{
	struct Light;
}
}
#include <vge/handler/painter/MultiAttribute.hpp>
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
 * @brief Send render commands for the Light.
 */
struct VGEGL_API Light : public vge::handler::painter::MultiAttribute
{
	//META_HANDLER_HPP( Light );
	
	void	setToDefaults();

protected:
	void		paint		( vgeGL::engine::Engine*, vgd::node::Light* );
};



} // namespace painter

} // namespace handler

} // namespace vgeGL

#endif //#ifndef _VGEGL_HANDLER_PAINTER_LIGHT_H
