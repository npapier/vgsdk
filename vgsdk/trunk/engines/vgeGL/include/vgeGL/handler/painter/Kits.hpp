// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_HANDLER_PAINTER_KITS_H
#define _VGEGL_HANDLER_PAINTER_KITS_H

#include "vgeGL/vgeGL.hpp"

#include <vge/handler/painter/Kit.hpp>

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
 * @brief Paint kit nodes.
 */
struct VGEGL_API Kits : public vge::handler::painter::Kit
{
	META_HANDLER_HPP( Kits );

	const vge::service::List	getServices	() const;
	const TargetVector			getTargets()	const;

	void	apply			( vge::engine::Engine*, vgd::node::Node* );
	void	unapply			( vge::engine::Engine*, vgd::node::Node* );
	
	void	setToDefaults	();
};



} // namespace painter

} // namespace handler

} // namespace vgeGL

#endif //#ifndef _VGEGL_HANDLER_PAINTER_KITS_H
