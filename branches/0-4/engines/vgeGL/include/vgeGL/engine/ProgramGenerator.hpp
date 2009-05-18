// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_ENGINE_PROGRAMGENERATOR_HPP
#define _VGEGL_ENGINE_PROGRAMGENERATOR_HPP

#include <vgd/Shp.hpp>
#include <vgd/field/DirtyFlag.hpp>

#include "vgeGL/vgeGL.hpp"



namespace vgeGL { namespace engine 
{ 
	struct Engine;
	struct FragmentShaderGenerator;
	struct GeometryShaderGenerator;
	struct ShaderGenerator;
	struct VertexShaderGenerator;
} }



namespace vgeGL
{

namespace engine
{



struct VGEGL_API ProgramGenerator : public vgd::field::DirtyFlag
{
	/**
	 * @brief Default constructor
	 */
	ProgramGenerator();


	// @todo returns list< ShaderType > containing modified shader
	void generate( vgeGL::engine::Engine * engine );

	/**
	 * @brief Retrieves the full GLSL program.
	 *
	 * @return the concatenation of all enabled shaders
	 */
	const std::string getCode();

	vgd::Shp< VertexShaderGenerator >			getVertexShaderGenerator();
	const vgd::Shp< VertexShaderGenerator >		getVertexShaderGenerator() const;

	vgd::Shp< FragmentShaderGenerator >			getFragmentShaderGenerator();
	const vgd::Shp< FragmentShaderGenerator >	getFragmentShaderGenerator() const;

	vgd::Shp< GeometryShaderGenerator >			getGeometryShaderGenerator();
	const vgd::Shp< GeometryShaderGenerator >	getGeometryShaderGenerator() const;


private:
	typedef std::vector< vgd::Shp<ShaderGenerator> > GeneratorContainer;
	GeneratorContainer m_generators;

	vgd::Shp< VertexShaderGenerator		>	m_vertex;
	vgd::Shp< FragmentShaderGenerator	>	m_fragment;
	vgd::Shp< GeometryShaderGenerator	>	m_geometry;
};



} // namespace engine

} // namespace vgeGL

#endif //#ifndef _VGEGL_ENGINE_PROGRAMGENERATOR_HPP
