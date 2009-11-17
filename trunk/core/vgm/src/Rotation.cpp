// VGSDK - Copyright (C) 2004-2006, 2009, Nicolas Papier.
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
 * Author(s)		:	Nick Thompson, David Mott, Howard Look.
 */

#include "vgm/Rotation.hpp"

#include "vgm/Matrix.hpp"



namespace vgm
{



// Rotation
Rotation::Rotation( void )
{
}



Rotation::Rotation( const float v[4] )
{
	setValue(v);
}



Rotation::Rotation( float q0, float q1, float q2, float q3 )
{
	setValue(q0, q1, q2, q3);
}



Rotation::Rotation( const MatrixR& m )
{
	setValue(m);
}



Rotation::Rotation( const Vec3f& axis, float radians )
{
	setValue(axis, radians);
}



Rotation::Rotation( const Vec3f& rotateFrom, const Vec3f& rotateTo )
{
	setValue(rotateFrom, rotateTo);
}



const float* Rotation::getValue( void ) const
{
	return (quat);
}



void Rotation::getValue(
		float& q0, float& q1,
		float& q2, float& q3 ) const
{
	q0 = quat[0];
	q1 = quat[1];
	q2 = quat[2];
	q3 = quat[3];
}



void Rotation::getValue( Vec3f& axis, float& radians ) const
{
	float	len;
	Vec3f	q;

	q[0] = quat[0];
	q[1] = quat[1];
	q[2] = quat[2];

	len = q.getLength();

	if ( len > 0.00001f) 
	{
		axis	= q * (1.0f / len);
		radians	= 2.0f * acosf(quat[3]);
	}
	else
	{
		axis.setValue(0.0f, 0.0f, 1.0f);
		radians = 0.0f;
	}
}



void Rotation::getValue( MatrixR& matrix ) const
{
	RawMatrix m;

	m[0][0] = 1.f - 2.0f * (quat[1] * quat[1] + quat[2] * quat[2]);
	m[0][1] =       2.0f * (quat[0] * quat[1] + quat[2] * quat[3]);
	m[0][2] =       2.0f * (quat[2] * quat[0] - quat[1] * quat[3]);
	m[0][3] = 0.0f;

	m[1][0] =       2.0f * (quat[0] * quat[1] - quat[2] * quat[3]);
	m[1][1] = 1.f - 2.0f * (quat[2] * quat[2] + quat[0] * quat[0]);
	m[1][2] =       2.0f * (quat[1] * quat[2] + quat[0] * quat[3]);
	m[1][3] = 0.0f;

	m[2][0] =       2.0f * (quat[2] * quat[0] + quat[1] * quat[3]);
	m[2][1] =       2.0f * (quat[1] * quat[2] - quat[0] * quat[3]);
	m[2][2] = 1.f - 2.0f * (quat[1] * quat[1] + quat[0] * quat[0]);
	m[2][3] = 0.0f;

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[3][3] = 1.0f;

	matrix = m;
}

float Rotation::getAngle() const
{
	return 2.0f * acosf(quat[3]);
}

Rotation Rotation::getIdentity( void )
{
	return Rotation(0.0f, 0.0f, 0.0f, 1.0f);
}



Rotation& Rotation::setValue( const float q[4] )
{
	quat[0] = q[0];
	quat[1] = q[1];
	quat[2] = q[2];
	quat[3] = q[3];
	normalize();

	return ( *this );
}



Rotation& Rotation::setValue( float q0, float q1, float q2, float q3 )
{
	quat[0] = q0;
	quat[1] = q1;
	quat[2] = q2;
	quat[3] = q3;
	normalize();

	return ( *this );
}



////////////////////////////////////////////////////////////////////////
//
// Description:
//    Sets value of rotation from a rotation matrix.
//    This algorithm is from "Quaternions and 4x4 Matrices", Ken
//    Shoemake, Graphics Gems II.
//
//  Here's the logic:
//    We're trying to find a quaterion 'q' that represents the same
//    rotation as the given matrix 'm'.
//    We know how to convert a quaterion to a rotation matrix; the
//    matrix is given by (where x,y,z,w are the quaterion elements):
//
//    x^2-y^2-z^2+w^2  2xy+2zw          2wx - 2yw        0
//    2xy-2zw          y^2-z^2-x^2+w^2  2yz + 2xw        0
//    2zx+2zw          2yz-2xw          z^2-x^2-y^2+w^2  0
//    0                0                0                x^2+y^2+z^2+w^2
//             (note that x^2+y^2+z^2+w^2==1 for a normalized quaterion)
//
//    We know m, we want to find x,y,z,w.  If you don't mind doing
//    square roots, then it is easy; for example:
//    m[0][0]+m[1][1]+m[2][2]+m[3][3] = 4w^2
//       (write it all out, and see all the terms cancel)
//    Or, w = sqrt(m[0][0]+m[1][1]+m[2][2]+m[3][3])/2
//    Similarly,
//        x = sqrt(m[0][0]-m[1][1]-m[2][2]+m[3][3])/2
//        y = sqrt(m[1][1]-m[2][2]-m[0][0]+m[3][3])/2
//        z = sqrt(m[2][2]-m[0][0]-m[1][1]+m[3][3])/2
//    However, you only really need to do one sqrt and find one of
//    x,y,z,w, because using the other elements of the matrix you
//    find, for example, that:
//    m[0][1]+m[1][0] = 2xy+2zw+2xy-2zw = 4xy
//    So if you know either x or y, you can find the other.
//
//    That is assuming that the first thing you find isn't zero, of
//    course.  In fact, you want the first element you find to be as
//    large as possible, to get more accuracy in the division.  You
//    can rewrite the diagonal elements as:
//    (w^2 - x^2 - y^2 - z^2) + 2x^2    = m[0][0]
//    (w^2 - x^2 - y^2 - z^2) + 2y^2    = m[1][1]
//    (w^2 - x^2 - y^2 - z^2) + 2z^2    = m[2][2]
//    ... and write the sum of the diagonals as:
//    (w^2 - x^2 - y^2 - z^2) + 2w^2    = m[0][0]+m[1][1]+m[2][2]+m[3][3]
//
//    Why do this?  Because now it is easy to see that if x is greater
//    than y, z, or w, then m[0][0] will be greater than the other
//    diagonals or the sum of the diagonals.
//
//    So, the overall strategy is:  Figure out which if x,y,z, or w
//    will be greatest by looking at the diagonals.  Compute that
//    value using the sqrt() formula.  Then compute the other values
//    using the other set of formulas.
//
Rotation& Rotation::setValue( const MatrixR& m )
{
	int i, j, k;

	// First, find largest diagonal in matrix:
	if (m[0][0] > m[1][1])
	{
		if (m[0][0] > m[2][2])
		{
			i = 0;
		}
		else
		{
			i = 2;
		}
	}
	else
	{
		if (m[1][1] > m[2][2]) 
		{
			i = 1;
		}
		else
		{
			i = 2;
		}
	}

	if (m[0][0]+m[1][1]+m[2][2] > m[i][i]) 
	{
		// Compute w first:
		quat[3] = static_cast< float >(sqrt(m[0][0]+m[1][1]+m[2][2]+m[3][3])/2.0f);

		// And compute other values:
		quat[0] = (m[1][2]-m[2][1])/(4*quat[3]);
		quat[1] = (m[2][0]-m[0][2])/(4*quat[3]);
		quat[2] = (m[0][1]-m[1][0])/(4*quat[3]);
	}
	else
	{
		// Compute x, y, or z first:
		j = (i+1)%3; k = (i+2)%3;

		// Compute first value:
		quat[i] = static_cast< float >(sqrt(m[i][i]-m[j][j]-m[k][k]+m[3][3])/2.0f);

		// And the others:
		quat[j] = (m[i][j]+m[j][i])/(4*quat[i]);
		quat[k] = (m[i][k]+m[k][i])/(4*quat[i]);

		quat[3] = (m[j][k]-m[k][j])/(4*quat[i]);
	}

#ifdef _DEBUG
	// Check to be sure output matches input:
	MatrixR check;
	getValue(check);
	bool ok = true;
	for (i = 0; i < 4 && ok; i++) 
	{
		for (j = 0; j < 4 && ok; j++) 
		{
			if (fabsf(m[i][j]-check[i][j]) > 1.0e-5)		ok = false;
		}
	}

	if (!ok) 
	{
		// FIXME
		assert( false );
		/*SoDebugError::post("Rotation::setValue(const MatrixR &)",
			   "Rotation does not agree with matrix; "
			   "this routine only works with rotation "
			   "matrices!");*/
	}
#endif

	return (*this);
}



Rotation& Rotation::setValue( const Vec3f& axis, float radians )
{
	Vec3f q( axis );
	q.normalize();

	q *= sinf(radians / 2.0f);

	quat[0] = q[0];
	quat[1] = q[1];
	quat[2] = q[2];

	quat[3] = cosf(radians / 2.0f);

	return(*this);
}



Rotation& Rotation::setValue( const Vec3f& rotateFrom, const Vec3f& rotateTo )
{
	Vec3f	from	= rotateFrom;
	Vec3f	to		= rotateTo;
	Vec3f	axis;
	float	cost;

	from.normalize();
	to.normalize();
	cost = from.dot(to);

	// check for degeneracies
	if (cost > 0.99999) 
	{
		// vectors are parallel
		quat[0] = quat[1] = quat[2] = 0.0f;
		quat[3] = 1.0;
		return *this;
	}
	else if (cost < -0.99999f)
	{
		// vectors are opposite
		// find an axis to rotate around, which should be
		// perpendicular to the original axis
		// Try cross product with (1,0,0) first, if that's one of our
		// original vectors then try  (0,1,0).
		Vec3f tmp = from.cross(Vec3f(1.0f, 0.0f, 0.0f));
		if (tmp.getLength() < 0.00001f)		tmp = from.cross(Vec3f(0.0f, 1.0f, 0.0f));

		tmp.normalize();
		setValue(tmp[0], tmp[1], tmp[2], 0.0f);
		return *this;
	}

	axis = rotateFrom.cross(rotateTo);
	axis.normalize();

	// use half-angle formulae
	// sin^2 t = ( 1 - cos (2t) ) / 2
	axis *= static_cast< float >(sqrt(0.5f * (1.0f - cost)));

	// scale the axis by the sine of half the rotation angle to get
	// the normalized quaternion
	quat[0] = axis[0];
	quat[1] = axis[1];
	quat[2] = axis[2];

	// cos^2 t = ( 1 + cos (2t) ) / 2
	// w part is cosine of half the rotation angle
	quat[3] = static_cast< float >(sqrt(0.5f * (1.0f + cost)));

	return (*this);
}



void Rotation::setValue(	const vgm::Vec2f center, const vgm::Vec2f p1, const vgm::Vec2f p2, const vgm::Vec2f viewport,
									const float radius )
{
	//
	vgm::Vec2f current( p2 - center );
	current[0] /= viewport[0];
	current[1] /= viewport[1];	
	
	vgm::Vec2f previous( p1 - center );
	previous[0] /= viewport[0];
	previous[1] /= viewport[1];

	//
	vgm::Vec3f		vfrom;
	vgm::Vec3f		vto;

	vfrom.setValue(	previous[0], previous[1], 0.f	);
	vto.setValue(		current[0], current[1], 0.f	);
	
	//
	vfrom.projectOnSphere(	radius );
	vto.projectOnSphere	(	radius );
	
	setValue( vfrom, vto );
}



Rotation& Rotation::operator *=( const Rotation& q )
{
	float p0, p1, p2, p3;

	p0 = (q.quat[3] * quat[0] + q.quat[0] * quat[3] +
		 q.quat[1] * quat[2] - q.quat[2] * quat[1]);

	p1 = (q.quat[3] * quat[1] + q.quat[1] * quat[3] +
		 q.quat[2] * quat[0] - q.quat[0] * quat[2]);

	p2 = (q.quat[3] * quat[2] + q.quat[2] * quat[3] +
		q.quat[0] * quat[1] - q.quat[1] * quat[0]);

	p3 = (q.quat[3] * quat[3] - q.quat[0] * quat[0] -
		q.quat[1] * quat[1] - q.quat[2] * quat[2]);

	quat[0] = p0;
	quat[1] = p1;
	quat[2] = p2;
	quat[3] = p3;

	normalize();

	return ( *this );
}



Rotation Rotation::operator *( const Rotation& q2 ) const
{
	const Rotation& q1 = *this;
	
	Rotation q(
		q2.quat[3] * q1.quat[0] + q2.quat[0] * q1.quat[3] +
		q2.quat[1] * q1.quat[2] - q2.quat[2] * q1.quat[1],

		q2.quat[3] * q1.quat[1] + q2.quat[1] * q1.quat[3] +
		q2.quat[2] * q1.quat[0] - q2.quat[0] * q1.quat[2],

		q2.quat[3] * q1.quat[2] + q2.quat[2] * q1.quat[3] +
		q2.quat[0] * q1.quat[1] - q2.quat[1] * q1.quat[0],

		q2.quat[3] * q1.quat[3] - q2.quat[0] * q1.quat[0] -
		q2.quat[1] * q1.quat[1] - q2.quat[2] * q1.quat[2]);

	q.normalize();

	return (q);
}



Rotation& Rotation::inverse( void )
{
	float invNorm = 1.0f / norm();

	quat[0] = -quat[0] * invNorm;
	quat[1] = -quat[1] * invNorm;
	quat[2] = -quat[2] * invNorm;
	quat[3] =  quat[3] * invNorm;

	return *this;
}



Rotation Rotation::getInverse( void ) const
{
	Rotation q = *this;
	q.inverse();

	return q;
}



void Rotation::scaleAngle( float scaleFactor )
{
	Vec3f myAxis;
	float   myAngle;

	// Get the Axis and angle.
	getValue( myAxis, myAngle );

	setValue( myAxis, (myAngle * scaleFactor) );
}



Rotation Rotation::getScaleAngle( float scaleFactor )
{
	Rotation r = *this;
	r.scaleAngle( scaleFactor );
	
	return ( r );
}



Rotation Rotation::slerp( const Rotation& rot0, const Rotation& rot1, float t )
{
	const float *r1q = rot1.getValue();

	Rotation	rot;
	float	rot1q[4];
	double	omega, cosom, sinom;
	double	scalerot0, scalerot1;
	int		i;

	// Calculate the cosine
	cosom = rot0.quat[0]*rot1.quat[0] + rot0.quat[1]*rot1.quat[1]
			+ rot0.quat[2]*rot1.quat[2] + rot0.quat[3]*rot1.quat[3];

	// adjust signs if necessary
	if ( cosom < 0.0 )
	{
		cosom = -cosom;
		for ( int j = 0; j < 4; j++ )
		{
			rot1q[j] = -r1q[j];
		}
	}
	else
	{
		for ( int j = 0; j < 4; j++ )
		{
			rot1q[j] = r1q[j];
		}
	}

	// calculate interpolating coeffs
	if ( (1.0 - cosom) > 0.00001 )
	{
		// standard case
		omega = acos(cosom);
		sinom = sin(omega);
		scalerot0 = sin((1.0 - t) * omega) / sinom;
		scalerot1 = sin(t * omega) / sinom;
	}
	else
	{
		// rot0 and rot1 very close - just do linear interp.
		scalerot0 = 1.0 - t;
		scalerot1 = t;
	}

	// build the new quarternion
	for (i = 0; i <4; i++)
	{
		rot.quat[i] = static_cast< float >( scalerot0 * rot0.quat[i] + scalerot1 * rot1q[i] );
	}

	return rot;
}



void Rotation::multVec( const Vec3f& src, Vec3f& dst ) const
{
	MatrixR myMat;
	getValue( myMat );

	myMat.multVecMatrix( src, dst );
}



const Vec3f Rotation::multVec( const Vec3f& src ) const
{
	MatrixR myMat;
	getValue( myMat );

	vgm::Vec3f dst;
	myMat.multVecMatrix( src, dst );

	return dst;
}



bool Rotation::operator ==( const Rotation& q2) const
{
	return (
		quat[0] == q2.quat[0] &&
		quat[1] == q2.quat[1] &&
		quat[2] == q2.quat[2] &&
		quat[3] == q2.quat[3] );
}



bool Rotation::operator !=( const Rotation& q2) const
{
	return !(*this == q2);
}



bool Rotation::equals( const Rotation& r, float tolerance ) const
{
	return ( Vec4f(quat).equals(Vec4f(r.quat), tolerance ) );
}



float Rotation::norm( void ) const
{
	return (
		quat[0] * quat[0] +
		quat[1] * quat[1] +
		quat[2] * quat[2] +
		quat[3] * quat[3] );
}



void Rotation::normalize( void )
{
	float	dist = 1.0f / static_cast< float >( sqrt(norm()) );

	quat[0] *= dist;
	quat[1] *= dist;
	quat[2] *= dist;
	quat[3] *= dist;
}


vgm::Vec3f operator *( const vgm::Vec3f& vec, const vgm::Rotation& rot)
{
	return rot.multVec(vec);
}

vgm::Vec3f& operator *=( vgm::Vec3f& vec, const vgm::Rotation& rot)
{
	vec = rot.multVec(vec);
	return vec;
}


} // namespace vgm
