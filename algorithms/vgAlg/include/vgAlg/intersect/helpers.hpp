// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGALG_INTERSECT_HELPERS_HPP
#define _VGALG_INTERSECT_HELPERS_HPP

#include "vgAlg/vgAlg.hpp"
#include <vgm/Vector.hpp>

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
 * @param oIndexA					first point of the triangle (ABC)
 * @param oIndexB					second point of the triangle (ABC)
 * @param oIndexC					third point of the triangle (ABC)
 * @param oBarycentricCoordOfP		(u,v) barycentric coordinates of P in (A, AB, BC). A is a local origin.
 * @param oDistance					fabs( ABC.distance(P) )
 *
 * @return true if a triangle was found, false otherwise.
 *
 * @pre isATriSet(vertexShape)
 *
 * @remark Only working on front face.
 * @todo Have to work on BACK face too.
 */
VGALG_API const bool getTriangle(	const vgm::Vec3f& P, const vgd::node::VertexShape * vertexShape,
									int32& oIndexA, int32& oIndexB, int32& oIndexC, vgm::Vec2f& oBarycentricCoordOfP, float& oDistance );
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

//@}



} // namespace intersect

} // namespace vgAlg

#endif //#ifndef _VGALG_INTERSECT_HELPERS_HPP
