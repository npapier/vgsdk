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

#include "vgm/Plane.hpp"

#include "vgm/Line.hpp"
#include "vgm/Matrix.hpp"



namespace vgm
{



Plane::Plane( void )	
{
}



Plane::Plane( const Vec3f& p0, const Vec3f& p1, const Vec3f& p2 )
{
	normalVec = (p1 - p0).cross(p2 - p0);
	normalVec.normalize();
	distance = normalVec.dot(p0);
}



Plane::Plane( const Vec3f& n, float d )
{
	normalVec = n;
	normalVec.normalize();
	distance = d;
}



Plane::Plane( const Vec3f& n, const Vec3f& p )
{
	normalVec = n;
	normalVec.normalize();
	distance = normalVec.dot(p);
}



const Vec3f& Plane::getNormal( void ) const
{
	return normalVec;
}



float Plane::getDistanceFromOrigin( void ) const
{
	return distance;
}



void Plane::offset( float d )
{
	distance += d;
}



void Plane::transform( const MatrixR& matrix )
{
	// Find the point on the plane along the normal from the origin
	Vec3f	point = normalVec * distance;

	// Transform the plane normal by the matrix
	// to get the new normal. Use the inverse transpose
	// of the matrix so that normals are not scaled incorrectly.
	MatrixR invTran = matrix.getInverse().getTranspose();
	invTran.multDirMatrix(normalVec, normalVec);
	normalVec.normalize();

	// Transform the point by the matrix
	matrix.multVecMatrix(point, point);

	// The new distance is the projected distance of the vector to the
	// transformed point onto the (unit) transformed normal. This is
	// just a dot product.
	distance = point.dot(normalVec);
}



bool Plane::intersect( const Line& l, Vec3f& intersection ) const
{
	float t, denom;

	// solve for t:
	//  n . (l.p + t * l.d) - d == 0

	denom = normalVec.dot(l.getDirection());
	if ( denom == 0.0 )
		return false;

	//  t = - (n . l.p - d) / (n . l.d)
	t = - (normalVec.dot(l.getPosition()) - distance) /  denom;

	intersection = l.getPosition() + l.getDirection() * t;

	return true;
}



bool Plane::isInHalfSpace( const Vec3f& point ) const
{
	// Multiply point by plane equation coefficients, compare distances
	return point.dot(normalVec) >= distance;
}



bool Plane::operator ==( const Plane& p2 ) const
{
	return (distance == p2.distance && normalVec == p2.normalVec);
}

bool Plane::operator !=( const Plane& p2 ) const
{ 
	return !(*this == p2);
}



} //namespace vgm
