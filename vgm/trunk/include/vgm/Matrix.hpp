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
 * Author(s)		:	Nick Thompson, David Mott, Howard Look.
 */

#ifndef _VGM_MATRIX_H
#define _VGM_MATRIX_H

#include "vgm/vgm.hpp"
#include "vgm/Rotation.hpp"
#include "vgm/Vector.hpp"



namespace vgm
{



struct Line;

/**
 * @brief Raw 4x4 matrix of floating-point elements.
 * 
 * @ingroup LinearAlgebra
 */
typedef float	RawMatrix[4][4];
typedef double	RawMatrixd[4][4];

/**
 * @brief 4x4 matrix of floating-point elements.
 *
 * The matrices are stored in <b>row-major order</b> (unlike <b>column-major order</b> for OpenGL).
 * But all matrices, created by this class, are the transposed of the OpenGL version.
 * So you can use it directly in OpenGL :)
 * 
 * @warning Matrix is not initialized by all constructors.
 *
 * @todo make a n*n version.
 *
 * @todo More C++ friendly ( operator * (vec, matrix) )..., 	void print( FILE *fp ) const;
 * @todo template for float, double.
 * @todo remove #ifdef DEBUGGING ?
 * @todo More C++ friendly(in this class ex: remove #define, improve identity()).
 * 
 * @ingroup LinearAlgebra
 */
struct VGM_API MatrixR
{
	/**
	 * @name Constructors and destructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 *
	 * @warning Matrix is not initialized.
	 */
	MatrixR( void );

	/**
	 * @brief Constructor given all 16 elements in row-major order.
	 *
	 * @remarks a \c y \c x => \c y = row and \c x = colomn
	 */
	MatrixR(	float a11, float a12, float a13, float a14,
				float a21, float a22, float a23, float a24,
				float a31, float a32, float a33, float a34,
				float a41, float a42, float a43, float a44 );

	/**
	 * @brief Constructor from a 4x4 array of elements.
	 */
	MatrixR( const RawMatrix& m );

	/**
	 * @brief Copy constructor.
	 */
	MatrixR( const MatrixR& m );
	//@}


	/**
	 * @name Matrix accessors.
	 *
	 * The following methods return matrix values and other informations.
	 */
	//@{

	/**
	 * @brief Sets value from 4x4 array of elements.
	 */
	void					setValue( const RawMatrix m );
	
	/**
	 * @brief Sets value from 4x4 array of elements.
	 */
	void					setValue( const RawMatrixd m );

	/**
	 * @brief Returns 4x4 array of elements.
	 */
	void					getValue( RawMatrix m ) const;

	/**
	 * @brief Returns 4x4 array of elements.
	 */
	void					getValue( RawMatrixd m ) const;

	/**
	 * @brief Returns 4x4 array of elements.
	 */
	const RawMatrix&	getValue( void ) const;

	/**
	 * @brief Returns 4x4 array of elements.
	 */
	RawMatrix&			getValue( void );

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
	void					identity( void );

	/**
	 * @brief Returns an identity matrix 
	 */
	static MatrixR		getIdentity( void );

	/**
	 * @brief Check if this matrix is identity.
	 */
	bool					isIdentity( void ) const;
	//@}


	/**
	 * @name Transformation accessors.
	 */
	//@{

	/**
	 * @brief Sets matrix to rotate by given rotation.
	 */
	void	setRotate( const Rotation& q );

	/**
	 * @brief Sets matrix to scale by given uniform factor.
	 */
	void	setScale( const float s );

	/**
	 * @brief Sets matrix to scale by given vector.
	 */
	void	setScale( const Vec3f& s );

	/**
	 * @brief Sets matrix to translate by given vector.
	 */
	void	setTranslate( const Vec3f& t );

	/**
	 * @brief Composes the matrix based on a translation, rotation, scale,
	 * orientation for scale, and center.
	 *
	 * The "center" is the center point for scaling and rotation.
	 * The "scaleOrientation" chooses the primary axes for the scale.
	 * Final computed matrix M is equal t * c * r * so * s * so-1 * c-1 like in VRML tranform node.
	 * In matrix transformation notation, where c (center), so (scaleOrientation), t (translation), r (rotation), and s (scale) are the equivalent transformation matrices
	 * and so-1(inverse of scaleOrientation), c-1(inverse of center).
	 */
	void	setTransform(
			const Vec3f&	translation,
			const Rotation& rotation,
			const Vec3f&	scaleFactor			= Vec3f(0.f, 0.f, 0.f),
			const Rotation&	scaleOrientation	= Rotation(0.f,0.f,0.f,1.f),
			const Vec3f&	center				= Vec3f(0.f, 0.f, 0.f) );

	/**
	 * @brief Decomposes the matrix into a translation, rotation, scale,
	 * and scale orientation.  Any projection information is discarded.
	 *
	 * The decomposition depends upon choice of center point for
	 * rotation and scaling, which is optional as the last parameter.
	 * Note that if the center is 0, decompose() is the same as
	 * factor() where "t" is translation, "u" is rotation, "s" is scaleFactor,
	 * and "r" is ScaleOrientattion.
	 */
	void	getTransform(
		Vec3f& translation,
		Rotation& rotation,
		Vec3f& scaleFactor,
		Rotation& scaleOrientation,
		const Vec3f& center			= Vec3f(0.f, 0.f, 0.f) ) const;

	/**
	 * @brief Set matrix to perspective matrix.
	 * 
	 * @param left		The coordinates for the left-vertical clipping planes.
	 * @param right	The coordinates for the right-vertical clipping planes.
	 * @param bottom  The coordinates for the bottom-horizontal clipping planes.
	 * @param top 		The coordinates for the top-horizontal clipping planes.
	 * @param zNear	The distance to the near-depth clipping planes. Distance must be positive. 
	 * @param zFar		The distance to the far-depth clipping planes. Distance must be positive.
	 * 
	 * The matrix is exactly the same as the one sets by the OpenGL function \c glFrustum.
	 */
	void	setFrustum(
		 float left, float right,
		 float bottom, float top,
		 float zNear, float zFar );

	/**
	 * @brief Set matrix to orthographic matrix.
	 * 
	 * @param left		The coordinates for the left-vertical clipping planes.
	 * @param right	The coordinates for the right-vertical clipping planes.
	 * @param bottom  The coordinates for the bottom-horizontal clipping planes.
	 * @param top 		The coordinates for the top-horizontal clipping planes.
	 * @param zNear	The distances to the near-depth clipping planes. Both distances must be positive. 
	 * @param zFar		The distances to the far-depth clipping planes. Both distances must be positive.
	 *
	 * The matrix is exactly the same as the one sets by the OpenGL function \c glOrtho and \c gluOrtho2D.
	 */
	void	setOrtho(
		 float left, float right,
		 float bottom, float top,
		 float zNear = -1, float zFar = 1 );

	/**
	 * @brief Set matrix to perspective matrix.
	 * 
	 * @param fovy		The field of view angle, in degrees, in the y-direction.
	 * @param aspect	The aspect ratio that determines the field of view in the x-direction. The aspect ratio is the 
	 * ratio of x (width) to y (height).
	 * @param zNear	The distance from the viewer to the near clipping plane (always positive).
	 * @param zFar		The distance from the viewer to the far clipping plane (always positive).
	 *
	 * @remark This method is an helper build upon setFrustum.
	 * 
	 * The matrix is exactly the same as the one sets by the GLU function \c gluPerspective.
	 */
	void setPerspective( float fovy, float aspect, float zNear, float zFar);

	/**
	 * @brief Set matrix to a viewing transformation.
	 * 
	 * @param eyex		The position of the eye point. 
	 * @param eyey		The position of the eye point.
	 * @param eyez		The position of the eye point.
	 * 
	 * @param centerx	The position of the reference point.
	 * @param centery	The position of the reference point.
	 * @param centerz	The position of the reference point.
	 * 
	 * @param upx		The direction of the up vector.
	 * @param upy		The direction of the up vector.
	 * @param upz		The direction of the up vector.
	 * 
	 * The matrix is exactly the same as the one sets by the GLU function \c gluLookAt.
	 */
	void setLookAt(	float eyex, float eyey, float eyez,
							float centerx, float centery, float centerz,
							float upx, float upy, float upz);
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
		const int32 r1, const int32 r2, const int32 r3,
		const int32 c1, const int32 c2, const int32 c3 ) const;

	/**
	 * @brief Returns determinant of upper-left 3x3 submatrix.
	 */
	float	det3( void ) const;

	/**
	 * @brief Returns determinant of entire matrix.
	 */
	float	det4( void ) const;
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
	MatrixR&		multLeft( const MatrixR& m );

	/**
	 * @brief Multiplies matrix by given matrix on right.
	 *
	 * this = this * m
	 */
	MatrixR&		multRight( const MatrixR& m );

	/**
	 * @brief Performs right multiplication with another matrix.
	 */
	MatrixR&		operator *=( const MatrixR& m );

	/**
	 * @brief Binary multiplication of matrices.
	 */
	friend VGM_API MatrixR	operator *( const MatrixR& m1, const MatrixR& m2 );

	/**
	 * @brief Returns inverse of matrix.
	 *
	 * Results are undefined for singular matrices.  Uses LU decomposition.
	 */
	MatrixR			getInverse( void ) const;

	/**
	 * @brief Inverse the matrix.
	 *
	 * Results are undefined for singular matrices.  Uses LU decomposition.
	 */
	void				inverse( void );

	/**
	 * @brief Returns transpose of matrix.
	 */
	MatrixR			getTranspose( void ) const;

	/**
	 * @brief Transpose the matrix.
	 */
	void				transpose( void );

	/**
	 * @brief Perform in-place LU decomposition of matrix.
	 *
	 * @param	index is index of rows in matrix.
	 * @param	d is the parity of row swaps.
	 * @return	Returns false if singular, true otherwise.
	 * @todo documentation.
	 */
	bool				LUDecomposition( int32 index[4], float& d );

	/**
	 * @brief Perform back-substitution on LU-decomposed matrix.
	 *
	 * @param index is permutation of rows from original matrix.
	 * @param b is input as the right-hand side vector B, and returns the solution vector X(for this * X = B ).
	 * @todo documentation.
	 */
	void				LUBackSubstitution( int32 index[4], float b[4]) const;

	/**
	 * @brief Factors a matrix m into 5 pieces.
	 *
	 * m = r s r^ u t, where r^ means transpose of r, and r and u are rotations, 
	 * s is a scale, and t is a translation. Any projection information is returned
	 * in proj.
	 */
	bool				factor(	MatrixR& r, Vec3f& s, MatrixR& u,
									Vec3f& t, MatrixR& proj) const;
	//@}

	/**
	 * @name Matrix * Vector arithmetic.
	 */
	//@{

	/**
	 * @brief Multiplies matrix by given column vector, giving vector result.
	 */
	void			multMatrixVec( const Vec3f& src, Vec3f& dst ) const;

	/**
	 * @brief Multiplies given row vector by matrix, giving vector result.
	 */
	void			multVecMatrix( const Vec3f& src, Vec3f& dst ) const;

	/**
	 * @brief Multiplies given row vector by matrix, giving vector result.
	 *
	 * @param src is assumed to be a direction vector, so translation part of matrix is ignored.
	 * @param dst vector result.
	 */
	void			multDirMatrix( const Vec3f& src, Vec3f& dst ) const;
	//@}

	/**
	 * @name Some useful computing and debug methods.
	 */

	/**
	 * @brief Multiplies the given line by the matrix resulting in a new line.
	 *
	 * Multiplies the given line's origin by the whole matrix, and the
	 * line's direction by the rotation portion of the matrix.
	 */
	void			multLineMatrix( const Line& src, Line& dst ) const;

	/**
	 * @brief Prints a formatted version of the matrix to the given file pointer.
	 *
	 * @todo same with std::string, idem for vectors, bb...
	 */
	// FIXME void			print( FILE *fp ) const;
	//@}



	/**
	 * @name Affectation methods.
	 */
	//@{

	/**
	 * @brief Sets value from 4x4 array of elements.
	 */
	MatrixR&		operator =( const RawMatrix m );

	/**
	 * @copydoc operator=(const RawMatrix&)
	 */
	MatrixR&		operator =( const MatrixR& m );

	/**
	 * @brief Sets value from a rotation.
	 */
	MatrixR&		operator =( const Rotation& q );
	//@}

	/**
	 * @name Comparison methods.
	 */
	//@{

	/**
	 * @brief Equality comparison.
	 */
	bool	operator ==( const MatrixR& m2 ) const;

	/**
	 * @brief Difference comparison.
	 */
	bool	operator !=( const MatrixR& m2 ) const;

	/**
	 * @brief Equality comparison within given tolerance, for each component.
	 */
	bool		equals( const MatrixR& m, const float tolerance ) const;
	//@}

private:

	/**
	 * Storage for 4x4 matrix.
	 */
	RawMatrix	matrix;

	/**
	 * Diagonalizes 3x3 matrix.
	 */
	void	jacobi3( float evalues[3], Vec3f evectors[3], int32& rots ) const;

	/**
	 * @brief Compute inverse of 3d affine matrix if possible.
	 *
	 * @param in  : 3d affine matrix.
	 * @param out : inverse of 3d affine matrix.
	 * @return true if input matrix is nonsingular and affine, false.otherwise.
	 */
	bool	affine_inverse( const MatrixR& in, MatrixR& out ) const;
};



} // namespace vgm

#endif // _VGM_MATRIX_H
