// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_HANDLER_CBB_TRANSFORMSEPARATOR_H
#define _VGE_HANDLER_CBB_TRANSFORMSEPARATOR_H

#include "vge/vge.hpp"

#include "vge/handler/TransformSeparator.hpp"
#include "vge/handler/cbb/Group.hpp"



namespace vge
{
	
namespace handler
{

namespace cbb
{



/**
 * @brief Compute bounding box for a vgd::node::TransformSeparator.
 */
struct VGE_API TransformSeparator :
	public Group,
	public vge::handler::TransformSeparator
{
	META_HANDLER_HPP( TransformSeparator );
		
	//const vge::service::List		getServices()	const;
	const TargetVector				getTargets()	const;

	void	apply		( vge::engine::Engine*, vgd::node::Node* );
	void	unapply	( vge::engine::Engine*, vgd::node::Node* );

	void	setToDefaults();
};



} // namespace cbb

} // namespace handler

} // namespace vge

#endif //#ifndef _VGE_HANDLER_CBB_TRANSFORMSEPARATOR_H
