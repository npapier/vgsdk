//// VGSDK - Copyright (C) 2013, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_HANDLER_PAINTER_DISPLACEMENT_HPP
//#define _VGEGLBASE_HANDLER_PAINTER_DISPLACEMENT_HPP
//
//#include <vge/handler/painter/SingleAttribute.hpp>
//#include "vgeGL/vgeGL.hpp"
//
//namespace vgd { namespace node { struct Displacement; } }
//
//namespace vgeGL { namespace engine { struct Engine; } }
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
// * @brief Implements painting service for Displacement node
// */
//struct VGEGLBASE_API Displacement : public vge::handler::painter::SingleAttribute
//{
//	META_HANDLER_HPP( Displacement  );
//
//	const TargetVector getTargets() const;
//
//	void apply	( vge::engine::Engine*, vgd::node::Node* );
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
//} // namespace vgeGL
//
//#endif //#ifndef _VGEGLBASE_HANDLER_PAINTER_DISPLACEMENT_HPP
//