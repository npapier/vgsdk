// VGL - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier



template< typename T, int32 N >
Vector<T,N>::Vector( void )
{
}



template< typename T, int32 N >
Vector<T,N>::Vector( const T* v )
{
	setValue( v );
}



template< typename T, int32 N >
Vector<T,N>::Vector( const Vector& v )
{
	setValue( v );
}



template< typename T, int32 N >
Vector<T,N>& Vector<T,N>::operator=( const Vector& v )
{
	if ( this != &v )
	{
		setValue( v );
	}
	
	return ( *this );
}



template< typename T, int32 N >
Vector<T,N>::Vector( Plane& p0, Plane& p1, Plane& p2)
{
#define DELTA 1e-6	
#define DET3(m) (( 			\
    m[0][0] * m[1][1] * m[2][2]	\
  + m[0][1] * m[1][2] * m[2][0]	\
  + m[0][2] * m[1][0] * m[2][1]	\
  - m[2][0] * m[1][1] * m[0][2]	\
  - m[2][1] * m[1][2] * m[0][0]	\
  - m[2][2] * m[1][0] * m[0][1]))

	float	v[3], del, mx[3][3], mi[3][3];
	
	// create 3x3 matrix of normal coefficients
	mx[0][0] = p0.getNormal()[0];
	mx[0][1] = p0.getNormal()[1];
	mx[0][2] = p0.getNormal()[2];
	mx[1][0] = p1.getNormal()[0];
	mx[1][1] = p1.getNormal()[1];
	mx[1][2] = p1.getNormal()[2];
	mx[2][0] = p2.getNormal()[0];
	mx[2][1] = p2.getNormal()[1];
	mx[2][2] = p2.getNormal()[2];

	// find determinant of matrix to use for divisor
	del = DET3(mx);

	//    printf("mx = %10.5f %10.5f %10.5f\n", mx[0][0], mx[0][1], mx[0][2]);
	//    printf("     %10.5f %10.5f %10.5f\n", mx[1][0], mx[1][1], mx[1][2]);
	//    printf("     %10.5f %10.5f %10.5f\n", mx[2][0], mx[2][1], mx[2][2]);
	if (del > -DELTA && del < DELTA)
	{	
		// if singular, just set to the origin
		vec[0] = 0;
		vec[1] = 0;
		vec[2] = 0;
	}
	else 
	{
		v[0] = p0.getDistanceFromOrigin();
		v[1] = p1.getDistanceFromOrigin();
		v[2] = p2.getDistanceFromOrigin();
		
		//	printf("v = %10.5f\n    %10.5f\n    %10.5f\n", v[0], v[1], v[2]);

		mi[0][0] = v[0]; mi[0][1] = mx[0][1]; mi[0][2] = mx[0][2];
		mi[1][0] = v[1]; mi[1][1] = mx[1][1]; mi[1][2] = mx[1][2];
		mi[2][0] = v[2]; mi[2][1] = mx[2][1]; mi[2][2] = mx[2][2];
		
		//	printf("mi = %10.5f %10.5f %10.5f\n", mi[0][0], mi[0][1], mi[0][2]);
		//	printf("     %10.5f %10.5f %10.5f\n", mi[1][0], mi[1][1], mi[1][2]);
		//	printf("     %10.5f %10.5f %10.5f\n", mi[2][0], mi[2][1], mi[2][2]);
		
		vec[0] = DET3(mi) / del;
		mi[0][0] = mx[0][0]; mi[0][1] = v[0]; mi[0][2] = mx[0][2];
		mi[1][0] = mx[1][0]; mi[1][1] = v[1]; mi[1][2] = mx[1][2];
		mi[2][0] = mx[2][0]; mi[2][1] = v[2]; mi[2][2] = mx[2][2];
		
		//	printf("mi = %10.5f %10.5f %10.5f\n", mi[0][0], mi[0][1], mi[0][2]);
		//	printf("     %10.5f %10.5f %10.5f\n", mi[1][0], mi[1][1], mi[1][2]);
		//	printf("     %10.5f %10.5f %10.5f\n", mi[2][0], mi[2][1], mi[2][2]);
		
		vec[1] = DET3(mi) / del;
		mi[0][0] = mx[0][0]; mi[0][1] = mx[0][1]; mi[0][2] = v[0];
		mi[1][0] = mx[1][0]; mi[1][1] = mx[1][1]; mi[1][2] = v[1];
		mi[2][0] = mx[2][0]; mi[2][1] = mx[2][1]; mi[2][2] = v[2];
		
		//	printf("mi = %10.5f %10.5f %10.5f\n", mi[0][0], mi[0][1], mi[0][2]);
		//	printf("     %10.5f %10.5f %10.5f\n", mi[1][0], mi[1][1], mi[1][2]);
		//	printf("     %10.5f %10.5f %10.5f\n", mi[2][0], mi[2][1], mi[2][2]);

		vec[2] = DET3(mi) / del;
	}
	//printf("%10.5f %10.5f %10.5f\n", vec[0], vec[1], vec[2]);
#undef DET3
#undef DELTA
}



template< typename T, int32 N >
const T* Vector<T,N>::getValue( void ) const
{
	return ( m_tCoord );
}



template< typename T, int32 N >
T* Vector<T,N>::getValue( void )
{
	return ( m_tCoord );
}



template< typename T, int32 N >
void Vector<T,N>::setValue( const T* v )
{
	for (int32 i=0; i<N; i++)
	{
		m_tCoord[i] = v[i];
	}
}



template< typename T, int32 N >
void Vector<T, N>::setValue( const Vector& v)
{
	for (int32 i=0; i<N; i++)
	{
		m_tCoord[i] = v.m_tCoord[i];
	}
}



template< typename T, int32 N >
T& Vector<T, N>::operator []( int32 i )
{
	return ( m_tCoord[i] );
}



template< typename T, int32 N >
const T& Vector<T, N>::operator []( int32 i ) const
{
	return ( m_tCoord[i] );
}



template< typename T, int32 N >
void Vector<T,N>::null( void )
{
	for (int32 i =0; i<N; i++)
	{
		m_tCoord[i]= (T)0;
	}
}



template< typename T, int32 N >
const bool Vector<T,N>::isNull( void ) const
{
	for (int32 i =0; i<N; i++)
	{
		if ( m_tCoord[i] != (T)0 )
		{
			return false;
		}
	}
	return true;
}



template< typename T, int32 N >
Vector<T,N> Vector<T,N>::operator+( const Vector& v ) const
{
	Vector res;
	for (int32 i =0; i<N; i++)
	{
		res.m_tCoord[i] = m_tCoord[i] + v.m_tCoord[i];
	}

	return res;
}



template< typename T, int32 N>
Vector<T,N> Vector<T,N>::operator-( const Vector& v ) const
{
	Vector res;
	for (int32 i =0; i<N; i++)
	{
		res.m_tCoord[i] = m_tCoord[i] - v.m_tCoord[i];
	}

	return res;
}



template< typename T, int32 N >
Vector<T,N> operator *( const Vector<T,N>& v, const T pScal )
{
	Vector<T,N> rv = v;
	rv *= pScal;

	return rv;
}



template< typename T, int32 N >
Vector<T,N> operator *( const T pScal, const Vector<T,N>& v )
{
	Vector<T,N> rv = v;
	rv *= pScal;

	return rv;
}





template< typename T, int32 N >
Vector<T,N> operator /( const Vector<T,N>& v, const T pScal )
{
	Vector<T,N> rv = v;
	rv /= pScal;

	return rv;
}



template< typename T, int32 N >
Vector<T,N> operator /( const T pScal, const Vector<T,N>& v )
{
	Vector<T,N> rv = v;
	rv /= pScal;

	return rv;
}



template< typename T, int32 N >
Vector<T,N> Vector<T,N>::operator -( void ) const
{
	Vector v;

	for (int32 i =0; i<N; i++)
	{
		v.m_tCoord[i] = -m_tCoord[i];
	}

	return v;
}



template< typename T, int32 N >
void Vector<T,N>::negate( void )
{
	for (int32 i =0; i<N; i++)
	{
		m_tCoord[i] = -m_tCoord[i];
	}
}



template< typename T, int32 N >
Vector<T,N>& Vector<T,N>::operator +=( const Vector& v )
{
	for (int32 i =0; i<N; i++)
	{
		m_tCoord[i] += v.m_tCoord[i];
	}

	return ( *this );
}



template< typename T, int32 N >
Vector<T,N>& Vector<T,N>::operator -=( const Vector& v )
{
	for (int32 i =0; i<N; i++)
	{
		m_tCoord[i] -= v.m_tCoord[i];
	}

	return ( *this );
}



template< typename T, int32 N >
Vector<T,N>& Vector<T,N>::operator *=( T d )
{
	for (int32 i =0; i<N; i++)
	{
		m_tCoord[i] *= d;
	}

	return ( *this );
}



template< typename T, int32 N >
Vector<T,N>& Vector<T,N>::operator /=( T d )
{
	assert( d != 0 );

	for (int32 i =0; i<N; i++)
	{
		m_tCoord[i] /= d;
	}

	return ( *this );
}



template< typename T, int32 N >
T Vector<T,N>::getSqrLength( void ) const
{
	T total = 0;

	for (int32 i =0; i<N; i++)
	{
		total +=  m_tCoord[i] * m_tCoord[i];
	}

	return total;
}



template< typename T, int32 N >
T Vector<T,N>::getLength( void ) const
{
	double racine;

	racine = sqrt( (double)getSqrLength() );

	return ( static_cast< T >(racine) );
}



template< typename T, int32 N >
T Vector<T,N>::normalize( void )
{
	T l = getLength();

	if ( l != 0.0 )
	{
		*this /= l;
	}

	return ( l );
}



template< typename T, int32 N >
Vector<T,N> Vector<T,N>::getNormalized( void ) const
{
	Vector v = *this;

	v.normalize();

	return ( v );
}



template< typename T, int32 N >
float Vector<T,N>::dot( const Vector& v ) const
{
	float retVal = 0.f;
	
	for( int32 i=0; i<N; i++)
	{
		retVal += this->m_tCoord[i] * v.m_tCoord[i];
	}
	
	return ( retVal );
}



template< typename T, int32 N >
Vector<T,N> Vector<T,N>::getClosestAxis() const
{
	Vec3f	axis(0.0, 0.0, 0.0), bestAxis;
	float	d, max = -21.234;

#define TEST_AXIS()						\
	if ((d = dot(axis)) > max) {		\
	max = d;							      \
	bestAxis = axis;						\
	}

	axis[0] = 1.0;	// +x axis
	TEST_AXIS();

	axis[0] = -1.0;	// -x axis
	TEST_AXIS();
	axis[0] = 0.0;
	
	axis[1] = 1.0;	// +y axis
	TEST_AXIS();
	
	axis[1] = -1.0;	// -y axis
	TEST_AXIS();
	axis[1] = 0.0;

	axis[2] = 1.0;	// +z axis
	TEST_AXIS();
	
	axis[2] = -1.0;	// -z axis
	TEST_AXIS();
	
#undef TEST_AXIS
	
	return bestAxis;
}



template< typename T, int32 N >
void Vector<T,N>::projectOnSphere( const float radius )
{
	assert( N == 3 );

	float rsqr;
	float dsqr;

	rsqr = radius * radius;
	dsqr = m_tCoord[0]*m_tCoord[0] + m_tCoord[1]*m_tCoord[1];

	if( dsqr < (rsqr*0.5f) )
	{
		m_tCoord[2] = sqrt( rsqr - dsqr );
	}
	else
	{
		m_tCoord[2] = rsqr / ( 2.f * sqrt(dsqr) );
	}
}



template< typename T, int32 N >
bool Vector<T,N>::operator==( const Vector& v2 ) const
{
	for (int32 i=0; i<N; i++)
	{
		if (v2.m_tCoord[i] != m_tCoord[i])
		{
			return false;
		}
	}

	return true;
}



template< typename T, int32 N >
bool Vector<T,N>::operator!=( const Vector& v2 ) const
{
	for (int32 i =0; i<N; i++)
	{
		if (v2.m_tCoord[i] != m_tCoord[i])
		{
			return true;
		}
	}

	return false;
}



template< typename T, int32 N >
bool Vector<T,N>::equals( const Vector& v, const float tolerance ) const
{
	Vector	diff = *this - v;

	return ( diff.dot(diff) <= tolerance );
}
