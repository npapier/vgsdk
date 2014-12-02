//// VGSDK - Copyright (C) 2004, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_HANDLER_PAINTER_TRANSFORMSEPARATOR_HPP
//#define _VGEGLBASE_HANDLER_PAINTER_TRANSFORMSEPARATOR_HPP
//
//#include "vgeGL/vgeGL.hpp"
//
//#include <vge/handler/TransformSeparator.hpp>
//#include <vge/handler/painter/Group.hpp>
//
//
//
//namespace vgeGL
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
// * @brief Use engine to push/pop matrices.
// */
//struct VGEGLBASE_API TransformSeparator : 
//	public vge::handler::painter::Group,
//	public vge::handler::TransformSeparator
//{
//	META_HANDLER_HPP( TransformSeparator );
//
//	const vge::service::List	getServices	() const;
//	const TargetVector			getTargets()	const;
//
//	void	apply				( vge::engine::Engine*, vgd::node::Node* );
//	void	unapply			( vge::engine::Engine*, vgd::node::Node* );
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
//} // namespace vgeGL
//
//#endif //#ifndef _VGEGLBASE_HANDLER_PAINTER_TRANSFORMSEPARATOR_HPP
//