// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vge/technique/Technique.hpp"



namespace vge
{

namespace technique
{



Technique::Technique() :
	m_currentPass	(	0 		),
	m_inPass		(	false	)
{
}



Technique::~Technique()
{
}



/*void Technique::resetEngine()
{
	engine()->resetStateStack();
	engine()->resetMatrices();
}*/



void Technique::prepareEval()
{
	assert( !m_inPass );

	m_currentPass = 0;
}



void Technique::finishEval()
{
	assert( !m_inPass );
	assert( m_currentPass > 0 && "No evaluation pass." );
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



uint32 Technique::currentPass() const
{
	return ( m_currentPass );
}



/*template< typename Visitors >
void Technique::push()
{
	assert( false ); // ???
}



void Technique::pop()
{
	assert( false );	// ???
}*/



//const vge::engine::Engine *Technique::engine() const
//{
//	return ( m_pEngine );
//}
//
//
//
//vge::engine::Engine *Technique::engine()
//{
//	return ( m_pEngine );
//}
//
//
//
//const vge::visitor::NodeCollectorExtended<Visitors> *Technique::collector() const
//{
//	return ( m_pCollector );
//}
//
//
//
//vge::visitor::NodeCollectorExtended<Visitors> *Technique::collector()
//{
//	return ( m_pCollector );
//}



//void Technique::forEach( const vgd::Shp< vge::service::Service > service )
//{
//	const typename std::vector< typename vge::visitor::NodeCollectorExtended<Visitors>::TraverseElement >& nodes
//			= collector().getNodes();
//	
//	typename std::vector< typename vge::visitor::NodeCollectorExtended<Visitors>::TraverseElement >::const_iterator i, iEnd;
//	
//	for(	i		= nodes.begin(),
//			iEnd	= nodes.end();
//			
//			i != iEnd;
//			
//			++i )
//	{
//		engine()->evaluate( service, i->first, i->second );
//	}
//}



void Technique::apply(	//const vgd::Shp< vge::service::Service > service, FIXME
						vge::engine::Engine * /*pEngine*/,
						vge::visitor::TraverseElementVector* /*pTraverseElements*/ )
{
	assert( false );
}



} // namespace technique

} // namespace vge
