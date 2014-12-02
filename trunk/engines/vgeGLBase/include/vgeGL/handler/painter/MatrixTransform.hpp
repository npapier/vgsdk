//// VGSDK - Copyright (C) 2004, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_HANDLER_PAINTER_MATRIXTRANSFORM_HPP
//#define _VGEGLBASE_HANDLER_PAINTER_MATRIXTRANSFORM_HPP
//
//#include "vgeGLBase/vgeGLBase.hpp"
//
//#include <vge/handler/painter/SingleAttribute.hpp>
//#include <vge/handler/MatrixTransform.hpp>
//
//namespace vgd
//{
//	namespace node
//	{
//		struct MatrixTransform;
//	}
//}
//
//namespace vgeGLBase
//{
//	namespace engine
//	{
//		struct Engine;
//	}
//	
//	namespace rc
//	{
//		struct DisplayList;
//	}
//}
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
// * @brief Send render commands for the MatrixTransform node.
// */
//struct VGEGLBASE_API MatrixTransform : 
//		public vge::handler::painter::SingleAttribute,
//		public vge::handler::MatrixTransform
//{
//	META_HANDLER_HPP( MatrixTransform );
//
//	const vge::service::List	getServices	() const;
//	const TargetVector			getTargets()	const;
//
//	void	apply				( vge::engine::Engine*, vgd::node::Node* );
//	void	unapply			( vge::engine::Engine*, vgd::node::Node* );
//	
//	void	setToDefaults	();
//	
//	void	paint				( vgeGLBase::engine::Engine*, vgd::node::MatrixTransform* );
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
//#endif //#ifndef _VGEGLBASE_HANDLER_PAINTER_MATRIXTRANSFORM_HPP
//