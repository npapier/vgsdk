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

#include "vgm/Box.hpp"

#include <limits>



namespace vgm
{



// *** Box3f ***
Box3f::Box3f( void )
{
	makeEmpty(); 
}



Box3f::Box3f(	float xmin, float ymin, float zmin,
				float xmax, float ymax, float zmax)
{
	m_min.setValue(xmin, ymin, zmin); 
	m_max.setValue(xmax, ymax, zmax);
}



Box3f::Box3f(const Vec3f& min, const Vec3f& max)
{
	m_min = min;
	m_max = max;
}



Box3f::~Box3f( void )
{
}



const Vec3f& Box3f::getMin( void ) const
{
	return m_min;
}



Vec3f& Box3f::getMin( void )
{
	return m_min;
}



const Vec3f& Box3f::getMax( void ) const 
{
	return m_max;
}



Vec3f& Box3f::getMax( void )
{
	return m_max;
}



Vec3f Box3f::getCenter( void ) const
{
	return Vec3f(
		0.5f * (m_min[0] + m_max[0]),
		0.5f * (m_min[1] + m_max[1]),
		0.5f * (m_min[2] + m_max[2]));
}



void Box3f::getOrigin( float& originX, float& originY, float& originZ) const
{
	originX = m_min[0]; 
	originY = m_min[1]; 
	originZ = m_min[2];
}



void Box3f::getSize( float& sizeX, float& sizeY, float& sizeZ) const
{
	sizeX = m_max[0] - m_min[0];
	sizeY = m_max[1] - m_min[1];
	sizeZ = m_max[2] - m_min[2];
}



void Box3f::makeEmpty( void )
{
	float floatMax = std::numeric_limits<float>::max();

	m_min.setValue(floatMax, floatMax, floatMax);
	m_max.setValue(-floatMax, -floatMax, -floatMax);
}



bool Box3f::isEmpty( void ) const
{
	return m_max[0] < m_min[0];
}



void Box3f::setBounds(
		float xmin, float ymin, float zmin,
		float xmax, float ymax, float zmax )
{
	m_min.setValue(xmin, ymin, zmin); 
	m_max.setValue(xmax, ymax, zmax);
}



void Box3f::setBounds( const Vec3f& min, const Vec3f& max )
{ 
	m_min = min; 
	m_max = max;
}



void Box3f::getBounds(
		float& xmin, float& ymin, float& zmin,
		float& xmax, float& ymax, float& zmax ) const
{ 
	m_min.getValue(xmin, ymin, zmin);
	m_max.getValue(xmax, ymax, zmax);
}



void Box3f::getBounds( Vec3f& min, Vec3f& max ) const
{
	min = getMin();
	max = getMax();
}



void Box3f::transform( const MatrixR& m )
{
	// a transformed empty box is still empty
	if ( isEmpty() ) return;

	Vec3f	newMin, newMax;
	int32	i;

	for (i = 0; i < 3; i++)
	{
		newMin[i] = minExtreme(m_min, m_max, m, i);
		newMax[i] = minExtreme(m_max, m_min, m, i);
	}
	float Wmin = minExtreme(m_min, m_max, m, 3);
	float Wmax = minExtreme(m_max, m_min, m, 3);

	// Division by small W's make things bigger; wacky things happen
	// if W's are negative, but negative W's are wacky so I think
	// that's OK:

	newMin /= Wmax;
	newMax /= Wmin;

	m_min = newMin;
	m_max = newMax;
}



void Box3f::extendBy( const Vec3f& pt )
{
	if (pt[0] < m_min[0]) m_min[0] = pt[0];
	if (pt[1] < m_min[1]) m_min[1] = pt[1];
	if (pt[2] < m_min[2]) m_min[2] = pt[2];
	if (pt[0] > m_max[0]) m_max[0] = pt[0];
	if (pt[1] > m_max[1]) m_max[1] = pt[1];
	if (pt[2] > m_max[2]) m_max[2] = pt[2];
}



void Box3f::extendBy( const Box3f& bb )
{
	if (bb.m_min[0] < m_min[0]) m_min[0] = bb.m_min[0];
	if (bb.m_min[1] < m_min[1]) m_min[1] = bb.m_min[1];
	if (bb.m_min[2] < m_min[2]) m_min[2] = bb.m_min[2];
	if (bb.m_max[0] > m_max[0]) m_max[0] = bb.m_max[0];
	if (bb.m_max[1] > m_max[1]) m_max[1] = bb.m_max[1];
	if (bb.m_max[2] > m_max[2]) m_max[2] = bb.m_max[2];
}



bool Box3f::intersect( const Vec3f& pt ) const
{
	return (
		(pt[0] >= m_min[0]) &&
		(pt[1] >= m_min[1]) &&
		(pt[2] >= m_min[2]) &&
		(pt[0] <= m_max[0]) &&
		(pt[1] <= m_max[1]) &&
		(pt[2] <= m_max[2]));
}



bool Box3f::intersect( const Box3f& bb ) const
{
	return (
		(bb.m_max[0] >= m_min[0]) && (bb.m_min[0] <= m_max[0]) &&
		(bb.m_max[1] >= m_min[1]) && (bb.m_min[1] <= m_max[1]) &&
		(bb.m_max[2] >= m_min[2]) && (bb.m_min[2] <= m_max[2]));
}



/**
 * @brief View-volume culling
 * 
 * View-volume culling: axis-aligned bounding box against view volume,
 * given as Model/View/Projection matrix.
 * Inputs:
 *    MVP:       Matrix from object to NDC space
 *                 (model/view/projection)
 * Inputs/Outputs:
 *    cullBits:  Keeps track of which planes we need to test against.
 *               Has three bits, for X, Y and Z.  If cullBits is 0,
 *               then the bounding box is completely inside the view
 *               and no further cull tests need be done for things
 *               inside the bounding box.  Zero bits in cullBits mean
 *               the bounding box is completely between the
 *               left/right, top/bottom, or near/far clipping planes.
 * Outputs:
 *    bool:    TRUE if bbox is completely outside view volume
 *               defined by MVP.
 *
 *
 *
 * How:
 *
 * An axis-aligned bounding box is the set of all points P,
 * Pmin < P < Pmax.  We're interested in finding out whether or not
 * any of those points P are clipped after being transformed through
 * MVP (transformed into clip space).
 *
 * A transformed point P'[x,y,z,w] is inside the view if [x,y,z] are
 * all between -w and w.  Otherwise the point is outside the view.
 *
 * Instead of testing individual points, we want to treat the range of
 * points P.  We want to know if:  All points P are clipped (in which
 * case the cull test succeeds), all points P are NOT clipped (in
 * which case they are completely inside the view volume and no more
 * cull tests need be done for objects inside P), or some points are
 * clipped and some aren't.
 *
 * P transformed into clip space is a 4-dimensional solid, P'.  To
 * speed things up, this algorithm finds the 4-dimensional,
 * axis-aligned bounding box of that solid and figures out whether or
 * not that bounding box intersects any of the sides of the view
 * volume.  In the 4D space with axes x,y,z,w, the view volume planes
 * are the planes x=w, x=-w, y=w, y=-w, z=w, z=-w.
 *
 * This is all easier to think about if we think about each of the X,
 * Y, Z axes in clip space independently; worrying only about the X
 * axis for a moment:
 *
 * The idea is to find the minimum and maximum possible X,W
 * coordinates of P'.  If all of the points in the
 * [(Xmin,Xmax),(Wmin,Wmax)] range satisfy -|W| < X < |W| (|W| is
 * absolute value of W), then the original bounding box P is
 * completely inside the X-axis (left/right) clipping planes of the
 * view volume.  In (x,w) space, a point (x,w) is clipped depending on
 * which quadrant it is in:
 *
 *    x=-w       x=w
 *      \   Q0   /
 *       \  IN  /
 *        \    /
 *         \  /
 * Q1       \/  Q2
 * CLIPPED  /\  CLIPPED    
 *         /  \ 
 *        /    \ 
 *       /  Q3  \ 
 *      / CLIPPED\ 
 *
 * If the axis-aligned box [(Xmin,Xmax),(Wmin,Wmax)] lies entirely in
 * Q0, then it is entirely inside the X-axis clipping planes (IN
 * case).  If it is not in Q0 at all, then it is clipped (OUT).  If it
 * straddles Q0 and some other quadrant, the bounding box intersects
 * the clipping planes (STRADDLE).  The 4 corners of the bounding box
 * are tested first using bitwise tests on their quadrant numbers; if
 * they determine the case is STRADDLE then a more refined test is
 * done on the 8 points of the original bounding box.
 * The test isn't perfect-- a bounding box that straddles both Q1 and
 * Q2 may be incorrectly classified as STRADDLE; however, those cases
 * are rare and the cases that are incorrectly classified will likely
 * be culled when testing against the other clipping planes (these
 * cases are cases where the bounding box is near the eye).
 * 
 * Finding [(Xmin,Xmax),(Wmin,Wmax)] is easy.  Consider Xmin.  It is
 * the smallest X coordinate when all of the points in the range
 * Pmin,Pmax are transformed by MVP; written out:
 *     X = P[0]*M[0][0] + P[1]*M[1][0] + P[2]*M[2][0] + M[3][0]
 * X will be minimized when each of the terms is minimized.  If the
 * matrix entry for the term is positive, then the term is minimized
 * by choosing Pmin; if the matrix entry is negative, the term is
 * minimized by choosing Pmax.  Three 'if' test will let us calculate
 * the transformed Xmin.  Xmax can be calculated similarly.
 * 
 * Testing for IN/OUT/STRADDLE for the Y and Z coordinates is done
 * exactly the same way.
 */
bool Box3f::outside(const MatrixR& MVP, int32& cullBits) const
{
	float Wmax = minExtreme(m_max, m_min, MVP, 3);
	if (Wmax < 0) return true;

	float Wmin = minExtreme(m_min, m_max, MVP, 3);

	// Do each coordinate:
	for (int32 i = 0; i < 3; i++) 
	{
		if (cullBits & (1<<i))
		{  // STRADDLES:
			float Cmin = minExtreme(m_min, m_max, MVP, i);
			
			// The and_bits and or_bits are used to keep track of
			// which quadrants point lie in.  The cases are:
			//
			// All in Q0:  IN
			//    (or_bits == 0)  --> and_bits MUST also be 0
			// Some/all in Q1, some/all in Q3: CULLED
			// Some/all in Q2, some/none in Q3: CULLED
			//    (and_bits != 0, or_bits != 0)
			// Some in Q1, some in Q2, some/none in Q3: STRADDLE
			//    (and_bits == 0, or_bits !=0)
			//
			int32 and_bits;
			int32 or_bits;
			and_bits = or_bits = quadrant(Cmin, Wmin);

			int32 q0 = quadrant(Cmin, Wmax);
			and_bits &= q0;
			or_bits |= q0;
			// Hit the STRADDLE case as soon as and_bits == 0 and
			// or_bits != 0:
			if (!(and_bits == 0 && or_bits != 0)) 
			{
				float Cmax = minExtreme(m_max, m_min, MVP, i);
				
				q0 = quadrant(Cmax, Wmin);
				and_bits &= q0;
				or_bits |= q0;
				
				if (!(and_bits == 0 && or_bits != 0)) 
				{
					q0 = quadrant(Cmax, Wmax);
					and_bits &= q0;
					or_bits |= q0;
					
					// Either completely IN or completely OUT:
					if (or_bits == 0) 
					{ // IN
						cullBits &= ~(1<<i); // Clear bit
						continue; // Continue for loop
					}
					else if (and_bits != 0) 
					{
						return true;  // CULLED
					}
				}
			}

			// Before we give up and just claim it straddles, do a
			// more refined test-- check the 8 corners of the
			// bounding box:
			
			// Test to see if all 8 corner points of the bounding box
			// are in the same quadrant.  If so, the object is either
			// completely in or out of the view.  Otherwise, it straddles
			// at least one of the view boundaries.
			and_bits = or_bits = findQuadrant(m_min[0], m_min[1], m_min[2], i, MVP);
			if (and_bits == 0 && or_bits != 0) continue;
			
			q0 = findQuadrant(m_max[0], m_max[1], m_max[2], i, MVP);
			and_bits &= q0;
			or_bits |= q0;
			if (and_bits == 0 && or_bits != 0) continue;

			q0 = findQuadrant(m_max[0], m_min[1], m_min[2], i, MVP);
			and_bits &= q0;
			or_bits |= q0;
			if (and_bits == 0 && or_bits != 0) continue;

			q0 = findQuadrant(m_min[0], m_max[1], m_max[2], i, MVP);
			and_bits &= q0;
			or_bits |= q0;
			if (and_bits == 0 && or_bits != 0) continue;
			
			q0 = findQuadrant(m_min[0], m_max[1], m_min[2], i, MVP);
			and_bits &= q0;
			or_bits |= q0;
			if (and_bits == 0 && or_bits != 0) continue;

			q0 = findQuadrant(m_max[0], m_min[1], m_max[2], i, MVP);
			and_bits &= q0;
			or_bits |= q0;
			if (and_bits == 0 && or_bits != 0) continue;
			
			q0 = findQuadrant(m_max[0], m_max[1], m_min[2], i, MVP);
			and_bits &= q0;
			or_bits |= q0;
			if (and_bits == 0 && or_bits != 0) continue;

			q0 = findQuadrant(m_min[0], m_min[1], m_max[2], i, MVP);
			and_bits &= q0;
			or_bits |= q0;

			// Either completely IN or completely OUT:
			if (or_bits == 0) 
			{ // IN
				cullBits &= ~(1<<i); // Clear bit
				continue; // Continue for loop
			}
			else if (and_bits != 0) 
			{
				return true;  // CULLED
			}
		}
	}
	return false;// Not culled
}



Vec3f Box3f::getClosestPoint( const Vec3f& point )
{
	Vec3f result;
	
	// trivial cases first
	if ( isEmpty() ) 
	{
		return point;
	}
	else if (point == getCenter()) 
	{
		// middle of z side
		result[0] = (m_max[0] + m_min[0])/2.0f;
		result[1] = (m_max[1] + m_min[1])/2.0f;
		result[2] = m_max[2];
	}
	else
	{
		// Find the closest point on a unit box (from -1 to 1),
		// then scale up.

		// Find the vector from center to the point, then scale
		// to a unit box.
		Vec3f vec = point - getCenter();
		float sizeX, sizeY, sizeZ;
		getSize(sizeX, sizeY, sizeZ);
		float halfX = sizeX/2.0f;
		float halfY = sizeY/2.0f;
		float halfZ = sizeZ/2.0f;
		
		if (halfX > 0.0)	vec[0] /= halfX;
		if (halfY > 0.0)	vec[1] /= halfY;
		if (halfZ > 0.0)	vec[2] /= halfZ;

		// Side to snap side that has greatest magnitude in the vector.
		Vec3f mag;
		mag[0] = fabs(vec[0]);
		mag[1] = fabs(vec[1]);
		mag[2] = fabs(vec[2]);

		result = mag;

		// Check if beyond corners
		if (result[0] > 1.0)	result[0] = 1.0;
		if (result[1] > 1.0)	result[1] = 1.0;
		if (result[2] > 1.0)	result[2] = 1.0;
		
		// snap to appropriate side	    
		if ((mag[0] > mag[1]) && (mag[0] >  mag[2])) 
		{
			result[0] = 1.0;
		}
		else if ((mag[1] > mag[0]) && (mag[1] >  mag[2])) 
		{	    
			result[1] = 1.0;
		}
		else if ((mag[2] > mag[0]) && (mag[2] >  mag[1])) 
		{
			result[2] = 1.0;
		}
		else if ((mag[0] == mag[1]) && (mag[0] == mag[2])) 
		{
			// corner
			result = Vec3f(1,1,1);
		}
		else if (mag[0] == mag[1]) 
		{
			// edge parallel with z
			result[0] = 1.0;
			result[1] = 1.0;
		}
		else if (mag[0] == mag[2]) 
		{
			// edge parallel with y
			result[0] = 1.0;
			result[2] = 1.0;
		}
		else if (mag[1] == mag[2]) 
		{
			// edge parallel with x
			result[1] = 1.0;
			result[2] = 1.0;
		}
		else
		{
			assert( false );
			// Can't determine vector to point.
		}
		
		// Now make everything point the right way
		for (int32 i=0; i < 3; i++)
		{
			if (vec[i] < 0.0)	result[i] = -result[i];
		}
		
		// scale back up and move to center
		result[0] *= halfX;
		result[1] *= halfY;
		result[2] *= halfZ;

		result += getCenter();
	}

	return result;
}



bool Box3f::hasVolume( void ) const
{
	return (m_max[0] > m_min[0] && m_max[1] > m_min[1] && m_max[2] > m_min[2] );
}


float Box3f::getVolume( void ) const
{
	if ( isEmpty() )	return 0.0;

	return (m_max[0] - m_min[0]) * (m_max[1] - m_min[1]) * (m_max[2] - m_min[2]);
}



void Box3f::getSpan( const Vec3f& direction, float& dMin, float& dMax) const
{
	int32		i;
	Vec3f	points[8];
	Vec3f	dir = direction;

	dir.normalize();

	/* Set up the eight points at the corners of the extent */
	points[0][2] = points[2][2] = points[4][2] = points[6][2] = m_min[2];
	points[1][2] = points[3][2] = points[5][2] = points[7][2] = m_max[2];

	points[0][0] = points[1][0] = points[2][0] = points[3][0] = m_min[0];
	points[4][0] = points[5][0] = points[6][0] = points[7][0] = m_max[0];

	points[0][1] = points[1][1] = points[4][1] = points[5][1] = m_min[1];
	points[2][1] = points[3][1] = points[6][1] = points[7][1] = m_max[1];

	points[0][2] = points[2][2] = points[4][2] = points[6][2] = m_min[2];
	points[1][2] = points[3][2] = points[5][2] = points[7][2] = m_max[2];
	
	dMin = std::numeric_limits<float>::max();
	dMax = -std::numeric_limits<float>::max();

	for (i = 0; i < 8; i++) 
	{
		float proj = points[i].dot(dir);
		
		if (proj < dMin)	dMin = proj;
		
		if (proj > dMax)	dMax = proj;
	}
}



bool Box3f::operator ==( const Box3f& b2 ) const
{
	return ( (getMin() == b2.getMin()) && (getMax() == b2.getMax()) );
}



bool Box3f::operator !=( const Box3f& b2 ) const
{
	return !(*this == b2);
}



float Box3f::minExtreme( const Vec3f& min, const Vec3f& max, 
						 const MatrixR& MVP, int32 whichCoord )
{
	return 
		(MVP[0][whichCoord]>0.0f ? min[0] : max[0])*MVP[0][whichCoord] +
		(MVP[1][whichCoord]>0.0f ? min[1] : max[1])*MVP[1][whichCoord] +
		(MVP[2][whichCoord]>0.0f ? min[2] : max[2])*MVP[2][whichCoord] +
		MVP[3][whichCoord];
}



int32 Box3f::quadrant( const float x, const float y ) 
{
	return (x < -y) | ((x > y) << 1);
}



int32 Box3f::findQuadrant( float x, float y, float z,
						 int32 n, const MatrixR& MVP )
{
	float c = MVP[0][n]*x + MVP[1][n]*y + MVP[2][n]*z + MVP[3][n] ;
	float w = MVP[0][3]*x + MVP[1][3]*y + MVP[2][3]*z + MVP[3][3] ;
	return quadrant(c, w);
}






// XfBox3f.

XfBox3f::XfBox3f( void )
{
	xform.identity();
	xformInv.identity();
	makeEmpty();
}



XfBox3f::XfBox3f( float xmin, float ymin, float zmin,
				  float xmax, float ymax, float zmax )
{
	xform.identity();
	xformInv.identity();
	setBounds( 
		Vec3f(xmin, ymin, zmin),
		Vec3f(xmax, ymax, zmax) );
}



XfBox3f::XfBox3f( const Vec3f& min, const Vec3f& max )
{
	xform.identity();
	xformInv.identity();
	setBounds(min, max);
}



XfBox3f::XfBox3f( const Box3f & box )
{
	xform.identity();
	xformInv.identity();
	*static_cast<Box3f*>(this) = box;
}



XfBox3f::~XfBox3f( void )
{
}



Vec3f XfBox3f::getCenter( void ) const
{
	Vec3f	p;

	// transform the center before returning it
	xform.multVecMatrix( (getMin() + getMax()) * .5f, p);

	return p;
}



void XfBox3f::getOrigin( float& originX, float& originY, float& originZ) const
{
	Box3f::getOrigin(originX, originY, originZ);
}



void XfBox3f::getSize( float& sizeX, float& sizeY, float& sizeZ) const
{
	Box3f::getSize(sizeX, sizeY, sizeZ);
}



void XfBox3f::makeEmpty( void )
{
	Box3f::makeEmpty();
}



bool XfBox3f::isEmpty() const
{
	return Box3f::isEmpty();
}



void XfBox3f::setBounds( float xmin, float ymin, float zmin,
						 float xmax, float ymax, float zmax )
{
	Box3f::setBounds(xmin, ymin, zmin, xmax, ymax, zmax);
}



void XfBox3f::setBounds( const Vec3f& min, const Vec3f& max )
{
	Box3f::setBounds( min, max);
}



void XfBox3f::getBounds( float& xmin, float& ymin, float& zmin,
						 float& xmax, float& ymax, float& zmax ) const
{
	Box3f::getBounds(xmin, ymin, zmin, xmax, ymax, zmax);
}



void XfBox3f::getBounds( Vec3f& min, Vec3f& max ) const
{
	Box3f::getBounds( min, max);
}



void XfBox3f::transform( const MatrixR& m )
{
	MatrixR new_xf = xform * m;
	setTransform(new_xf);
}



void XfBox3f::setTransform( const MatrixR& m )
{
	const float PRECISION_LIMIT = (1.e-13f);

	xform = m; 

	// Check for degenerate matrix:
	float det = m.det4();
	if (det < PRECISION_LIMIT && det > -PRECISION_LIMIT)
	{
		// We'll mark inverse[0][0] with numeric_limits<float>::max() (max floating point
		// value) as special value to indicate degenerate transform.
		xformInv = MatrixR(
			std::numeric_limits<float>::max(),0,0,0,
			0,0,0,0,
			0,0,0,0,
			0,0,0,0);
	}
	else
	{
		xformInv = m.getInverse();
	}
}



const MatrixR& XfBox3f::getTransform( void ) const
{
	return xform;
}



const MatrixR& XfBox3f::getInverse( void ) const
{
	return xformInv;
}



void XfBox3f::extendBy( const Vec3f& pt )
{
	// If our transform is degenerate, project this box, which will
	// transform min/max and get a box with identity xforms:
	if (xformInv[0][0] == std::numeric_limits<float>::max())
	{
		*this = XfBox3f(this->project());
	}

	Vec3f p;
	xformInv.multVecMatrix(pt, p);
	Box3f::extendBy(p);
}



void XfBox3f::extendBy( const Box3f& bb )
{
	extendBy( XfBox3f(bb) );
}



void XfBox3f::extendBy( const XfBox3f& bb )
{
	if ( bb.isEmpty() )
	{
		// bb is empty, no change
		return;
	}
	else if ( isEmpty() )
	{
		// we're empty, use bb
		*this = bb;
	}
	else if (	xformInv[0][0] != std::numeric_limits<float>::max() &&
				bb.xformInv[0][0] != std::numeric_limits<float>::max())
	{
		// Neither box is empty and they are in different spaces. To
		// get the best results, we'll perform the merge of the two
		// boxes in each of the two spaces. Whichever merge ends up
		// being smaller is the one we'll use.
		// Note that we don't perform a project() as part of the test.
		// This is because projecting almost always adds a little extra
		// space. It also gives an unfair advantage to the
		// box more closely aligned with world space.  In the simplest
		// case this might be preferable. However, over many objects,
		// we are better off going with the minimum in local space,
		// and not worrying about projecting until the very end.

		XfBox3f	xfbox1, xfbox2;
		Box3f		box1, box2;

		// Convert bb into this's space to get box1
		xfbox1 = bb;
		// Rather than calling transform(), which calls inverse(),
		// we'll do it ourselves, since we already know the inverse matrix.
		// I.e., we could call: xfbox1.transform(xformInv);
		xfbox1.xform *= xformInv;
		xfbox1.xformInv.multRight(xform);
		box1 = xfbox1.project();

		// Convert this into bb's space to get box2
		xfbox2 = *this;
		// Same here for: xfbox2.transform(bb.xformInv);
		xfbox2.xform *= bb.xformInv;
		xfbox2.xformInv.multRight(bb.xform);
		box2 = xfbox2.project();

		// Extend this by box1 to get xfbox1
		xfbox1 = *this;
		xfbox1.Box3f::extendBy(box1);
		// Use Box3f method; box1 is already in xfbox1's space
		// (otherwise, we'll get an infinite loop!)

		// Extend bb by box2 to get xfbox2
		xfbox2 = bb;
		xfbox2.Box3f::extendBy(box2);
		// Use Box3f method; box2 is already in xfbox2's space
		// (otherwise, we'll get an infinite loop!)

		float vol1 = xfbox1.getVolume();
		float vol2 = xfbox2.getVolume();

		// Take the smaller result and extend appropriately
		if (vol1 <= vol2) 
		{
			Box3f::extendBy(box1);
		}
		else 
		{
			*this = bb;
			Box3f::extendBy(box2);
		}
		
	}
	else if (xformInv[0][0] == std::numeric_limits<float>::max()) 
	{
		if (bb.xformInv[0][0] == std::numeric_limits<float>::max()) 
		{
			// Both boxes are degenerate; project them both and
			// combine them:
			Box3f box = this->project();
			box.extendBy(bb.project());
			*this = XfBox3f(box);
		}
		else
		{
			// this is degenerate; transform our min/max into bb's
			// space, and combine there:
			Box3f box(getMin(), getMax());
			box.transform(xform*bb.xformInv);
			*this = bb;
			Box3f::extendBy(box);
		}
	}
	else
	{
		// bb is degenerate; transform it into our space and combine:
		Box3f box(bb.getMin(), bb.getMax());
		box.transform(bb.xform*xformInv);
		Box3f::extendBy(box);
	}
}



bool XfBox3f::intersect( const Vec3f& pt ) const
{
	if (xformInv[0][0] != std::numeric_limits<float>::max())
	{
		Vec3f p;
		xformInv.multVecMatrix(pt, p);
		return Box3f::intersect(p);
	}

	Box3f box = this->project();	// Degenerate; project and test:

	return box.intersect(pt);
}



bool XfBox3f::intersect( const Box3f& bb ) const
{
	return project().intersect(bb);
}



bool XfBox3f::hasVolume() const
{
	return Box3f::hasVolume();
}



float XfBox3f::getVolume( void ) const
{
	if ( isEmpty() )	return 0.0;

	// The volume of a transformed box is just its untransformed
	// volume times the determinant of the upper-left 3x3 of
	// the xform matrix. Quoth Paul Strauss: "Pretty cool, indeed."
	float objVol = Box3f::getVolume();
	float factor = xform.det3();
	return factor * objVol;
}



void XfBox3f::getSpan(	const Vec3f &direction,
						float& dMin, float& dMax) const
{
	project().getSpan(direction, dMin, dMax);
}



Box3f XfBox3f::project( void ) const
{
	Box3f	box( getMin(), getMax() );
	box.transform( xform );

	return box;
}



bool XfBox3f::operator ==( const XfBox3f& b2 ) const
{
	Box3f b1Proj = project();
	Box3f b2Proj = b2.project();

	return (b1Proj == b2Proj);
}



bool XfBox3f::operator !=( const XfBox3f& b2 ) const
{
	return !(*this == b2);
}



} // namespace vgm
