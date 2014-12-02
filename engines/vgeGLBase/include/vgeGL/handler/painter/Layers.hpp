// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_HANDLER_PAINTER_LAYERS_HPP
#define _VGEGL_HANDLER_PAINTER_LAYERS_HPP

#include "vgeGL/vgeGL.hpp"

#include <glo/GLSLProgram.hpp>
#include <vgd/node/Layers.hpp>
#include <vge/handler/painter/Group.hpp>

namespace vgd
{
	namespace node
	{
		struct Texture1D;
		struct Texture2D;
	}
}

namespace vgeGL
{
	namespace engine
	{
		struct Engine;
	}
	
	namespace rc
	{
		struct DisplayList;
	}	
}



namespace vgeGL
{
	
namespace handler
{

namespace painter
{



/**
 * @brief Render a vgd::node::Layers.
 */
struct VGEGL_API Layers : public vge::handler::painter::Group
{
	META_HANDLER_HPP( Layers );

	const TargetVector					getTargets()	const;

	void	apply			( vge::engine::Engine*, vgd::node::Node* );
	void	unapply			( vge::engine::Engine*, vgd::node::Node* );
	
	void	setToDefaults	();
	
	void	paint			( vgeGL::engine::Engine*, vgd::node::Layers* );

	/**
	 * @brief Configures/updates dirtyFlagImage, pTex*
	 * ouput pScissor and pTex2DForScissor 
	 * 
	 * @return true if it is a scissor pass
	 * */
	const bool configure(	vgd::Shp< vgd::basic::IImage > pIImage,
							vgd::node::Layers::ComposeOperatorValueType composeOperator,
							vgd::field::DirtyFlag*	dirtyFlagImage,
							vgd::Shp< vgd::node::Texture2D > pTex2D, vgd::Shp< vgd::node::Texture1D >	pTex1D,
							vgd::Shp< vgd::basic::IImage >& pScissor, vgd::Shp< vgd::node::Texture2D >& pTex2DForScissor );
						
	/**
	 * @brief Configure current shaders
	 */
	void configureShaders(	vgd::Shp< vgd::basic::IImage > pIImage, vgd::field::DirtyFlag*	dirtyFlagImage,
					vgd::node::Layers::ComposeOperatorValueType composeOperator,
					vgd::Shp< vgd::basic::IImage >& pScissor, vgd::Shp< vgd::node::Texture2D >& pTex2DForScissor );							

	void configureGLState(	bool& bFirstPass,
							vgd::node::Layers::ComposeOperatorValueType composeOperator,
							vgd::Shp< vgd::basic::IImage > pScissor );

							
private:
	/**
	 * @brief Scan the whole image and ...
	 * 
	 * @pre pScissor->format() == RGBA or pScissor->format() == BGRA or pScissor->format() == LUMINANCE_ALPHA
	 * @pre pScissor->format() == pImage->format()
	 * 
	 * @pre pScissor->type() == UINT8
	 * @pre pImage->type() == UINT8
	 * @pre same size for image and scissor.
	 * 
	 * @param pScissor	image to scan.
	 * @param pImage		image to scan.
	 */
	void	applyScissorMask( vgd::Shp< vgd::basic::IImage > pScissor, vgd::Shp< vgd::basic::IImage > pImage );
	
	void initializeShaders();
	void destroyShaders();

	static bool				m_shadersAlreadyInitialized;
	static glo::GLSLProgram *m_pReplaceShader;
	static glo::GLSLProgram *m_pPaletteReplaceShader;

	static glo::GLSLProgram *m_pScissorReplaceShader;
	static glo::GLSLProgram *m_pScissorPaletteReplaceShader;
};



} // namespace painter

} // namespace handler

} // namespace vgeGL

#endif //#ifndef _VGEGL_HANDLER_PAINTER_LAYERS_HPP
