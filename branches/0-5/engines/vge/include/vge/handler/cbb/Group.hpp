// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_HANDLER_CBB_GROUP_HPP
#define _VGE_HANDLER_CBB_GROUP_HPP

#include "vge/vge.hpp"

#include "vge/handler/cbb/ComputeBoundingBox.hpp"



namespace vge
{
	
namespace handler
{

namespace cbb
{



/**
 * @brief Compute bounding box for a vgd::node::Group, MultiSwitch and Switch.
 */
struct VGE_API Group : public ComputeBoundingBox
{
	META_HANDLER_HPP( Group );
		
	const TargetVector	getTargets()	const;

	void	apply	( vge::engine::Engine*, vgd::node::Node* );
	void	unapply	( vge::engine::Engine*, vgd::node::Node* );

	void	setToDefaults();
};



} // namespace cbb

} // namespace handler

} // namespace vge

#endif //#ifndef _VGE_HANDLER_CBB_GROUP_HPP
