//// VGSDK - Copyright (C) 2011, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_RC_FLUID_HPP
//#define _VGEGLBASE_RC_FLUID_HPP
//
//#include <vector>
//#include <vgd/Shp.hpp>
//#include <vge/rc/IResource.hpp>
//#include "vgeGLBase/engine/GLSLState.hpp"
//#include "vgeGLBase/rc/FrameBufferObject.hpp"
//
//namespace vgd
//{
//namespace node 
//{
//	struct Grid;
//	struct FrameBuffer;
//	struct Separator;
//	struct Texture2D;
//}
//}
//
//
//
//namespace vgeGLBase
//{
//
//namespace rc
//{
//
//
//
///**
// * @brief Fluid rc
// */
//struct VGEGLBASE_API Fluid : public vge::rc::IResource, public glo::IResource
//{
//// for simu pp
//	typedef vgeGLBase::engine::GLSLState::OutputBufferPropertyStateContainer OutputBufferPropertyStateContainer;
//	vgd::Shp< OutputBufferPropertyStateContainer >	outputBufferProperties;
//
//	// HEIGHT MAPS
//	vgd::Shp< vgd::node::FrameBuffer >				frameBuffer;
//	vgd::Shp< vgeGLBase::rc::FrameBufferObject > 		fbo;
//	// 0 scene height map
//	// 1 blood height map
//	std::vector< vgd::Shp< vgd::node::Texture2D > >	heightMaps;
//
//	vgd::Shp< vgeGLBase::rc::FrameBufferObject > 		postProcessingFBO;
//
//	// GRID
//	vgd::Shp< vgd::node::Grid >			grid;
//
//	// NODES FOR FLUID PAINTER (see handler)
//	vgd::Shp< vgd::node::Separator >	separator;
//
//	// SIMULATION using post-processing
//	vgd::Shp< vgd::node::Group >	postProcessingGroup;
//
//	typedef vgeGLBase::engine::GLSLState::PostProcessingStateContainer PostProcessingStateContainer;
//	PostProcessingStateContainer					postProcessing;
//};
//
//
//
//} // namespace rc
//
//} // namespace vgeGLBase
//
//#endif //#ifndef _VGEGLBASE_RC_FLUID_HPP
//