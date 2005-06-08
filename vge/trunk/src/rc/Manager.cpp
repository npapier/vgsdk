// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vge/rc/Manager.hpp"

#include <vgd/node/Node.hpp>

#include "vge/rc/IResource.hpp"



namespace vge
{

namespace rc
{



Manager::~Manager()
{
	clear();
}



bool Manager::add( vgd::node::Node *pNode, IResource *pResource )
{
	assert( pNode != 0 );
	assert( pResource != 0 );
	
	ResourcesPair elt(pNode, pResource );

	std::pair< ResourcesMap::iterator, bool > retVal;
	retVal = m_resources.insert( elt );
	
	return ( retVal.second );
}



bool Manager::remove( vgd::node::Node *pNode )
{
	assert( pNode != 0 );
	
	ResourcesMap::iterator iter = m_resources.find( pNode );

	if ( iter != m_resources.end() )
	{
		// Founded, delete the resource and remove ResourcePair.
		assert( iter->second != 0 );
		delete iter->second;
		m_resources.erase( iter );
		
		return ( true );
	}
	else
	{
		// Not founded
		return ( false );
	}
}



void Manager::clear()
{
	for(	ResourcesMap::iterator	i = m_resources.begin();
			i != m_resources.end();
			i = m_resources.begin()
		)
	{
		assert( i->second != 0 );
		
		delete i->second;
		m_resources.erase( i );
	}
}



IResource* Manager::getAbstract( vgd::node::Node *pNode )
{
	assert( pNode != 0 );
	
	ResourcesMap::iterator iter = m_resources.find( pNode );

	if ( iter != m_resources.end() )
	{
		// Founded.
		return ( iter->second );
	}
	else
	{
		// Not founded
		return ( 0 );
	}
}



uint32 Manager::getNum() const
{
	return ( m_resources.size() );
}



std::pair< Manager::ResourcesMap::const_iterator, Manager::ResourcesMap::const_iterator >
	Manager::getIterators()
{
	return ( 
		std::pair< Manager::ResourcesMap::const_iterator, Manager::ResourcesMap::const_iterator >(
			m_resources.begin(),
			m_resources.end() )
			);
}


			
} // namespace rc

} // namespace vge
