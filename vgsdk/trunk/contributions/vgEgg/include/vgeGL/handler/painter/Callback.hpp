// VGSDK - Copyright (C) 2006, Clement Forest.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_HANDLER_PAINTER_CALLBACK_H
#define _VGEGL_HANDLER_PAINTER_CALLBACK_H

#include <vge/handler/painter/SingleAttribute.hpp>

#include "vgeGL/vgeGL.hpp"

namespace vgd
{
	namespace node
	{
		struct Callback;
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
 * @brief Send render commands for the Callback node.
 */
struct VGEGL_API Callback : public vge::handler::painter::SingleAttribute
{
	META_HANDLER_HPP( Callback );

	const TargetVector	getTargets()	const;

	void	apply				( vge::engine::Engine*, vgd::node::Node* );
	void	unapply			( vge::engine::Engine*, vgd::node::Node* );
	
	void	setToDefaults	();
};



} // namespace painter

} // namespace handler

} // namespace vgeGL

#endif //#ifndef _VGEGL_HANDLER_PAINTER_CALLBACK_H
