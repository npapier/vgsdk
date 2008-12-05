// VGSDK - Copyright (C) 2004-2006, 2008, Clément Forest, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Clément Forest
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

#ifndef _VGM_MATRIX33_HPP
#define _VGM_MATRIX33_HPP

#include "vgm/vgm.hpp"
#include "vgm/Vector.hpp"



namespace vgm
{


/**
 * @brief Raw 3x3 matrix of floating-point elements.
 * 
 * @ingroup LinearAlgebra
 */
typedef float	RawMatrix33[3][3];
typedef double	RawMatrixd33[3][3];

/**
 * @brief 3x3 matrix of floating-point elements.
 *
 * 
 * @warning Matrix is not initialized by all constructors.
 *
 * @todo More C++ friendly ( operator * (vec, matrix) )..., 	void print( FILE *fp ) const;
 * @todo template for float, double.
 * @todo remove #ifdef DEBUGGING ?
 * @todo More C++ friendly(in this class ex: remove #define, improve setIdentity()).
 * 
 * @todo make a n*n version.
 * 
 * @ingroup LinearAlgebra
 */
struct VGM_API Matrix33
{
	/**
	 * @name Constructors and destructor
	 */
	//@{

	/**
	 * @brief Default constructor.
	 *
	 * @warning Matrix is not initialized.
	 */
	Matrix33();

	/**
	 * @brief Constructor given all 16 elements in row-major order.
	 *
	 * @remarks a \c y \c x => \c y = row and \c x = colomn
	 */
	Matrix33(	float a11, float a12, float a13,
				float a21, float a22, float a23,
				float a31, float a32, float a33);

	/**
	 * @brief Constructor from a 3x3 array of elements.
	 */
	explicit Matrix33( const RawMatrix33& m );

	/**
	 * @brief Constructor from a 3x3 array of elements.
	 */
	explicit Matrix33( const RawMatrixd33& m );

	/**
	 * @brief Constructor from an array of 9 elements.
	 */
	explicit Matrix33( const float* m );
	
	/**
	 * @brief Constructor from an array of 9 elements.
	 */
	explicit Matrix33( const double* m );

	/**
	 * @brief Copy constructor.
	 */
	Matrix33( const Matrix33& m );
	
	//@}


	/**
	 * @name Matrix accessors
	 *
	 * The following methods return matrix values and other informations.
	 */
	//@{

	/**
	 * @brief Sets value from 4x4 array of elements.
	 */
	void setValue( const RawMatrix33 m );
	
	/**
	 * @brief Sets value from 4x4 array of elements.
	 */
	void setValue( const RawMatrixd33 m );
	
	/**
	 * @brief Sets value from an array of 16 elements.
	 */
	void setValue( const float* m );
	
	/**
	 * @brief Sets value from an array of 16 elements.
	 */
	void setValue( const double* m );
	
	/**
	 * @brief Sets the row from a vector of 4 elements
	 */
	void setRow( const int32 row, const vgm::Vec3f value );
	
	/**
	 * @brief Sets the column from a vector of 4 elements
	 */
	void setColumn( const int32 column, const vgm::Vec3f value );

	/**
	 * @brief Returns 4x4 array of elements.
	 */
	void getValue( RawMatrix33 m ) const;

	/**
	 * @brief Returns 4x4 array of elements.
	 */
	void getValue( RawMatrixd33 m ) const;
	
	/**
	 * @brief Returns an array of 16 elements.
	 */
	void getValue( float *m ) const;

	/**
	 * @brief Returns an array of 16 elements.
	 */
	void getValue( double *m ) const;

	/**
	 * @brief Returns the desired row
	 */
	const vgm::Vec3f getRow( const int32 row );

	/**
	 * @brief Returns the desired column
	 */
	const vgm::Vec3f getColumn( const int32 column );

	/**
	 * @brief Returns 4x4 array of elements.
	 */
	const RawMatrix33&	getValue() const;

	/**
	 * @brief Returns 4x4 array of elements.
	 */
	RawMatrix33&			getValue();

	/**
	 * @brief Make it look like a usual matrix (so you can do m[3][2], returns element in 3th row and 2th column).
	 * 
	 * @remarks MatrixR m;   m[x][y] returns element in x th row and y th column.
	 */
	float *				operator []( int32 i );

	/**
	 * @brief Make it look like a usual matrix (so you can do m[3][2], returns element in 3th row and 2th column).
	 * 
	 * @remarks MatrixR m;   m[x][y] returns element in x th row and y th column.
	 */
	const float *		operator []( const int32 i ) const;

	/**
	 * @brief Direct access to an element of the matrix (so you can do m(3,2), returns element in 3th column and 2th row).
	 * 
	 * @remarks MatrixR m;   m(x, y) returns element in x th column and y th row.
	 */
	float&				operator() ( const int32 column, const int32 row );
	
	/**
	 * @brief Direct access to an element of the matrix (so you can do m(3,2), returns element in 3th column and 2th row).
	 * 
	 * @remarks MatrixR m;   m(x, y) returns element in x th column and y th row.
	 */
	const float&		operator() ( const int32 column, const int32 row ) const;

	/**
	 * @brief Sets matrix to be identity.
	 */
	void					setIdentity();

	/**
	 * @brief Returns an identity matrix 
	 */
	static Matrix33			getIdentity();

	/**
	 * @brief Check if this matrix is identity.
	 */
	bool					isIdentity() const;
	
	/**
	 * @brief Invalidates the matrix.
	 * 
	 * @author Guillaume Brocker
	 */
	void setInvalid();
	
	/**
	 * @brief Returns an invalid matrix
	 */
	static const Matrix33 getInvalid();
	
	/**
	 * @brief Test if the matrix is invalid.
	 * 
	 * @author Guillaume Brocker
	 */
	const bool isInvalid() const;
	//@}


	/**
	 * @name Determinant computation.
	 */
	//@{

	/**
	 * @brief Returns determinant of 3x3 submatrix composed of given row and
	 * column indices (0-3 for each).
	 *
	 * @todo Optimization : The above method is, 10 multiplication, 5 subtraction and 1 division.
	 * The usual elementary text book method:
	 * D =   a11*a22*a33 + a21*a32*a13 + a31*a12*a23 
	 *       - a11*a23*a32 - a21*a12*a33 - a31*a22*a13
	 * is 12 multiplication, 2 addition and 3 subtractctions.
	 * And its easy improvement:
	 * D =  a11*(a22*a33-a23*a32)
	 *     + a21*(a32*a13-a12*a33)
	 *     + a31*(a12*a23-a22*a13)
	 * is 9 multiplications, 3 subtractions and 2 additions.
	 */
	float	det3(
		const int32 r1, const int32 r2,
		const int32 c1, const int32 c2 ) const;

	/**
	 * @brief Returns determinant of entire matrix.
	 */
	float	det3() const;
	//@}


	/**
	 * @name Matrix arithmetic.
	 */
	//@{

	/**
	 * @brief Multiplies matrix by given matrix on left.
	 *
	 * this = m * this
	 */
	Matrix33&		multLeft( const Matrix33& m );

	/**
	 * @brief Multiplies matrix by given matrix on right.
	 *
	 * this = this * m
	 */
	Matrix33&		multRight( const Matrix33& m );

	/**
	 * @brief Performs right multiplication with another matrix.
	 */
	Matrix33&		operator *=( const Matrix33& m );


	/**
	 * @brief add another matrix.
	 */

	Matrix33 operator+ (const Matrix33& m) const;


	/**
	 * @brief substract another matrix.
	 */

	Matrix33 operator- (const Matrix33& m) const;


	/**
	 * @brief Binary multiplication of matrices.
	 */
	friend VGM_API Matrix33	operator *( const Matrix33& m1, const Matrix33& m2 );

	/**
	 * @brief Returns inverse of matrix.
	 *
	 * Results are undefined for singular matrices.  Uses LU decomposition.
	 */
	Matrix33			getInverse() const;

	/**
	 * @brief Inverse the matrix.
	 *
	 * Results are undefined for singular matrices.  Uses LU decomposition.
	 */
	void				inverse();

	/**
	 * @brief Returns transpose of matrix.
	 */
	Matrix33			getTranspose() const;

	/**
	 * @brief Transpose the matrix.
	 */
	void				transpose();

	/**
	 * @name Assignement methods.
	 */
	//@{

	/**
	 * @brief Sets value from 4x4 array of elements.
	 */
	Matrix33&		operator =( const RawMatrix33 m );

	/**
	 * @copydoc operator=(const RawMatrix&)
	 */
	Matrix33&		operator =( const Matrix33& m );
	//@}

	/**
	 * @name Comparison methods.
	 */
	//@{

	/**
	 * @brief Equality comparison.
	 */
	bool	operator ==( const Matrix33& m2 ) const;

	/**
	 * @brief Difference comparison.
	 */
	bool	operator !=( const Matrix33& m2 ) const;

	/**
	 * @brief Equality comparison within given tolerance, for each component.
	 */
	bool		equals( const Matrix33& m, const float tolerance ) const;
	//@}

private:

	/**
	 * Storage for 4x4 matrix.
	 */
	RawMatrix33	matrix;

};


/**
 * @brief Multiplication of a vector3 by a matrix (V*M)
 * 
 * @relates Vector
 * @relates Matrix
 * 
 * @ingroup LinearAlgebra
 */
Vec3f VGM_API operator*(const Vec3f& vec, const Matrix33& mat);


/**
 * @brief Multiplication of a matrix by a vector3 (M*V)
 * 
 * @relates Vector
 * @relates Matrix
 * 
 * @ingroup LinearAlgebra
 */
Vec3f VGM_API operator*(const Matrix33& mat, const Vec3f& vec);




} // namespace vgm

#endif // _VGM_MATRIX_HPP
