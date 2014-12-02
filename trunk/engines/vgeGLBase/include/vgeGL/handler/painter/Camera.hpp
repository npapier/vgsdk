// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_HANDLER_PAINTER_CAMERA_HPP
#define _VGEGL_HANDLER_PAINTER_CAMERA_HPP

#include "vgeGL/vgeGL.hpp"

#include <vge/handler/Camera.hpp>
#include <vge/handler/painter/SingleAttribute.hpp>

namespace vgd
{
	namespace node
	{
		struct Camera;
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
 * @brief Send render commands for the Camera.
 */
struct VGEGL_API Camera : 
	public vge::handler::painter::SingleAttribute, 
	public vge::handler::Camera
{
	META_HANDLER_HPP( Camera );

	const vge::service::List	getServices	() const;
	const TargetVector			getTargets()	const;

	void	apply			( vge::engine::Engine*, vgd::node::Node* );
	void	unapply			( vge::engine::Engine*, vgd::node::Node* );
	
	void	setToDefaults	();

	void	paint			( vgeGL::engine::Engine*, vgd::node::Camera* );
};



} // namespace painter

} // namespace handler

} // namespace vgeGL

#endif //#ifndef _VGEGL_HANDLER_PAINTER_CAMERA_HPP
