//// VGSDK - Copyright (C) 2013, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_HANDLER_PAINTER_DECAL_HPP
//#define _VGEGLBASE_HANDLER_PAINTER_DECAL_HPP
//
//#include <vge/handler/painter/MultiAttribute.hpp>
//#include "vgeGLBase/engine/GLSLState.hpp"
//
//namespace vgd { namespace node { struct Decal; } }
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
// * @brief Updates engine state and rendering of Decal node
// */
//struct VGEGLBASE_API Decal : public vge::handler::painter::MultiAttribute
//{
//	META_HANDLER_HPP( Decal  );
//
//	const TargetVector getTargets()	const;
//
//	void apply	( vge::engine::Engine*, vgd::node::Node* );
//	void unapply( vge::engine::Engine*, vgd::node::Node* );
//	
//	void setToDefaults();
//
//	typedef vgeGLBase::engine::GLSLState::DecalStateContainer DecalStateContainer;
//	static void paint( vgeGLBase::engine::Engine *, DecalStateContainer * decals );
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
//#endif //#ifndef _VGEGLBASE_HANDLER_PAINTER_DECAL_HPP
//