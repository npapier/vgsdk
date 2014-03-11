// VGSDK - Copyright (C) 2004, 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_HANDLER_BASIC_TRANSFORMSEPARATOR_HPP
#define _VGE_HANDLER_BASIC_TRANSFORMSEPARATOR_HPP

#include "vge/handler/TransformSeparator.hpp"
#include "vge/handler/basic/Group.hpp"



namespace vge
{
	
namespace handler
{

namespace basic
{



/**
 * @brief Computes bounding box for a vgd::node::TransformSeparator.
 */
struct VGE_API TransformSeparator :
	public Group,
	public vge::handler::TransformSeparator
{
	META_HANDLER_HPP( TransformSeparator );
		
	//const vge::service::List		getServices()	const;
	const TargetVector		getTargets()	const;

	void	apply	( vge::engine::Engine*, vgd::node::Node* );
	void	unapply	( vge::engine::Engine*, vgd::node::Node* );

	void	setToDefaults();
};



} // namespace basic

} // namespace handler

} // namespace vge

#endif //#ifndef _VGE_HANDLER_BASIC_TRANSFORMSEPARATOR_HPP
