//// VGSDK - Copyright (C) 2004, 2011, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_HANDLER_PAINTER_DIRECTIONALLIGHT_HPP
//#define _VGEGLBASE_HANDLER_PAINTER_DIRECTIONALLIGHT_HPP
//
//#include "vgeGLBase/handler/painter/Light.hpp"
//
//namespace vgd { namespace node { struct DirectionalLight; } }
//
//namespace vgeGLBase
//{
//	namespace engine
//	{
//		struct Engine;
//		struct GLSLState;
//		struct LightState;
//	}
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
///**
// * @brief Send render commands for the directional light.
// */
//struct VGEGLBASE_API DirectionalLight : public vgeGLBase::handler::painter::Light
//{
//	META_HANDLER_HPP( DirectionalLight );
//
//	const TargetVector getTargets() const;
//
//	void	apply	( vge::engine::Engine*, vgd::node::Node* );
//	void	unapply	( vge::engine::Engine*, vgd::node::Node* );
//
//	void	setToDefaults();
//
//	void	updateGLSLState( vgeGLBase::engine::Engine * engine, vgd::node::DirectionalLight * light, vgeGLBase::engine::GLSLState& glslState );
//	void	updateUnitState( vgeGLBase::engine::Engine * engine, vgd::node::DirectionalLight * light, vgd::Shp< vgeGLBase::engine::LightState > lightState );
//	void	paint( vgeGLBase::engine::Engine *pEngine, vgd::node::DirectionalLight *pDirectionalLight );
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
//#endif //#ifndef _VGEGLBASE_HANDLER_PAINTER_DIRECTIONALLIGHT_HPP
//