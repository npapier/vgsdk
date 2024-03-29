//// VGSDK - Copyright (C) 2004, 2011, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_HANDLER_PAINTER_LIGHT_HPP
//#define _VGEGLBASE_HANDLER_PAINTER_LIGHT_HPP
//
//#include <vge/handler/painter/MultiAttribute.hpp>
//#include "vgeGLBase/vgeGLBase.hpp"
//
//namespace vgd { namespace node { struct Light; } }
//
//namespace vgeGLBase
//{
//	namespace engine
//	{
//		struct Engine;
//		struct LightState;
//	}
//
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
// * @brief Send render commands for the Light.
// */
//struct VGEGLBASE_API Light : public vge::handler::painter::MultiAttribute
//{
//	//META_HANDLER_HPP( Light );
//
//	void	setToDefaults();
//
//protected:
//	void	updateUnitState( vgeGLBase::engine::Engine * engine, vgd::node::Light * light, vgd::Shp< vgeGLBase::engine::LightState > lightState );
//	void	paint		( vgeGLBase::engine::Engine*, vgd::node::Light* );
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
//#endif //#ifndef _VGEGLBASE_HANDLER_PAINTER_LIGHT_HPP
//