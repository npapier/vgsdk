// VGSDK - Copyright (C) 2004, 2006, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Clément Forest

#include "vge/rc/Manager.hpp"

#include <boost/bind.hpp>
#include <boost/signals/connection.hpp>
#include <vgd/ScopedPtr.hpp>
#include <vgd/node/Node.hpp>

#include "vge/rc/IResource.hpp"



namespace vge
{

namespace rc
{



struct Manager::Resource
{
	/**
	 * @brief Constructor
	 * 
	 * @param rc	pointer on a resource
	 * 
	 * @remarks Ownership of the given resource is acquired by this class.
	 */
	Resource( IResource *rc )
	:	m_rc(rc)
	{}

	/**
	 * @brief Destructor
	 */
	~Resource()
	{
		if ( m_nodeDestructorConnection.connected() )
		{
			m_nodeDestructorConnection.disconnect();
		}

		assert( m_nodeDestructorConnection.connected() == false );
	}

private:

	friend struct Manager;

	/**
	 * @name Data
	 */
	//@{

	/**
	 * @todo use glo::IResource ?
	 */
	vgd::ScopedPtr< IResource > m_rc;

	/**
	 * @brief Each node is linked to its own resource (see vge::rc::Manager).
	 * This object is the signal/slot connection between a node and its resource.
	 */
	boost::signals::connection m_nodeDestructorConnection;
};






// *********************************************************************************************************************

Manager::~Manager()
{
	clear();
}



const bool Manager::add( vgd::node::Node *pNode, IResource *pResource )
{
	assert( pNode != 0 );
	assert( pResource != 0 );
	
	vgd::Shp<Resource> value( new Resource(pResource) );
	std::pair< ResourcesMap::iterator, bool > retVal = m_resources.insert( ResourcesPair(pNode, value) );
	
	if ( retVal.second )
	{
		// Insertion is successful

		// Configures the resource (i.e. connects Node to Manager)
		assert( value->m_nodeDestructorConnection.connected() == false );
		value->m_nodeDestructorConnection = pNode->connect( boost::bind(&Manager::remove, this, _1) );
	}
	// else if insertion fails nothing to do
	
	return retVal.second;
}



const bool Manager::remove( vgd::node::Node *pNode )
{
	assert( pNode != 0 );
	
	ResourcesMap::iterator iter = m_resources.find( pNode );

	if ( iter != m_resources.end() )
	{
		// Found the given node
		assert( iter->second->m_nodeDestructorConnection.connected() );			
		// disconnect() done by ~Resource();

		// Removes the resource
		m_resources.erase( iter );

		return true;
	}
	else
	{
		// Not found
		return false;
	}
}



void Manager::clear()
{
	// The following code is equivalent to m_resources.clear();
	while(!m_resources.empty())
	{
		m_resources.erase(m_resources.begin());
	}
}



IResource* Manager::getAbstract( vgd::node::Node *pNode )
{
	assert( pNode != 0 );
	
	ResourcesMap::iterator iter = m_resources.find( pNode );

	if ( iter != m_resources.end() )
	{
		// Found
		return iter->second->m_rc.get();
	}
	else
	{
		// Not found
		return 0;
	}
}



const uint32 Manager::getNum() const
{
	return static_cast<const uint32>( m_resources.size() );
}



//std::pair< Manager::ResourcesMap::const_iterator, Manager::ResourcesMap::const_iterator >
//	Manager::getIterators()
//{
//	return ( 
//		std::pair< Manager::ResourcesMap::const_iterator, Manager::ResourcesMap::const_iterator >(
//			m_resources.begin(),
//			m_resources.end() )
//			);
//}



} // namespace rc

} // namespace vge
