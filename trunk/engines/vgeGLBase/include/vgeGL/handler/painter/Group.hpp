// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_HANDLER_PAINTER_GROUP_HPP
#define _VGEGL_HANDLER_PAINTER_GROUP_HPP

#include "vgeGL/vgeGL.hpp"

#include <vge/handler/painter/Group.hpp>



namespace vgeGL
{

namespace handler
{

namespace painter
{



/**
 * @brief Rendering of Group node
 */
struct VGEGL_API Group : public vge::handler::painter::Group
{
	META_HANDLER_HPP( Group );

	const vge::service::List	getServices() const;
	const TargetVector			getTargets() const;

	void apply( vge::engine::Engine*, vgd::node::Node* );
	void unapply( vge::engine::Engine*, vgd::node::Node* );

	void setToDefaults();
};



} // namespace painter

} // namespace handler

} // namespace vgeGL

#endif //#ifndef _VGEGL_HANDLER_PAINTER_GROUP_HPP
