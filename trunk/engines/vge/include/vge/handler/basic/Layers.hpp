// VGSDK - Copyright (C) 2004, 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_HANDLER_BASIC_LAYERS_HPP
#define _VGE_HANDLER_BASIC_LAYERS_HPP

#include "vge/handler/Kit.hpp"
#include "vge/handler/basic/Basic.hpp"



namespace vge
{
	
namespace handler
{

namespace basic
{

/**
 * @brief Compute bounding box for Layers nodes.
 */
struct VGE_API Layers : public Basic, public vge::handler::Kit
{
	META_HANDLER_HPP( Layers );
		
	const TargetVector				getTargets()	const;

	void	apply		( vge::engine::Engine*, vgd::node::Node* );
	void	unapply	( vge::engine::Engine*, vgd::node::Node* );

	void	setToDefaults();
};



} // namespace basic

} // namespace handler

} // namespace vge

#endif //#ifndef _VGE_HANDLER_BASIC_LAYERS_HPP
