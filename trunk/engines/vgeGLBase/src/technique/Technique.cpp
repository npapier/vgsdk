//// VGSDK - Copyright (C) 2004, 2007, 2008, 2009, 2010, 2011, 2013, Nicolas Papier.
//// Distributed under the terms of the GNU Library General Public License (LGPL)
//// as published by the Free Software Foundation.
//// Author Nicolas Papier
//
//#include "vgeGLBase/technique/Technique.hpp"
//
//#include "vgeGLBase/engine/Engine.hpp"
//#include "vgeGLBase/engine/GLSLState.hpp"
//#include "vgeGLBase/engine/ProgramGenerator.hpp"
////#include "vgeGLBase/engine/ShaderGenerator.hpp"
//#include "vgeGLBase/pass/Pass.hpp"
//
//
//
//namespace vgeGLBase
//{
//
//namespace technique
//{
//
//
//
//Technique::Technique()
//:	m_engine(0)
//{}
//
//
//
//void Technique::beginPass( const PassIsolationMask isolationMask )
//{
//	if ( isGL_GREMEDY_string_marker() )
//	{
//		std::stringstream ss;
//		ss << "initializePass()";
//		glStringMarkerGREMEDY( 0, ss.str().c_str() );
//	}
//
//	//
//	using vgeGLBase::engine::GLState;
//	using vgeGLBase::engine::GLSLState;
//
//	vgAssert( m_engine->getGLStateStack().getSize() == 1 );
//	vgAssert( m_engine->getGLSLStateStack().getSize() == 1 );
//
//	vge::technique::Technique::beginPass(isolationMask);
//
//	m_engine->clearTextureUnits();
//
//	vgAssert( m_engine->getGLStateStack().getSize() == 2 );
//	vgAssert( m_engine->getGLSLStateStack().getSize() == 2 );
//
//	//m_engine->getGLStateStack().clear( GLState() );
//	//m_engine->getGLSLState().reset( m_engine->getMaxLights(), m_engine->getMaxTexUnits() );
//
//	if ( isGL_GREMEDY_string_marker() )
//	{
//		std::stringstream ss;
//		ss << "BEGIN: " << m_passDescription;
//		glStringMarkerGREMEDY( 0, ss.str().c_str() );
//	}
//}
//
//
//
//void Technique::endPass()
//{
//	if ( isGL_GREMEDY_string_marker() )
//	{
//		std::stringstream ss;
//		ss << "END: " << m_passDescription;
//		glStringMarkerGREMEDY( 0, ss.str().c_str() );
//		m_passDescription.clear();
//	}
//
//	vge::technique::Technique::endPass();
//
//	// @todo doc
//	//dynamic_cast<vgeGLBase::engine::Engine*>(getEngine())->setOutputBuffers();
//
//	if ( isGL_GREMEDY_string_marker() )
//	{
//		std::stringstream ss;
//		glStringMarkerGREMEDY( 0, "endPass" );
//	}
//}
//
//
//
//vgeGLBase::engine::Engine * Technique::glEngine() const
//{
//	return m_engine;
//}
//
//
//
//void Technique::prepareEval( vgeGLBase::engine::Engine *engine, vge::visitor::TraverseElementVector* traverseElements )
//{
//	//
//	::vge::technique::Technique::prepareEval( engine, traverseElements );
//
//	//
//	m_engine = engine;
//
//	//
//	using vgeGLBase::engine::GLState;
//	using vgeGLBase::engine::GLSLState;
//
//	engine->getGLStateStack().clear( vgd::makeShp(new GLState()) );
//	engine->getGLSLStateStack().clear( vgd::makeShp(new GLSLState(engine->getMaxTexUnits())) );
//
//	// @todo doc
//	engine->setOutputBuffers();
//	engine->setCurrentPrivateOutputBuffers();
//
//	if ( engine->isGLSLEnabled() )
//	{
//		engine->getGLSLProgramGenerator()->dirty();
//	}
//}
//
//
//
//void Technique::evaluatePass(	vgd::Shp< vge::pass::Pass > pass, vgd::Shp< vge::service::Service > service,
//								const PassIsolationMask isolationMask, const bool nestedPass )
//{
//	vgAssert( pass != 0 );
//	vgAssert( service != 0 );
//
//	if ( nestedPass )
//	{
//		applyPassIsolation( m_engine, isolationMask );
//	}
//	else
//	{
//		beginPass( isolationMask );
//	}
//
//	vgAssert( m_engine != 0 );
//	vgAssert( getTraverseElements() != 0 );
//
//	pass->apply( this, m_engine, getTraverseElements(), service );
//
//	if ( nestedPass )
//	{
//		unapplyPassIsolation( m_engine );
//	}
//	else
//	{
//		endPass();
//	}
//}
//
//
//
//void Technique::prepareEval( vge::engine::Engine * /*engine*/, vge::visitor::TraverseElementVector* /*traverseElements*/ )
//{
//	vgAssert( false );
//}
//
//
//
//void Technique::apply( vge::engine::Engine * /*engine*/, vge::visitor::TraverseElementVector* /*traverseElements*/ )
//{
//	vgAssert( false) ;
//}
//
//
//
//} // namespace technique
//
//} // namespace vgeGLBase
//