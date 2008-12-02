// VGSDK - Copyright (C) 2008, Guillaume Brocker
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGEGL_HANDLER_CBB_CALLBACK_HPP
#define _VGEGL_HANDLER_CBB_CALLBACK_HPP

#include <vge/handler/cbb/ComputeBoundingBox.hpp>

#include "vgeGL/vgeGL.hpp"

namespace vgd
{
	namespace node
	{
		struct Callback;
	}
}

namespace vgeGL
{
	namespace engine
	{
		struct Engine;
	}	
}


namespace vgeGL
{
	
namespace handler
{

namespace cbb
{



/**
 * @brief Computes the bounding box for the Callback node.
 */
struct VGEGL_API Callback : public vge::handler::cbb::ComputeBoundingBox
{
	META_HANDLER_HPP( Callback );

	const TargetVector	getTargets()	const;

	void	apply	( vge::engine::Engine*, vgd::node::Node* );
	void	unapply	( vge::engine::Engine*, vgd::node::Node* );
	
	void	setToDefaults	();
};



} // namespace cbb

} // namespace handler

} // namespace vgeGL

#endif //#ifndef _VGEGL_HANDLER_CBB_CALLBACK_HPP
