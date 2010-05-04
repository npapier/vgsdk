// VGSDK - Copyright (C) 2004, 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_HANDLER_BASIC_KITS_HPP
#define _VGE_HANDLER_BASIC_KITS_HPP

#include "vge/handler/Kit.hpp"
#include "vge/handler/basic/Basic.hpp"



namespace vge
{

namespace handler
{

namespace basic
{

/**
 * @brief Compute bounding box for all kits in the core of vgsdk.
 */
struct VGE_API Kits : public Basic, public vge::handler::Kit
{
	META_HANDLER_HPP( Kits );
		
	const TargetVector				getTargets()	const;

	void	apply		( vge::engine::Engine*, vgd::node::Node* );
	void	unapply	( vge::engine::Engine*, vgd::node::Node* );

	void	setToDefaults();
};



} // namespace basic

} // namespace handler

} // namespace vge

#endif //#ifndef _VGE_HANDLER_BASIC_KITS_HPP
