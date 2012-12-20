// VGSDK - Copyright (C) 2008, 2012, Pierre-Jean Bensoussan, Nicolas Papier, Alexandre Di Pino.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Pierre-Jean Bensoussan
// Author Alexandre Di Pino
// Author Nicolas Papier

#ifndef _VGALG_NODE_VERTEXSHAPE_HPP
#define _VGALG_NODE_VERTEXSHAPE_HPP

#include "vgAlg/vgAlg.hpp"
#include <vgd/field/EditorRO.hpp>
#include <vgd/field/EditorRW.hpp>
#include <vgd/field/Vector.hpp>
#include <vgd/field/Integer.hpp>

namespace vgd
{
	template<class T> struct Shp;
	namespace node { struct VertexShape; }
}



namespace vgAlg
{

namespace node
{



/**
 * @name Normals/tangents computing management
 */
//@{

/**
 * @brief Enumeration of different compute normal implementations.
 */
enum COMPUTE_NORMAL_METHOD
{
	NO_COMPUTE_NORMAL  = 0,
	COMPUTE_NORMAL_STANDARD,	///< using vgm::Vector
	DEFAULT_COMPUTE_NORMAL = COMPUTE_NORMAL_STANDARD
};

/**
 * @brief Enumeration of different compute tangent implementations.
 */
enum COMPUTE_TANGENT_METHOD
{
	NO_COMPUTE_TANGENT,
	COMPUTE_TANGENT_STANDARD,	///< using vgm::Vector
	DEFAULT_COMPUTE_TANGENT = COMPUTE_TANGENT_STANDARD
};

/**
 * @brief Enumeration of different compute normalization implementations.
 */
enum COMPUTE_NORMALIZATION_METHOD
{
	NO_COMPUTE_NORMALIZATION,
	COMPUTE_NORMALIZATION_STANDARD,	///< using vgm::Vector
	DEFAULT_COMPUTE_NORMALIZATION = COMPUTE_NORMALIZATION_STANDARD
};

/**
 * @brief get normals compute methods
 */
VGALG_API const vgAlg::node::COMPUTE_NORMAL_METHOD getComputeNormalMethod();

/**
 * @brief set normals compute methods
 */
VGALG_API void setComputeNormalMethod( const vgAlg::node::COMPUTE_NORMAL_METHOD value);


/**
 * @brief get tangents compute methods
 */
VGALG_API const vgAlg::node::COMPUTE_TANGENT_METHOD getComputeTangentMethod();


/**
 * @brief set tangents compute methods
 */
VGALG_API void setComputeTangentMethod( const vgAlg::node::COMPUTE_TANGENT_METHOD value);


/**
 * @brief get normalize compute methods
 */
VGALG_API const vgAlg::node::COMPUTE_NORMALIZATION_METHOD getNormalizationMethod();


/**
 * @brief set normalize compute methods
 */
VGALG_API void setNormalizationMethod( const vgAlg::node::COMPUTE_NORMAL_METHOD value );


/**
 * @brief get othogonalize tangent compute methods
 */
VGALG_API const bool getOrthogonalize();


/**
 * @brief get othogonalize tangent compute methods
 */
VGALG_API void setOrthogonalize( const bool value );
//@}



/**
 * @name Algorithms on vertex shape
 */
//@{

/**
 * @brief Inverse the orientation of primitives.
 * 
 * @param vertexShape		the vertexShape node
 * 
 * This method reverses (clockwise to conterclockwise or ccw to cw) the orientation 
 * of each triangles and quads of the given vertexShape.
 */
VGALG_API void invertPrimitiveOrientation( vgd::Shp< vgd::node::VertexShape > vertexShape );


/**
 * @brief Inverse the orientation of normals.
 * 
 * @param vertexShape		the vertexShape node
 * 
 * This method reverses the orientation of each normals of the given vertexShape.
 */
VGALG_API void invertNormalOrientation( vgd::Shp< vgd::node::VertexShape > vertexShape );


/**
 * @brief Transform quad primitives into triangle.
 * 
 * @param vertexShape		the vertexShape node
 * 
 * This method transforms QUAD primitives into TRIANGLE.
 *
 * @todo Take care of texCoord field(s)
 */
VGALG_API void triangulate( vgd::Shp< vgd::node::VertexShape > vertexShape );


/**
 * @brief Computes normals for the given vertex shape (with or without normalization)
 * 
 * @param vertexShape		the vertex shape node
 */
VGALG_API void computeNormals( vgd::Shp< vgd::node::VertexShape > vertexShape/*, const vgAlg::node::COMPUTE_NORMAL_METHOD value todo */);


/**
 * @brief Computes tangents for the given vertex shape (with ot without normalization)
 *
 * @param vertexShape		the vertex shape node
 *
 * @pre vertexShape->getNumTexUnits() > 0
 */
VGALG_API void computeTangents(	vgd::Shp< vgd::node::VertexShape > vertexShape/*, const vgAlg::node::COMPUTE_NORMAL_METHOD value todo */);
//@}


/**
 * @name Normalization
 */
//@{
/**
 * @brief Normalizes the 'normal' field of the given vertex shape
 */
VGALG_API void normalizeNormals( vgd::Shp< vgd::node::VertexShape > vertexShape/*, const vgAlg::node::COMPUTE_NORMAL_METHOD value todo */ );


/**
 * @brief Normalizes the 'tangent' field of the given vertex shape
 */
VGALG_API void normalizeTangents( vgd::Shp< vgd::node::VertexShape > vertexShape/*, const vgAlg::node::COMPUTE_NORMAL_METHOD value todo */ );


/**
 * @brief Normalizes all vectors in the given field
 *
 * @todo Vec2 Vec4 or generic version
 */
VGALG_API void normalizeField( vgd::field::EditorRW< vgd::field::MFVec3f >& field/*, const vgAlg::node::COMPUTE_NORMAL_METHOD value todo */);
//@}



/**
 * @name Normals/Tangents/normalization computing functions
 */
//@{

/**
 * @brief Computes mesh normals (one normal per vertex)
 */
VGALG_API void computeNormalsStandard(	vgd::field::EditorRO< vgd::field::MFVec3f >&	vertices,
										vgd::field::EditorRO< vgd::field::MFUInt32 >&	vertexIndex,
										vgd::field::EditorRW< vgd::field::MFVec3f >&	normals,
										const int32 numTris );

/**
 * @brief Computes mesh tangents
 */
VGALG_API void computeTangentsStandard(	vgd::field::EditorRO< vgd::field::MFVec3f >&	vertices,
										vgd::field::EditorRO< vgd::field::MFUInt32 >&	vertexIndex,
										vgd::field::EditorRW< vgd::field::MFVec3f >&	tangent,
										vgd::field::EditorRO< vgd::field::MFVec3f >&	normals,
										vgd::field::EditorRO< vgd::field::MFVec2f >&	texCoord,
										const int32 numTris );

/**
 * @brief Normalizes all vectors in the given field
 *
 * @todo Vec2 Vec4 or generic version
 */
VGALG_API void normalizeFieldStandard( vgd::field::EditorRW< vgd::field::MFVec3f >& field );
//@}



} // namespace node

} //namespace vgAlg

//@}

#endif // #ifndef _VGALG_NODE_VERTEXSHAPE_HPP
