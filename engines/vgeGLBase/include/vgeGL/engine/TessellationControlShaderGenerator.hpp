// VGSDK - Copyright (C) 2012, Alexandre Di Pino.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Alexandre Di Pino

#ifndef _VGEGL_ENGINE_TESSELLATIONCONTROLSHADERGENERATOR_HPP
#define _VGEGL_ENGINE_TESSELLATIONCONTROLSHADERGENERATOR_HPP

#include "vgeGL/engine/ShaderGenerator.hpp"



namespace vgeGL
{

namespace engine
{



/**
 * @brief Tessellation Control Shader code generator.
 */
struct VGEGL_API TessellationControlShaderGenerator : public ShaderGenerator
{
	/**
	 * @brief Default constructor
	 */
	TessellationControlShaderGenerator();

	// Overridden;
	const bool generate( vgeGL::engine::Engine * engine );
};



} // namespace engine

} // namespace vgeGL

#endif //#ifndef _VGEGL_ENGINE_TESSELLATIONCONTROLSHADERGENERATOR_HPP