// VGSDK - Copyright (C) 2004-2006, 2013, 2014, Nicolas Papier.
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
#include "vgm/Segment.hpp"



namespace vgm
{



Plane::Plane()
{
}



Plane::Plane( const Vec3f& p0, const Vec3f& p1, const Vec3f& p2 )
{
	setValue( p0, p1, p2 );
}



Plane::Plane( const Vec3f& n, float d )
{
	setValue( n, d );
}



Plane::Plane( const Vec3f& n, const Vec3f& p )
{
	setValue( n, p );
}



void Plane::setValue( const Vec3f& p0, const Vec3f& p1, const Vec3f& p2 )
{
	m_normalVec = (p1 - p0).cross(p2 - p0);
	m_normalVec.normalize();
	m_distance = m_normalVec.dot(p0);
}



void Plane::setValue( const Vec3f& n, float d )
{
	m_normalVec = n;
	m_normalVec.normalize();
	m_distance = d;
}



void Plane::setValue( const Vec3f& n, const Vec3f& p )
{
	m_normalVec = n;
	m_normalVec.normalize();
	m_distance = m_normalVec.dot(p);
}



const Vec3f& Plane::getNormal( void ) const
{
	return m_normalVec;
}



float Plane::getDistanceFromOrigin( void ) const
{
	return m_distance;
}



const Vec4f Plane::getValue() const
{
	const vgm::Vec4f retVal( m_normalVec[0], m_normalVec[1], m_normalVec[2], -m_distance );
	return retVal;
}



void Plane::offset( float d )
{
	m_distance += d;
}



void Plane::transform( const MatrixR& matrix )
{
	// Find the point on the plane along the normal from the origin
	Vec3f	point = m_normalVec * m_distance;

	// Transform the plane normal by the matrix
	// to get the new normal. Use the inverse transpose
	// of the matrix so that normals are not scaled incorrectly.
	MatrixR invTran = matrix.getInverse().getTranspose();
	invTran.multDirMatrix(m_normalVec, m_normalVec);
	m_normalVec.normalize();

	// Transform the point by the matrix
	matrix.multVecMatrix(point, point);

	// The new distance is the projected distance of the vector to the
	// transformed point onto the (unit) transformed normal. This is
	// just a dot product.
	m_distance = point.dot(m_normalVec);
}



bool Plane::intersect( const Line& l, Vec3f& intersection ) const
{
	float t, denom;

	// solve for t:
	//  n . (l.p + t * l.d) - d == 0

	denom = m_normalVec.dot(l.getDirection());
	if ( denom == 0.0 )
		return false;

	//  t = - (n . l.p - d) / (n . l.d)
	t = - (m_normalVec.dot(l.getPosition()) - m_distance) /  denom;

	intersection = l.getPosition() + l.getDirection() * t;

	return true;
}



bool Plane::intersect(const Segment& l, Vec3f& intersection) const
{
	float t, denom;
	Vec3f direction = l.getEnd() - l.getBegin();
	// solve for t:
	//  n . (l.p + t * l.d) - d == 0

	denom = m_normalVec.dot(direction);
	if (denom == 0.0)
		return false;

	//  t = - (n . l.p - d) / (n . l.d)
	t = -(m_normalVec.dot(l.getBegin()) - m_distance) / denom;

	intersection = l.getBegin() + direction * t;

	return t >= 0.0 && t <= 1.0;
}


const Vec3f Plane::intersect( Plane& p0, Plane& p1, Plane& p2) const
{
	Vec3f vec;

#define DELTA 1e-6	
#define DET3(m) (( 			\
    m[0][0] * m[1][1] * m[2][2]	\
  + m[0][1] * m[1][2] * m[2][0]	\
  + m[0][2] * m[1][0] * m[2][1]	\
  - m[2][0] * m[1][1] * m[0][2]	\
  - m[2][1] * m[1][2] * m[0][0]	\
  - m[2][2] * m[1][0] * m[0][1]))

	float	v[3], del, mx[3][3], mi[3][3];
	
	// create 3x3 matrix of normal coefficients
	mx[0][0] = p0.getNormal()[0];
	mx[0][1] = p0.getNormal()[1];
	mx[0][2] = p0.getNormal()[2];
	mx[1][0] = p1.getNormal()[0];
	mx[1][1] = p1.getNormal()[1];
	mx[1][2] = p1.getNormal()[2];
	mx[2][0] = p2.getNormal()[0];
	mx[2][1] = p2.getNormal()[1];
	mx[2][2] = p2.getNormal()[2];

	// find determinant of matrix to use for divisor
	del = DET3(mx);

	//    printf("mx = %10.5f %10.5f %10.5f\n", mx[0][0], mx[0][1], mx[0][2]);
	//    printf("     %10.5f %10.5f %10.5f\n", mx[1][0], mx[1][1], mx[1][2]);
	//    printf("     %10.5f %10.5f %10.5f\n", mx[2][0], mx[2][1], mx[2][2]);
	if (del > -DELTA && del < DELTA)
	{	
		// if singular, just set to the origin
		vec[0] = 0;
		vec[1] = 0;
		vec[2] = 0;
	}
	else 
	{
		v[0] = p0.getDistanceFromOrigin();
		v[1] = p1.getDistanceFromOrigin();
		v[2] = p2.getDistanceFromOrigin();
		
		//	printf("v = %10.5f\n    %10.5f\n    %10.5f\n", v[0], v[1], v[2]);

		mi[0][0] = v[0]; mi[0][1] = mx[0][1]; mi[0][2] = mx[0][2];
		mi[1][0] = v[1]; mi[1][1] = mx[1][1]; mi[1][2] = mx[1][2];
		mi[2][0] = v[2]; mi[2][1] = mx[2][1]; mi[2][2] = mx[2][2];
		
		//	printf("mi = %10.5f %10.5f %10.5f\n", mi[0][0], mi[0][1], mi[0][2]);
		//	printf("     %10.5f %10.5f %10.5f\n", mi[1][0], mi[1][1], mi[1][2]);
		//	printf("     %10.5f %10.5f %10.5f\n", mi[2][0], mi[2][1], mi[2][2]);
		
		vec[0] = DET3(mi) / del;
		mi[0][0] = mx[0][0]; mi[0][1] = v[0]; mi[0][2] = mx[0][2];
		mi[1][0] = mx[1][0]; mi[1][1] = v[1]; mi[1][2] = mx[1][2];
		mi[2][0] = mx[2][0]; mi[2][1] = v[2]; mi[2][2] = mx[2][2];
		
		//	printf("mi = %10.5f %10.5f %10.5f\n", mi[0][0], mi[0][1], mi[0][2]);
		//	printf("     %10.5f %10.5f %10.5f\n", mi[1][0], mi[1][1], mi[1][2]);
		//	printf("     %10.5f %10.5f %10.5f\n", mi[2][0], mi[2][1], mi[2][2]);
		
		vec[1] = DET3(mi) / del;
		mi[0][0] = mx[0][0]; mi[0][1] = mx[0][1]; mi[0][2] = v[0];
		mi[1][0] = mx[1][0]; mi[1][1] = mx[1][1]; mi[1][2] = v[1];
		mi[2][0] = mx[2][0]; mi[2][1] = mx[2][1]; mi[2][2] = v[2];
		
		//	printf("mi = %10.5f %10.5f %10.5f\n", mi[0][0], mi[0][1], mi[0][2]);
		//	printf("     %10.5f %10.5f %10.5f\n", mi[1][0], mi[1][1], mi[1][2]);
		//	printf("     %10.5f %10.5f %10.5f\n", mi[2][0], mi[2][1], mi[2][2]);

		vec[2] = DET3(mi) / del;
	}
	//printf("%10.5f %10.5f %10.5f\n", vec[0], vec[1], vec[2]);
	
	return vec;

#undef DET3
#undef DELTA
}


const vgm::Vec3f Plane::project( const vgm::Vec3f& p ) const
{
	const vgm::Vec3f POntoThePlane = p - getNormal() * distance(p);
	return POntoThePlane;
}


const float Plane::distance( const Vec3f& point ) const
{
	return point.dot(m_normalVec) - m_distance;
}


const bool Plane::isIn( const Vec3f& point, const float tolerance ) const
{
	const float dist = distance(point);

	return vgm::equals( dist, 0.f, tolerance );
}


const bool Plane::isInHalfSpace( const Vec3f& point ) const
{
	// Multiply point by plane equation coefficients, compare distances
	return point.dot(m_normalVec) >= m_distance;
}



bool Plane::operator ==( const Plane& p2 ) const
{
	return (m_distance == p2.m_distance && m_normalVec == p2.m_normalVec);
}

bool Plane::operator !=( const Plane& p2 ) const
{ 
	return !(*this == p2);
}



} //namespace vgm
