// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_BASIC_CLASSREGISTRY_HPP
#define _VGD_BASIC_CLASSREGISTRY_HPP

#include <set>
#include <string>
#include <sstream>
#include <utility>

#include "vgd/vgd.hpp"
#include "vgd/Shp.hpp"

namespace vgd
{
	namespace node
	{
		struct Node;
	}
}



namespace vgd
{

namespace basic
{



/**
 * @brief Registry of classes.
 * 
 * Register a class consists to :
 * 
 * \li store an instance of each registered class in the registry.
 * \li the registered class must implements IMPLEMENT_INDEXABLE_CLASS(...). Then the index is correctly initialized when
 * calling add(). @sa IndexableClass for more details on class with an index.
 * 
 * With the registry, enumerate all registered nodes is possible.
 */
template< typename baseClassType >
struct ClassRegistry
{
	/**
	 * @name Typedefs.
	 */
	//@{
	
	/**
	 * @brief Set of registered classes.
	 */
	typedef typename std::set<		vgd::Shp<baseClassType>		>		ClassSet;
	
	//@}

	
	/**
	 * @brief Register a new class.
	 * 
	 * @return true if class is successfully registred, false otherwise(already registered).
	 * 
	 * @todo Check if the same class is inserted more than once, but it should never occurs.
	 */
	template< typename classType >
	bool	add( vgd::Shp< classType > shpClass )
	{
		// STEP 1: register this class.
		std::pair< typename ClassSet::iterator, bool > retVal;
		
		retVal = m_classes.insert( shpClass );

		if ( retVal.second )
		{
			// successfully register this class.

			// STEP 2: Initialization of class index.
			int32& index = classType::getClassIndexStatic();

			if ( index == -1 )
			{
				// class index not yet initialized.
				// => Initialize class index.
				index = static_cast< int32 >(baseClassType::getClassRegistry().getNumRegistered()) - 1;
			}
			/*else nothing to do (register the same class multiples times is useful for vgd::node::MultiAttribute.
			{
				assert( false && "This is a new class (not registered), but with a class index already initialized !!!");
				return ( false );
			}*/
		}
		else
		{
			assert( false && "This class is already registered ? This should never occurs. No more memory ? ");
			
			return ( false );
		}

		return ( retVal.second );
	}

	/**
	 * @brief Gets all registered classes.
	 * 
	 * @return A string with all registered classes names separated by space.
	 */
	std::string		get( void ) const
	{
		std::stringstream strStream;
		
		for(	typename ClassSet::const_iterator i = m_classes.begin();
				i != m_classes.end();
				i++ )
		{
			strStream << "(" << typeid(*i).name() << ") ";
		}
		strStream << std::endl << std::ends;
	
		return ( std::string(strStream.str()) );
	}

	
	
	/**
	 * @brief Returns the number of registered classes.
	 * 
	 * @return Number of registered classes.
	 */
	uint32			getNumRegistered( void ) const
	{
		return ( static_cast<uint32>( m_classes.size() ) );
	}



	/**
	 * @brief Gets a pair with a begin and end iterator on the class set.
	 */
	std::pair< typename ClassSet::iterator, typename ClassSet::iterator > getIterators( void )
	{
		return ( 
			std::pair< typename ClassRegistry::ClassSet::iterator, typename ClassRegistry::ClassSet::iterator >(
				m_classes.begin(),
				m_classes.end() )
				);
	}
	



private:

	/**
	 * @brief Container for registry.
	 */
	ClassSet		m_classes;
};



} // namespace basic

} // namespace vgd

#endif //#ifndef _VGD_BASIC_CLASSREGISTRY_HPP
