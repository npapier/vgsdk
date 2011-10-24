// VGSDK - Copyright (C) 2009, 2010, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_TECHNIQUE_FORWARDRENDERING_HPP
#define _VGEGL_TECHNIQUE_FORWARDRENDERING_HPP

#include <vgd/node/Camera.hpp>
#include <vgd/node/LightModel.hpp>
#include <vgd/node/TransformDragger.hpp>
#include "vgeGL/engine/GLSLState.hpp"
#include "vgeGL/technique/DepthOfField.hpp"
#include "vgeGL/technique/Main.hpp"

namespace glo { struct FrameBufferObject; struct Texture2D; }
namespace vgd { namespace node { struct Fluid; struct Grid; struct FrameBuffer; struct Quad; struct Texture2D; } }
namespace vgeGL { namespace rc { struct Fluid; struct FrameBufferObject; } }


namespace vgeGL
{

namespace technique
{



struct ShadowMappingInput;



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
	void passInformationsCollector( vgeGL::engine::Engine * engine, vge::visitor::TraverseElementVector* traverseElements );
	void passUpdateShadowMaps( vgeGL::engine::Engine * engine, vge::visitor::TraverseElementVector* traverseElements );
		vgd::Shp< vgeGL::rc::FrameBufferObject > configureShadowMap( vgeGL::engine::Engine * engine, const uint currentLightIndex );
	void passDepthOnly( vgeGL::engine::Engine * engine, vge::visitor::TraverseElementVector* traverseElements );

	// LightModel
	vgd::node::LightModel *							lightModel;
	vgd::node::LightModel::ShadowValueType			shadowType;
	vgd::node::LightModel::ShadowMapTypeValueType	shadowMapType;

	// VIEW MATRIX and PROJECTION MATRIX
	vgd::node::Camera *				camera;
	vgd::node::TransformDragger *	transformDragger;

	vgm::MatrixR	transformDraggerMatrix;
	vgm::MatrixR	invTransformDraggerMatrix;

	vgm::MatrixR	viewMatrix;
	vgm::MatrixR	invViewMatrix;

	vgd::Shp< vgeGL::engine::GLSLState > glslStateFinal;

	// STEREO
	bool isStereoEnabled;

	// SHADOW MAPPING
	vgd::Shp< ShadowMappingInput >				m_shadowMappingInput;
	bool isShadowEnabled;

	std::vector< vgm::MatrixR >					lightLookAt;


	void stageConfigureShadowMapping( vgeGL::engine::Engine * engine );


	// FLUID
	bool				isFluidEnabled;

	vgd::node::Fluid *	fluid;
	vgm::MatrixR		fluidModelViewMatrix;

	// helpers
	float positionMapScaleFactor;
	vgd::Shp< vgeGL::rc::Fluid > getFluidRC( vgeGL::engine::Engine * engine );
	void stageInitializeFluidPostProcessing( vgd::node::Fluid * fluid, vgd::Shp< vgeGL::rc::Fluid > fluidRC );
	void stageInitializeFluidRC( vgeGL::engine::Engine * engine, vgd::node::Fluid * fluid, vgd::Shp< vgeGL::rc::Fluid > fluidRC );
	void stageUpdateFluidEmittersAndDrainers( vgeGL::engine::Engine * engine, vgd::node::Fluid * fluid, vgd::Shp< vgeGL::rc::Fluid > fluidRC );
	void stageUpdateFluidSimulationParameters( vgeGL::engine::Engine * engine, vgd::node::Fluid * fluid, vgd::Shp< vgeGL::rc::Fluid > fluidRC );

	//
	void stageInitializeFluid( vgeGL::engine::Engine * engine, vge::visitor::TraverseElementVector * traverseElements );

	void stageFluidUpdateSceneHeightMap( vgeGL::engine::Engine * engine, vge::visitor::TraverseElementVector * traverseElements );

	void stageFluidSimulation( vgeGL::engine::Engine * engine );


// @todo separate outputbuffers and post-processing
	// POST-PROCESSING (and OutputBuffers)
struct PostProcessingPipelineRC
{
	// FBO 0 and 1 for TMP|PREVIOUS buffers
	vgd::Shp< vgd::node::FrameBuffer >				frameBuffer0;
	vgd::Shp< vgeGL::rc::FrameBufferObject > 		fbo0;
	std::vector< vgd::Shp< vgd::node::Texture2D > >	textures0;	///< textures for FBO 0

	vgd::Shp< vgd::node::FrameBuffer >				frameBuffer1;
	vgd::Shp< vgeGL::rc::FrameBufferObject >		fbo1;
	std::vector< vgd::Shp< vgd::node::Texture2D > >	textures1;	///< textures for FBO 1

	vgd::Shp< vgeGL::rc::FrameBufferObject >		outputFbo;
};

/*struct PostProcessingRC
{
	vgd::node::PostProcessing::Input0ValueType input0;
	vgd::node::PostProcessing::Input1ValueType input1;
	vgd::node::PostProcessing::Input2ValueType input2;

	float 		param1f0;
	vgm::Vec4f	param4f0;
	vgm::Vec4f	param4f1;

	vgd::node::PostProcessing::OutputValueType output;

	float		scale;

	//std::pair< std::string, std::string > filter;
	vgd::Shp< Program > program;
	float m_lastCurrentScaleForVertex; // for blit()

};*/

	//std::vector< PostProcessingRC > postProcessingsRC;

	PostProcessingPipelineRC pppRC;

	// for info pass
public: // for modification by technique::DepthOfField
	bool hasOutputBufferProperties;
		// input for post-processing
	typedef vgeGL::engine::GLSLState::OutputBufferPropertyStateContainer OutputBufferPropertyStateContainer;
	OutputBufferPropertyStateContainer * m_outputBufferProperties;

	bool isPostProcessingEnabled;
private:
		// input for post-processing
	typedef vgeGL::engine::GLSLState::PostProcessingStateContainer PostProcessingStateContainer;
	PostProcessingStateContainer * m_postProcessing;

	// OutputBuffers/PostProcessing
	bool drawingSurfaceSizeChanged;		// @todo must be computed in info pass (generic information).

	//
	float m_lastCurrentScaleForVertex;

	// Initializes fbo 0 and 1 internal buffers for ping-pong rendering (i.e. PREVIOUS0, OUTPUT_TMP0)
	void stageInitializePostProcessingBuffers( vgeGL::engine::Engine * engine );


	// Configures fragment shader stages FRAGMENT_OUTPUT_DECLARATION and FRAGMENT_OUTPUT
	void stageConfigurePostProcessing( vgeGL::engine::Engine * engine );

	// Apply the post-processing and blits the result.
	void stagePostProcessing( vgeGL::engine::Engine * engine );

public: // for technique::DepthOfField
	// post-processing core details
	const vgd::Shp< vgeGL::rc::FrameBufferObject > applyPostProcessing(
		vgeGL::engine::Engine * engine,
		std::vector< vgd::Shp< vgd::node::Texture2D > >&	outputBuffers,
		PostProcessingStateContainer *						postProcessingContainer );

	void blit( vgeGL::engine::Engine * engine, vgd::Shp< vgeGL::rc::FrameBufferObject > fbo );
private:

	// OVERLAY
	typedef vgeGL::engine::GLSLState::OverlayStateContainer OverlayStateContainer;
	OverlayStateContainer * m_overlays;

	bool renderOverlays;
	void stageOverlays( vgeGL::engine::Engine * engine );


//
	/**
	 * @name Buffers
	 */
	//@{

	void stageInitializeOutputBuffers( vgeGL::engine::Engine * engine );
	void initializeEngineBuffers( vgeGL::engine::Engine * engine, OutputBufferPropertyStateContainer * outputBufferProperties );
		vgd::Shp< vgd::node::FrameBuffer >				m_frameBuffer;
		vgd::Shp< vgeGL::rc::FrameBufferObject > 		m_fbo;
public: // for technique::DepthOfField
		std::vector< vgd::Shp< vgd::node::Texture2D > >	m_textures;		///< textures for FBO







	vgd::Shp< vgd::node::Quad >						m_quad1;
	vgd::Shp< vgd::node::Quad >						m_quad2;
	vgd::Shp< vgd::node::Quad >						m_quad3;

	vgd::Shp< vgd::node::Texture2D >				m_blackTexture2D; // @todo moves in Engine or in a repository ?
	//@}

	vgeGL::technique::DepthOfField dof;

// @todo only glo FBO
	//typedef std::vector< vgd::Shp< vgd::node::Texture2D > > TextureContainer;
	//createsFBORetValType createsFBO( vgeGL::engine::Engine * engine, std::vector< AttachmentType > attachments, std::back_insert_iterator< TextureContainer > backInserter );
};



} // namespace technique

} // namespace vgeGL

#endif //#ifndef _VGEGL_TECHNIQUE_FORWARDRENDERING_HPP
