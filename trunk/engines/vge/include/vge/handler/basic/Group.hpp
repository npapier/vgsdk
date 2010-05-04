// VGSDK - Copyright (C) 2004, 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_HANDLER_BASIC_GROUP_HPP
#define _VGE_HANDLER_BASIC_GROUP_HPP

#include "vge/handler/basic/Basic.hpp"



namespace vge
{

namespace handler
{

namespace basic
{



/**
 * @brief Compute bounding box for a vgd::node::Group, MultiSwitch and Switch.
 */
struct VGE_API Group : public Basic
{
	META_HANDLER_HPP( Group );
		
	const TargetVector	getTargets()	const;

	void	apply	( vge::engine::Engine*, vgd::node::Node* );
	void	unapply	( vge::engine::Engine*, vgd::node::Node* );

	void	setToDefaults();
};



} // namespace basic

} // namespace handler

} // namespace vge

#endif //#ifndef _VGE_HANDLER_BASIC_GROUP_HPP
