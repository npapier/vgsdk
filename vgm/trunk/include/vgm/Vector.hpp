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
 * Author(s)		:	Nick Thompson, David Mott, Howard Look.
 */

#ifndef _VGM_VECTOR_HPP
#define _VGM_VECTOR_HPP

#include <cmath>

#include "vgm/vgm.hpp"



namespace vgm
{

/**
 * @brief Vector of N components of type T.
 * 
 * @warning vector is not initialized by all constructors.
 * 
 * @todo Check tmp/tmp.cpp
 * 
 * @ingroup LinearAlgebra
 */
template< typename T, int32 N >
struct Vector
{
	/**
	 * @name Constructors ,destructor and assign operator.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 *
	 * @warning vector is not initialized.
	 */
	Vector( void );

	/**
	 * @brief Constructor with value affectation from array of n components.
	 */
	explicit Vector( const T* v );

	/**
	 * @brief Copy constructor.
	 */
	Vector( const Vector& v );
	
	/**
	 * @brief Assign operator.
	 */
	Vector& operator=( const Vector& v );
	//@}

	/**
	 * @name Constructors not available in all dimensions.
	 * 
 	 * @todo move it to a partial specialization of this template.
	 */
	//@{

	/**
 	 * @brief Constructor from 2 components.
 	 * 
 	 * @remarks only if dimension is equal to 2.
 	 */
	Vector( const T c1, const T c2 )
	{
		assert(N==2);
		
		m_tCoord[0] = c1;
		m_tCoord[1] = c2;
	}
	
	/**
 	 * @brief Constructor from 3 components.
 	 * 
 	 * @remarks only if dimension is equal to 3.
 	 */
	Vector( const T c1, const T c2, const T c3 )
	{
		assert(N==3);
		
		m_tCoord[0] = c1;
		m_tCoord[1] = c2;
		m_tCoord[2] = c3;
	}

	/**
 	 * @brief Constructor from 4 components.
 	 * 
 	 * @remarks only if dimension is equal to 4.
 	 */
	Vector( const T c1, const T c2, const T c3, const T c4 )
	{
		assert(N==4);
		
		m_tCoord[0] = c1;
		m_tCoord[1] = c2;
		m_tCoord[2] = c3;
		m_tCoord[3] = c4;
	}	
	//@}
	 


	/**
	 * @name Vector accessors.
	 *
	 * The following methods return and set vector values.
	 */
	//@{

	/**
	 * @brief Returns pointer to array of n components.
	 */
	const T*	getValue( void ) const;

	/**
	 * @brief Returns pointer to array of n components.
	 */
	T*			getValue( void );

	/**
	 * @brief Set value of vector from array of n components.
	 */
	void		setValue( const T* );

	/**
	 * @brief Set value of vector from another one (with same dimension).
	 */
	void		setValue( const Vector& );

	/**
	 * @brief Accesses indexed component of vector.
	 */
	T&			operator []( int32 i );

	/**
	 * @brief  Accesses indexed component of vector.
	 */
	const T&	operator []( int32 i ) const;

	/**
	 * @brief Get value of vector of 2 components.
	 * 
 	 * @remarks only if dimension is equal to 2.
	 */
	void		getValue( T& c1, T& c2 ) const
	{
		assert( N == 2 );
		
		c1 = m_tCoord[0];
		c2 = m_tCoord[1];
	}
	
	/**
	 * @brief Set value of vector of 2 components.
	 * 
 	 * @remarks only if dimension is equal to 2.
	 */
	void		setValue( const T c1, const T c2 )
	{
		assert( N == 2 );
				
		m_tCoord[0] = c1;
		m_tCoord[1] = c2;
	}
		
	/**
	 * @brief Get value of vector of 3 components.
	 * 
 	 * @remarks only if dimension is equal to 3.
	 */
	void		getValue( T& c1, T& c2, T& c3 ) const
	{
		assert( N == 3 );
		
		c1 = m_tCoord[0];
		c2 = m_tCoord[1];
		c3 = m_tCoord[2];
	}
	
	/**
	 * @brief Set value of vector of 3 components.
	 * 
 	 * @remarks only if dimension is equal to 3.
	 */
	void		setValue( const T c1, const T c2, const T c3 )
	{
		assert( N == 3 );
				
		m_tCoord[0] = c1;
		m_tCoord[1] = c2;
		m_tCoord[2] = c3;
	}
	
	/**
	 * @brief Get value of vector of 4 components.
	 * 
 	 * @remarks only if dimension is equal to 4.
	 */
	void		getValue( T& c1, T& c2, T& c3, T& c4 ) const
	{
		assert( N == 4 );
		
		c1 = m_tCoord[0];
		c2 = m_tCoord[1];
		c3 = m_tCoord[2];
		c4 = m_tCoord[3];
	}
	
	/**
	 * @brief Set value of vector of 4 components.
	 * 
 	 * @remarks only if dimension is equal to 4.
	 */
	void		setValue( const T c1, const T c2, const T c3, const T c4 )
	{
		assert( N == 4 );
				
		m_tCoord[0] = c1;
		m_tCoord[1] = c2;
		m_tCoord[2] = c3;
		m_tCoord[3] = c4;
	}
	//@}


	/**
	 * @name Vector arithmetic.
	 */
	//@{

	/**
	 * @brief Set the vector to null.
	 */
	void			null( void );

	/**
	 * @brief Test if the vector is null.
	 */
	const bool	isNull( void ) const;

	/**
	 * @brief Component-wise binary vector addition operators.
	 */
	Vector			operator +( const Vector& v2 ) const;

	/**
	 * @brief Component-wise binary vector subtraction operators.
	 */
	Vector			operator -( const Vector& v2 ) const;

	/**
	 * @brief Nondestructive unary negation - returns a new vector.
	 */
	Vector			operator -( void ) const;

	/**
	 * @brief Negates each component of vector in place.
	 */
	void				negate( void );

	/**
	 * @brief Component-wise vector addition operators.
	 */
	Vector&			operator +=( const Vector& u );

	/**
	 * @brief Component-wise vector subtraction operators.
	 */
	Vector&			operator -=( const Vector& u );

	/**
	 * @brief Component-wise scalar multiplication operators.
	 */
	Vector&			operator *=( T d );

	/**
	 * @brief Component-wise scalar division operators.
	 *
	 * @pre d is not zero.
	 */
	Vector&			operator /=( T d );
	//@}


	/**
	 * @name More Vector arithmetic.
	 */
	//@{

	/**
	 * @brief Returns squared geometric length of vector.
	 */
	T		getSqrLength( void ) const;

	/**
	 * @brief Returns length of vector.
	 */
	T		getLength( void ) const;

	/**
	 * @brief Changes vector to be unit length.
	 */
	T		normalize( void );

	/**
	 * @brief Returns normalized vector(unit lenght).
	 */
	Vector	getNormalized( void ) const;

	/**
	 * @brief Returns the dot product of two vectors.
	 */
	float		dot( const Vector& v ) const;



	/**
	 * @brief Returns the cross product of two vectors.
	 * 
	 * @remarks only if dimension is equal to 3.
	 */
	Vector	cross( const Vector& rV ) const
	{
		assert( N == 3 );
		
		Vector v;
		
		v.m_tCoord[0] = m_tCoord[1]* rV.m_tCoord[2] -  m_tCoord[2]* rV.m_tCoord[1];
		v.m_tCoord[1] = m_tCoord[2]* rV.m_tCoord[0] -  m_tCoord[0]* rV.m_tCoord[2];
		v.m_tCoord[2] = m_tCoord[0]* rV.m_tCoord[1] -  m_tCoord[1]* rV.m_tCoord[0];
		
		return ( v );
	}


	
	/**
	 * @brief Returns principal axis that is closest.
	 * 
	 * based on maximum dot product to this vector.
	 */
	Vector	getClosestAxis() const;

	/**
	 * @brief Projects vector onto a sphere of radius \c radius
	 * 
	 * @param radius		radius of the sphere
	 * 
 	 * @remarks only if dimension is equal to 3.
	 */
	void	projectOnSphere( const float radius = 1.f );
	//@}



	/**
	 * @name Comparison methods.
	 */
	//@{

	/**
	 * @brief Equality comparison.
	 */
	bool			operator ==( const Vector& v2 ) const;

	/**
	 * @brief Difference comparison.
	 */
	bool			operator !=( const Vector& v2 ) const;

	/**
	 * @brief Equality comparison within given tolerance, for each component.
	 */
	bool			equals( const Vector& v, const float tolerance ) const;
	//@}

protected:

	/**
	 * @brief Storage for coordinates of vector.
	 */
	T		m_tCoord[N];
};

/**
 * @brief Component-wise binary scalar multiplication operators.
 * 
 * @relates Vector
 * 
 * @ingroup LinearAlgebra
 */
template< typename T, int32 N >
Vector<T,N> operator *( const T pScal, const Vector<T,N>& v );

/**
 * @brief Component-wise binary scalar multiplication operators.
 * 
 * @relates Vector
 * 
 * @ingroup LinearAlgebra
 */
template< typename T, int32 N >
Vector<T,N> operator *( const Vector<T,N>& v, const T pScal );

/**
 * @brief Component-wise binary scalar division operators.
 * 
 * @relates Vector
 * 
 * @ingroup LinearAlgebra
 */
template< typename T, int32 N >
Vector<T,N> operator /( const T pScal, const Vector<T,N>& v );

/**
 * @brief Component-wise binary scalar division operators.
 * 
 * @relates Vector
 * 
 * @ingroup LinearAlgebra
 */
template< typename T, int32 N >
Vector<T,N> operator /( const Vector<T,N>& v, const T pScal );

/**
 * @brief 2d vector class used to store 2d vectors and points.
 * 
 * @ingroup LinearAlgebra
 */
typedef Vector<	double, 2 > Vec2d;

/**
 * @brief 3D vector class used to store 3D vectors and points.
 *
 * This class is used throughout VGL for arguments and return values.
 * 
 * @ingroup LinearAlgebra
 */
typedef Vector< double, 3 > Vec3d;

/**
 * @brief 4d vector class used to store 4d vectors and points.
 * 
 * @ingroup LinearAlgebra
 */
typedef Vector<	double, 4 > Vec4d;

/**
 * @brief 2d vector class used to store 2d vectors and points.
 * 
 * @ingroup LinearAlgebra
 */
typedef Vector<	float, 2 > Vec2f;

/**
 * @brief 3D vector class used to store 3D vectors and points.
 *
 * This class is used throughout VGL for arguments and return values.
 * 
 * @ingroup LinearAlgebra
 */
typedef Vector< float, 3 > Vec3f;

/**
 * @brief 4d vector class used to store 4d vectors and points.
 * 
 * @ingroup LinearAlgebra
 */
typedef Vector<	float, 4 > Vec4f;

/**
 * @brief 2d vector class used to store 2d vectors and points.
 * 
 * @ingroup LinearAlgebra
 */
typedef Vector<	int32, 2 > Vec2i;

/**
 * @brief 3D vector class used to store 3D vectors and points.
 *
 * This class is used throughout VGL for arguments and return values.
 * 
 * @ingroup LinearAlgebra
 */
typedef Vector< int32, 3 > Vec3i;

/**
 * @brief 4d vector class used to store 4d vectors and points.
 * 
 * @ingroup LinearAlgebra
 */
typedef Vector<	int32, 4 > Vec4i;



#include "vgm/Vector.hxx"



} // namespace vgm

#endif // #ifndef _VGM_VECTOR_HPP
