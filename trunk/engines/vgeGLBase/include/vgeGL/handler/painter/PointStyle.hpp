//// VGSDK - Copyright (C) 2010, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_HANDLER_PAINTER_POINTSTYLE_HPP
//#define _VGEGLBASE_HANDLER_PAINTER_POINTSTYLE_HPP
//
//#include "vgeGL/vgeGL.hpp"
//
//#include <vge/handler/painter/SingleAttribute.hpp>
//
//namespace vgd { namespace node { struct PointStyle; } }
//
//namespace vgeGL 
//{
//	namespace engine	{ struct Engine;		}
//	namespace rc		{ struct DisplayList;	}
//}
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
// * @brief Send render commands for the PointStyle node
// */
//struct VGEGLBASE_API PointStyle : public vge::handler::painter::SingleAttribute
//{
//	META_HANDLER_HPP( PointStyle );
//
//	const TargetVector getTargets() const;
//
//	void apply( vge::engine::Engine*, vgd::node::Node* );
//	void unapply( vge::engine::Engine*, vgd::node::Node* );
//
//	void setToDefaults();
//
//	void paint( vgeGL::engine::Engine*, vgd::node::PointStyle* );
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
//#endif //#ifndef _VGEGLBASE_HANDLER_PAINTER_POINTSTYLE_HPP
//