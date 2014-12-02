//// VGSDK - Copyright (C) 2004, 2007, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_HANDLER_PAINTER_TEXTURE2D_HPP
//#define _VGEGLBASE_HANDLER_PAINTER_TEXTURE2D_HPP
//
//#include "vgeGLBase/handler/painter/Texture.hpp"
//
//namespace vgd { namespace node { struct Texture2D; } }
//
//namespace vgeGLBase { namespace rc { struct Texture2D; } }
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
// * @brief Send render commands for the Texture2D node
// */
//struct VGEGLBASE_API Texture2D : public vgeGLBase::handler::painter::Texture
//{
//	META_HANDLER_HPP( Texture2D );
//
//	const TargetVector	getTargets()	const;
//
//	void	apply	( vge::engine::Engine*, vgd::node::Node* );
//	void	unapply	( vge::engine::Engine*, vgd::node::Node* );
//	
//	void	setToDefaults	();
//
//	/**
//	 * @brief Creates/updates the 2D texture and updates parameters.
//	 */
//	void	synchronize	( vgeGLBase::engine::Engine*, vgd::node::Texture2D*, vgeGLBase::rc::Texture2D* );
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
//#endif //#ifndef _VGEGLBASE_HANDLER_PAINTER_TEXTURE2D_HPP
//