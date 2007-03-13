// VGSDK - Copyright (C) 2004-2006, Nicolas Papier.
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

#ifndef _VGM_LINE_HPP
#define _VGM_LINE_HPP

#include "vgm/vgm.hpp"
#include "vgm/Vector.hpp"



namespace vgm
{



struct Box3f;
	
/**
 * @brief Represents a directed line in 3D space.
 * 
 * Line provides a way of specifying a directed line, through a 3D point (origin) and a vector direction in 3D space.
 * 
 * @ingroup Geometry
 */
struct VGM_API Line
{



	/**
	 * @name Constructors and destructor.
	 */
	//@{
	Line();

	/**
	 * @brief Construct a line from two points lying on the line.
	 * 
	 * If you want to construct a line from a position and a direction, use
	 * Line(p, p + d). Line is directed from p0 to p1.
	 */
	Line( const Vec3f& p0, const Vec3f& p1 );
	//@}

	/**
	 * @name Accessors.
	 */
	//@{
	
	/**
	 * @brief Construct a line from two points lying on the line.
	 * 
	 * If you want to construct a line from a position and a direction, use
	 * Line(p, p + d). Line is directed from p0 to p1.
	 * @sa Line(const Vec3f&,const Vec3f&)
	 * 
	 */
	void			setValue( const Vec3f& p0, const Vec3f& p1 );

	/**
	 * @brief Set the position of the line.
	 */
	const Vec3f&	getPosition( void ) const;
	
	/**
	 * @brief Set the direction of the line.
	 */
	const Vec3f&	getDirection( void ) const;
	//@}


	/**
	 * @name Some useful computing methods.
	 */
	//@{

	/**
	 * @brief Find closest points between the two lines.
	 *
	 * Return false if they are parallel, otherwise return true.
	 * Find points on this line and on line2 that are closest to each other.
	 * If the lines intersect, then ptOnThis and ptOnLine2 will be equal.
	 * If the lines are parallel, then false is returned, and the contents of
	 * ptOnThis and ptOnLine2 are undefined.
	 */
	bool		getClosestPoints(	const Line& line2,
									Vec3f& ptOnThis,
									Vec3f& ptOnLine2 ) const;
									
	/**
	 * @brief Returns the closest point on the line to the given point.
	 */
	Vec3f		getClosestPoint( const Vec3f& point ) const;
	//@}



	/**
	 * @name Intersection methods.
	 */
	//@{

	/**
	 * @brief Intersect the line with a 3D box.
	 * 
	 * The line is intersected with the twelve triangles that make up the box.
	 */
	 bool intersect(	const Box3f& box,
						Vec3f& enter, Vec3f& exit ) const;

	/**
	 * @brief Intersect the line with a 3D box.  The line is augmented with an
	 * angle to form a cone.
	 * 
	 * The box must lie within pickAngle of the line.  If the angle is < 0.0, abs(angle) is the radius of a
	 * cylinder for an orthographic intersection. 
	 */
	bool intersect( float angle, const Box3f& box ) const;
	
	/**
	 * @brief Intersect the line with a point.  
	 * 
	 * @param pickAngle	The angle which makes the cone.
	 * @param point		The point to interesect.
	 * @return			true if there is an intersection, false otherwise.
	 *
	 * The line is augmented with an angle to form a cone.
	 * The point must lie within pickAngle of the line.
	 * If the angle is < 0.0, abs(angle) is the radius of a cylinder for an orthographic 
	 * intersection.
	 */
	bool intersect( float pickAngle, const Vec3f& point ) const;

	/**
	 * @brief Intersect the line with a line segment.
	 * 
	 * @param pickAngle		The angle which makes the cone.
	 * @param v0				One endpoint of the line segment.
	 * @param v1				The other endpoint of the line segment.
	 * @param intersection	The intersection point.
	 *
	 * The line is augmented with an angle to form a cone.
	 * The line segment must lie within pickAngle of the line.
	 * If an intersection occurs, the intersection point is placed in intersection.
	 */
	 bool intersect(	float pickAngle, const Vec3f& v0, const Vec3f& v1,
	 					Vec3f& intersection ) const;

	/**
	 * @brief Intersects the line with the triangle formed by v0, v1, v2.
	 * 
	 * @return Returns true if there is an intersection. If there is an
	 * intersection, barycentric will contain the barycentric
	 * coordinates of the intersection (for v0, v1, v2, respectively)
	 * and front will be set to true if the ray intersected the front
	 * of the triangle (as defined by the right hand rule).
	 */
	bool intersect(	const Vec3f& v0,
					const Vec3f& v1,
					const Vec3f& v2,
					Vec3f& pt, Vec3f& barycentric, bool& front ) const;
	//@}
	
private:

	/**
	 * @name Parametric description: l(t) = pos + t * dir
	 */
	//@{
	Vec3f	pos;
	Vec3f	dir;
	//@}
};

} // namespace vgm

#endif // #ifndef _VGM_LINE_HPP
