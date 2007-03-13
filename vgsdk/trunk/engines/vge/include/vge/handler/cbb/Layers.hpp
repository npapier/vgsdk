// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_HANDLER_CBB_LAYERS_H
#define _VGE_HANDLER_CBB_LAYERS_H

#include "vge/vge.hpp"

#include "vge/handler/Kit.hpp"
#include "vge/handler/cbb/ComputeBoundingBox.hpp"



namespace vge
{
	
namespace handler
{

namespace cbb
{

/**
 * @brief Compute bounding box for Layers nodes.
 */
struct VGE_API Layers : public ComputeBoundingBox, public vge::handler::Kit
{
	META_HANDLER_HPP( Layers );
		
	const TargetVector				getTargets()	const;

	void	apply		( vge::engine::Engine*, vgd::node::Node* );
	void	unapply	( vge::engine::Engine*, vgd::node::Node* );

	void	setToDefaults();
};



} // namespace cbb

} // namespace handler

} // namespace vge

#endif //#ifndef _VGE_HANDLER_CBB_LAYERS_H
