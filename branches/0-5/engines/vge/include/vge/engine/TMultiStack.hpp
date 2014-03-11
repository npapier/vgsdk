// VGSDK - Copyright (C) 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_ENGINE_TMULTISTACK_HPP
#define _VGE_ENGINE_TMULTISTACK_HPP

#include <vector>

#include "vge/engine/TStack.hpp"



namespace vge
{

namespace engine
{



/**
 * @brief Container to store one or more stacks of objects.
 */
template< typename T >
struct TMultiStack
{
	typedef TStack< T > StackType;		///< type of a single stack

	/**
	 * @brief Constructor
	 * 
	 * Constructs the specified number of stacks and resets completely them.
	 * 
	 * @param numberOfStacks		number of stacks
	 */
	TMultiStack( const uint numberOfStacks = 0 );

	/**
	 * @brief Clears completely this container.
	 *
	 * All the stacks are dropped.
	 */
	void clear();

	/**
	 * @brief Resets completely all stacks.
	 * 
	 * @param numberOfStacks		number of stacks
	 *
	 * @post (*this)[i].isEmpty() == true
	 *
	 * @todo add( uint ), remove(uint)
	 */
	void resize( const uint numberOfStacks );

	/**
	 * @brief Tests if the number of stacks is zero.
	 * 
	 * @return true if the number of stacks is zero, false otherwise.
	 */
	const bool isEmpty() const;

	/**
	 * @brief Returns the number of stacks.
	 *
	 * @return the number of stacks
	 */
	const uint getSize() const;


	/**
	 * @name Stack accessors
	 */
	//@{

	/**
	 * @brief Returns the desired stack
	 *
	 * @param index		zero-base index
	 */
	StackType& operator []( const uint index );

	/**
	 * @brief Returns the desired stack
	 *
	 * @param index		zero-base index
	 */
	const StackType& operator []( const uint index ) const;


	/**
	 * @brief Sets for each stack the element at the top.
	 * 
	 * @param value	value to assign at the top
	 */
	void setTop( const T& value );

	/**
	 * @brief Adds an element
	 *
	 * Adds a new element at the top of each stack, above its current top element.
	 *
	 * @param element		new element to add
	 */
	void push( const T& element );

	/**
	 * @brief Adds an element 
	 *
	 * Adds a copy of the current top of each stack at the top of the stack, above its current top element.
	 */
	void push();

	/**
	 * @brief Removes an element
	 * 
	 * Removes the element on top of each stack, effectively reducing its size by one.
	 *
	 * @return true if sucessful, false if size of the stack is already zero.
	 *
	 * @todo throw an exception when stacks have != size.
	 */
	const bool pop();

	//@}


private:

	std::vector< StackType > m_stacks;	///< containers of stacks
};



#include "vge/engine/TMultiStack.hxx"



} // namespace engine

} // namespace vge

#endif //#ifndef _VGE_ENGINE_TMULTISTACK_HPP
