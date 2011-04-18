// VGSDK - Copyright (C) 2004, 2006, 2007, 2008, 2009, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vge/technique/Technique.hpp"

#include "vge/engine/Engine.hpp"
#include "vge/pass/Pass.hpp"
#include "vge/service/Painter.hpp"



namespace vge
{

namespace technique
{



Technique::Technique()
:	m_currentPass		(	0 						),
	m_inPass			(	false					),
	//m_passIsolationMask	(	PassIsolationMask(0)	),

	m_engine			(	0	),
	m_traverseElements	(	0	),

	m_paintService		(	vge::service::Painter::create() )

	//m_passDescription
{}



Technique::~Technique()
{
	// Virtual destructor
}



void Technique::prepareEval( vge::engine::Engine *engine, vge::visitor::TraverseElementVector* traverseElements )
{
	m_currentPass = 0;
	assert( !m_inPass && "prepareEval() called inside a pass." );
	m_passIsolationMask.resize(0);//	= PassIsolationMask(0);

	m_engine			= engine;
	m_traverseElements	= traverseElements;

	//
	engine->resetStateStack(); // @todo resetEval(); ? see Technique::prepareEval in vgeGL
}



void Technique::finishEval()
{
	assert( !m_inPass && "finishEval() called inside a pass." );
	assert( m_currentPass > 0 && "No evaluation pass." );

	m_engine			= 0;
	m_traverseElements	= 0;
}



void Technique::setPassDescription( const std::string description )
{
	m_passDescription = description;
}



void Technique::beginPass( const PassIsolationMask isolationMask )
{
	assert( !m_inPass && "beginPass() called inside a pass." );

	++m_currentPass;
	m_inPass = true;

	// Processes isolation mask
	applyPassIsolation( m_engine, isolationMask );
}



void Technique::endPass()
{
	assert( m_inPass && "endPass() called outside a pass." );

	// Processes isolation mask
	unapplyPassIsolation( m_engine );

	//
	m_inPass = false;
}



void Technique::applyPassIsolation( vge::engine::Engine *engine, const PassIsolationMask isolationMask )
{
	if ( isolationMask & RESET_MATRICES )
	{
		engine->resetMatrices();
	}

	if ( isolationMask & REGARD_ALL )
	{
		engine->regard();
	}

	if ( isolationMask & PUSH_POP_STATE )
	{
		engine->push();
	}

	// Stores isolation mask for endPass()
	m_passIsolationMask.push_back( isolationMask );
}


void Technique::unapplyPassIsolation( vge::engine::Engine *engine )
{
	const PassIsolationMask passIsolationMask = m_passIsolationMask.back();

	if ( passIsolationMask & PUSH_POP_STATE )
	{
		engine->pop();
	}

	// Resets isolation mask
	m_passIsolationMask.pop_back();
}



const uint Technique::getCurrentPass() const
{
	return m_currentPass;
}



const bool Technique::isInsideAPass() const
{
	return m_inPass;
}



void Technique::evaluatePass(	vgd::Shp< vge::pass::Pass > pass, vgd::Shp< vge::service::Service > service,
								vge::engine::Engine * engine,
								const PassIsolationMask isolationMask, const bool nestedPass )
{
	assert( pass != 0 );
	assert( service != 0 );
	assert( engine != 0 );

	if ( nestedPass )
	{
		applyPassIsolation( engine, isolationMask );
	}
	else
	{
		beginPass( isolationMask );
	}

	//assert( m_engine != 0 );
	assert( getTraverseElements() != 0 );

	pass->apply( this, engine, getTraverseElements(), service );

	if ( nestedPass )
	{
		unapplyPassIsolation( engine );
	}
	else
	{
		endPass();
	}
}



/*void Technique::push()
{
	assert( m_engine != 0 );

	m_engine getEngine()->push();
}


void Technique::pop()
{
	assert( m_engine != 0 );

	m_engine getEngine()->pop();
}*/



vge::visitor::TraverseElementVector *Technique::getTraverseElements() const
{
	return m_traverseElements;
}



vgd::Shp< vge::service::Service > Technique::paintService()
{
	return m_paintService;
}



/*vge::engine::Engine * Technique::getEngine() const
{
	return m_engine;
}*/



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

