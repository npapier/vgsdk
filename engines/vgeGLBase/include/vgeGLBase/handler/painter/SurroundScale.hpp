//// VGSDK - Copyright (C) 2004, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_HANDLER_PAINTER_SURROUNDSCALE_HPP
//#define _VGEGLBASE_HANDLER_PAINTER_SURROUNDSCALE_HPP
//
//#include "vgeGLBase/vgeGLBase.hpp"
//
//#include <vge/handler/painter/SingleAttribute.hpp>
//#include <vge/handler/SurroundScale.hpp>
//
//namespace vgd
//{
//	namespace node
//	{
//		struct SurroundScale;
//	}
//}
//
//namespace vgeGLBase
//{
//	namespace engine
//	{
//		struct Engine;
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
// * @brief Send render command for geometrical transformation.
// */
//struct VGEGLBASE_API SurroundScale : 
//		public vge::handler::painter::SingleAttribute,
//		public vge::handler::SurroundScale
//{
//	META_HANDLER_HPP( SurroundScale );
//
//	const vge::service::List	getServices	() const;
//	const TargetVector			getTargets()	const;
//
//	void	apply				( vge::engine::Engine*, vgd::node::Node* );
//	void	unapply			( vge::engine::Engine*, vgd::node::Node* );
//	
//	void	setToDefaults	();
//	
//	void	paint				( vgeGLBase::engine::Engine*, vgd::node::SurroundScale* );
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
//#endif //#ifndef _VGEGLBASE_HANDLER_PAINTER_SURROUNDSCALE_HPP
//