//// VGSDK - Copyright (C) 2010, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_HANDLER_PAINTER_OVERLAY_HPP
//#define _VGEGLBASE_HANDLER_PAINTER_OVERLAY_HPP
//
//#include "vgeGLBase/engine/GLSLState.hpp"
//#include "vgeGLBase/handler/painter/LayerPlan.hpp"
//
//namespace vgd { namespace node { struct Overlay; } }
//
//namespace vgeGLBase { namespace engine { struct Engine; } }
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
// * @brief Send render commands for the overlay node
// */
//struct VGEGLBASE_API Overlay : public vgeGLBase::handler::painter::LayerPlan
//{
//	META_HANDLER_HPP( Overlay  );
//
//	const TargetVector getTargets() const;
//
//	void apply	( vge::engine::Engine*, vgd::node::Node* );
//	void unapply( vge::engine::Engine*, vgd::node::Node* );
//
//	void setToDefaults();
//
//	typedef vgeGLBase::engine::GLSLState::OverlayStateContainer OverlayStateContainer;
//	static void paint( vgeGLBase::engine::Engine *, OverlayStateContainer * overlays );
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
//#endif //#ifndef _VGEGLBASE_HANDLER_PAINTER_OVERLAY_HPP
//