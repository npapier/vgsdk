// VGSDK - Copyright (C) 2004-2006, 2008, Clément Forest.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Clément Forest

#include "vgm/Matrix33.hpp"

#include <cmath>
#include <limits>



namespace vgm
{



// Matrix

// Handy absolute value macro:
#define ABS(a)		((a) < 0.0 ? -(a) : (a))

Matrix33::Matrix33()
{
}



Matrix33::Matrix33(	
				float a11, float a12, float a13,
				float a21, float a22, float a23,
				float a31, float a32, float a33 )
{
	// row 0
	matrix[0][0] = a11;
	matrix[0][1] = a12;
	matrix[0][2] = a13;

	// row 1
	matrix[1][0] = a21;
	matrix[1][1] = a22;
	matrix[1][2] = a23;

	// row 2
	matrix[2][0] = a31;
	matrix[2][1] = a32;
	matrix[2][2] = a33;
}



Matrix33::Matrix33( const RawMatrix33& m )
{
	setValue( m );
}



Matrix33::Matrix33( const RawMatrixd33& m )
{
	setValue( m );
}



Matrix33::Matrix33( const float* m )
{
	setValue( m );
}



Matrix33::Matrix33( const double* m )
{
	setValue( m );
}



Matrix33::Matrix33( const Matrix33& m )
{
	setValue( m.matrix );
}



void Matrix33::setValue( const RawMatrix33 m )
{
	matrix[0][0] = m[0][0];
	matrix[0][1] = m[0][1];
	matrix[0][2] = m[0][2];

	matrix[1][0] = m[1][0];
	matrix[1][1] = m[1][1];
	matrix[1][2] = m[1][2];

	matrix[2][0] = m[2][0];
	matrix[2][1] = m[2][1];
	matrix[2][2] = m[2][2];

}



void Matrix33::setValue( const RawMatrixd33 m )
{
	matrix[0][0] = static_cast<float>(m[0][0]);
	matrix[0][1] = static_cast<float>(m[0][1]);
	matrix[0][2] = static_cast<float>(m[0][2]);

	matrix[1][0] = static_cast<float>(m[1][0]);
	matrix[1][1] = static_cast<float>(m[1][1]);
	matrix[1][2] = static_cast<float>(m[1][2]);

	matrix[2][0] = static_cast<float>(m[2][0]);
	matrix[2][1] = static_cast<float>(m[2][1]);
	matrix[2][2] = static_cast<float>(m[2][2]);

}



void Matrix33::setValue( const float* m )
{
	matrix[0][0] = m[0];
	matrix[0][1] = m[1];
	matrix[0][2] = m[2];

	matrix[1][0] = m[4];
	matrix[1][1] = m[5];
	matrix[1][2] = m[6];

	matrix[2][0] = m[8];
	matrix[2][1] = m[9];
	matrix[2][2] = m[10];

}



void Matrix33::setValue( const double* m )
{
	matrix[0][0] = static_cast<float>(m[0]);
	matrix[0][1] = static_cast<float>(m[1]);
	matrix[0][2] = static_cast<float>(m[2]);

	matrix[1][0] = static_cast<float>(m[4]);
	matrix[1][1] = static_cast<float>(m[5]);
	matrix[1][2] = static_cast<float>(m[6]);

	matrix[2][0] = static_cast<float>(m[8]);
	matrix[2][1] = static_cast<float>(m[9]);
	matrix[2][2] = static_cast<float>(m[10]);

}



void Matrix33::setRow( const int32 row, const vgm::Vec3f value )
{
	matrix[row][0] = value[0];
	matrix[row][1] = value[1];
	matrix[row][2] = value[2];
}



void Matrix33::setColumn( const int32 column, const vgm::Vec3f value )
{
	matrix[0][column] = value[0];
	matrix[1][column] = value[1];
	matrix[2][column] = value[2];
}



void Matrix33::getValue( RawMatrix33 m ) const
{
	m[0][0] = matrix[0][0];
	m[0][1] = matrix[0][1];
	m[0][2] = matrix[0][2];

	m[1][0] = matrix[1][0];
	m[1][1] = matrix[1][1];
	m[1][2] = matrix[1][2];

	m[2][0] = matrix[2][0];
	m[2][1] = matrix[2][1];
	m[2][2] = matrix[2][2];

}



void Matrix33::getValue( RawMatrixd33 m ) const
{
	m[0][0] = static_cast<double>(matrix[0][0]);
	m[0][1] = static_cast<double>(matrix[0][1]);
	m[0][2] = static_cast<double>(matrix[0][2]);

	m[1][0] = static_cast<double>(matrix[1][0]);
	m[1][1] = static_cast<double>(matrix[1][1]);
	m[1][2] = static_cast<double>(matrix[1][2]);

	m[2][0] = static_cast<double>(matrix[2][0]);
	m[2][1] = static_cast<double>(matrix[2][1]);
	m[2][2] = static_cast<double>(matrix[2][2]);

}



void Matrix33::getValue( float *m ) const
{
	m[0]	= matrix[0][0];
	m[1]	= matrix[0][1];
	m[2]	= matrix[0][2];

	m[3]	= matrix[1][0];
	m[4]	= matrix[1][1];
	m[5]	= matrix[1][2];

	m[6]	= matrix[2][0];
	m[7]	= matrix[2][1];
	m[8]	= matrix[2][2];
}



void Matrix33::getValue( double *m ) const
{
	m[0]	= static_cast<double>(matrix[0][0]);
	m[1]	= static_cast<double>(matrix[0][1]);
	m[2]	= static_cast<double>(matrix[0][2]);

	m[3]	= static_cast<double>(matrix[1][0]);
	m[4]	= static_cast<double>(matrix[1][1]);
	m[5]	= static_cast<double>(matrix[1][2]);

	m[6]	= static_cast<double>(matrix[2][0]);
	m[7]	= static_cast<double>(matrix[2][1]);
	m[8]	= static_cast<double>(matrix[2][2]);
}



const vgm::Vec3f Matrix33::getRow( const int32 row )
{
	const vgm::Vec3f retVal( matrix[row][0], matrix[row][1], matrix[row][2] );
	
	return retVal;
}



const vgm::Vec3f Matrix33::getColumn( const int32 column )
{
	const vgm::Vec3f retVal( matrix[0][column], matrix[1][column], matrix[2][column] );
	
	return retVal;
}



const RawMatrix33& Matrix33::getValue() const
{
	return matrix;
}



RawMatrix33& Matrix33::getValue()
{
	return matrix;
}



float *Matrix33::operator []( int32 i )
{
	return &matrix[i][0];
}



const float * Matrix33::operator []( const int32 i ) const
{
	return &matrix[i][0];
}



float& Matrix33::operator() ( const int32 column, const int32 row )
{
	return ( matrix[row][column] );
}



const float& Matrix33::operator() ( const int32 column, const int32 row ) const
{
	return ( matrix[row][column] );
}



void Matrix33::setIdentity()
{
	matrix[0][0] = 1.0;
	matrix[0][1] = 0.0;
	matrix[0][2] = 0.0;

	matrix[1][0] = 0.0;
	matrix[1][1] = 1.0;
	matrix[1][2] = 0.0;

	matrix[2][0] = 0.0;
	matrix[2][1] = 0.0;
	matrix[2][2] = 1.0;
}



Matrix33 Matrix33::getIdentity()
{
	return Matrix33(
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0);
}



bool Matrix33::isIdentity() const
{
	return ( 
		(matrix[0][0] == 1.0) &&
		(matrix[0][1] == 0.0) &&
		(matrix[0][2] == 0.0) &&
		(matrix[1][0] == 0.0) &&
		(matrix[1][1] == 1.0) &&
		(matrix[1][2] == 0.0) &&
		(matrix[2][0] == 0.0) &&
		(matrix[2][1] == 0.0) &&
		(matrix[2][2] == 1.0) );
}



void Matrix33::setInvalid()
{
	const float fMax = std::numeric_limits< float >::max();
	
	matrix[0][0] = fMax;
	matrix[0][1] = fMax;
	matrix[0][2] = fMax;

	matrix[1][0] = fMax;
	matrix[1][1] = fMax;
	matrix[1][2] = fMax;

	matrix[2][0] = fMax;
	matrix[2][1] = fMax;
	matrix[2][2] = fMax;
}



const Matrix33 Matrix33::getInvalid()
{
	Matrix33 matrix;
	
	matrix.setInvalid();
	return matrix;
}


	
const bool Matrix33::isInvalid() const
{
	const float fMax = std::numeric_limits< float >::max();
	
	return ( 
		(matrix[0][0] == fMax) ||
		(matrix[0][1] == fMax) ||
		(matrix[0][2] == fMax) ||
		(matrix[1][0] == fMax) ||
		(matrix[1][1] == fMax) ||
		(matrix[1][2] == fMax) ||
		(matrix[2][0] == fMax) ||
		(matrix[2][1] == fMax) ||
		(matrix[2][2] == fMax) );	
}





float Matrix33::det3(	const int32 r1, const int32 r2,
							const int32 c1, const int32 c2) const
{
	return (
		matrix[r1][c1] * matrix[r2][c2] -
		matrix[r1][c2] * matrix[r2][c1] );
}


float Matrix33::det3() const
{
	return (
		matrix[0][2] * det3(1, 2, 0, 1) +
		matrix[1][2] * det3(0, 2, 0, 1) +
		matrix[2][2] * det3(0, 1, 0, 1) );
}



Matrix33& Matrix33::multLeft( const Matrix33& m )
{
	// Trivial cases
	if ( m.isIdentity() )
	{
		return *this;
	}
	else if ( isIdentity() )
	{
		return (*this = m);
	}

	RawMatrix33	tmp;

#define MULT_LEFT(i,j) (m.matrix[i][0]*matrix[0][j] + \
			m.matrix[i][1]*matrix[1][j] + \
						m.matrix[i][2]*matrix[2][j])

	tmp[0][0] = MULT_LEFT(0,0);
	tmp[0][1] = MULT_LEFT(0,1);
	tmp[0][2] = MULT_LEFT(0,2);

	tmp[1][0] = MULT_LEFT(1,0);
	tmp[1][1] = MULT_LEFT(1,1);
	tmp[1][2] = MULT_LEFT(1,2);

	tmp[2][0] = MULT_LEFT(2,0);
	tmp[2][1] = MULT_LEFT(2,1);
	tmp[2][2] = MULT_LEFT(2,2);

#undef MULT_LEFT

	setValue( tmp ); // *this = tmp;

	return ( *this );
}



Matrix33& Matrix33::multRight( const Matrix33& m )
{
	// Trivial cases
	if ( m.isIdentity() )
	{
		return *this;
	}
	else if ( isIdentity() )
	{
		return (*this = m);
	}

	RawMatrix33	tmp;

#define MULT_RIGHT(i,j) (matrix[i][0]*m.matrix[0][j] + \
			 matrix[i][1]*m.matrix[1][j] + \
			 matrix[i][2]*m.matrix[2][j])

	tmp[0][0] = MULT_RIGHT(0,0);
	tmp[0][1] = MULT_RIGHT(0,1);
	tmp[0][2] = MULT_RIGHT(0,2);

	tmp[1][0] = MULT_RIGHT(1,0);
	tmp[1][1] = MULT_RIGHT(1,1);
	tmp[1][2] = MULT_RIGHT(1,2);

	tmp[2][0] = MULT_RIGHT(2,0);
	tmp[2][1] = MULT_RIGHT(2,1);
	tmp[2][2] = MULT_RIGHT(2,2);

#undef MULT_RIGHT

	setValue( tmp ); // *this = tmp;
	
	return ( *this );
}



Matrix33& Matrix33::operator *=( const Matrix33& m )
{
	return multRight(m);
}


Matrix33 Matrix33::operator +( const Matrix33& m ) const
{
	Matrix33 r(matrix[0][0] + m[0][0], matrix[0][1] + m[0][1], matrix[0][2] + m[0][2],
			   matrix[1][0] + m[1][0], matrix[1][1] + m[1][1], matrix[1][2] + m[1][2],
			   matrix[2][0] + m[2][0], matrix[2][1] + m[2][1], matrix[2][2] + m[2][2]);
	return r;
}

Matrix33 Matrix33::operator -( const Matrix33& m ) const
{
	Matrix33 r(matrix[0][0] - m[0][0], matrix[0][1] - m[0][1], matrix[0][2] - m[0][2],
			   matrix[1][0] - m[1][0], matrix[1][1] - m[1][1], matrix[1][2] - m[1][2],
			   matrix[2][0] - m[2][0], matrix[2][1] - m[2][1], matrix[2][2] - m[2][2]);
	return r;
}


Matrix33 operator *( const Matrix33& l, const Matrix33& r )
{
	Matrix33 m = l;

	m *= r;

	return m;
}



// Returns inverse of matrix. Results are undefined for
// singular matrices.  Uses LU decomposition, from Numerial Recipies in C,
// pp 43-45.  They say "There is no better way."
//
// Oh, yeah! Well, if the matrix is affine, there IS a better way.
// So we call affine_inverse to see if we can get away with it...
Matrix33 Matrix33::getInverse() const
{
	// Trivial case
	if ( isIdentity() )
	{
		return Matrix33::getIdentity();
	}


	// Calculate the determinant of submatrix A and determine if the matrix
	// is singular as limited by the double precision floating
	// point data representation

	double det_1;
	double pos, neg, temp;

#define ACCUMULATE \
	if (temp >= 0.0) \
	pos += temp; \
	else\
	neg += temp;

	pos = neg = 0.0;
	temp =  matrix[0][0] * matrix[1][1] * matrix[2][2];
	ACCUMULATE
	temp =  matrix[0][1] * matrix[1][2] * matrix[2][0];
	ACCUMULATE
	temp =  matrix[0][2] * matrix[1][0] * matrix[2][1];
	ACCUMULATE
	temp = -matrix[0][2] * matrix[1][1] * matrix[2][0];
	ACCUMULATE
	temp = -matrix[0][1] * matrix[1][0] * matrix[2][2];
	ACCUMULATE
	temp = -matrix[0][0] * matrix[1][2] * matrix[2][1];
	ACCUMULATE
	det_1 = pos + neg;
#undef ACCUMULATE

#define PRECISION_LIMIT (1.0e-15)


	Matrix33 result;

	// Is the submatrix A singular?
	temp = det_1 / (pos - neg);
	if (ABS(temp) < PRECISION_LIMIT)
	{
		result.setInvalid();
		return result;
	}

	// Calculate inverse(A) = adj(A) / det(A)
	det_1 = 1.0f / det_1;
	result[0][0] = static_cast< float >( (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) * det_1 );
	result[1][0] = static_cast< float >( -(matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) * det_1);
	result[2][0] = static_cast< float >( (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]) * det_1 );
	result[0][1] = static_cast< float >( -(matrix[0][1] * matrix[2][2] - matrix[0][2] * matrix[2][1]) * det_1);
	result[1][1] = static_cast< float >( (matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0]) * det_1 );
	result[2][1] = static_cast< float >( -(matrix[0][0] * matrix[2][1] - matrix[0][1] * matrix[2][0]) * det_1);
	result[0][2] = static_cast< float >( (matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1]) * det_1 );
	result[1][2] = static_cast< float >( -(matrix[0][0] * matrix[1][2] - matrix[0][2] * matrix[1][0]) * det_1);
	result[2][2] = static_cast< float >( (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) * det_1 );

#undef PRECISION_LIMIT

	return result ;

}



void Matrix33::inverse()
{
	Matrix33 matrixInverse = getInverse();
	setValue( matrixInverse.matrix );
}



Matrix33 Matrix33::getTranspose() const
{
	return Matrix33(
		matrix[0][0], matrix[1][0], matrix[2][0],
		matrix[0][1], matrix[1][1], matrix[2][1],
		matrix[0][2], matrix[1][2], matrix[2][2]);
}



void Matrix33::transpose()
{
	Matrix33 matrixTranspose = getTranspose();
	setValue( matrixTranspose.matrix );
}





Matrix33& Matrix33::operator =( const RawMatrix33 m )
{
	setValue( m );

	return ( *this );
}



Matrix33& Matrix33::operator =( const Matrix33& m )
{
	setValue( m.matrix );

	return ( *this );
}




bool Matrix33::operator ==( const Matrix33& m2 ) const
{
	return (
		matrix[0][0] == m2.matrix[0][0] &&
		matrix[0][1] == m2.matrix[0][1] &&
		matrix[0][2] == m2.matrix[0][2] &&

		matrix[1][0] == m2.matrix[1][0] &&
		matrix[1][1] == m2.matrix[1][1] &&
		matrix[1][2] == m2.matrix[1][2] &&

		matrix[2][0] == m2.matrix[2][0] &&
		matrix[2][1] == m2.matrix[2][1] &&
		matrix[2][2] == m2.matrix[2][2]
		);
}



bool Matrix33::operator !=( const Matrix33& m2 ) const
{
	return !(*this == m2);
}



bool Matrix33::equals( const Matrix33& m, const float tolerance ) const
{
	int32		i, j;
	float	d;

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++) 
		{
			d = matrix[i][j] - m.matrix[i][j];
			if ( ABS(d) > tolerance )	return ( false );
		}
	}

	return ( true );
}


Vec3f operator*(const Vec3f&vec, const Matrix33&mat)
{
	Vec3f ret(vec[0]*mat[0][0]+vec[1]*mat[1][0]+vec[2]*mat[2][0],
			  vec[0]*mat[0][1]+vec[1]*mat[1][1]+vec[2]*mat[2][1],
			  vec[0]*mat[0][2]+vec[1]*mat[1][2]+vec[2]*mat[2][2]);
		return ret;
}


Vec3f operator*(const Matrix33&mat, const Vec3f&vec)
{
	Vec3f ret(vec[0]*mat[0][0]+vec[1]*mat[0][1]+vec[2]*mat[0][2],
			  vec[0]*mat[1][0]+vec[1]*mat[1][1]+vec[2]*mat[1][2],
			  vec[0]*mat[2][0]+vec[1]*mat[2][1]+vec[2]*mat[2][2]);
		return ret;
}


} // namespace vgm
