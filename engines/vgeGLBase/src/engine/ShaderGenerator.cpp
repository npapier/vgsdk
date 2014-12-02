//// VGSDK - Copyright (C) 2008, 2010, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#include "vgeGL/engine/ShaderGenerator.hpp"
//
//#include "vgeGL/engine/Engine.hpp"
//
//
//
//namespace vgeGL
//{
//
//namespace engine
//{
//
//
//
//ShaderGenerator::ShaderGenerator( const glo::GLSLProgram::ShaderType shaderType )
//:	m_shaderType	( shaderType ),
//	m_mainDirtyFlag	( "main" ),
//	m_isEnabled		( true )
//	//m_decl, m_code1, m_code2
//{}
//
//
//
//const glo::GLSLProgram::ShaderType ShaderGenerator::getShaderType() const
//{
//	return m_shaderType;
//}
//
//
//
//vgd::field::DirtyFlag& ShaderGenerator::getMainDirtyFlag()
//{
//	return m_mainDirtyFlag;
//}
//
//
//
//void ShaderGenerator::setEnabled( const bool isEnabled )
//{
//	m_isEnabled = isEnabled;
//}
//
//
//
//const bool ShaderGenerator::isEnabled() const
//{
//	return m_isEnabled;
//}
//
//
//
//const std::string ShaderGenerator::getCode() const
//{
//	return m_decl + m_code1 + m_code2;
//}
//
//
//
//} // namespace engine
//
//} // namespace vgeGL
//