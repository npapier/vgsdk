//// VGSDK - Copyright (C) 2013, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_HANDLER_PAINTER_GEOMORPH_HPP
//#define _VGEGLBASE_HANDLER_PAINTER_GEOMORPH_HPP
//
//#include "vgeGLBase/vgeGLBase.hpp"
//
//#include <vge/handler/painter/Painter.hpp>
//
//namespace vgd { namespace node { struct Node; } }
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
// * @brief Rendering of GeoMorph node
// */
//struct VGEGLBASE_API GeoMorph : public vge::handler::painter::Painter
//{
//	META_HANDLER_HPP( GeoMorph );
//
//	const TargetVector getTargets() const;
//
//	void apply( vge::engine::Engine*, vgd::node::Node* );
//	void unapply( vge::engine::Engine*, vgd::node::Node* );
//
//	void setToDefaults();
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
//#endif //#ifndef _VGEGLBASE_HANDLER_PAINTER_GEOMORPH_HPP
//