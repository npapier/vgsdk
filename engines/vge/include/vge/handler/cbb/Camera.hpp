// VGSDK - Copyright (C) 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_HANDLER_CBB_CAMERA_HPP
#define _VGE_HANDLER_CBB_CAMERA_HPP

#include "vge/vge.hpp"

#include "vge/handler/Camera.hpp"
#include "vge/handler/cbb/ComputeBoundingBox.hpp"



namespace vge
{

namespace handler
{

namespace cbb
{



/**
 * @brief Compute bounding box for a vgd::node::Camera.
 */
struct VGE_API Camera :
	public ComputeBoundingBox,
	public vge::handler::Camera
{
	META_HANDLER_HPP( Camera );

	const TargetVector getTargets()	const;

	void apply	( vge::engine::Engine*, vgd::node::Node* );
	void unapply( vge::engine::Engine*, vgd::node::Node* );

	void setToDefaults();
};



} // namespace cbb

} // namespace handler

} // namespace vge

#endif //#ifndef _VGE_HANDLER_CBB_CAMERA_HPP
