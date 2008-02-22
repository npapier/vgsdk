// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_HANDLER_CBB_SHAPE_HPP
#define _VGE_HANDLER_CBB_SHAPE_HPP

#include "vge/vge.hpp"

#include "vge/handler/cbb/ComputeBoundingBox.hpp"



namespace vge
{
	
namespace handler
{

namespace cbb
{



/**
 * @brief Compute bounding box for all Shape (Box, Quad, VertexShape).
 */
struct VGE_API Shape : public ComputeBoundingBox
{
	META_HANDLER_HPP( Shape );

	//const vge::service::List		getServices()	const;
	const TargetVector				getTargets()	const;

	void	apply		( vge::engine::Engine*, vgd::node::Node* );
	void	unapply	( vge::engine::Engine*, vgd::node::Node* );

	void	setToDefaults();
};



} // namespace cbb

} // namespace handler

} // namespace vge

#endif //#ifndef _VGE_HANDLER_CBB_SHAPE_HPP
