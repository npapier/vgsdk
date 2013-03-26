// VGSDK - Copyright (C) 2013, Nicolas Papier.
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

#include "vgm/Sphere.hpp"

#include "vgm/Box.hpp"
#include "vgm/Line.hpp"



namespace vgm
{


Sphere::Sphere()
{}


Sphere::Sphere( const Vec3f& center, const float radius )
:	m_center( center ),
	m_radius( radius )
{}


Sphere::Sphere( const Box3f& box )
{
	circumscribe( box );
}


const Sphere Sphere::getInvalid()
{
	Sphere retVal;
	retVal.setInvalid();
	return retVal;
}


void Sphere::setValue( const Vec3f& center, const float radius )
{
	m_center = center;
	m_radius = radius;
}


void Sphere::setCenter( const Vec3f& center )
{
	m_center = center;
}


void Sphere::setRadius( const float radius )
{
	m_radius = radius;
}


void Sphere::setInvalid()
{
	m_radius = std::numeric_limits< float >::max();
}


const Vec3f& Sphere::getCenter() const
{
	return m_center;
}


const float Sphere::getRadius() const
{
	return m_radius;
}


const bool Sphere::isInvalid( void ) const
{
	return m_radius == std::numeric_limits<float>::max();
}


const bool Sphere::isValid( void ) const
{
	return !isInvalid();
}


void Sphere::circumscribe( const Box3f& box )
{
	m_center = 0.5f * (box.getMin() + box.getMax());
	m_radius = (box.getMax() - m_center).getLength();
}


const bool Sphere::isIn( const vgm::Vec3f& P ) const
{
	const float distanceBetweenCenterAndP = (P - m_center).getLength();
	return distanceBetweenCenterAndP <= getRadius();
}


// line-sphere intersection algorithm lifted from Eric Haines chapter in 
// Glassner's "Introduction to Ray Tracing", pp. 35-7
const vgm::Vec3f Sphere::intersect( const Line& line ) const
{
	float	B,C;	// At^2 + Bt + C = 0, but A is 1 since we normalize Rd
	float	discr;	// discriminant (B^2 - 4AC)
	Vec3f	v;
	float	t,sqroot;
	vgm::Vec3f intersection;
	bool doesIntersect = true;

	// setup B,C
	v = line.getPosition() - m_center;
	B = 2.f * (line.getDirection().dot(v));
	C = v.dot(v) - (m_radius * m_radius);

	// compute discriminant
	// if negative, there is no intersection
	discr = B*B - 4.f*C;
	if (discr < 0.f) {
		// line and sphere do not intersect
		doesIntersect = false;
	}
	else {
		// compute t0: (-B - sqrt(B^2 - 4AC)) / 2A  (A = 1)
		sqroot = sqrtf(discr);
		t = (-B - sqroot) * 0.5f;
		if (t < 0.f) {
			// no intersection, try t1: (-B + sqrt(B^2 - 4AC)) / 2A  (A = 1)
			t = (-B + sqroot) * 0.5f;
		}

		if (t < 0.f) {
			// line and sphere do not intersect
			doesIntersect = false;
		}
		else {
			// intersection! point is (point + (dir * t))
			intersection = line.getPosition() + (line.getDirection() * t);
		}
	}

	return doesIntersect ? intersection : vgm::Vec3f::getInvalid();
}


// line-sphere intersection algorithm lifted from Eric Haines chapter in 
// Glassner's "Introduction to Ray Tracing", pp. 35-7
const bool Sphere::intersect( const Line& line, Vec3f& enter, Vec3f& exit ) const
{
	float	B,C;	// At^2 + Bt + C = 0, but A is 1 since we normalize Rd
	float	discr;	// discriminant (B^2 - 4AC)
	Vec3f	v;
	float	sqroot;
	bool doesIntersect = true;

	// setup B,C
	v = line.getPosition() - m_center;
	B = 2.f * (line.getDirection().dot(v));
	C = v.dot(v) - (m_radius * m_radius);

	// compute discriminant
	// if negative, there is no intersection
	discr = B*B - 4.f*C;

	if (discr < 0.f) {
		// line and sphere do not intersect
		doesIntersect = false;
	}
	else {
		sqroot = sqrtf(discr);

		float t0 = (-B - sqroot) * 0.5f;
		enter = line.getPosition() + (line.getDirection() * t0);

		float t1 = (-B + sqroot) * 0.5f;
		exit = line.getPosition() + (line.getDirection() * t1);
	}

	return doesIntersect;
}


} // namespace vgm
