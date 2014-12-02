//// VGSDK - Copyright (C) 2004, 2011, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_HANDLER_PAINTER_DIRECTIONALLIGHT_HPP
//#define _VGEGLBASE_HANDLER_PAINTER_DIRECTIONALLIGHT_HPP
//
//#include "vgeGL/handler/painter/Light.hpp"
//
//namespace vgd { namespace node { struct DirectionalLight; } }
//
//namespace vgeGL
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
///**
// * @brief Send render commands for the directional light.
// */
//struct VGEGLBASE_API DirectionalLight : public vgeGL::handler::painter::Light
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
//	void	updateGLSLState( vgeGL::engine::Engine * engine, vgd::node::DirectionalLight * light, vgeGL::engine::GLSLState& glslState );
//	void	updateUnitState( vgeGL::engine::Engine * engine, vgd::node::DirectionalLight * light, vgd::Shp< vgeGL::engine::LightState > lightState );
//	void	paint( vgeGL::engine::Engine *pEngine, vgd::node::DirectionalLight *pDirectionalLight );
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
//#endif //#ifndef _VGEGLBASE_HANDLER_PAINTER_DIRECTIONALLIGHT_HPP
//