// VGSDK - Copyright (C) 2008, 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_HANDLER_BASIC_COORDINATESYSTEM_HPP
#define _VGE_HANDLER_BASIC_COORDINATESYSTEM_HPP

#include "vge/handler/CoordinateSystem.hpp"
#include "vge/handler/basic/Basic.hpp"



namespace vge
{

namespace handler
{

namespace basic
{



/**
 * @brief Evaluates CoordinateSystem node.
 */
struct VGE_API CoordinateSystem :
	public Basic,
	public vge::handler::CoordinateSystem
{
	META_HANDLER_HPP( CoordinateSystem );
		
	//const vge::service::List		getServices()	const;
	const TargetVector		getTargets()	const;

	void	apply	( vge::engine::Engine*, vgd::node::Node* );
	void	unapply	( vge::engine::Engine*, vgd::node::Node* );

	void	setToDefaults();
};



} // namespace basic

} // namespace handler

} // namespace vge

#endif //#ifndef _VGE_HANDLER_BASIC_COORDINATESYSTEM_HPP
