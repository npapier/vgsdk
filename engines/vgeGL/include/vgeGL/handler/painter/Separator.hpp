// VGSDK - Copyright (C) 2004, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_HANDLER_PAINTER_SEPARATOR_HPP
#define _VGEGL_HANDLER_PAINTER_SEPARATOR_HPP

//#include <vge/handler/Separator.hpp>

#include "vgeGL/handler/painter/TransformSeparator.hpp"



namespace vgeGL
{

namespace handler
{

namespace painter
{



/**
 * brief Send OpenGL commands to push/pop attributes and matrices.
 */
struct VGEGL_API Separator : 
	public vgeGL::handler::painter::TransformSeparator
	//,public vge::handler::Separator
{
	META_HANDLER_HPP( Separator );

	const vge::service::List	getServices	() const;
	const TargetVector			getTargets()	const;

	void	apply	( vge::engine::Engine*, vgd::node::Node* );
	void	unapply	( vge::engine::Engine*, vgd::node::Node* );
	
	void	setToDefaults();
};



} // namespace painter

} // namespace handler

} // namespace vgeGL

#endif //#ifndef _VGEGL_HANDLER_PAINTER_SEPARATOR_HPP
