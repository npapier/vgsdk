//// VGSDK - Copyright (C) 2007, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_HANDLER_PAINTER_LAYERPLAN_HPP
//#define _VGEGLBASE_HANDLER_PAINTER_LAYERPLAN_HPP
//
//#include "vgeGLBase/vgeGLBase.hpp"
//
//#include <vge/handler/painter/MultiAttribute.hpp>
//
//namespace vgd { namespace node { struct LayerPlan; } }
//
//namespace vgeGLBase {  namespace engine { struct Engine; } }
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
// * @brief Send render commands for the layer plane node
// */
//struct VGEGLBASE_API LayerPlan : public vge::handler::painter::MultiAttribute
//{
//	META_HANDLER_HPP( LayerPlan  );
//
//	//const vge::service::List			getServices	() const;
//	const TargetVector					getTargets()	const;
//
//	void apply( vge::engine::Engine*, vgd::node::Node* );
//	void unapply( vge::engine::Engine*, vgd::node::Node* );
//	
//	void setToDefaults();
//	
//	static void	paint( vgeGLBase::engine::Engine*, vgd::node::LayerPlan* );
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
//#endif //#ifndef _VGEGLBASE_HANDLER_PAINTER_LAYERPLAN_HPP
//