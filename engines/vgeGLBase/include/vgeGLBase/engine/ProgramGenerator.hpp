//// VGSDK - Copyright (C) 2008, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#ifndef _VGEGLBASE_ENGINE_PROGRAMGENERATOR_HPP
//#define _VGEGLBASE_ENGINE_PROGRAMGENERATOR_HPP
//
//#include <vector>
//#include <vgd/Shp.hpp>
//#include <vgd/field/DirtyFlag.hpp>
//
//#include "vgeGLBase/vgeGLBase.hpp"
//
//
//
//namespace vgeGLBase { namespace engine 
//{ 
//	struct Engine;
//	struct FragmentShaderGenerator;
//	struct GeometryShaderGenerator;
//	struct ShaderGenerator;
//	struct VertexShaderGenerator;
//	struct TessellationControlShaderGenerator;
//	struct TessellationEvaluationShaderGenerator;
//} }
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
//struct VGEGLBASE_API ProgramGenerator : public vgd::field::DirtyFlag
//{
//	/**
//	 * @brief Default constructor
//	 */
//	ProgramGenerator();
//
//
//	// @todo returns list< ShaderType > containing modified shader
//	void generate( vgeGLBase::engine::Engine * engine );
//
//	/**
//	 * @brief Retrieves the full GLSL program.
//	 *
//	 * @return the concatenation of all enabled shaders
//	 */
//	const std::string getCode();
//
//	vgd::Shp< VertexShaderGenerator >			getVertexShaderGenerator();
//	const vgd::Shp< VertexShaderGenerator >		getVertexShaderGenerator() const;
//
//	vgd::Shp< FragmentShaderGenerator >			getFragmentShaderGenerator();
//	const vgd::Shp< FragmentShaderGenerator >	getFragmentShaderGenerator() const;
//
//	vgd::Shp< GeometryShaderGenerator >			getGeometryShaderGenerator();
//	const vgd::Shp< GeometryShaderGenerator >	getGeometryShaderGenerator() const;
//
//	vgd::Shp< TessellationControlShaderGenerator >	getTessellationControlShaderGenerator();
//	const vgd::Shp< TessellationControlShaderGenerator >	getTessellationControlShaderGenerator() const;
//
//	vgd::Shp< TessellationEvaluationShaderGenerator >	getTessellationEvaluationShaderGenerator();
//	const vgd::Shp< TessellationEvaluationShaderGenerator >	getTessellationEvaluationShaderGenerator() const;
//
//private:
//	typedef std::vector< vgd::Shp<ShaderGenerator> > GeneratorContainer;
//	GeneratorContainer m_generators;
//
//	vgd::Shp< VertexShaderGenerator		>	m_vertex;
//	vgd::Shp< FragmentShaderGenerator	>	m_fragment;
//	vgd::Shp< GeometryShaderGenerator	>	m_geometry;
//	vgd::Shp< TessellationControlShaderGenerator > m_tessControl;
//	vgd::Shp< TessellationEvaluationShaderGenerator > m_tessEval;
//};
//
//
//
//} // namespace engine
//
//} // namespace vgeGLBase
//
//#endif //#ifndef _VGEGLBASE_ENGINE_PROGRAMGENERATOR_HPP
//