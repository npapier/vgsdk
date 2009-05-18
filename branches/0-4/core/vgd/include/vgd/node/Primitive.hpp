// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_PRIMITIVE_HPP
#define _VGD_NODE_PRIMITIVE_HPP

#include "vgd/vgd.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief A sequence of 3d geometrical primitive (like triangle, triangle strip, polygon...).
 * 
 * It use getNumIndices() sequential elements from the field \c vertexIndex in the current Shape starting at index
 * given by getIndex() to construct a sequence of the same geometrical primitive.
 * The type of primitive is selected with setType() method.
 */
struct VGD_API Primitive
{
	/**
	 * @name Typedefs.
	 */
	//@{
	
	/**
	 * @brief Geometrical primitives.
	 * 
	 * @remarks Be careful, the elements of this enumeration are ordered(see vgeGL::handler::painter::VertexShape).
	 */
	typedef enum {
		
		NONE	=0,

		POINTS,

		LINES, LINE_STRIP, LINE_LOOP,

		TRIANGLES, TRIANGLE_STRIP, TRIANGLE_FAN, 

		QUADS, QUAD_STRIP,

		POLYGON

	} Type;
	//@}



	/**
	 * @name Constructor.
	 */
	//@{
	
	/**
	 * @brief Constructor.
	 */
	Primitive( const Type type = TRIANGLES, const int32 index = -1, const int32 numIndices = 0 );
	//@}



	/**
	 *  @name Accessors.
	 */
	//@{

	/**
	 * @brief Sets the type of primitive.
	 *
	 * @param type		type of primitive.
	 */
	void       setType( const Type type );

	/**
	 * @brief Gets the type of primitive.
	 *
	 * @return type of primitive.
	 */
	const Type getType() const;


	/**
	 * @brief Sets the starting index of the primitives.
	 * 
	 * @param index	starting index of the primitives in the field getFVertexIndex().
	 */
	void        setIndex( const int32 index );

	/**
	 * @brief Gets the starting index of the primitives.
	 * 
	 * @return			starting index of the primitives in the field getFVertexIndex().
	 */
	const int32 getIndex() const;


	/**
	 * @brief Sets number of indices.
	 *
	 * Examples :
	 * 
	 * \li for one triangles(TRIANGLES), sets number of indices to 3.
	 * \li for one triangles strips with two triangles(TRIANGLE_STRIP), set number of indices to 3 + 1 = 4.
	 */
	void        setNumIndices( const int32 numIndices );

	/**
	 * @brief Gets number of indices.
	 */
	const int32 getNumIndices() const;
	//@}



protected:
	/**
	 * @name Datas.
	 */
	//@{
	
	/**
	 * @brief Type of the primitive.
	 */
	Type	m_type;

	/**
	 * @brief Index of the primitive.
	 */
	int32 m_index;
	
	/**
	 * @brief Number of indices.
	 */
	int32 m_numIndices;
	//@}
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_PRIMITIVE_HPP
