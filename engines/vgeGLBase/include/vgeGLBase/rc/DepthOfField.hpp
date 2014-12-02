//// VGSDK - Copyright (C) 2011, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_RC_DEPTHOFFIELD_HPP
//#define _VGEGLBASE_RC_DEPTHOFFIELD_HPP
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
//	struct FrameBuffer;
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
// * @brief Depth of field rc
// */
//struct VGEGLBASE_API DepthOfField : public vge::rc::IResource, public glo::IResource
//{
//	// Output buffers
//	vgd::Shp< vgd::node::OutputBufferProperty >	colorBuffer;
//	vgd::Shp< vgd::node::OutputBufferProperty >	blurFactorBuffer;
//
//	// Post-processing
//	typedef vgeGLBase::engine::GLSLState::PostProcessingStateContainer PostProcessingStateContainer;
//
//	vgd::Shp< vgd::node::Group >					rootPostProcessing;
//	PostProcessingStateContainer					postProcessing;
//};
//
//
//
//} // namespace rc
//
//} // namespace vgeGLBase
//
//#endif //#ifndef _VGEGLBASE_RC_DEPTHOFFIELD_HPP
//