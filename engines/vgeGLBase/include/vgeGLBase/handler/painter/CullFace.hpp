//// VGSDK - Copyright (C) 2008, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_HANDLER_PAINTER_CULLFACE_HPP
//#define _VGEGLBASE_HANDLER_PAINTER_CULLFACE_HPP
//
//#include "vgeGLBase/vgeGLBase.hpp"
//
//#include <vge/handler/painter/SingleAttribute.hpp>
//
//namespace vgd { namespace node { struct CullFace; } }
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
// * @brief Send render commands for the CullFace node.
// */
//struct VGEGLBASE_API CullFace : public vge::handler::painter::SingleAttribute
//{
//	META_HANDLER_HPP( CullFace );
//
//	const TargetVector getTargets() const;
//
//	void apply( vge::engine::Engine*, vgd::node::Node* );
//	void unapply( vge::engine::Engine*, vgd::node::Node* );
//
//	void setToDefaults();
//
//	void paint( vgeGLBase::engine::Engine*, vgd::node::CullFace* );
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
//#endif //#ifndef _VGEGLBASE_HANDLER_PAINTER_CULLFACE_HPP
//