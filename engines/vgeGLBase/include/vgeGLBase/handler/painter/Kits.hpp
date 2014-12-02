//// VGSDK - Copyright (C) 2004, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_HANDLER_PAINTER_KITS_HPP
//#define _VGEGLBASE_HANDLER_PAINTER_KITS_HPP
//
//#include "vgeGLBase/vgeGLBase.hpp"
//
//#include <vge/handler/painter/Kit.hpp>
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
// * @brief Paint kit nodes.
// */
//struct VGEGLBASE_API Kits : public vge::handler::painter::Kit
//{
//	META_HANDLER_HPP( Kits );
//
//	const vge::service::List	getServices	() const;
//	const TargetVector			getTargets()	const;
//
//	void	apply			( vge::engine::Engine*, vgd::node::Node* );
//	void	unapply			( vge::engine::Engine*, vgd::node::Node* );
//	
//	void	setToDefaults	();
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
//#endif //#ifndef _VGEGLBASE_HANDLER_PAINTER_KITS_HPP
//