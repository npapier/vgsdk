// VGSDK - Copyright (C) 2004, 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_HANDLER_BASIC_SHAPE_HPP
#define _VGE_HANDLER_BASIC_SHAPE_HPP

#include "vge/handler/basic/Basic.hpp"



namespace vge
{
	
namespace handler
{

namespace basic
{



/**
 * @brief Compute bounding box for all Shape (Box, Quad, VertexShape).
 */
struct VGE_API Shape : public Basic
{
	META_HANDLER_HPP( Shape );

	//const vge::service::List		getServices()	const;
	const TargetVector				getTargets()	const;

	void	apply		( vge::engine::Engine*, vgd::node::Node* );
	void	unapply	( vge::engine::Engine*, vgd::node::Node* );

	void	setToDefaults();
};



} // namespace basic

} // namespace handler

} // namespace vge

#endif //#ifndef _VGE_HANDLER_BASIC_SHAPE_HPP
