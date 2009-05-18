// VGSDK - Copyright (C) 2004, 2006, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_RC_MANAGER_HPP
#define _VGE_RC_MANAGER_HPP

#include "vge/vge.hpp"

#include <map>
#include <utility>

namespace vgd
{
	template<class T> struct Shp;
	
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
	}
}



namespace vge
{

namespace rc
{

/**
 * @brief Manager of resources used by handlers.
 *
 * This class provides a way to keep track of all 3d resources (display list, texture, vertex buffer object...) used by vgsdk.
 * 
 * @remarks \c Not \c assignable.
 * 
 * @todo A manager per type of Resource ?
 * @todo Statistics.
 */
struct VGE_API Manager
{
	/**
	 * @name Destructor
	 */
	//@{
	
	/**
	 * @brief Destructor
	 * 
	 * All resources(IResource*) stored in this manager are released.
	 */
	virtual ~Manager();

	//@}



	/**
	 * @name Actions
	 */
	//@{

	/**
	 * @brief Adds new resource associated to a node in the manager.
	 *
	 * @pre pNode != 0
	 * @pre pResource != 0
	 * 
	 * @param pNode			pointer on node.
	 * @param pResource		pointer on resource.
	 * 
	 * @return true if the pair (node,resource) was successfully added, false otherwise (i.e. node already added).
	 * 
	 * @remarks remove() method is called automatically when nodes are destroyed. Because this manager is connected to 
	 * the node signal that is sent at node destruction time.
	 * 
	 * @remarks pResource is deleted by the Manager.
	 */
	const bool	add( vgd::node::Node *pNode, IResource *pResource );

	/**
	 * @brief Removes a resource associated to a node in the manager.
	 *
	 * @param pNode		pointer on node.
	 * 
	 * @return true if (node,resource) was successfully removed, false otherwise (i.e. not in the manager).
	 */
	const bool	remove( vgd::node::Node *pNode );

	/**
	 * @brief Removes all resources in the manager.
	 */
	void		clear();
	
	//@}



	/**
	 * @name Accessors
	 */
	//@{

	/**
	 * @brief Gets the resource associated to the given node.
	 * 
	 * @param pNode		pointer on node.
	 * @return			pointer on the desired resource or 0 if there is no resource associated with this node.
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
	 * @return			pointer on the desired resource or 0 if there is no resource associated with this node or cast
	 * fails.
	 *
	 * @remark A lookup in a map is performed in this method.
	 */
	template< typename resourceType >
	resourceType*	get( vgd::node::Node *pNode )
	{
		IResource *pResource			= getAbstract(pNode);
		
		resourceType *pCastedResource	= dynamic_cast< resourceType* >(pResource);
		
		assert( pCastedResource != 0 && "Target resource type is invalid." );
		
		return pCastedResource;
	}

	/**
	 * @brief Returns the number of resource objects in the manager.
	 *
	 * @return number of resource objects.
	 */
	const uint32 getNum() const;

	/**
	 * @todo FIXME temporary disabled => must be reactivated ?
	 * 
	 * brief Gets a pair with a begin and end iterator on the resources map.
	 */
	//std::pair< ResourcesMap::const_iterator, ResourcesMap::const_iterator > getIterators();
	
	//@}



private:

	/**
	 * @brief Declaration of resource managed by this class.
	 */
	struct Resource;

	/**
	 * @name Typedefs
	 */
	//@{
	
	/**
	 * @brief Map of all resources.
	 */
	typedef std::map< vgd::node::Node*, vgd::Shp< Resource > >		ResourcesMap;

	/**
	 * @brief An element of the map.
	 */	
	typedef std::pair< vgd::node::Node*, vgd::Shp< Resource > >		ResourcesPair;

	//@}

	/**
	 * @brief Container for all resources.
	 */
	ResourcesMap		m_resources;
};



} // namespace rc

} // namespace vge

#endif //#ifndef _VGE_RC_MANAGER_HPP
