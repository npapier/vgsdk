// VGSDK - Copyright (C) 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_RC_NOISE_HPP
#define _VGEGL_RC_NOISE_HPP

#include <glo/IResource.hpp>
#include <vgd/Shp.hpp>
#include <vge/rc/IResource.hpp>
#include "vgeGL/engine/GLSLState.hpp"

namespace vgd { namespace node { struct Texture2D; } }



namespace vgeGL
{

namespace rc
{


// @todo post-processing rc (base class for Noise and DepthOfField)
/**
 * @brief Noise rc
 */
struct VGEGL_API Noise : public vge::rc::IResource, public glo::IResource
{
	// Output buffers
	vgd::Shp< vgd::node::OutputBufferProperty >	colorBuffer;

	// Texture containing random value
	vgd::Shp< vgd::node::Texture2D >			randomTexture;

	// Post-processing
	typedef vgeGL::engine::GLSLState::PostProcessingStateContainer PostProcessingStateContainer;

	vgd::Shp< vgd::node::Group >					rootPostProcessing;
	PostProcessingStateContainer					postProcessing;
};



} // namespace rc

} // namespace vgeGL

#endif //#ifndef _VGEGL_RC_NOISE_HPP
