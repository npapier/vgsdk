//// VGSDK - Copyright (C) 2010, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_HANDLER_PAINTER_MULTIPLEINSTANCES_HPP
//#define _VGEGLBASE_HANDLER_PAINTER_MULTIPLEINSTANCES_HPP
//
//#include <vge/handler/painter/Shape.hpp>
//#include "vgeGLBase/vgeGLBase.hpp"
//
//namespace vgd { namespace node { struct MultipleInstances; } }
//
//namespace vgeGLBase 
//{
//namespace engine	{ struct Engine;		}
//namespace rc		{ struct DisplayList;	}
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
// * @brief Send render commands for the MultipleInstances node.
// */
//struct VGEGLBASE_API MultipleInstances : public vge::handler::painter::Shape
//{
//	META_HANDLER_HPP( MultipleInstances );
//
//	const TargetVector getTargets() const;
//
//	void apply( vge::engine::Engine*, vgd::node::Node* );
//	void unapply( vge::engine::Engine*, vgd::node::Node* );
//
//	void setToDefaults();
//
//	void paint( vgeGLBase::engine::Engine*, vgd::node::MultipleInstances* );
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
//#endif //#ifndef _VGEGLBASE_HANDLER_PAINTER_MULTIPLEINSTANCES_HPP
//