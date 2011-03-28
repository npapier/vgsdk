// VGSDK - Copyright (C) 2009, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_ENGINE_TSTACK_HPP
#define _VGE_ENGINE_TSTACK_HPP

#include <deque>
#include <vgBase/Type.hpp>
#include <vgd/Shp.hpp>



namespace vge
{

namespace engine
{



/**
 * @brief Stack (LIFO last-in first-out)
 *
 * This containers adaptors extends slightly the interface of the standard stack (clear(), push()).
 *
 * requirements for T : CopyConstructible (for push() method)
 */
template< typename T, class Container = std::deque<T> >
struct TStack
{
	/**
	 * @brief Default constructor
	 */
	TStack();

	/**
	 * @brief Clears completely the stack.
	 *
	 * All the elements in the stack are dropped.
	 */
	void clear();

	/**
	 * @brief Clears completely the stack, then adds an element
	 *
	 * All the elements in the stack are dropped, then adds a new element at the top
	 * of the stack, above its current top element.
	 *
	 * @param element		new element to add
	 *
	 * @remarks same as clear(), push( element );
	 */
	void clear( const T& element );

	/**
	 * @brief Tests if the stack is empty.
	 * 
	 * @return true if the stack is empty, false otherwise.
	 */
	const bool isEmpty() const;

	/**
	 * @brief Returns the number of elements in the stack.
	 *
	 * @return the number of elements in the stack.
	 */
	const uint getSize() const;


	/**
	 * @name Element accessors
	 */
	//@{

	/**
	 * @brief Gets the top of the stack.
	 * 
	 * @return the top of the stack.
	 */
	const T& getTop() const;

	/**
	 * @brief Gets the top of the stack.
	 * 
	 * @return the top of the stack.
	 */
	T& getTop();

	/**
	 * @brief Sets the top of the stack.
	 * 
	 * @param value	value to assign at the top of the stack.
	 */
	void setTop( const T& value );

	/**
	 * @brief Adds an element
	 *
	 * Adds a new element at the top of the stack, above its current top element.
	 *
	 * @param element		new element to add
	 */
	void push( const T& element );

	/**
	 * @brief Adds an element 
	 *
	 * Adds a copy of the current top of the stack at the top of the stack, above its current top element.
	 */
	void push();

	/**
	 * @brief Removes an element
	 * 
	 * Removes the element on top of the stack, effectively reducing its size by one.
	 *
	 * @return true if sucessful, false if size of the stack is already zero.
	 */
	const bool pop();

	//@}

protected:
	Container m_container; ///< underlying container used to implement stack
};



template< typename T >
struct TStackShp : public TStack< vgd::Shp< T > >
{
	TStackShp();

	void push();
};



#include "vge/engine/TStack.hxx"



} // namespace engine

} // namespace vge

#endif //#ifndef _VGE_ENGINE_TSTACK_HPP
