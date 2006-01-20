// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

/*
 * This file is a work based on the open source release of Open Inventor (from SGI).
 */

/*
 *
 *  Copyright (C) 2000 Silicon Graphics, Inc.  All Rights Reserved. 
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  Further, this software is distributed without any warranty that it is
 *  free of the rightful claim of any third person regarding infringement
 *  or the like.  Any license provided herein, whether implied or
 *  otherwise, applies only to this software file.  Patent licenses, if
 *  any, provided herein do not apply to combinations of this program with
 *  other software, or any other product whatsoever.
 * 
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *  Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,
 *  Mountain View, CA  94043, or:
 * 
 *  http://www.sgi.com 
 * 
 *  For further information regarding this notice, see: 
 * 
 *  http://oss.sgi.com/projects/GenInfo/NoticeExplan/
 *
 */

/*
 * Author(s)		:	Paul S. Strauss, Nick Thompson, David Mott.
 */

#ifndef _VGM_PLANE_H
#define _VGM_PLANE_H

#include "vgm/vgm.hpp"
#include "vgm/Vector.hpp"



namespace vgm
{

struct MatrixR;
struct Line;

/**
 * @brief Represents an oriented plane in 3D space. 
 * 
 * The plane is defined by a plane normal and a distance from the origin along that normal.
 * Planes may be used to represent either planes or half-spaces. 
 * In the latter case (as for the isInHalfSpace() method), the
 * half-space is defined to be all points on the plane or on the side
 * of the plane in the direction of the plane normal.
 * 
 * The 4 coefficients of the plane equation of an Plane can be
 * obtained easily as the 3 coordinates of the plane normal and the
 * distance, in that order.
 * 
 * @ingroup Geometry
 */
struct VGM_API Plane
{
	/**
	 * @name Constructors and destructor.
	 */
	//@{
	
	/**
	 * @brief Default constructor.
	 */
	Plane( void );
	
	/**
	 * @brief Construct a plane given 3 points.
	 * 
	 * Orientation is computed by taking (p1 - p0) x (p2 - p0) and
	 * pointing the normal in that direction.
	 */
	Plane( const Vec3f& p0, const Vec3f& p1, const Vec3f& p2 );

	/**
	 * @brief Construct a plane given normal and distance from origin along normal.
	 * 
	 * Orientation is given by the normal vector n.
	 */
	Plane( const Vec3f& n, float d );

	/**
	 * @brief Construct a plane given normal and a point to pass through
	 * 
	 * Orientation is given by the normal vector n.
	 */
	Plane( const Vec3f& n, const Vec3f& p );
	//@}
	
	/**
	 * @name Plane accessors.
	 */
	//@{

	/**
	 * @brief Returns normal vector to plane.
	 */
	const Vec3f&	getNormal( void ) const;
	
	/**
	 * @brief Returns distance from origin to plane.
	 */
	float			getDistanceFromOrigin( void ) const;
	//@}

	/**
	 * @name Transformation accessors.
	 */
	//@{
	
	/**
	 * @brief Offset a plane by a given distance.
	 */
	void	offset( float d );

	/**
	 * @brief Transforms the plane by the given matrix.
	 */
	void	transform( const MatrixR& matrix );
	//@}

	/**
	 * @name Intersection methods.
	 */
	//@{

	/**
	 * @brief Intersect line and plane, returning true if there is an intersection
	 * false if line is parallel to plane.
	 */
	bool	intersect( const Line& l,
					   Vec3f& intersection) const;

	/**
	 * @brief Returns true if the given point is within the half-space
	 * defined by the plane.
	 */
	bool	isInHalfSpace( const Vec3f& point ) const;
	//@}

	/**
	 * @name Comparison methods.
	 */
	//@{
	
	/**
	 * @brief Equality comparison.
	 */
	bool	operator ==( const Plane& p2 ) const;
	
	/**
	 * @brief Difference comparison.
	 */	
	bool	operator !=( const Plane& p2 ) const;
	//@}

private:

	/**
	 * @name Plane data.
	 * 
	 * Plane is all p such that normalVec . p - distance = 0
	 */
	//@{
	
	/**
	 * @brief Normal to the plane.
	 */
	Vec3f	normalVec;

	/**
	 * @brief Distance from origin to plane: distance * normalVec is on the plane.
	 */
	float	distance;
	//@}
};

} // namespace vgm

#endif // #ifndef _VGM_PLANE_H
