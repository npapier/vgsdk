// VGSDK - Copyright (C) 2012, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_HANDLER_PAINTER_ENGINEPROPERTIES_HPP
#define _VGEGL_HANDLER_PAINTER_ENGINEPROPERTIES_HPP

#include "vge/handler/basic/EngineProperties.hpp"
#include "vgeGL/vgeGL.hpp"

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

namespace painter
{



/**
 * @brief Sets values from vgd::node::EngineProperties into GLSLState.
 */
struct VGEGL_API EngineProperties : public vge::handler::basic::EngineProperties
{
	META_HANDLER_HPP( EngineProperties );

	const vge::service::List 	getServices() const;
	//const TargetVector			getTargets() const;

	void	apply	( vge::engine::Engine*, vgd::node::Node* );
	void	unapply	( vge::engine::Engine*, vgd::node::Node* );

	void	setToDefaults();
};



} // namespace painter

} // namespace handler

} // namespace vgeGL

#endif //#ifndef _VGEGL_HANDLER_PAINTER_ENGINEPROPERTIES_HPP
