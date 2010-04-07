// VGSDK - Copyright (C) 2007, 2008, 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_RC_TMANAGER_HPP
#define _VGE_RC_TMANAGER_HPP

#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>
//#include <boost/signals/trackable.hpp>
#include <map>
#include <utility>

#include <vgd/basic/NamedObject.hpp>

#include "vge/vge.hpp"

namespace vgd { template<class T> struct Shp; }



namespace vge
{

namespace rc
{

/**
 * @brief Templated resource manager
 * 
 * This class is used for the storage and retrieval of resource identified by a unique key.
 * 
 * @remarks \c Not \c assignable.
 * 
 * @todo Some methods for doing statistics on resources. 
 */
template< typename KeyType, typename ResourceType >
struct TManager : /*public boost::signals::trackable,*/ public boost::noncopyable, public vgd::basic::NamedObject
{
	/**
	 * @name Constructor and destructor
	 */
	//@{

	/**
	 * @brief Constructor
	 *
	 * @param name 		name of the manager
	 */
	TManager( const std::string name );

	/**
	 * @brief Virtual destructor
	 * 
	 * All resources stored in this manager are released.
	 */
	virtual ~TManager();

	//@}



	/**
	 * @name Actions
	 */
	//@{

	/**
	 * @brief Adds a new resource associated to a unique key in the manager.
	 *
	 * @pre resource != 0
	 * 
	 * @param key 			the key value
	 * @param resource		the resource to add
	 * 
	 * @return true if the pair (key,resource) was successfully added, false otherwise (i.e. key already added).
	 */
	const bool add( const KeyType& key, vgd::Shp< ResourceType > resource );

	/**
	 * @brief Adds a new resource associated to a unique key in the manager.
	 *
	 * @pre resource != 0
	 * 
	 * @param key 			the key value
	 * @param resource		the resource to add
	 * 
	 * @return true if the pair (key,resource) was successfully added, false otherwise (i.e. key already added).
	 * 
	 * @remarks The ownership of resource is transfered to this manager. So the destruction is done by this class.
	 */
	const bool add( const KeyType& key, ResourceType * resource );

	/**
	 * @brief Removes a resource associated to a key in the manager.
	 *
	 * @param key		the key value
	 * 
	 * @return true if (key,resource) was successfully removed, false otherwise (i.e. not in the manager).
	 */
	const bool remove( const KeyType& key );

	/**
	 * @brief Removes all resources owned by the manager.
	 */
	void clear();

	//@}



	/**
	 * @name Accessors
	 */
	//@{

	/**
	 * @brief Gets the resource associated to the given key.
	 * 
	 * @param key		the key value
	 * 
	 * @return			a pointer on the desired resource, or 0 if there is no resource associated to the given key.
	 */
	ResourceType *	getAbstract( const KeyType& key );

	/**
	 * @brief Gets the resource associated to the given key.
	 * 
	 * @param key		the key value
	 * 
	 * @return			a pointer on the desired resource, or an empty pointer if there is no resource associated to the given key.
	 */
	vgd::Shp< ResourceType > getAbstractShp( const KeyType& key );

	/**
	 * @brief Gets the resource associated to the given key.
	 * 
	 * @pre	resourceType must be the good one or an assertion will occurs.
	 * 
	 * @param key		the key value
	 * 
	 * @return			a pointer on the desired resource, or 0 if there is no resource associated to the given key.
	 * 					When the given resource type is wrong, an assertion will occurs and the return value would be 0.
	 */
	template< typename OutResourceType >
	OutResourceType * get( const KeyType& key );

	/**
	 * @brief Gets the resource associated to the given key.
	 * 
	 * @pre	resourceType must be the good one or an assertion will occurs.
	 * 
	 * @param key		the key value
	 * 
	 * @return			a pointer on the desired resource, or an empty pointer if there is no resource associated to the given key.
	 * 					When the given resource type is wrong, an assertion will occurs and the return value would be an empty pointer.
	 */
	template< typename OutResourceType >
	vgd::Shp< OutResourceType > getShp( const KeyType& key );

	/**
	 * @brief Returns the number of resources owned by this manager.
	 *
	 * @return the number of resources
	 */
	const uint getNum() const;

	//@}



private:

	/**
	 * @brief Container for a single resource managed by this class.
	 */
	struct ResourceContainer;

	/**
	 * @name Typedefs
	 */
	//@{

	/**
	 * @brief Map of all resources.
	 */
	typedef std::map< KeyType, vgd::Shp< ResourceContainer > >		ResourcesMap;

	/**
	 * @brief An element of the map.
	 */
	typedef std::pair< KeyType, vgd::Shp< ResourceContainer > >		ResourcesValueType;

	//@}

	/**
	 * @brief Container for all resources.
	 */
	ResourcesMap		m_resources;
};



} // namespace rc

} // namespace vge

#include "vge/rc/TManager.hxx"

#endif //#ifndef _VGE_RC_TMANAGER_HPP
