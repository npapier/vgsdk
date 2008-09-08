// VGSDK - Copyright (C) 2007, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include <vgd/ScopedPtr.hpp>



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
	 * 
	 * @remarks Ownership of the given resource is acquired by this class.
	 */
	ResourceContainer( ResourceType *rc )
	 :	m_rc(rc)
	{}

	/**
	 * @brief Gets the owned resource.
	 *
	 * @return a pointer on the resource
	 */
	const ResourceType *getResourcePointer() const { return m_rc.get(); }

	/**
	 * @brief Gets the owned resource.
	 *
	 * @return a pointer on the resource
	 */
	ResourceType *getResourcePointer() { return m_rc.get(); }

private:
	/**
	 * @name Data
	 */
	//@{

	/**
	 * @brief The owned resource
	 */
	vgd::ScopedPtr< ResourceType > m_rc;
	//@}
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
	m_resources.clear();
}



template< typename KeyType, typename ResourceType >
ResourceType* TManager< KeyType, ResourceType >::getAbstract( const KeyType& key )
{
	typename ResourcesMap::iterator iter = m_resources.find( key );

	if ( iter != m_resources.end() )
	{
		// A match is found for the key
		return iter->second->getResourcePointer();
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
const uint TManager< KeyType, ResourceType >::getNum() const
{
	return static_cast< const uint >( m_resources.size() );
}



} // namespace rc

} // namespace vge
