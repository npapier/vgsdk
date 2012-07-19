// VGSDK - Copyright (C) 2007, 2008, 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include <vgd/Shp.hpp>



namespace vge
{

namespace rc
{



// ********* template Manager::ResourceContainer *********


// @todo removes this resource container and stores directly the resource in the TManager ?

template< typename KeyType, typename ResourceType >
struct TManager<KeyType, ResourceType>::ResourceContainer
{
	/**
	 * @brief Constructor
	 * 
	 * @param rc	pointer on the resource
	 */
	ResourceContainer( vgd::Shp< ResourceType > rc )
	 :	m_rc(rc)
	{}

	/**
	 * @brief Constructor
	 * 
	 * @param rc	pointer on the resource
	 */
	ResourceContainer( ResourceType *rc )
	 :	m_rc(rc)
	{}


	/**
	 * @brief Returns the pointer on the owned resource.
	 *
	 * @return a pointer on the owned resource.
	 */
	const vgd::Shp< ResourceType > getShp() const { return m_rc; }
	
	/**
	 * @brief Returns the pointer on the owned resource.
	 *
	 * @return a pointer on the owned resource.
	 */
	vgd::Shp< ResourceType > getShp() { return m_rc; }

	/**
	 * @brief Returns the pointer on the owned resource.
	 *
	 * @return a pointer on the owned resource.
	 */
	const ResourceType * get() const { return m_rc.get(); }

	/**
	 * @brief Returns the pointer on the owned resource.
	 *
	 * @return a pointer on the owned resource.
	 */
	ResourceType * get() { return m_rc.get(); }


private:
	vgd::Shp< ResourceType > m_rc; ///< the resource
};






// ********* template Manager *********
template< typename KeyType, typename ResourceType >
TManager< KeyType, ResourceType >::TManager( const std::string name )
:	NamedObject( name )
{
}



template< typename KeyType, typename ResourceType >
TManager< KeyType, ResourceType >::~TManager()
{
	clear();
}



template< typename KeyType, typename ResourceType >
const bool TManager< KeyType, ResourceType >::add( const KeyType& key, vgd::Shp< ResourceType > resource )
{
	assert( resource != 0 && "Null pointer" );

	vgd::Shp< ResourceContainer > value( new ResourceContainer(resource) );
	std::pair< typename ResourcesMap::iterator, bool > retVal = m_resources.insert( ResourcesValueType(key, value) );

	return retVal.second;
}


template< typename KeyType, typename ResourceType >
const bool TManager< KeyType, ResourceType >::add( const KeyType& key, ResourceType *resource )
{
	assert( resource != 0 && "Null pointer" );

	vgd::Shp< ResourceContainer > value( new ResourceContainer(resource) );
	std::pair< typename ResourcesMap::iterator, bool > retVal = m_resources.insert( ResourcesValueType(key, value) );

	return retVal.second;
}



template< typename KeyType, typename ResourceType >
const bool TManager< KeyType, ResourceType >::remove( const KeyType& key )
{
	typename ResourcesMap::iterator iter = m_resources.find( key );

	if ( iter != m_resources.end() )
	{
		// A match is found for the key
		// Removes it
		m_resources.erase( iter );

		return true;
	}
	else
	{
		// No match is found for the key
		return false;
	}
}



template< typename KeyType, typename ResourceType >
void TManager< KeyType, ResourceType >::clear()
{
	// The following code is equivalent to m_resources.clear();
	while(!m_resources.empty())
	{
		m_resources.erase(m_resources.begin());
	}
}



template< typename KeyType, typename ResourceType >
vgd::Shp< ResourceType > TManager< KeyType, ResourceType >::getAbstractShp( const KeyType& key )
{
	typename ResourcesMap::iterator iter = m_resources.find( key );

	if ( iter != m_resources.end() )
	{
		// A match is found for the key
		return iter->second->getShp();
	}
	else
	{
		// No match is found for the key
		return vgd::Shp< ResourceType >();
	}
}



template< typename KeyType, typename ResourceType >
ResourceType* TManager< KeyType, ResourceType >::getAbstract( const KeyType& key )
{
	typename ResourcesMap::iterator iter = m_resources.find( key );

	if ( iter != m_resources.end() )
	{
		// A match is found for the key
		return iter->second->get();
	}
	else
	{
		// No match is found for the key
		return 0;
	}
}



template< typename KeyType, typename ResourceType >
template< typename OutResourceType >
OutResourceType* TManager< KeyType, ResourceType >::get( const KeyType& key )
{
	ResourceType *resource = getAbstract(key);

	if ( resource == 0 )
	{
		return 0;
	}
	else
	{
		OutResourceType *castedResource = dynamic_cast< OutResourceType* >(resource);
		assert( castedResource != 0 && "Target resource type is invalid." );

		return castedResource;
	}
}

template< typename KeyType, typename ResourceType >
template< typename OutputIterator >
void TManager< KeyType, ResourceType >::getKeys( OutputIterator& key )
{
	typename ResourcesMap::const_iterator	it;

	for (	it = m_resources.begin(); 
			it != m_resources.end(); 
			++it)
	{
		*key++ = it->first;
	}
}



template< typename KeyType, typename ResourceType >
template< typename OutResourceType >
vgd::Shp< OutResourceType > TManager< KeyType, ResourceType >::getShp( const KeyType& key )
{
	vgd::Shp< ResourceType > resource = getAbstractShp(key);

	if ( !resource )
	{
		return vgd::Shp<OutResourceType>();
	}
	else
	{
		vgd::Shp< OutResourceType > castedResource = vgd::dynamic_pointer_cast< OutResourceType >(resource);
		assert( castedResource != 0 && "Target resource type is invalid." );

		return castedResource;
	}
}



template< typename KeyType, typename ResourceType >
const uint TManager< KeyType, ResourceType >::getNum() const
{
	return static_cast< const uint >( m_resources.size() );
}



} // namespace rc

} // namespace vge
