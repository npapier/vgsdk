//// VGSDK - Copyright (C) 2004, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_HANDLER_PAINTER_LIGHTMODEL_HPP
//#define _VGEGLBASE_HANDLER_PAINTER_LIGHTMODEL_HPP
//
//#include "vgeGLBase/vgeGLBase.hpp"
//
//#include <vge/handler/painter/SingleAttribute.hpp>
//
//namespace vgd
//{
//	namespace node
//	{
//		struct LightModel;
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
// * @brief Send render commands for the LightModel node.
// */
//struct VGEGLBASE_API LightModel : public vge::handler::painter::SingleAttribute
//{
//	META_HANDLER_HPP( LightModel  );
//
//	const TargetVector getTargets() const;
//
//	void	apply	( vge::engine::Engine*, vgd::node::Node* );
//	void	unapply	( vge::engine::Engine*, vgd::node::Node* );
//	
//	void	setToDefaults();
//	
//	void	paint( vgeGLBase::engine::Engine*, vgd::node::LightModel* );
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
//#endif //#ifndef _VGEGLBASE_HANDLER_PAINTER_LIGHTMODEL_HPP
//