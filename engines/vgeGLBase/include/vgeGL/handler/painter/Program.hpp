//// VGSDK - Copyright (C) 2008, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_HANDLER_PAINTER_PROGRAM_HPP
//#define _VGEGLBASE_HANDLER_PAINTER_PROGRAM_HPP
//
//#include <vge/handler/painter/SingleAttribute.hpp>
//#include "vgeGL/vgeGL.hpp"
//
//namespace vgd { namespace node { struct Program; } }
//
//namespace vgeGL
//{
//	namespace engine { struct Engine; } 
//	namespace rc { struct GLSLProgram; }
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
///**
// * @brief OpenGL implementation of Program node
// */
//struct VGEGLBASE_API Program : public vge::handler::painter::SingleAttribute
//{
//	META_HANDLER_HPP( Program );
//
//	const TargetVector	getTargets() const;
//
//	void apply	( vge::engine::Engine *, vgd::node::Node * );
//	void unapply( vge::engine::Engine *, vgd::node::Node * );
//
//	void setToDefaults();
//
//	void bind			( vgeGL::engine::Engine * /*engine*/, vgd::node::Program * /*node*/, vgeGL::rc::GLSLProgram * /*resource*/ );
//	void synchronize	( vgeGL::engine::Engine * /*engine*/, vgd::node::Program * /*node*/, vgeGL::rc::GLSLProgram * /*resource*/ );
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
//#endif //#ifndef _VGEGLBASE_HANDLER_PAINTER_PROGRAM_HPP
//