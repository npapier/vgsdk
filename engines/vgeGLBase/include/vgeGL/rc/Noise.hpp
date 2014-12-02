//// VGSDK - Copyright (C) 2011, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_RC_NOISE_HPP
//#define _VGEGLBASE_RC_NOISE_HPP
//
//#include <glo/IResource.hpp>
//#include <vgd/basic/Time.hpp>
//#include <vgd/Shp.hpp>
//#include <vge/rc/IResource.hpp>
//#include "vgeGL/engine/GLSLState.hpp"
//
//namespace vgd { namespace node { struct Texture2D; } }
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
//// @todo post-processing rc (base class for Noise and DepthOfField)
///**
// * @brief Noise rc
// */
//struct VGEGLBASE_API Noise : public vge::rc::IResource, public glo::IResource
//{
//	/**
//	 * @brief Default constructor
//	 */
//	Noise()
//	:	lastRandomUniformUpdate	( false						),
//		lastUsedRandomValue		( vgm::Vec4f::getInvalid()	),
//		lastUsedTimeValue		( 0							)
//	{}
//
//	// Output buffers
//	vgd::Shp< vgd::node::OutputBufferProperty >	colorBuffer;
//
//	// Texture containing random value
//	vgd::Shp< vgd::node::Texture2D >			randomTexture;
//
//	// Post-processing
//	typedef vgeGL::engine::GLSLState::PostProcessingStateContainer PostProcessingStateContainer;
//
//	vgd::Shp< vgd::node::Group >					rootPostProcessing;
//	PostProcessingStateContainer					postProcessing;
//
//	// Data used to implement Noise.frequency
//	vgd::basic::Time	lastRandomUniformUpdate;
//	vgm::Vec4f			lastUsedRandomValue;
//	uint64				lastUsedTimeValue;
//};
//
//
//
//} // namespace rc
//
//} // namespace vgeGL
//
//#endif //#ifndef _VGEGLBASE_RC_NOISE_HPP
//