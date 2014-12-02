//// VGSDK - Copyright (C) 2011, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_HANDLER_PAINTER_FLUID_HPP
//#define _VGEGLBASE_HANDLER_PAINTER_FLUID_HPP
//
//#include "vgeGL/vgeGL.hpp"
//#include <vge/handler/painter/Shape.hpp>
//
//namespace vgd { namespace node { struct Fluid; } }
//
//namespace vgeGL { namespace engine { struct Engine; } }
//namespace vgeGL { namespace rc { struct Fluid; } }
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
// * @brief Send render commands for the fluid node
// */
//struct VGEGLBASE_API Fluid : public vge::handler::painter::Shape
//{
//	META_HANDLER_HPP( Fluid  );
//
//	const TargetVector getTargets() const;
//
//	void apply( vge::engine::Engine*, vgd::node::Node* );
//	void unapply( vge::engine::Engine*, vgd::node::Node* );
//
//	void setToDefaults();
//
//	void paint( vgeGL::engine::Engine*, vgd::node::Fluid* );
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
//#endif //#ifndef _VGEGLBASE_HANDLER_PAINTER_FLUID_HPP
//