// VGSDK - Copyright (C) 2004-2006, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

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

#ifndef _VGM_ROTATION_HPP
#define _VGM_ROTATION_HPP

#include "vgm/Vector.hpp"



namespace vgm
{



struct MatrixR;

/**
 * @brief Class for representing a rotation.
 *
 * Object that stores a rotation. There are several ways to specify a
 * rotation: quaternion (4 floats), 4x4 rotation matrix, or axis and angle.
 * All angles are in radians and all rotations are right-handed.
 *
 * It is stored internally as a quaternion, which has 4 floating-point components.
 *
 * @ingroup LinearAlgebra
 * 
 * @todo add methods to convert deg2rad and rad2deg @sa vgd::Utilities
 * @todo complete affectation methods ?, mult* methods ?
 */
struct VGM_API Rotation
{
	/**
	 * @name Constructors and destructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 *
	 * @warning Rotation is not initialized.
	 */
	Rotation( void );

	/**
	 * @brief Constructor given a quaternion as an array of 4 components.
	 */
	Rotation( const float v[4] );

	/**
	 * @brief Constructor given a quaternion as an array of 4 components.
	 */
	template< typename InType >
	Rotation( const InType * q );

	/**
	 * @brief Constructor given 4 individual components of a quaternion.
	 *
	 * @warning This differs from the four numbers in an axis/radian definition.
	 */
	Rotation( float q0, float q1, float q2, float q3 );

	/**
	 * @brief Constructor given a rotation matrix.
	 *
	 * @warning Matrix constructor requires a valid rotation matrix.
	 */
	Rotation( const MatrixR& m );

	/**
	 * @brief Constructor given axis/radians creates a rotation of 
	 * angle radians about the given axis.constructor.
	 */
	Rotation( const Vec3f& axis, float radians );

	/**
	 * @brief Constructor for rotation that rotates one direction vector to another.
	 *
	 * The rotateFrom and rotateTo vectors are normalized by the constructor before calculating the rotation.
	 */
	Rotation( const Vec3f& rotateFrom, const Vec3f& rotateTo );
	//@}


	/**
	 * @name Rotation accessors.
	 *
	 * The following methods return rotation values and other informations.
	 */
	//@{

	/**
	 * @brief Returns pointer to array of 4 components defining quaternion.
	 */
	const float	*	getValue( void ) const;

	/**
	 * @brief Returns 4 individual components of rotation quaternion.
	 */
	void			getValue(
		float& q0, float& q1,
		float& q2, float& q3 ) const;

	/**
	 * @brief Returns corresponding 3D rotation axis vector and angle in radians.
	 */
	void			getValue( Vec3f& axis, float& radians ) const;

	/**
	 * @brief Returns corresponding 4x4 rotation matrix.
	 */
	void			getValue( MatrixR& matrix ) const;

	/**
	 * @brief Returns the angle of the corresponding rotation.
	 */
	float			getAngle() const;

	/**
	 * @brief Null rotation.
	 */
	static Rotation	getIdentity( void );

	/**
	 * @brief	Creates an invalid rotation.
	 */
	static const Rotation getInvalid();

	/**
	 * @brief	Tells if the rotation is invalid.
	 */
	const bool isInvalid() const;

	/**
	 * @brief	Set the rotation as invalid.
	 */
	void setInvalid();

	/**
	 * @brief Sets value of rotation from array of 4 components of a quaternion.
	 */
	Rotation&		setValue( const float q[4] );

	/**
	 * @brief Sets value of rotation from array of 4 components of a quaternion.
	 */
	template< typename InType >
	Rotation& setValue( const InType * q );

	/**
	 * @brief Sets value of rotation from 4 individual components of a quaternion.
	 */
	Rotation&		setValue( float q0, float q1, float q2, float q3 );

	/**
	 * @brief Sets value of vector from 3D rotation axis vector and angle in radians.
	 */
	Rotation&		setValue( const Vec3f& axis, float radians );

	/**
	 * @brief Sets value of rotation from a rotation matrix.
	 *
	 * I don't know what will happen if you call this with something
	 * that isn't a rotation.
	 */
	Rotation&		setValue( const MatrixR& m );
	
	/**
	 * @brief Sets rotation to rotate one direction vector to another.
	 *
	 * The rotateFrom and rotateTo vectors are normalized by the constructor before calculating the rotation.
	 */
	Rotation&		setValue( const Vec3f& rotateFrom, const Vec3f& rotateTo );

	/**
	 * @brief Sets rotation to simulate a track-ball.
	 * 
	 * Project the points onto the virtual trackball, then figure out the axis of rotation, which is the cross product of
	 * P1 P2 and O P1 (O is the center of the ball).
	 * 
	 * @param center		center of the ball
	 * @param p1			point p1
	 * @param p2			point p2
	 * @param viewport	viewport size to normalize p1, p2 and center.
	 * @param radius		radius of virtual ball.
	 */
	void	setValue(	const vgm::Vec2f center, const vgm::Vec2f p1, const vgm::Vec2f p2, const vgm::Vec2f viewport,
							const float radius = 1.0f );
	//@}


	/**
	 * @name Rotation arithmetic.
	 */
	//@{

	/**
	 * @brief Multiplies by another rotation; results in product of rotations.
	 */
	Rotation&			operator *=( const Rotation& q );

	/**
	 * @brief Multiplication of two rotations; results in product of rotations.
	 */
	Rotation			operator *( const Rotation& q2 ) const;

	/**
	 * @brief Changes a rotation to be its inverse.
	 */
	Rotation&			inverse( void );

	/**
	 * @brief Returns the inverse of a rotation.
	 */
	Rotation			getInverse( void ) const;

	/**
	 * @brief Keep the axis the same. Multiply the angle of rotation by 
	 * the amount 'scaleFactor'
	 */
	void				scaleAngle( float scaleFactor );

	/**
	 * @brief Returns a rotation with a scaled angle
	 * @sa Rotation::scaleAngle(float)
	 */
	Rotation			getScaleAngle( float scaleFactor );

	/**
	 * @brief Spherical linear interpolation: as t goes from 0 to 1, returned
	 * value goes from rot0 to rot1.
	 */
	static Rotation	slerp( const Rotation& rot0, const Rotation& rot1, float t );
	//@}


	/**
	 * @name Methods for applying rotation to objects.
	 */
	//@{

	/**
	 * @brief Puts the given vector through this rotation.
	 *
	 * Multiplies the given vector by the matrix of this rotation.
	 */
	void multVec( const Vec3f& src, Vec3f& dst ) const;

	/**
	 * @brief Puts the given vector through this rotation.
	 *
	 * Multiplies the given vector by the matrix of this rotation.
	 */
	const Vec3f multVec( const Vec3f& src ) const;
	//@}


	/**
	 * @name Comparison methods.
	 */
	//@{

	/**
	 * @brief Equality comparison operator.
	 */
	bool				operator ==( const Rotation& q2 ) const;

	/**
	 * @brief Difference comparison.
	 */
	bool				operator !=( const Rotation& q2 ) const;

	/**
	 * @brief Equality comparison within given tolerance.
	 *
	 * Tolerance is the square of the length of the maximum distance between the two quaternion vectors.
	 */
	bool				equals( const Rotation& r, float tolerance ) const;
	//@}

private:

	/**
	 * @brief Storage for quaternion components.
	 */
	float	quat[4];

	/**
	 * @brief Returns the norm (square of the 4D length) of a rotation's quaterion.
	 */
	float	norm( void ) const;

	/**
	 * @brief Normalizes a rotation quaternion to unit 4D length.
	 */
	void	normalize( void );
};



template< typename InType >
Rotation::Rotation( const InType * q )
{
	setValue( q );
}



template< typename InType >
Rotation& Rotation::setValue( const InType * q )
{
	quat[0] = static_cast< float >( q[0] );
	quat[1] = static_cast< float >( q[1] );
	quat[2] = static_cast< float >( q[2] );
	quat[3] = static_cast< float >( q[3] );
	normalize();

	return ( *this );
}


/**
 * @brief Multiply a vector by a rotation.
 */
VGM_API vgm::Vec3f operator *( const vgm::Vec3f& vec, const vgm::Rotation& rot);

/**
 * @brief Multiply a vector by a rotation.
 */
VGM_API vgm::Vec3f& operator *=( vgm::Vec3f& vec, const vgm::Rotation& rot);



} // namespace vgm

#endif // #ifndef _VGM_ROTATION_HPP
