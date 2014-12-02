//// VGSDK - Copyright (C) 2012, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_RC_ANTIALIASING_HPP
//#define _VGEGLBASE_RC_ANTIALIASING_HPP
//
//#include <glo/IResource.hpp>
//#include <vgd/Shp.hpp>
//#include <vge/rc/IResource.hpp>
//#include "vgeGL/engine/GLSLState.hpp"
//
//
//
//namespace vgeGL
//{
//
//namespace rc
//{
//
//
//// @todo post-processing rc (base class for Noise, DepthOfField and Antialiasing)
///**
// * @brief Antialiasing rc
// */
//struct VGEGLBASE_API Antialiasing : public vge::rc::IResource, public glo::IResource
//{
//	// Output buffers
//	vgd::Shp< vgd::node::OutputBufferProperty >	colorBuffer;
//
//	// Post-processing
//	typedef vgeGL::engine::GLSLState::PostProcessingStateContainer PostProcessingStateContainer;
//
//	vgd::Shp< vgd::node::Group >					rootPostProcessing;
//	PostProcessingStateContainer					postProcessing;
//};
//
//
//
//} // namespace rc
//
//} // namespace vgeGL
//
//#endif //#ifndef _VGEGLBASE_RC_ANTIALIASING_HPP
//