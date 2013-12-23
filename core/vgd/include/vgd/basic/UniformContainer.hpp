// VGSDK - Copyright (C) 2010, 2011, 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_BASIC_UNIFORMCONTAINER_HPP
#define _VGD_BASIC_UNIFORMCONTAINER_HPP

#include <map>
#include <string>
#include <utility>
#include "vgd/field/Uniform.hpp"
#include "vgd/vgd.hpp"



namespace vgd
{

namespace basic
{


/**
 * @brief Specialized container to manage uniform variables
 *
 * An uniform variable is a global variable whose value are the same across the entire primitive being processed.
 *
 * @todo simplify interface, see vgd::node::Uniforms.
 * @todo dirty flags
 */
struct VGD_API UniformContainer
{
	/**
	 * @brief Clears content
	 *
	 * All the elements in the container are dropped.
	 */
	void clear();


	/**
	 * @brief Adds a new uniform variable
	 *
	 * @pre isUniform(name) not true
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
	// @todo remove me setUniform()/sethUniform() is enough
	template< typename T >
	const T setUniform( const std::string& name, const T& value )
	{
		vgAssertN( isUniform(name), "Uniform named '%s' not found", name.c_str() );

		ContainerType::iterator iUniform = m_container.find( name );
		if ( iUniform != m_container.end() )
		{
			const T retVal = boost::get< const T >(iUniform->second);
			// Found
			iUniform->second = value;
			return retVal;
		}
		else
		{
			// Not found
			vgAssertN( false, "Uniform not found" );
		}

		return T();
	}


	/**
	 * @brief Sets the value of an uniform variable
	 *
	 * @param name		name of the uniform variable
	 * @param value		value of the uniform variable
	 *
	 * @todo post isDirty()
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
			addUniform(name, value);
		}
	}


protected:
	typedef std::string						KeyType;
	typedef vgd::field::UniformValue		ValueType;
	typedef std::map< KeyType, ValueType >	ContainerType;

	typedef ContainerType::const_iterator				ConstIteratorType;
	typedef std::pair< ContainerType::iterator, bool >	RetValType;

	/**
	 * @brief Returns a pair (begin, end) containing iterators on ContainerType.
	 *
	 * @return a pair containing the (begin, end) interators to traverse this container
	 */
	std::pair< ConstIteratorType, ConstIteratorType > getIterators() const;


private:
	ContainerType m_container;			///< container of uniform variables a map< name,value >.
};



} // namespace basic

} // namespace vgd

#endif //#ifndef _VGD_BASIC_UNIFORMCONTAINER_HPP
