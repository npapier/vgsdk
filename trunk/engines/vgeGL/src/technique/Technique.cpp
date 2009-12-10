// VGSDK - Copyright (C) 2004, 2007, 2008, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgeGL/technique/Technique.hpp"

#include "vgeGL/engine/Engine.hpp"
#include "vgeGL/engine/ProgramGenerator.hpp"
//#include "vgeGL/engine/ShaderGenerator.hpp"
#include "vgeGL/pass/Pass.hpp"



namespace vgeGL
{

namespace technique
{



Technique::Technique()
:	m_engine(0)
{}



void Technique::beginPass( const PassIsolationMask isolationMask )
{
	vge::technique::Technique::beginPass(isolationMask);

	if ( isGL_GREMEDY_string_marker() )
	{
		std::stringstream ss;
		ss << "BEGIN:" << m_passDescription;
		glStringMarkerGREMEDY( 0, ss.str().c_str() );
	}
}

void Technique::endPass()
{
	vge::technique::Technique::endPass();

	if ( isGL_GREMEDY_string_marker() )
	{
		std::stringstream ss;
		ss << "END:" << m_passDescription;
		glStringMarkerGREMEDY( 0, ss.str().c_str() );
		m_passDescription.clear();
	}
}



void Technique::prepareEval( vgeGL::engine::Engine *engine, vge::visitor::TraverseElementVector* traverseElements )
{
	//
	::vge::technique::Technique::prepareEval( engine, traverseElements );

	//
	m_engine = engine;

// ???????????????????
// @todo move to pass
//	engine->getGLSLState().reset( engine->getMaxLights(), engine->getMaxTexUnits() );
// @todo disable the two following lines, and see stack<GL/GLSLState> growing !!! (TBT)
//	engine->getGLStateStack().clear( GLState() );
//	engine->getGLSLStateStack().clear( GLSLState(getMaxLights(), getMaxTexUnits()) );

	if ( engine->isGLSLEnabled() )
	{
		//
		engine->getGLSLProgramGenerator()->dirty();
	}
}



void Technique::evaluatePass(	vgd::Shp< vge::pass::Pass > pass, vgd::Shp< vge::service::Service > service,
								const PassIsolationMask isolationMask, const bool nestedPass )
{
	assert( pass != 0 );
	assert( service != 0 );

	if ( nestedPass )
	{
		applyPassIsolation( m_engine, isolationMask );
	}
	else
	{
		beginPass( isolationMask );
	}

	assert( m_engine != 0 );
	assert( getTraverseElements() != 0 );

	pass->apply( this, m_engine, getTraverseElements(), service );

	if ( nestedPass )
	{
		unapplyPassIsolation( m_engine );
	}
	else
	{
		endPass();
	}
}



vge::engine::Engine * Technique::getEngine() const
{
	return m_engine;
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
