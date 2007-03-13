// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_HANDLER_PAINTER_WIRESHAPE_H
#define _VGEGL_HANDLER_PAINTER_WIRESHAPE_H

#include "vgeGL/vgeGL.hpp"

#include "vgeGL/handler/painter/VertexShape.hpp"



namespace vgeGL
{
	
namespace handler
{

namespace painter
{



/**
 * @brief Send render commands for the WireShape.
 */
struct VGEGL_API WireShape : public VertexShape
{
	META_HANDLER_HPP( WireShape );

	const TargetVector					getTargets()	const;

	void	apply				( vge::engine::Engine*, vgd::node::Node* );
	void	unapply			( vge::engine::Engine*, vgd::node::Node* );
	
	void	setToDefaults	();
};



} // namespace painter

} // namespace handler

} // namespace vgeGL

#endif //#ifndef _VGEGL_HANDLER_PAINTER_WIRESHAPE_H
