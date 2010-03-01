// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/engine/GeometryShaderGenerator.hpp"

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
	m_decl.clear();
	m_code1.clear();
	m_code2.clear();

	return true;
}



} // namespace engine

} // namespace vgeGL
