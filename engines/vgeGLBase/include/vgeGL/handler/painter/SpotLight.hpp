//// VGSDK - Copyright (C) 2004, 2006, 2011, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_HANDLER_PAINTER_SPOTLIGHT_HPP
//#define _VGEGLBASE_HANDLER_PAINTER_SPOTLIGHT_HPP
//
//#include "vgeGLBase/handler/painter/PointLight.hpp"
//
//namespace vgd { namespace node { struct SpotLight; } }
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
// * @brief Send render commands for the spot light.
// */
//struct VGEGLBASE_API SpotLight : public vgeGLBase::handler::painter::PointLight
//{
//	META_HANDLER_HPP( SpotLight );
//
//	const TargetVector getTargets()	const;
//
//	void	apply	( vge::engine::Engine*, vgd::node::Node* );
//	void	unapply	( vge::engine::Engine*, vgd::node::Node* );
//
//	void	setToDefaults();
//
//	void	updateGLSLState( vgeGLBase::engine::Engine * engine, vgd::node::SpotLight * spotLight, vgeGLBase::engine::GLSLState& glslState );
//	void	updateUnitState( vgeGLBase::engine::Engine * engine, vgd::node::SpotLight * spotLight, vgd::Shp< vgeGLBase::engine::LightState > lightState );
//
//	void	paint( vgeGLBase::engine::Engine *pEngine, vgd::node::SpotLight * pSpotLight );
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
//#endif //#ifndef _VGEGLBASE_HANDLER_PAINTER_SPOTLIGHT_HPP
//