// VGSDK - Copyright (C) 2010, 2011, Nicolas Papier.
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
#include <vgm/Matrix.hpp>



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
	 * @return true if success
	 */
	template< typename T >
	const bool addUniform( const std::string& name, const T value = T() )
	{
		RetValType retVal = m_container.insert( std::make_pair(name, value) );
		if ( !retVal.second )
		{
			vgAssertN( false, "Unable to add uniform named '%s'. Uniform name must be unique.", name.c_str() );
			return false;
		}
		else
		{
			return true;
		}
	}

	/**
	 * @brief Removes a uniform variable
	 *
	 * @param name		name of the uniform variable
	 *
	 * @return true if success, false otherwise
	 */
	const bool removeUniform( const std::string& name );

	/**
	 * @brief Tests if an uniform variable exists.
	 *
	 * @param name		name of the uniform variable
	 *
	 * @return true if the variable exists, false otherwise	
	 */
	const bool isUniform( const std::string& name ) const;

	/**
	 * @brief Returns the number of uniform variables
	 */
	const uint getSize() const;

	/**
	 * @brief Sets the value of an uniform variable
	 *
	 * @param name		name of the uniform variable
	 * @param value		value of the uniform variable
	 *
	 * @pre isUniform(name)
	 */	
	template< typename T >
	void setUniform( const std::string& name, const T& value )
	{
		vgAssertN( isUniform(name), "Uniform named '%s' not found", name.c_str() );

		ContainerType::const_iterator iUniform = m_container.find( name );
		if ( iUniform != m_container.end() )
		{
			// Found
			iUniform->second = value;
		}
		else
		{
			// Not found
			vgAssertN( false, "Uniform not found" );
		}
	}


	/**
	 * @brief Sets the value of an uniform variable
	 *
	 * @param name		name of the uniform variable
	 * @param value		value of the uniform variable
	 *
	 * @post isDirty()
	 */
	template< typename T >
	void sethUniform( const std::string& name, const T& value )
	{
		ContainerType::iterator iUniform = m_container.find( name );
		if ( iUniform != m_container.end() )
		{
			// Found
			iUniform->second = value;
		}
		else
		{
			// Not found
			addUniform(name,value);
		}
	}


	// @todo getUniform()
	// @todo dirty flags
	//void destroy();							///< code for destructor
	//void copy( const UniformContainer& src );	///< code for copy constructor

	typedef std::string KeyType;
	typedef boost::variant<
		float,
		vgm::Vec2f, vgm::Vec3f, vgm::Vec4f,
		vgm::MatrixR > ValueType;
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
