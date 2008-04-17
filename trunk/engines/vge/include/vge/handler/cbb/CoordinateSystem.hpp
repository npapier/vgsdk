// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_HANDLER_CBB_COORDINATESYSTEM_HPP
#define _VGE_HANDLER_CBB_COORDINATESYSTEM_HPP

#include "vge/handler/CoordinateSystem.hpp"
#include "vge/handler/cbb/ComputeBoundingBox.hpp"



namespace vge
{

namespace handler
{

namespace cbb
{



/**
 * @brief Evaluates CoordinateSystem node.
 */
struct VGE_API CoordinateSystem :
	public ComputeBoundingBox,
	public vge::handler::CoordinateSystem
{
	META_HANDLER_HPP( CoordinateSystem );
		
	//const vge::service::List		getServices()	const;
	const TargetVector		getTargets()	const;

	void	apply	( vge::engine::Engine*, vgd::node::Node* );
	void	unapply	( vge::engine::Engine*, vgd::node::Node* );

	void	setToDefaults();
};



} // namespace cbb

} // namespace handler

} // namespace vge

#endif //#ifndef _VGE_HANDLER_CBB_COORDINATESYSTEM_HPP
