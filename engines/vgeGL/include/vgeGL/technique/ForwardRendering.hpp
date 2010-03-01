// VGSDK - Copyright (C) 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_TECHNIQUE_FORWARDRENDERING_HPP
#define _VGEGL_TECHNIQUE_FORWARDRENDERING_HPP

#include "vgeGL/technique/Main.hpp"

namespace glo { struct Texture2D; }



namespace vgeGL
{

namespace technique
{


namespace
{
	struct ShadowMappingInput;
}

/**
 * @brief Forward rendering technique.
 *
 * This is the default technique to render opaque and transparent object with/without shadow.
 *
 * In forward rendering, rendering primitives are transformed, usually in a conceptual pipeline similar to the fixed function OpenGL model, from the model to the device.
 * This technique supports shadow computation. 
 * In the shadow mapping technique, shadows are created by testing whether a pixel in the scene is visible from the light 
 * source, by comparing it to a depth image of the light's view, stored in a texture. The shadow mapping was introduced
 * by Williams Lance in Casting Curved Shadows On Curved Surfaces, Computer Graphics Lab New York Institute of Techno, 
 * 1978 [Will1978].
 * At this time, it works only for SpotLight
 *
 * @todo only the first one.
 *
 * @ingroup g_techniques_vgeGL
 * @ingroup g_techniques
 */
struct VGEGL_CLASS_API ForwardRendering : public Main
{
	/**
	 * @brief Default constructor
	 */
	VGEGL_API ForwardRendering();


	/**
	 * @brief Evaluates the technique
	 *
	 * @param engine			evaluation engine
	 * @param traverseElements	the "flatten" scene graph to evaluate
	 */
	VGEGL_API void apply( vgeGL::engine::Engine * engine, vge::visitor::TraverseElementVector * traverseElements );

private:
	vgd::Shp< ShadowMappingInput > m_shadowMappingInput;
};



} // namespace technique

} // namespace vgeGL

#endif //#ifndef _VGEGL_TECHNIQUE_FORWARDRENDERING_HPP
