//// VGSDK - Copyright (C) 2008, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#include "vgeGL/engine/ProgramGenerator.hpp"
//
//#include "vgeGL/engine/FragmentShaderGenerator.hpp"
//#include "vgeGL/engine/GeometryShaderGenerator.hpp"
//#include "vgeGL/engine/VertexShaderGenerator.hpp"
//#include "vgeGL/engine/TessellationControlShaderGenerator.hpp"
//#include "vgeGL/engine/TessellationEvaluationShaderGenerator.hpp"
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
//ProgramGenerator::ProgramGenerator()
//:	DirtyFlag( "ProgramGenerator" ),
//	m_vertex(	vgd::makeShp(new VertexShaderGenerator()) ),
//	m_tessControl( vgd::makeShp(new TessellationControlShaderGenerator()) ),
//	m_geometry(	vgd::makeShp(new GeometryShaderGenerator()) ), 
//	m_tessEval( vgd::makeShp(new TessellationEvaluationShaderGenerator()) ),
//	m_fragment(	vgd::makeShp(new FragmentShaderGenerator()) )
//{
//	m_generators.reserve(5);
//	m_generators.push_back( m_vertex );
//	m_generators.push_back( m_tessControl );
//	m_generators.push_back( m_geometry );
//	m_generators.push_back( m_tessEval );
//	m_generators.push_back( m_fragment );
//}
//
//
//
//void ProgramGenerator::generate( vgeGL::engine::Engine * engine )
//{
//	if ( isDirty() )
//	{
//		for(	GeneratorContainer::iterator	i		= m_generators.begin(),
//												iEnd	= m_generators.end();
//				i != iEnd;
//				++i )
//		{
//			vgd::Shp< ShaderGenerator > element = *i;
//			assert( element != 0 );
//
//			if (	element->isEnabled() &&
//					element->getMainDirtyFlag().isDirty() )
//			{
//				/*const bool hasBeenGenerated = */element->generate( engine );
//				// @todo uses hasBeenGenerated
//			}
//			// else nothing to do
//		}
//
//		// validate();
//	}
//	// else nothing to do
//
//	//assert( isValid() );
//}
//
//
//
//const std::string ProgramGenerator::getCode()
//{
//	std::string retVal;
//
//	for(	GeneratorContainer::iterator	i		= m_generators.begin(),
//											iEnd	= m_generators.end();
//			i != iEnd;
//			++i )
//	{
//		vgd::Shp< ShaderGenerator > element = *i;
//		assert( element != 0 );
//
//		if ( element->isEnabled() )
//		{
//			retVal += element->getCode();
//		}
//	}
//
//	return retVal;
//}
//
//
//
//vgd::Shp< VertexShaderGenerator > ProgramGenerator::getVertexShaderGenerator()
//{
//	return m_vertex;
//}
//
//
//const vgd::Shp< VertexShaderGenerator > ProgramGenerator::getVertexShaderGenerator() const
//{
//	return m_vertex;
//}
//
//
//vgd::Shp< FragmentShaderGenerator > ProgramGenerator::getFragmentShaderGenerator()
//{
//	return m_fragment;
//}
//
//
//const vgd::Shp< FragmentShaderGenerator > ProgramGenerator::getFragmentShaderGenerator() const
//{
//	return m_fragment;
//}
//
//
//vgd::Shp< GeometryShaderGenerator > ProgramGenerator::getGeometryShaderGenerator()
//{
//	return m_geometry;
//}
//
//
//const vgd::Shp< GeometryShaderGenerator > ProgramGenerator::getGeometryShaderGenerator() const
//{
//	return m_geometry;
//}
//
//
//vgd::Shp< TessellationControlShaderGenerator >	 ProgramGenerator::getTessellationControlShaderGenerator()
//{
//	return m_tessControl;
//}
//
//
//const vgd::Shp< TessellationControlShaderGenerator >	 ProgramGenerator::getTessellationControlShaderGenerator() const
//{
//	return m_tessControl;
//}
//
//
//vgd::Shp< TessellationEvaluationShaderGenerator >	 ProgramGenerator::getTessellationEvaluationShaderGenerator()
//{
//	return m_tessEval;
//}
//
//
//const vgd::Shp< TessellationEvaluationShaderGenerator >	 ProgramGenerator::getTessellationEvaluationShaderGenerator() const
//{
//	return m_tessEval;
//}
//
//
//} // namespace engine
//
//} // namespace vgeGL
//