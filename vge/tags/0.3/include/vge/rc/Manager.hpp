// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_RC_MANAGER_H
#define _VGE_RC_MANAGER_H

#include "vge/vge.hpp"

#include <map>
#include <utility>
namespace vgd
{
namespace node
{
	struct Node;
}
}



namespace vge
{

namespace rc
{

struct IResource;

/**
 * @brief Manager of all resources used by handlers.
 *
 * This class provides a way to keep track of all resources (display list, texture, vertex buffer object...) used by vgsdk.
 * 
 * @remarks \c Not \c assignable.
 * 
 * @todo A manager per type of Resource ?
 * @todo Use weak_pointer insteed of Node* for never having invalidate Node*.
 * @todo Statistics.
 */
struct VGE_API Manager
{
	/**
	 * @name Typedefs.
	 */
	//@{
	
	/**
	 * @brief Map of all resources.
	 */
	typedef std::map< vgd::node::Node*, IResource* >		ResourcesMap;

	/**
	 * @brief An element of the map.
	 */	
	typedef std::pair< vgd::node::Node*, IResource* >		ResourcesPair;

	//@}

	
	
	/**
	 * @name Destructor.
	 */
	//@{
	
	/**
	 * @brief Destructor.
	 * 
	 * All resources(IResource*) stored in this manager are released.
	 */
	~Manager();
	//@}



	/**
	 * @name Actions.
	 */
	//@{

	/**
	 * @brief Adds new resource associated to a node in the manager.
	 *
	 * @param pNode		pointer on node.
	 * @param pResource	pointer on resource.
	 * 
	 * @return true if (node,resource) is successfully added, false otherwise(node already added).
	 * 
	 * @remarks pResource is deleted by the Manager.
	 */
	bool		add( vgd::node::Node *pNode, IResource *pResource );

	/**
	 * @brief Removes a resource associated to a node in the manager.
	 *
	 * @param pNode		pointer on node.
	 * 
	 * @return true if (node,resource) is successfully removed, false otherwise(not in the manager).
	 */
	bool		remove( vgd::node::Node *pNode );

	/**
	 * @brief Removes all resources in the manager.
	 */
	void		clear();
	
	//@}



	/**
	 * @name Accessors.
	 */
	//@{

	/**
	 * @brief Gets the resource associated to the given node.
	 * 
	 * @param pNode		pointer on node.
	 * @return				pointer on the desired resource or 0 if there is no resource associated with this node.
	 * 
	 * @remark A lookup in a map is performed in this method.
	 */
	IResource*	getAbstract( vgd::node::Node *pNode );

	/**
	 * @brief Gets the resource associated to the given node.
	 * 
	 * @pre	resourceType must be the good one or an assert will occurs.
	 * 
	 * @param pNode		pointer on node.
	 * @return				pointer on the desired resource or 0 if there is no resource associated with this node or cast
	 * fails.
	 *
	 * @remark A lookup in a map is performed in this method.
	 */
	template< typename resourceType >
	resourceType*	get( vgd::node::Node *pNode )
	{
		assert( pNode != 0 );
		
		ResourcesMap::iterator iter = m_resources.find( pNode );
	
		if ( iter != m_resources.end() )
		{
			// Founded.
			assert( dynamic_cast< resourceType* >(iter->second) != 0 && "Target resource type is invalid." );
			return ( dynamic_cast< resourceType* >(iter->second) );
		}
		else
		{
			// Not founded
			return ( 0 );
		}
	}

	/**
	 * @brief Returns the number of resource objects in the manager.
	 *
	 * @return number of resource objects.
	 */
	uint32			getNum() const;

	/**
	 * @brief Gets a pair with a begin and end iterator on the resources map.
	 */
	std::pair< ResourcesMap::const_iterator, ResourcesMap::const_iterator > getIterators();
	
	//@}



private:

	/**
	 * @brief Container for all resources.
	 */
	ResourcesMap		m_resources;
};



} // namespace rc

} // namespace vge

#endif //#ifndef _VGE_RC_MANAGER_H
