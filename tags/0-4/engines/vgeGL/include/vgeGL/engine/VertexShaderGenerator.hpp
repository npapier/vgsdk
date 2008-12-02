// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_ENGINE_VERTEXSHADERGENERATOR_HPP
#define _VGEGL_ENGINE_VERTEXSHADERGENERATOR_HPP

#include "vgeGL/engine/ShaderGenerator.hpp"



namespace vgeGL
{

namespace engine
{



/**
 * @brief Vertex shader code generator.
 */
struct VGEGL_API VertexShaderGenerator : public ShaderGenerator
{
	/**
	 * @brief Default constructor
	 */
	VertexShaderGenerator();

	// Overridden
	const bool generate( vgeGL::engine::Engine * engine );
};



} // namespace engine

} // namespace vgeGL

#endif //#ifndef _VGEGL_ENGINE_VERTEXSHADERGENERATOR_HPP
