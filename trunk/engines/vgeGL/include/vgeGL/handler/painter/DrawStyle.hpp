// VGSDK - Copyright (C) 2004, 2006, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_HANDLER_DRAWSTYLE_HPP
#define _VGEGL_HANDLER_DRAWSTYLE_HPP

#include <vge/handler/painter/SingleAttribute.hpp>

#include "vgeGL/vgeGL.hpp"

namespace vgd
{
	namespace node
	{
		struct DrawStyle;
		struct VertexShape;
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

struct VertexShape;

/**
 * @brief Send render commands for the DrawStyle node
 * 
 * @todo this handler do nothing. Remove it ( see macro META_... ).
 */
struct VGEGL_API DrawStyle : public vge::handler::painter::SingleAttribute
{
	META_HANDLER_HPP( DrawStyle  );

	const TargetVector getTargets() const;

	void apply	( vge::engine::Engine*, vgd::node::Node* );
	void unapply( vge::engine::Engine*, vgd::node::Node* );

	void setToDefaults();

	/**
	 * @name Internal helpers
	 */
	//@{
	static void paintVertexShapeWithShapeProperty(	vgeGL::engine::Engine *, vgd::node::VertexShape *,
													vgeGL::handler::painter::VertexShape * );

	static void paintVertexShapeNormals(vgeGL::engine::Engine *, vgd::node::VertexShape *,
										vgeGL::handler::painter::VertexShape * );
	//@}
};



} // namespace painter

} // namespace handler

} // namespace vgeGL

#endif //#ifndef _VGEGL_HANDLER_DRAWSTYLE_HPP
