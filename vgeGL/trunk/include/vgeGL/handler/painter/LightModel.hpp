// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_HANDLER_PAINTER_LIGHTMODEL_H
#define _VGEGL_HANDLER_PAINTER_LIGHTMODEL_H

#include "vgeGL/vgeGL.hpp"

#include <vge/handler/painter/SingleAttribute.hpp>

namespace vgd
{
	namespace node
	{
		struct LightModel;
	}
}

namespace vgeGL
{
	namespace engine
	{
		struct Engine;
	}
	
	namespace rc
	{
		struct DisplayList;
	}
}



namespace vgeGL
{
	
namespace handler
{

namespace painter
{



/**
 * @brief Send render commands for the LightModel node.
 */
struct VGEGL_API LightModel : public vge::handler::painter::SingleAttribute
{
	META_HANDLER_HPP( LightModel  );

	//const vge::service::List			getServices	() const;
	const TargetVector					getTargets()	const;

	void	apply				( vge::engine::Engine*, vgd::node::Node* );
	void	unapply			( vge::engine::Engine*, vgd::node::Node* );
	
	void	setToDefaults	();
	
	void	paint				( vgeGL::engine::Engine*, vgd::node::LightModel* );
};



} // namespace painter

} // namespace handler

} // namespace vgeGL

#endif //#ifndef _VGEGL_HANDLER_PAINTER_LIGHTMODEL_H
