// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_PRIMITIVE_H
#define _VGD_NODE_PRIMITIVE_H

#include "vgd/vgd.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Abstraction of a 3d geometrical primitive (like triangle, triangle strip, polygon...).
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
	 * @remarks Be careful, the elements of this enumeration are ordered(see vgeGL::handler::VertexShapePainter).
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
	 * @param type : type of primitive.
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
	 * @param index	starting index of the primitives in the vertex table.
	 */
	void        setIndex( const int32 index );

	/**
	 * @brief Gets the starting index of the primitives.
	 * 
	 * @return			starting index of the primitives in the field getFVertex().
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

#endif //#ifndef _VGD_NODE_PRIMITIVE_H
