// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_ENGINE_MULTIMATRIXSTACK_H
#define _VGE_ENGINE_MULTIMATRIXSTACK_H

#include "vge/vge.hpp"

#include <vector>
#include <vgm/Matrix.hpp>



namespace vge
{
	
namespace engine
{

/**
 * @brief An object for storing one or more stacks of matrix.
 * 
 * @todo Convert to a template.
 */
struct VGE_API MultiMatrixStack
{
	/**
	 * @brief Constructor.
	 * 
	 * Constructs the specified number of matrix stacks and resets completely them.
	 * 
	 * @param size							number of stack.
	 * @param matrixStackSizeHint		number of matrices in a stack that are reserved at construct time.
	 */
	MultiMatrixStack( const uint32 size = 1, const uint32 matrixStackSizeHint = 1 );

	/**
	 * @brief Resets completely all stacks.
	 * 
	 * @post		sizeOf(...) must return 1 and getTop(...).isIdentity() must return true.
	 */
	void resize( const uint32 size );
	
	/**
	 * @brief Returns the number of matrix stacks
	 */
	int32	size() const;

	/**
	 * @brief Resets completely the specified stack.
	 * 
	 * @param index		zero-base index.
	 * 
	 * @post		sizeOf(...) must return 1 and getTop(...).isIdentity() must return true.
	 */
	void reset( const int32 index = 0 );

	/**
	 * @brief Tests if the specified stack is empty.
	 * 
	 * @param index		zero-base index.
	 * 
	 * @return true if the stack is empty, false otherwise.
	 */	
	bool isEmpty( const int32 index = 0) const;
	
	/**
	 * @brief Returns the number of elements in the specified stack.
	 * 
	 * @param index		zero-base index.
	 * 
	 * @return the number of elements in the stack.
	 */
	int32 sizeOf( const int32 index = 0 ) const;

	/**
	 * @brief Sets the top of the stack.
	 * 
	 * @param value		value to assign at the top of the stack.
	 * @param index		zero-base index.
	 */
	void setTop( const vgm::MatrixR& value, const int32 index = 0 );

	/**
	 * @brief Gets the top of the stack.
	 * 
	 * @param index		zero-base index.
	 * 
	 * @return the top of the stack.
	 */
	const vgm::MatrixR& getTop( const int32 index = 0 ) const;

	/**
	 * @brief Gets the top of the stack.
	 * 
	 * @param index		zero-base index.
	 * 
	 * @return the top of the stack.
	 */
	vgm::MatrixR& getTop( const int32 index = 0 );

	/**
	 * @brief Adds an element(a copy of the current top) at the top of the stack.
	 * 
	 * @param index		zero-base index.
	 */
	void push( const int32 index = 0 );

	/**
	 * @brief Adds an element(a copy of the current top) at the top of the stack (for each stack).
	 */
	void pushAll();

	/**
	 * @brief Removes the element from the top of the stack.
	 * 
	 * @param index		zero-base index.
	 * 
	 * @return true if sucessful, false if size of the stack is already zero.
	 */
	bool pop( const int32 index = 0 );
	
	/**
	 * @brief Removes the element from the top of the stack (for each stack).
	 * 
	 * @return true if sucessful, false if size of at least one stack is already zero.
	 */
	bool popAll();

	/**
	 * @brief Accessor to the matrix stack size hint.
	 */
	void setMatrixStackSizeHint( const uint32 size );
	
	/**
	 * @brief Accessor to the matrix stack size hint.
	 */
	const uint32 getMatrixStackSizeHint() const;



private:

	/**
	 * @brief Stack of matrix.
	 */
	typedef std::vector< vgm::MatrixR >				MatrixStack;

	/**
	 * @brief Hint for the size of matrix stack.
	 */
	uint32													m_matrixStackSizeHint;
	
	/**
	 * @brief The stacks.
	 */
	std::vector< MatrixStack >							m_stacks;
};



} // namespace engine

} // namespace vge

#endif //#ifndef _VGE_ENGINE_MULTIMATRIXSTACK_H
