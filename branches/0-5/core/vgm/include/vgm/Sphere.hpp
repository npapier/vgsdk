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

#ifndef _VGM_SPHERE_HPP
#define _VGM_SPHERE_HPP

#include "vgm/vgm.hpp"
#include "vgm/Vector.hpp"



namespace vgm
{

struct Box3f;
struct Line;

/**
 * @brief Represents a sphere in 3D space.
 *
 * @ingroup Geometry
 *
 * @todo valid/invalid
 */
struct VGM_API Sphere
{
	/**
	 * @name Constructor
	 */
	//@{

	/**
	 * @brief Default constructor
	 */
	Sphere();

	/**
	 * @brief Construct a sphere given center and radius
	 */
	Sphere( const Vec3f& center, const float radius );

	/**
	 * @brief Construct a sphere containing the given box
	 */
	Sphere( const Box3f& box );

	/**
	 * @brief Return an invalid sphere
	 */
	static const Sphere getInvalid();
	//@}


	/**
	 * @name Accessors
	 */
	//@{

	/**
	 * @brief Change the center and radius
	 */
	void setValue( const Vec3f& center, const float radius );

	/**
	 * @brief Set the center
	 */
	void setCenter( const Vec3f& center );

	/**
	 * @brief Set the radius
	 */
	void setRadius( const float radius );

	/**
	 * @brief Invalidate the sphere.
	 *
	 * @post isInvalid() == true
	 */
	void setInvalid();


	/**
	 * @brief Return the center
	 */
	const Vec3f& getCenter() const;

	/**
	 * @brief Return the radius
	 */
	const float getRadius() const;

	/**
	 * @brief Test if the sphere is invalid
	 */
	const bool isInvalid( void ) const;

	/**
	 * @brief Test if the sphere is valid
	 */
	const bool isValid( void ) const;
	//@}


	/**
	 * @name High level accessors
	 */
	//@{

	/**
	 * @brief Circumscribe the sphere to contain the given box
	 */
	void circumscribe( const Box3f& box );
	//@}


	/**
	 * @name Intersection methods
	 */
	//@{

	/**
	 * @brief Test if a point is inside the sphere
	 */
	const bool isIn( const vgm::Vec3f& P ) const;

	/**
	 * @brief Intersect line and sphere
	 *
	 * @param line			the line to test
	 *
	 * @return the returned intersection point if there is an intersection, otherwise an invalid point (i.e. returnedValue.isInvalid() == true).
	 */
	const vgm::Vec3f intersect( const Line& line ) const;

	/**
	 * @brief Intersect line and sphere
	 *
	 * @param line		the line to test
	 * @param enter		enter point
	 * @param exit		exit point
	 *
	 * @return true if there is an intersection, otherwise false
	 */
	const bool intersect( const Line& line, Vec3f& enter, Vec3f& exit ) const;
	//@}


private:
	Vec3f	m_center;
	float	m_radius;
};


} // namespace vgm

#endif // #ifndef _VGM_SPHERE_HPP
