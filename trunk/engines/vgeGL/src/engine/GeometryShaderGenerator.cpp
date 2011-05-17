// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/engine/GeometryShaderGenerator.hpp"

#include <vgd/node/Program.hpp>
#include "vgeGL/engine/Engine.hpp"



namespace vgeGL
{

namespace engine
{



// GeometryShaderGenerator
GeometryShaderGenerator::GeometryShaderGenerator()
:	ShaderGenerator( glo::GLSLProgram::GEOMETRY )
{
}



const bool GeometryShaderGenerator::generate( vgeGL::engine::Engine * engine )
{
	// Retrieves the GLSL state
	GLSLState& state = engine->getGLSLState();

	// Clears the code repository
	m_decl.clear();
	m_code1.clear();
	m_code2.clear();

	m_decl += GLSLHelpers::getVersionDecl();
	m_decl += GLSLHelpers::getVGSDKUniformDecl();

	// Test if custom program must be installed
	if ( state.isEnabled( PROGRAM ) )
	{
		vgd::node::Program * program = state.getProgram();
		assert( program );

		std::string shaderStr;
		program->getShader( vgd::node::Program::GEOMETRY, shaderStr );

		m_code1 = shaderStr;

		return true;
	}

	return true;
}



} // namespace engine

} // namespace vgeGL
