//// VGSDK - Copyright (C) 2004, 2006, 2013, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_HANDLER_DRAWSTYLE_HPP
//#define _VGEGLBASE_HANDLER_DRAWSTYLE_HPP
//
//#include <vge/handler/painter/SingleAttribute.hpp>
//
//#include "vgeGLBase/vgeGLBase.hpp"
//
//namespace vgd
//{
//	namespace node
//	{
//		struct DrawStyle;
//		struct VertexShape;
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
//struct VertexShape;
//
///**
// * @brief Send render commands for the DrawStyle node
// * 
// * @todo this handler do nothing. Remove it ( see macro META_... ).
// */
//struct VGEGLBASE_API DrawStyle : public vge::handler::painter::SingleAttribute
//{
//	META_HANDLER_HPP( DrawStyle  );
//
//	const TargetVector getTargets() const;
//
//	void apply	( vge::engine::Engine*, vgd::node::Node* );
//	void unapply( vge::engine::Engine*, vgd::node::Node* );
//
//	void setToDefaults();
//
//	/**
//	 * @name Internal helpers
//	 */
//	//@{
//	static void paintVertexShapeWithShapeProperty(	vgeGLBase::engine::Engine *, vgd::node::VertexShape *,
//													vgeGLBase::handler::painter::VertexShape * );
//
//	//@}
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
//#endif //#ifndef _VGEGLBASE_HANDLER_DRAWSTYLE_HPP
//