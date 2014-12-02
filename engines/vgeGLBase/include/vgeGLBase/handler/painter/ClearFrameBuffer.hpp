//// VGSDK - Copyright (C) 2004, 2011, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_HANDLER_PAINTER_CLEARFRAMEBUFFER_HPP
//#define _VGEGLBASE_HANDLER_PAINTER_CLEARFRAMEBUFFER_HPP
//
//#include <vge/handler/painter/SingleAttribute.hpp>
//#include "vgeGLBase/engine/Engine.hpp"
//
//namespace vgd
//{
//	namespace node
//	{
//		struct ClearFrameBuffer;
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
// * @brief Send render commands for the frame buffer.
// */
//struct VGEGLBASE_API ClearFrameBuffer : public vge::handler::painter::SingleAttribute
//{
//	META_HANDLER_HPP( ClearFrameBuffer );
//
//	const TargetVector getTargets() const;
//
//	void apply( vge::engine::Engine*, vgd::node::Node* );
//	void unapply( vge::engine::Engine*, vgd::node::Node* );
//
//	void setToDefaults();
//
//	void paint( vgeGLBase::engine::Engine*, vgd::node::ClearFrameBuffer* );
//
//	static void applyBufferUsagePolicy( vgeGLBase::engine::Engine * engine, const vge::engine::BufferUsagePolicy policy, const vge::engine::EyeUsagePolicy eyePolicy );
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
//#endif //#ifndef _VGEGLBASE_HANDLER_PAINTER_CLEARFRAMEBUFFER_HPP
//