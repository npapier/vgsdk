// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_BASIC_UNIFORMCONTAINER_HPP
#define _VGE_BASIC_UNIFORMCONTAINER_HPP

#include <boost/variant.hpp>
#include <map>
#include <string>
#include <utility>
#include <vge/vge.hpp>
#include <vgm/Vector.hpp>


namespace vge
{

namespace basic
{



/**
 * @brief Specialized container to manage uniform variables.
 *
 * An uniform variable is a global variable whose value are the same across the entire primitive being processed.
 */
struct VGE_API UniformContainer
{
	/**
	 * @name Constructors
	 */
	//@{


	/**
	 * brief Default constructor
	 */
	//UniformContainer();

	/**
	 * brief Copy constructor
	 */
	//TUnitContainer( const TUnitContainer& value )
	//{
	//	copy(value);
	//}

	/**
	 * brief Assign operator
	 */
	//TUnitContainer& operator =( const TUnitContainer& value )
	//{
		//if ( this != &value )
		//{
			// remove() not needed
			//copy( value );
		//}
		//return (*this);
	//}

	//@}



	/**
	 * @brief Clears content
	 *
	 * All the elements in the container are dropped.
	 */
	void clear();


	/**
	 * @brief Adds a new uniform variable
	 *
	 * @param name		name of the uniform variable
	 * @param value		value of the uniform variable
	 *
	 * @return true if sucess
	 */
	template< typename T >
	const bool addUniform( const std::string& name, const T value = T() )
	{
		RetValType retVal = m_container.insert( std::make_pair(name, value) );
		if ( !retVal.second )
		{
			assert( false && "Unable to add this uniform. Uniform name must be unique." );
			return false;
		}
		else
		{
			return true;
		}
	}

	const bool removeUniform( const std::string& name );

	const bool isUniform( const std::string& name ) const;
	const uint getSize() const;

	template< typename T >
	void setUniform( const std::string& name, const T& value )
	{
		assert( isUniform(name) && "Uniform not found" );

		ContainerType::const__iterator iUniform = m_container.find( name );
		if ( iUniform != m_container.end() )
		{
			// Found
			iUniform->second = value;
		}
		else
		{
			// Not found
			assert( false && "Uniform not found" );
		}
	}

	
	// @todo getUniform()
	// @todo dirty flags
	//void destroy();							///< code for destructor
	//void copy( const UniformContainer& src );	///< code for copy constructor

	typedef std::string KeyType;
	typedef boost::variant< float, vgm::Vec4f > ValueType;
	typedef std::map< KeyType, ValueType > ContainerType;

	typedef ContainerType::const_iterator	ConstIteratorType;

	std::pair< ConstIteratorType, ConstIteratorType > getIterators() const;



private:
	ContainerType m_container;			///< container of uniform variables a map< name,value >.

	typedef std::pair< ContainerType::iterator, bool > RetValType;	
};



} // namespace basic

} // namespace vge

#endif //#ifndef _VGE_BASIC_UNIFORMCONTAINER_HPP
