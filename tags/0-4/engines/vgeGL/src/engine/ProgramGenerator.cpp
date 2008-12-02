// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/engine/ProgramGenerator.hpp"

#include "vgeGL/engine/FragmentShaderGenerator.hpp"
#include "vgeGL/engine/GeometryShaderGenerator.hpp"
#include "vgeGL/engine/VertexShaderGenerator.hpp"



namespace vgeGL
{

namespace engine
{



ProgramGenerator::ProgramGenerator()
:	DirtyFlag( "ProgramGenerator" ),
	m_vertex(	vgd::makeShp(new VertexShaderGenerator()) ),
	m_fragment(	vgd::makeShp(new FragmentShaderGenerator()) ),
	m_geometry(	vgd::makeShp(new GeometryShaderGenerator()) )
{
	m_generators.reserve(3);
	m_generators.push_back( m_vertex );
	m_generators.push_back( m_fragment );
	m_generators.push_back( m_geometry );
}



void ProgramGenerator::generate( vgeGL::engine::Engine * engine )
{
	if ( isDirty() )
	{
		for(	GeneratorContainer::iterator	i		= m_generators.begin(),
												iEnd	= m_generators.end();
				i != iEnd;
				++i )
		{
			vgd::Shp< ShaderGenerator > element = *i;
			assert( element != 0 );

			if (	element->isEnabled() &&
					element->getMainDirtyFlag().isDirty() )
			{
				const bool hasBeenGenerated = element->generate( engine );
				// @todo uses hasBeenGenerated
			}
			// else nothing to do
		}

		// validate();
	}
	// else nothing to do

	// assert( isValid() );
}



const std::string ProgramGenerator::getCode()
{
	std::string retVal;

	for(	GeneratorContainer::iterator	i		= m_generators.begin(),
											iEnd	= m_generators.end();
			i != iEnd;
			++i )
	{
		vgd::Shp< ShaderGenerator > element = *i;
		assert( element != 0 );

		if ( element->isEnabled() )
		{
			retVal += element->getCode();
		}
	}

	return retVal;
}



vgd::Shp< VertexShaderGenerator > ProgramGenerator::getVertexShaderGenerator()
{
	return m_vertex;
}


const vgd::Shp< VertexShaderGenerator > ProgramGenerator::getVertexShaderGenerator() const
{
	return m_vertex;
}


vgd::Shp< FragmentShaderGenerator > ProgramGenerator::getFragmentShaderGenerator()
{
	return m_fragment;
}


const vgd::Shp< FragmentShaderGenerator > ProgramGenerator::getFragmentShaderGenerator() const
{
	return m_fragment;
}


vgd::Shp< GeometryShaderGenerator > ProgramGenerator::getGeometryShaderGenerator()
{
	return m_geometry;
}


const vgd::Shp< GeometryShaderGenerator > ProgramGenerator::getGeometryShaderGenerator() const
{
	return m_geometry;
}



} // namespace engine

} // namespace vgeGL
