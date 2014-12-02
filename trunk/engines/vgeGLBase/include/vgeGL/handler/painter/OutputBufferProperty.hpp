//// VGSDK - Copyright (C) 2010, 2014, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_HANDLER_PAINTER_OUTPUTBUFFERPROPERTY_HPP
//#define _VGEGLBASE_HANDLER_PAINTER_OUTPUTBUFFERPROPERTY_HPP
//
//#include <iterator>
//#include <vector>
//#include <vge/handler/painter/MultiAttribute.hpp>
//#include "vgeGLBase/engine/GLSLState.hpp"
//
//namespace glo { struct GLSLProgram; }
//
//namespace vgd { namespace node { struct FrameBuffer; struct OutputBufferProperty; struct Texture2D; } }
//
//namespace vgeGLBase
//{
//namespace engine { struct Engine; }
//namespace rc { struct FrameBufferObject; }
//}
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
// * @brief Send render commands for the output buffer property node
// */
//struct VGEGLBASE_API OutputBufferProperty : public vge::handler::painter::MultiAttribute
//{
//	META_HANDLER_HPP( OutputBufferProperty  );
//
//	const TargetVector getTargets()	const;
//
//	void apply	( vge::engine::Engine*, vgd::node::Node* );
//	void unapply( vge::engine::Engine*, vgd::node::Node* );
//
//	void setToDefaults();
//
//
//
//	/**
//	 * @brief Computes texture size needed to fullfil the OutputBufferProperty requirements (field size and sizeSemantic)
//	 */
//	static const vgm::Vec2i computeTextureSize( vgeGLBase::engine::Engine * engine, vgd::node::OutputBufferProperty * node );
//
//	typedef vgeGLBase::engine::GLSLState::OutputBufferPropertyStateContainer OutputBufferPropertyStateContainer;
//	typedef std::vector< vgd::Shp< vgd::node::Texture2D > > TextureContainer;
//	static void paint(	vgeGLBase::engine::Engine * engine,
//						OutputBufferPropertyStateContainer * outputBufferProperties,
//						std::back_insert_iterator< TextureContainer > backInserter );
//
//	/**
//	 * @param node	the node describing the desired Texture2D or null to retrieve a depth Texture2D.internalFormat=DEPTH_COMPONENT_24
//	 */
//	static vgd::Shp< vgd::node::Texture2D > createOrGetTexture2D( vgeGLBase::engine::Engine * engine, vgd::node::OutputBufferProperty * node );
//
//	typedef std::pair< vgd::Shp< vgd::node::FrameBuffer >, vgd::Shp< vgeGLBase::rc::FrameBufferObject > > createsFBORetValType;
//	static createsFBORetValType createsFBO(	vgeGLBase::engine::Engine * engine,
//		OutputBufferPropertyStateContainer * outputBufferProperties,
//		std::back_insert_iterator< TextureContainer > backInserter,
//		const bool addDepth = false );
//
//	static const std::string getFragmentOutputDeclarationStageString( vgeGLBase::engine::Engine * engine, OutputBufferPropertyStateContainer * outputBufferProperties );
//	static const std::string getFragmentOutputStageString( vgeGLBase::engine::Engine * engine, OutputBufferPropertyStateContainer * outputBufferProperties );
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
//#endif //#ifndef _VGEGLBASE_HANDLER_PAINTER_OUTPUTBUFFERPROPERTY_HPP
//