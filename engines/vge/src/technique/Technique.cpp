// VGSDK - Copyright (C) 2004, 2006, 2007, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vge/technique/Technique.hpp"

//#include <vgd/Shp.hpp>
#include <vge/pass/Pass.hpp>



namespace vge
{

namespace technique
{



Technique::Technique()
:	m_currentPass	(	0 		),
	m_inPass		(	false	),
	
	m_engine			(	0	),
	m_traverseElements	(	0	)
{}



Technique::~Technique()
{}



/*void Technique::resetEngine()
{
	engine()->resetStateStack();
	engine()->resetMatrices();
}*/



void Technique::prepareEval( vge::engine::Engine *engine, vge::visitor::TraverseElementVector* traverseElements )
{
	assert( !m_inPass );

	m_currentPass = 0;
	
	m_engine			= engine;
	m_traverseElements	= traverseElements;
}



void Technique::finishEval()
{
	assert( !m_inPass );
	assert( m_currentPass > 0 && "No evaluation pass." );
	
	m_engine			= 0;
	m_traverseElements	= 0;
}



void Technique::beginPass()
{
	assert( !m_inPass );
	
	++m_currentPass;
	m_inPass = true;
}



void Technique::endPass()
{
	assert( m_inPass );	
	
	m_inPass = false;
}



const uint32 Technique::getCurrentPass() const
{
	return m_currentPass;
}



const bool Technique::isInsideAPass() const
{
	return m_inPass;
}



void Technique::evaluatePass( vgd::Shp< vge::pass::Pass > pass, vgd::Shp< vge::service::Service > service )
{
	beginPass();

	assert( m_engine != 0 );
	assert( m_traverseElements != 0 );
		
	pass->apply( this, m_engine, getTraverseElements(), service );
	
	endPass();
}



vge::visitor::TraverseElementVector	*Technique::getTraverseElements() const
{
	return m_traverseElements;
}



} // namespace technique

} // namespace vge


///*
// @todo FIXME
//BeginFirstPass(); reset*();
//EndFirstPass();
//For an active technique, this method is invoked after the traversal of the scene graph. The changes made in "preparePass()" should be undone here
//
//
//
//	engine();
//	nodes();
//	
//	vge::engine::Engine&										m_engine;
//	vge::visitor::NodeCollectorExtended<Visitors>&	m_collector
//	
//
//
//MainTechnique()
//{
//	reset();
//	
//	CollectNodes();
//
//	Begin();
//	
//	BeginFirstPass();
//	for_each();
//	EndFirstPass(); disregard();
//
//	BeginNextPass( push true); resetState(); resetMatrix();
//	for_each();
//	EndNextPass();
//	
//	End(); regard();

