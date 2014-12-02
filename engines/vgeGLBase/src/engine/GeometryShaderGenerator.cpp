//// VGSDK - Copyright (C) 2008, 2012, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#include "vgeGLBase/engine/GeometryShaderGenerator.hpp"
//
//#include <vgd/node/Program.hpp>
//#include "vgeGLBase/engine/Engine.hpp"
//
//
//
//namespace vgeGLBase
//{
//
//namespace engine
//{
//
//
//
//// GeometryShaderGenerator
//GeometryShaderGenerator::GeometryShaderGenerator()
//:	ShaderGenerator( glo::GLSLProgram::GEOMETRY )
//{
//}
//
//
//
//const bool GeometryShaderGenerator::generate( vgeGLBase::engine::Engine * engine )
//{
//	// Retrieves the GLSL state
//	GLSLState& state = engine->getGLSLState();
//
//	// Clears the code repository
//	m_decl.clear();
//	m_code1.clear();
//	m_code2.clear();
//
////	m_decl += getDefines( state );
//
//	m_code2 +=
//		
//		"#version 410 compatibility\n"
//		"\n"
//		"#define POSITION		0\n"
//		"#define COLOR			3\n"
//		"#define TEXCOORD		4\n"
//		"#define FRAG_COLOR		0\n"
//		"\n"
//		"layout(triangles, invocations = 1) in;\n"
//		"layout(triangles, max_vertices = 3) out;\n"
//		"\n"
//		"in block\n"
//		"{\n"
//		"	vec4 Color;\n"
//		"} In[];\n"
//		"\n"
//		"out block\n"
//		"{\n"
//		"	vec4 Color;\n"
//		"} Out;\n"
//		"\n"
//		"in vec3 ecNormal[];\n"
//		"in vec4 ecPosition[];\n"
//		"layout (location = 0) out vec3 myNormal;\n"
//		"layout (location = 1) out vec4 myPosition;\n"
//		"\n"
//		"if (bump)\n"
//		"{\n"
//		"	out vec3 myTsLightVector[NUM_LIGHT];\n"
//		"	out vec3 myTsLightDirection[NUM_LIGHT];\n"
//		"	out vec3 myTsViewVector;\n"
//		"	out vec2 myVTexCoords00;\n"
//		"	out vec2 myVTexCoords01;\n"
//		"	out vec2 myVTexCoords02;\n"
//		"	out vec2 myVTexCoords10;\n"
//		"	out vec2 myVTexCoords12;\n"
//		"	out vec2 myVTexCoords20;\n"
//		"	out vec2 myVTexCoords21;\n"
//		"	out vec2 myVTexCoords22;\n"
//		"	in vec3 tsLightVector[NUM_LIGHT][];\n"
//		"	in vec3 tsLightDirection[NUM_LIGHT][];\n"
//		"	in vec3 tsViewVector[];\n"
//		"	in vec2 vTexCoords00[];\n"
//		"	in vec2 vTexCoords01[];\n"
//		"	in vec2 vTexCoords02[];\n"
//		"	in vec2 vTexCoords10[];\n"
//		"	in vec2 vTexCoords12[];\n"
//		"	in vec2 vTexCoords20[];\n"
//		"	in vec2 vTexCoords21[];\n"
//		"	in vec2 vTexCoords22[];\n"			
//		"}\n"
//		"\n"
//		"void main()\n"
//		"{	\n"
//		"	for(int i = 0; i < gl_in.length(); ++i)\n"
//		"	{\n"
//		"		gl_Position = gl_in[i].gl_Position;\n"
//		"		myNormal = ecNormal[i];\n"
//		"		myPosition = ecPosition[i];\n"
//		"		if (bump)\n"
//		"		{\n"
//		"			myTsLightVector[NUM_LIGHT] = tsLightVector[NUM_LIGHT][i];\n"
//		"			myTsLightDirection[NUM_LIGHT] = tsLightDirection[NUM_LIGHT][i];\n"
//		"			myTsViewVector = tsViewVector[i];\n"
//		"			myVTexCoords00 = vTexCoords00[i];\n"
//		"			myVTexCoords01 = vTexCoords01[i];\n"
//		"			myVTexCoords02 = vTexCoords02[i];\n"
//		"			myVTexCoords10 = vTexCoords10[i];\n"
//		"			myVTexCoords12 = vTexCoords12[i];\n"
//		"			myVTexCoords20 = vTexCoords20[i];\n"
//		"			myVTexCoords21 = vTexCoords21[i];\n"
//		"			myVTexCoords22 = vTexCoords22[i];\n"
//		"		}\n"
//		"		Out.Color = In[i].Color;\n"
//		"		EmitVertex();\n"
//		"	}\n"
//		"	EndPrimitive();\n"
//		"}\n";
//
//	// Test if custom program must be installed
//	if ( state.isEnabled( PROGRAM ) )
//	{
//		vgd::node::Program * program = state.getProgram();
//		assert( program );
//
//		if ( program->getGeometryUse() )
//		{
//			std::string shaderStr = program->getGeometry();
//			m_decl.clear();
//			m_code2.clear();
//			m_code1 = shaderStr;
//			return true;
//		}
//	}
//
//	return true;
//}
//
//
//
//} // namespace engine
//
//} // namespace vgeGLBase
//