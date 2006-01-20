// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_HANDLER_DRAWSTYLE_H
#define _VGEGL_HANDLER_DRAWSTYLE_H

#include "vgeGL/vgeGL.hpp"

#include <vge/handler/painter/SingleAttribute.hpp>

namespace vgd
{
	namespace node
	{
		struct DrawStyle;
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
 * @brief Send render commands for the DrawStyle node
 * 
 * @todo this handler do nothing. Remove it.
 */
struct VGEGL_API DrawStyle : public vge::handler::painter::SingleAttribute
{
	META_HANDLER_HPP( DrawStyle  );

	const TargetVector		getTargets()	const;


	void	apply				( vge::engine::Engine*, vgd::node::Node* );
	void	unapply			( vge::engine::Engine*, vgd::node::Node* );
	
	void	setToDefaults	();
};



} // namespace painter

} // namespace handler

} // namespace vgeGL

#endif //#ifndef _VGEGL_HANDLER_DRAWSTYLE_H
