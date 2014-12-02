//// VGSDK - Copyright (C) 2013, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_HANDLER_PAINTER_TESSELLATIONPROPERTIES_HPP
//#define _VGEGLBASE_HANDLER_PAINTER_TESSELLATIONPROPERTIES_HPP
//
//#include <vge/handler/painter/SingleAttribute.hpp>
//#include "vgeGLBase/vgeGLBase.hpp"
//
//namespace vgd { namespace node { struct TessellationProperties; } }
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
// * @brief Implements painting service for TessellationProperties node
// */
//struct VGEGLBASE_API TessellationProperties : public vge::handler::painter::SingleAttribute
//{
//	META_HANDLER_HPP( TessellationProperties  );
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
//} // namespace vgeGLBase
//
//#endif //#ifndef _VGEGLBASE_HANDLER_PAINTER_TESSELLATIONPROPERTIES_HPP
//