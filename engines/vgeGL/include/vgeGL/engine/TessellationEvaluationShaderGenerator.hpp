// VGSDK - Copyright (C) 2012, Alexandre Di Pino.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Alexandre Di Pino

#ifndef _VGEGL_ENGINE_TESSELLATIONEVALUATIONSHADERGENERATOR_HPP
#define _VGEGL_ENGINE_TESSELLATIONEVALUATIONSHADERGENERATOR_HPP

#include "vgeGL/engine/ShaderGenerator.hpp"



namespace vgeGL
{

namespace engine
{



/**
 * @brief Tessellation Evaluation Shader code generator.
 */
struct VGEGL_API TessellationEvaluationShaderGenerator : public ShaderGenerator
{
	/**
	 * @brief Default constructor
	 */
	TessellationEvaluationShaderGenerator();

	// Overridden
	const bool generate( vgeGL::engine::Engine * engine );
};



} // namespace engine

} // namespace vgeGL

#endif //#ifndef _VGEGL_ENGINE_TESSELLATIONEVALUATIONSHADERGENERATOR_HPP