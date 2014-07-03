// VGSDK - Copyright (C) 2004, 2006, 2007, 2008, 2009, 2010, 2011, 2013, Nicolas Papier.
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

#include <algorithm>
#include <cmath>
#include <glm/glm.hpp>
#include <iomanip>
#include <limits>
#include <sstream> 
#include <vector>

#include <vgDebug/helpers.hpp>

#include "vgm/operations.hpp"



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
template< typename T, int N >
struct Vector
{
	typedef T value_type;	///< Defines an alias on the components type

	/**
	 * @name Constructors, destructor and assign operator
	 */
	//@{

	/**
	 * @brief Default constructor.
	 *
	 * @warning vector is not initialized.
	 */
	Vector();



	/**
	 * @brief Constructor from a glm vector
 	 */
	Vector( const glm::vec2 v )
	{
		const uint minSize = std::min( N, 2 );
		for( int i=0; i<minSize; ++i )
		{
			m_tCoord[i] = v[i];
		}
	}

	/**
	 * @brief Constructor from a glm vector
 	 */
	Vector( const glm::vec3 v )
	{
		const uint minSize = std::min( N, 3 );
		for( int i=0; i<minSize; ++i )
		{
			m_tCoord[i] = v[i];
		}
	}

	/**
	 * @brief Constructor from a glm vector
 	 */
	Vector( const glm::vec4 v )
	{
		const uint minSize = std::min( N, 4 );
		for( int i=0; i<minSize; ++i )
		{
			m_tCoord[i] = v[i];
		}
	}



	/**
	 * @brief Constructor with value affectation from array of n components.
	 */
	explicit Vector( const T* v );

	/**
	 * @brief Constructor with value affectation from array of n components.
	 */
	template< typename InType >
	explicit Vector< T, N >( const InType* v );


	/**
	 * @brief Copy constructor
	 */
	Vector( const Vector& v );


	/**
	 * @brief Constructor from another Vector
	 *
	 * Determines the range of elements that can be copied from the input
	 * vector into the new vector by using the smallest size among the 
	 * input and new vector sizes.
	 * 
	 * Than copies and converts each elements of the range from the input 
	 * vector into the new vector.
	 *  
	 * As a result, all new vector's elements will be assigned with
	 * a converted element of the input vector when the input vector's size
	 * is greater or equal to the new vector's size. Otherwise, some elements of the
	 * new vector will be initialized to zero (See VectorCast for a more lazy initialization).
	 *
	 * See usage examples below.
	 * 
@code
const vgm::Vec3f	in1( 1.f, 2.f, 3.f );
vgm::Vec3i		out1( in1 );
@endcode

@code
const vgm::Vec3i	in2( 1, 2, 3 );
vgm::Vec3f		out2( in2 );
@endcode

@code
const vgm::Vec3i	in3( 1, 2, 3 );
vgm::Vec2f		out3( in3 );
@endcode

@code
const vgm::Vec2f	in4( 1.f, 2.f );
vgm::Vec3i		out4( in4 );
@endcode

@code
const vgm::Vec3f	in5( 1.f, 2.f, 3.f );
vgm::Vec2f		out5( in5 );
vgm::Vec4f		out5b( in5 );
@endcode
	 *
	 * @relates VectorCast
	 * @ingroup LinearAlgebra
	 */
	template< typename InType, int InSize >
	explicit Vector< T, N >( const Vector< InType, InSize > & v )
	{
		const uint minSize = std::min( N, InSize );

		for( uint i = 0; i < minSize; ++i )
		{
			m_tCoord[i] = static_cast< T >( v[i] );
		}

		for( uint i = minSize; i < N; ++i )
		{
			m_tCoord[i] = static_cast< T >( 0 );
		}
	}


	/**
	 * @brief Construct of vector of N components using a vector of N-1 components and a value
	 */
	template< int InSize >
	Vector( const Vector< T, InSize > v, const T c )
	{
		setValue( v, c );
	}

	/**
	 * @brief Construct of vector of N components using a vector of N-2 components and two values
	 */
	template< int InSize >
	Vector( const Vector< T, InSize > v, const T c3, const T c4 )
	{
		setValue( v, c3, c4 );
	}

	/**
	 * @brief Assign operator.
	 */
	Vector& operator=( const Vector& v );
	//@}

	/**
	 * @name Constructors not available in all dimensions
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

	/**
 	 * @brief Constructor from 5 components.
 	 * 
 	 * @remarks only if dimension is equal to 5.
 	 */
	Vector( const T c1, const T c2, const T c3, const T c4, const T c5 )
	{
		assert(N==5);

		m_tCoord[0] = c1;
		m_tCoord[1] = c2;
		m_tCoord[2] = c3;
		m_tCoord[3] = c4;
		m_tCoord[4] = c5;
	}
	//@}



	/**
	 * @name Vector accessors
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
	 * @brief Set value of vector from array of n components.
	 */
	template< typename InType >
	void		setValue( const InType* );

	/**
	 * @brief Set value of vector from another one (with same dimension).
	 */
	void		setValue( const Vector& );

	/**
	 * @brief Set value of vector of N components using a vector of N-1 components and a value
	 */
	template< int InSize >
	void setValue( const Vector< T, InSize > v, const T c )
	{
		assert( InSize == N - 1 );

		for( uint i = 0; i < InSize; ++i )
		{
			m_tCoord[i] = v[i];
		}

		m_tCoord[InSize] = c;
	}

	/**
	 * @brief Set value of vector of N components using a vector of N-2 components and two values
	 */
	template< int InSize >
	void setValue( const Vector< T, InSize > v, const T c3, const T c4 )
	{
		vgAssert( InSize == N - 2 );

		for( uint i = 0; i < InSize; ++i )
		{
			m_tCoord[i] = v[i];
		}

		m_tCoord[InSize] = c3;
		m_tCoord[InSize+1] = c4;
	}

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

	/**
	 * @brief	Retrieves the number of components.
	 */
	vgDEPRECATED( const uint getSize() const )
	{
		return static_cast<uint>(N);
	}

	/**
	 * @brief	Retrieves the dimension of the vector.
	 */
	const uint getDim() const
	{
		return static_cast<uint>(N);
	}
	//@}


	/**
	 * @name Vector arithmetic
	 */
	//@{

	/**
	 * @brief Set the vector to null.
	 */
	vgDEPRECATED( void		null( void ) ); 

	/**
	 * @brief Set the vector to null.
	 */
	void		setNull( void );

	/**
	 * @brief Returns a null vector.
	 */
	static const Vector getNull();

	/**
	 * @brief Test if the vector is null.
	 */
	const bool	isNull( void ) const;

	/**
	 * @brief Invalidates the vector.
	 * 
	 * @author	Guillaume Brocker
	 */
	void setInvalid( void );

	/**
	 * @brief Returns an invalid vector
	 */
	static const Vector getInvalid();

	/**
	 * @brief Tests if the vector is invalid.
	 * 
	 * @author	Guillaume Brocker
	 */
	const bool isInvalid( void ) const;

	/**
	 * @brief Tests if the vector is valid.
	 */
	const bool isValid( void ) const;

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
	void			negate( void );

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
	 * @name More Vector arithmetic
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
	 * @brief Returns normalized vector(unit length).
	 */
	Vector	getNormalized( void ) const;

	/**
	 * @brief Returns the dot product of two vectors.
	 */
	float		dot( const Vector& v ) const;

	/**
	 * @brief Returns the angle between two vectors.
	 *
	 * @return the angle in radians between the two vectors.
	 */
	const float getAngle( const Vector& v ) const;

	/**
	 * @brief Tests if two vectors are collinear.
	 *
	 * @return true if the two vectors are collinear, false otherwise.
	 */
	const bool isCollinear( const Vector& v, const float tolerance = vgm::Epsilon<T>::value() ) const;



	/**
	 * @brief Returns the cross product of two vectors.
	 * 
	 * @remarks only if dimension is equal to 3.
	 */
	Vector cross( const Vector& rV ) const;


	
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
	 * @name Comparison methods
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
	bool			equals( const Vector& v, const float tolerance = vgm::Epsilon<T>::value() ) const;
	//@}



	/**
	 * @brief Returns a string containing each value of this vector separated by the given separator.
	 *
	 * @param precision		see std::setprecision()
	 * @param separator		separator used between each value of this vector
	 */
	const std::string toString( const int precision = 12, const std::string separator = " " ) const;



protected:

	/**
	 * @brief Storage for coordinates of vector.
	 */
	T m_tCoord[N];
};



/**
 * @brief Component-wise binary scalar multiplication operators.
 * 
 * @relates Vector
 * 
 * @ingroup LinearAlgebra
 */
template< typename T, int N >
Vector<T,N> operator *( const T pScal, const Vector<T,N>& v );

/**
 * @brief Component-wise binary scalar multiplication operators.
 * 
 * @relates Vector
 * 
 * @ingroup LinearAlgebra
 */
template< typename T, int N >
Vector<T,N> operator *( const Vector<T,N>& v, const T pScal );

/**
 * @brief Component-wise binary scalar division operators.
 * 
 * @relates Vector
 * 
 * @ingroup LinearAlgebra
 */
template< typename T, int N >
Vector<T,N> operator /( const T pScal, const Vector<T,N>& v );

/**
 * @brief Component-wise binary scalar division operators.
 * 
 * @relates Vector
 * 
 * @ingroup LinearAlgebra
 */
template< typename T, int N >
Vector<T,N> operator /( const Vector<T,N>& v, const T pScal );

/**
 * @brief Converts any vgm::Vector into a @c std::vector instance.
 * 
 * Copies and converts each element of the input vector into the output vector.
 * As a result, the output vector will have as many elements as the input vector.
 * 
 * See usage examples below.
 * 
@code
const vgm::Vec3f   in( 0.1f, 0.2f, 0.3f );
std::vector< int > out( vector_cast< int >(in) );
@endcode

@code
const vgm::Vec3i     in( 1, 2, 3 );
std::vector< float > out( vector_cast< float >(in) );
@endcode
 * 
 * @relates Vector
 * @ingroup LinearAlgebra
 * 
 * @author	Guillaume Brocker
 */
template< typename Out, typename In, int InSize >
const std::vector< Out > vector_cast( const Vector< In, InSize > & in );

/**
 * @brief Converts any @c std::vector into a vgm::Vector instance.
 * 
 * Determines the range of elements that can be copied from the input
 * vector into the output vector by using the smallest size among the 
 * input and output vector sizes.
 * 
 * Than copies and converts each elements of the range from the input 
 * vector into the output vector.
 *  
 * As a result, all output vector's elements will be assigned with
 * a converted element of the input vector when the input vector's size
 * is greater or equal to the output vector's size. Otherwise, some elements
 * of the output vector will be left uninitialized and that vector may be invalid.
 * 
 * See usage examples below.
 * 
@code
std::vector< int > in;
in.push_back( 1 );
in.push_back( 2 );
in.push_back( 3 );

vgm::Vec2f out2( vector_cast< float, 2 >( in ) );
vgm::Vec3f out3( vector_cast< float, 3 >( in ) );
@endcode
 *
 * @relates Vector
 * @ingroup LinearAlgebra
 *
 * @author	Guillaume Brocker
 */
template< typename Out, int OutSize, typename In >
const Vector< Out, OutSize > vector_cast( const std::vector< In > & in );



/**
 * @brief Converts any vgm::Vector into any vgm::Vector instance.
 * 
 * @see template< typename InType, int InSize > explicit Vector< T, N >( const Vector< InType, InSize >&)
 *
 * See usage examples below.
 * 
@code
const vgm::Vec3f	in1( 1.f, 2.f, 3.f );
vgm::Vec3i		out1( vgm::VectorCast< int, 3 >(in1) );
@endcode

@code
const vgm::Vec3i	in2( 1, 2, 3 );
vgm::Vec3f		out2( vgm::VectorCast< float, 3 >(in2) );
@endcode

@code
const vgm::Vec3i	in3( 1, 2, 3 );
vgm::Vec2f		out3( vgm::VectorCast< float, 2 >(in3) );
@endcode

@code
const vgm::Vec2f	in4( 1.f, 2.f );
vgm::Vec3i		out4( vgm::VectorCast< int, 3 >(in4) );
@endcode

@code
const vgm::Vec3f	in5( 1.f, 2.f, 3.f );
vgm::Vec2f		out5( vgm::VectorCast< float, 2 >(in5) );
vgm::Vec4f		out5b( vgm::VectorCast<float, 4>(in5) );

Be careful, out5b[3] is undefined.
@endcode

 * 
 * @relates Vector
 * @ingroup LinearAlgebra
 */
template< typename Out, int OutSize, typename In, int InSize >
const vgm::Vector< Out, OutSize > VectorCast( const Vector< In, InSize > & in );



/**
 * @brief 2d vector class used to store 2d vectors and points.
 * 
 * @ingroup LinearAlgebra
 */
typedef Vector<	double, 2 > Vec2d;

/**
 * @brief 3d vector class used to store 3d vectors and points.
 *
 * This class is used throughout vgsdk for arguments and return values.
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
 * @brief 5d vector class used to store 5d vectors and points.
 * 
 * @ingroup LinearAlgebra
 */
typedef Vector<	double, 5 > Vec5d;

/**
 * @brief 2d vector class used to store 2d vectors and points.
 * 
 * @ingroup LinearAlgebra
 */
typedef Vector<	float, 2 > Vec2f;

/**
 * @brief 3d vector class used to store 3d vectors and points.
 *
 * This class is used throughout vgsdk for arguments and return values.
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
 * @brief 5d vector class used to store 5d vectors and points.
 * 
 * @ingroup LinearAlgebra
 */
typedef Vector<	float, 5 > Vec5f;

/**
 * @brief 2d vector class used to store 2d vectors and points.
 * 
 * @ingroup LinearAlgebra
 */
typedef Vector<	int32, 2 > Vec2i;

/**
 * @brief 3d vector class used to store 3d vectors and points.
 *
 * This class is used throughout vgsdk for arguments and return values.
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

/**
 * @brief 5d vector class used to store 5d vectors and points.
 * 
 * @ingroup LinearAlgebra
 */
typedef Vector<	int32, 5 > Vec5i;



#include "vgm/Vector.hxx"



/**
 * @name Constructs a glm vector from a vgm::Vector
 */
//@{
VGM_API glm::vec2 glm( const vgm::Vec2f& v );
VGM_API glm::vec3 glm( const vgm::Vec3f& v );
VGM_API glm::vec4 glm( const vgm::Vec4f& v );
//@}

} // namespace vgm

#endif // #ifndef _VGM_VECTOR_HPP
