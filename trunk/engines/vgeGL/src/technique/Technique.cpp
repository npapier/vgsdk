// VGSDK - Copyright (C) 2004, 2007, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/technique/Technique.hpp"

#include "vgeGL/engine/Engine.hpp"
#include "vgeGL/engine/ProgramGenerator.hpp"
#include "vgeGL/engine/ShaderGenerator.hpp"
#include "vgeGL/pass/Pass.hpp"



namespace vgeGL
{

namespace technique
{



Technique::Technique()
:	m_engine(0)
{}



void Technique::prepareEval( vgeGL::engine::Engine *engine, vge::visitor::TraverseElementVector* traverseElements )
{
	//
	::vge::technique::Technique::prepareEval( engine, traverseElements );

	//
	m_engine = engine;

	// @todo move to pass
	engine->getGLSLState().reset( engine->getMaxTexUnits() );

	if ( engine->isGLSLEnabled() )
	{
		//
		engine->getGLSLProgramGenerator()->dirty();

		//

		vgeGL::engine::GLSLHelpers::clearLightFlags();
	}
}



void Technique::evaluatePass( vgd::Shp< vge::pass::Pass > pass, vgd::Shp< vge::service::Service > service )
{
	beginPass();

	assert( m_engine != 0 );
	assert( getTraverseElements() != 0 );

	pass->apply( this, m_engine, getTraverseElements(), service );

	endPass();
}



void Technique::prepareEval( vge::engine::Engine * /*engine*/, vge::visitor::TraverseElementVector* /*traverseElements*/ )
{
	assert( false );
}



void Technique::apply( vge::engine::Engine * /*engine*/, vge::visitor::TraverseElementVector* /*traverseElements*/ )
{
	assert( false) ;
}


	
} // namespace technique

} // namespace vgeGL
