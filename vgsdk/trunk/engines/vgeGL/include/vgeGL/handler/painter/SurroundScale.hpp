// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_HANDLER_PAINTER_SURROUNDSCALE_H
#define _VGEGL_HANDLER_PAINTER_SURROUNDSCALE_H

#include "vgeGL/vgeGL.hpp"

#include <vge/handler/painter/SingleAttribute.hpp>
#include <vge/handler/SurroundScale.hpp>

namespace vgd
{
	namespace node
	{
		struct SurroundScale;
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
 * @brief Send render command for geometrical transformation.
 */
struct VGEGL_API SurroundScale : 
		public vge::handler::painter::SingleAttribute,
		public vge::handler::SurroundScale
{
	META_HANDLER_HPP( SurroundScale );

	const vge::service::List	getServices	() const;
	const TargetVector			getTargets()	const;

	void	apply				( vge::engine::Engine*, vgd::node::Node* );
	void	unapply			( vge::engine::Engine*, vgd::node::Node* );
	
	void	setToDefaults	();
	
	void	paint				( vgeGL::engine::Engine*, vgd::node::SurroundScale* );
};



} // namespace painter

} // namespace handler

} // namespace vgeGL

#endif //#ifndef _VGEGL_HANDLER_PAINTER_SURROUNDSCALE_H
