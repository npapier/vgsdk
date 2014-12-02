//// VGSDK - Copyright (C) 2004, 2009, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_HANDLER_PAINTER_SEPARATOR_HPP
//#define _VGEGLBASE_HANDLER_PAINTER_SEPARATOR_HPP
//
////#include <vge/handler/Separator.hpp>
//
//#include "vgeGLBase/handler/painter/TransformSeparator.hpp"
//
//
//
//namespace vgeGLBase
//{
//
//namespace handler
//{
//
//namespace painter
//{
//
//
//
///**
// * brief Send OpenGL commands to push/pop attributes and matrices.
// */
//struct VGEGLBASE_API Separator : 
//	public vgeGLBase::handler::painter::TransformSeparator
//	//,public vge::handler::Separator
//{
//	META_HANDLER_HPP( Separator );
//
//	const vge::service::List	getServices	() const;
//	const TargetVector			getTargets()	const;
//
//	void	apply	( vge::engine::Engine*, vgd::node::Node* );
//	void	unapply	( vge::engine::Engine*, vgd::node::Node* );
//	
//	void	setToDefaults();
//};
//
//
//
//} // namespace painter
//
//} // namespace handler
//
//} // namespace vgeGLBase
//
//#endif //#ifndef _VGEGLBASE_HANDLER_PAINTER_SEPARATOR_HPP
//