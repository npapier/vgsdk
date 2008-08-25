// VGSDK - Copyright (C) 2007, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

//#include <boost/signals/connection.hpp>
#include <vgd/ScopedPtr.hpp>



namespace vge
{

namespace rc
{



// ********* template Manager::ResourceContainer *********


template< typename KeyType/*, typename ResourceType*/ >
struct TManager<KeyType>::ResourceContainer
{
	/**
	 * @brief Constructor
	 * 
	 * @param rc	pointer on the resource
	 * 
	 * @remarks Ownership of the given resource is acquired by this class.
	 */
	ResourceContainer( glo::IResource *rc )
	 :	m_rc(rc)
	{}

	/**
	 * @brief Gets the owned resource.
	 *
	 * @return a pointer on the resource
	 */
	const glo::IResource *getResourcePointer() const { return m_rc.get(); }

	/**
	 * @brief Gets the owned resource.
	 *
	 * @return a pointer on the resource
	 */
	glo::IResource *getResourcePointer() { return m_rc.get(); }

private:
	/**
	 * @name Data
	 */
	//@{

	/**
	 * @brief The owned resource
	 */
	vgd::ScopedPtr< glo::IResource > m_rc;

	/**
	 * brief This object is the signal/slot connection between an object and its resource.
	 */
	//boost::signals::scoped_connection m_connection;
};






// ********* template Manager *********
template< typename KeyType >
TManager< KeyType >::~TManager()
{
	clear();
}



template< typename KeyType >
const bool TManager< KeyType >::add( const KeyType& key, glo::IResource *resource )
{
	assert( resource != 0 && "Null pointer" );

	vgd::Shp< ResourceContainer > value( new ResourceContainer(resource) );
	std::pair< typename ResourcesMap::iterator, bool > retVal = m_resources.insert( ResourcesValueType(key, value) );

	return retVal.second;
}



template< typename KeyType >
const bool TManager< KeyType >::remove( const KeyType& key )
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



template< typename KeyType >
void TManager< KeyType >::clear()
{
	m_resources.clear();
}



template< typename KeyType >
glo::IResource* TManager< KeyType >::getAbstract( const KeyType& key )
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



template< typename KeyType >
template< typename ResourceType >
ResourceType* TManager< KeyType >::get( const KeyType& key )
{
	glo::IResource *resource = getAbstract(key);

	if ( resource == 0 )
	{
		return 0;
	}
	else
	{
		ResourceType *castedResource = dynamic_cast< ResourceType* >(resource);
		assert( castedResource != 0 && "Target resource type is invalid." );

		return castedResource;
	}
}



template< typename KeyType >
const uint TManager< KeyType >::getNum() const
{
	return static_cast< const uint >( m_resources.size() );
}



} // namespace rc

} // namespace vge
