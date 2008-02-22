// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_HANDLER_CBB_MATRIXTRANSFORM_HPP
#define _VGE_HANDLER_CBB_MATRIXTRANSFORM_HPP

#include "vge/vge.hpp"

#include "vge/handler/MatrixTransform.hpp"
#include "vge/handler/cbb/ComputeBoundingBox.hpp"



namespace vge
{
	
namespace handler
{

namespace cbb
{



/**
 * @brief Compute bounding box for a vgd::node::MatrixTransform.
 */
struct VGE_API MatrixTransform :
	public ComputeBoundingBox,
	public vge::handler::MatrixTransform
{
	META_HANDLER_HPP( MatrixTransform );
		
	//const vge::service::List		getServices()	const;
	const TargetVector				getTargets()	const;

	void	apply		( vge::engine::Engine*, vgd::node::Node* );
	void	unapply	( vge::engine::Engine*, vgd::node::Node* );

	void	setToDefaults();
};



} // namespace cbb

} // namespace handler

} // namespace vge

#endif //#ifndef _VGE_HANDLER_CBB_MATRIXTRANSFORM_HPP
