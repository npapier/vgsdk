// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGALG_INTERSECT_HELPERS_HPP
#define _VGALG_INTERSECT_HELPERS_HPP

#include "vgAlg/vgAlg.hpp"
#include <vgm/Vector.hpp>

namespace vgm { struct Plane; struct Sphere; struct TriangleExt; }
namespace vgd { namespace node { struct VertexShape; } }


namespace vgAlg
{

namespace intersect
{


/**
 * @name High-level intersection functions
 */
//@{

/**
 * @brief Search the triangle (ABC) containing the point P in the given vertexShape.
 *
 * @param P							point to seach in the shape
 * @param vertexShape				shape where to look for the triangle
 * @param oABC						the triangle ABC, indices of points ABC and the hit point P with barycentric coordinates (u,v) in (A, AB, BC). A is a local origin.
 * @param oDistance					fabs( ABC.distance(P) )
 *
 * @return true if a triangle was found, false otherwise.
 *
 * @pre isATriSet(vertexShape)
 */
VGALG_API const bool getTriangle(	const vgm::Vec3f& P, const vgd::node::VertexShape * vertexShape,
									vgm::TriangleExt& oABC, float& oDistance );
//@}



/**
 * @name Low-level intersection functions
 */
//@{

/**
 * @brief Test if the given point P is inside the triangle ABC.
 *
 * @pre P is coplanar with ABC
 *
 * @param P						point to test
 * @param A						first point to build the triangle
 * @param B						second point to build the triangle
 * @param C						third point to build the triangle
 * @param oBarycentricCoordP	(u,v) barycentric coordinates of P in (A, AB, BC). A is a local origin.
 *
 * @return true if P is in the triangle, false otherwise.
 */
VGALG_API const bool isPointPInTriangleABC(	const vgm::Vec3f P, const vgm::Vec3f A, const vgm::Vec3f B, const vgm::Vec3f C,
											vgm::Vec2f& oBarycentricCoordP );


/**
 * @brief Returns all triangles of the given shape that are inside the sphere.
 *
 * @param vertexShape			the shape to filter
 * @param sphere				criterion to filter triangles
 * @param oTrianglesIndices		an array containing triangles indices (indices in vertex/normal/texCoord arrays).
 *
 * @remark Membership of triangle to sphere is true if A or B or C is inside S(phere) or
 * if [AB]^sphere != 0 or [BC]^sphere != 0 or [CA]^sphere != 0 with ^ <=> intersection
 */
VGALG_API const bool getTriangles(	const vgd::node::VertexShape * vertexShape, const vgm::Sphere& sphere,
									std::vector< uint32 >& oTrianglesIndices );

/**
 * @brief Returns all triangles of the given shape that are in the half space defined by the given plane.
 *
 * @param vertexShape				the shape to filter
 * @param trianglesIndicesToFilter	an array containing triangles indices to look at or empty to look at all triangles of the vertexShape
 * @param plane						criterion to filter triangles
 * @param oTrianglesIndices			an array containing triangles indices (indices in vertex/normal/texCoord arrays).
 *
 * @remark Membership of triangle to half space defined by plane is true if at least one vertex of the triangle verified the criterion
 */
VGALG_API const bool getTriangles(	const vgd::node::VertexShape * vertexShape, const std::vector< uint32 >& trianglesIndicesToFilter,
									const vgm::Plane& plane,
									std::vector< uint32 >& oTrianglesIndices );

//@}



} // namespace intersect

} // namespace vgAlg

#endif //#ifndef _VGALG_INTERSECT_HELPERS_HPP
