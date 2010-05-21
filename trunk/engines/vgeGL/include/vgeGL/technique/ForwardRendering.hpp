// VGSDK - Copyright (C) 2009, 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_TECHNIQUE_FORWARDRENDERING_HPP
#define _VGEGL_TECHNIQUE_FORWARDRENDERING_HPP

#include <iterator>
#include <utility>
#include "vgeGL/engine/GLSLState.hpp"
#include "vgeGL/technique/Main.hpp"

namespace glo { struct FrameBufferObject; struct Texture2D; }
namespace vgd { namespace node { struct FrameBuffer; struct Quad; struct Texture2D; } }
namespace vgeGL { namespace rc { struct FrameBufferObject; } }


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
	//
	vgd::Shp< ShadowMappingInput >				m_shadowMappingInput;

	//
	typedef vgeGL::engine::GLSLState::PostProcessingStateContainer PostProcessingStateContainer;
	vgd::Shp< PostProcessingStateContainer > m_postProcessing;
	float m_lastCurrentScaleForVertex;

	const vgd::Shp< vgeGL::rc::FrameBufferObject > applyPostProcessing( vgeGL::engine::Engine * engine, const vgd::Shp< vgeGL::rc::FrameBufferObject > fbo0, const vgd::Shp< vgeGL::rc::FrameBufferObject > fbo1 );
	void blit( vgeGL::engine::Engine * engine, vgd::Shp< vgeGL::rc::FrameBufferObject > fbo );


	/**
	 * @name Buffers
	 */
	//@{

	void initializeBuffers( vgeGL::engine::Engine * engine );

	vgd::Shp< vgd::node::FrameBuffer >				m_frameBuffer0;
	vgd::Shp< vgd::node::FrameBuffer >				m_frameBuffer1;
	vgd::Shp< vgd::node::FrameBuffer >				m_frameBuffer;

	vgd::Shp< vgeGL::rc::FrameBufferObject > 		m_fbo0;
	vgd::Shp< vgeGL::rc::FrameBufferObject >		m_fbo1;
	vgd::Shp< vgeGL::rc::FrameBufferObject > 		m_fbo;
	int m_normalIndex;
	int m_positionIndex;

// @todo removes
	std::vector< vgd::Shp< vgd::node::Texture2D > >	m_textures0;	///< textures for FBO 0
	std::vector< vgd::Shp< vgd::node::Texture2D > >	m_textures1;	///< textures for FBO 1
	std::vector< vgd::Shp< vgd::node::Texture2D > >	m_textures;		///< textures for FBO

	vgd::Shp< vgd::node::Quad >						m_quad1;
	vgd::Shp< vgd::node::Quad >						m_quad2;
	vgd::Shp< vgd::node::Quad >						m_quad3;

	vgd::Shp< vgd::node::Texture2D >				m_blackTexture2D; // @todo moves in Engine or in a repository ?
	//@}

	enum AttachmentType
	{
		// COLOR FORMATS
		COLOR_RGB,
		COLOR_RGB_16F,
		COLOR_RGB_32F,
		COLOR_RGBA,
		COLOR_RGBA_16F,
		COLOR_RGBA_32F,
		COLOR_LUMINANCE_16F,
		// DEPTH FORMATS
		DEPTH,
		DEPTH_COMPONENT_24 // @todo others DEPTH_COMPONENT*
	};

// @todo only glo FBO
	typedef std::pair< vgd::Shp< vgd::node::FrameBuffer >, vgd::Shp< vgeGL::rc::FrameBufferObject > > createsFBORetValType;
	typedef std::vector< vgd::Shp< vgd::node::Texture2D > > TextureContainer;
	createsFBORetValType createsFBO( vgeGL::engine::Engine * engine, std::vector< AttachmentType > attachments, std::back_insert_iterator< TextureContainer > backInserter );
};



} // namespace technique

} // namespace vgeGL

#endif //#ifndef _VGEGL_TECHNIQUE_FORWARDRENDERING_HPP
