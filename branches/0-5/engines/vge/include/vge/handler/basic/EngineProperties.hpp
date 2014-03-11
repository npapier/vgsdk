// VGSDK - Copyright (C) 2012, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_HANDLER_BASIC_ENGINEPROPERTIES_HPP
#define _VGE_HANDLER_BASIC_ENGINEPROPERTIES_HPP

#include "vge/handler/basic/Basic.hpp"



namespace vge
{

namespace handler
{

namespace basic
{



/**
 * @brief Sets values from vgd::node::EngineProperties into vge::engine::Engine.
 */
struct VGE_API EngineProperties : public Basic
{
	META_HANDLER_HPP( EngineProperties );

	const vge::service::List 	getServices() const;
	const TargetVector			getTargets() const;

	void	apply	( vge::engine::Engine*, vgd::node::Node* );
	void	unapply	( vge::engine::Engine*, vgd::node::Node* );

	void	setToDefaults();
};



} // namespace basic

} // namespace handler

} // namespace vge

#endif //#ifndef _VGE_HANDLER_BASIC_ENGINEPROPERTIES_HPP
