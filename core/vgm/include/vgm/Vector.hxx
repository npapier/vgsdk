// VGSDK - Copyright (C) 2004, 2006, 2007, 2008, 2009, 2010, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier



template< typename T, int N >
Vector<T,N>::Vector()
{}



template< typename T, int N >
Vector<T,N>::Vector( const T* v )
{
	setValue( v );
}



template< typename T, int N >
template< typename InType >
Vector<T,N>::Vector( const InType* v )
{
	setValue( v );
}



template< typename T, int N >
Vector<T,N>::Vector( const Vector& v )
{
	setValue( v );
}



template< typename T, int N >
Vector<T,N>& Vector<T,N>::operator=( const Vector& v )
{
	if ( this != &v )
	{
		setValue( v );
	}
	
	return ( *this );
}



template< typename T, int N >
const T* Vector<T,N>::getValue( void ) const
{
	return m_tCoord;
}



template< typename T, int N >
T* Vector<T,N>::getValue( void )
{
	return m_tCoord;
}



template< typename T, int N >
void Vector<T,N>::setValue( const T* v )
{
	for (int32 i=0; i<N; i++)
	{
		m_tCoord[i] = v[i];
	}
}



template< typename T, int N >
template< typename InType >
void Vector<T,N>::setValue( const InType* v )
{
	for (int32 i=0; i<N; i++)
	{
		m_tCoord[i] = static_cast< T >( v[i] );
	}
}



template< typename T, int N >
void Vector<T, N>::setValue( const Vector& v )
{
	for (int32 i=0; i<N; i++)
	{
		m_tCoord[i] = v.m_tCoord[i];
	}
}



template< typename T, int N >
T& Vector<T, N>::operator []( int32 i )
{
	return m_tCoord[i];
}



template< typename T, int N >
const T& Vector<T, N>::operator []( int32 i ) const
{
	return m_tCoord[i];
}



template< typename T, int N >
void Vector<T,N>::null( void )
{
	for (int32 i =0; i<N; i++)
	{
		m_tCoord[i]= (T)0;
	}
}



template< typename T, int N >
void Vector<T,N>::setNull( void )
{
	for (int32 i =0; i<N; i++)
	{
		m_tCoord[i]= (T)0;
	}
}



template< typename T, int N >
const Vector<T,N> Vector<T,N>::getNull()
{
	Vector<T,N>	vector;
	vector.setNull();

	return vector;
}


template< typename T, int N >
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



template< typename T, int N >
void Vector<T,N>::setInvalid( void )
{
	const T tMax = std::numeric_limits< T >::max();
	
	for( int32 i = 0; i<N; i++)
	{
		m_tCoord[i] = tMax;
	}
}



template< typename T, int N >
const Vector<T,N> Vector<T,N>::getInvalid()
{
	Vector<T,N>	vector;
	
	vector.setInvalid();
	return vector;
}



template< typename T, int N >
const bool Vector<T,N>::isInvalid( void ) const
{
	const T tMax	= std::numeric_limits< T >::max();
	bool	invalid	= false;
	
	for (int32 i = 0; i<N && invalid==false; i++)
	{
		invalid = (m_tCoord[i] == tMax);
	}
	return invalid;
}



template< typename T, int N >
const bool Vector<T,N>::isValid( void ) const
{
	return !isInvalid();
}



template< typename T, int N >
Vector<T,N> Vector<T,N>::operator+( const Vector& v ) const
{
	Vector res;
	for (int32 i =0; i<N; i++)
	{
		res.m_tCoord[i] = m_tCoord[i] + v.m_tCoord[i];
	}

	return res;
}



template< typename T, int N>
Vector<T,N> Vector<T,N>::operator-( const Vector& v ) const
{
	Vector res;
	for (int32 i =0; i<N; i++)
	{
		res.m_tCoord[i] = m_tCoord[i] - v.m_tCoord[i];
	}

	return res;
}



template< typename T, int N >
Vector<T,N> operator *( const Vector<T,N>& v, const T pScal )
{
	Vector<T,N> rv = v;
	rv *= pScal;

	return rv;
}



template< typename T, int N >
Vector<T,N> operator *( const T pScal, const Vector<T,N>& v )
{
	Vector<T,N> rv = v;
	rv *= pScal;

	return rv;
}



template< typename T, int N >
Vector<T,N> operator /( const Vector<T,N>& v, const T pScal )
{
	Vector<T,N> rv = v;
	rv /= pScal;

	return rv;
}



template< typename T, int N >
Vector<T,N> operator /( const T pScal, const Vector<T,N>& v )
{
	Vector<T,N> rv = v;
	rv /= pScal;

	return rv;
}



template< typename T, int N >
Vector<T,N> Vector<T,N>::operator -( void ) const
{
	Vector v;

	for (int32 i =0; i<N; i++)
	{
		v.m_tCoord[i] = -m_tCoord[i];
	}

	return v;
}



template< typename T, int N >
void Vector<T,N>::negate( void )
{
	for (int32 i =0; i<N; i++)
	{
		m_tCoord[i] = -m_tCoord[i];
	}
}



template< typename T, int N >
Vector<T,N>& Vector<T,N>::operator +=( const Vector& v )
{
	for (int32 i =0; i<N; i++)
	{
		m_tCoord[i] += v.m_tCoord[i];
	}

	return *this;
}



template< typename T, int N >
Vector<T,N>& Vector<T,N>::operator -=( const Vector& v )
{
	for (int32 i =0; i<N; i++)
	{
		m_tCoord[i] -= v.m_tCoord[i];
	}

	return *this;
}



template< typename T, int N >
Vector<T,N>& Vector<T,N>::operator *=( T d )
{
	for (int32 i =0; i<N; i++)
	{
		m_tCoord[i] *= d;
	}

	return *this;
}



template< typename T, int N >
Vector<T,N>& Vector<T,N>::operator /=( T d )
{
	assert( d != 0 );

	for (int32 i =0; i<N; i++)
	{
		m_tCoord[i] /= d;
	}

	return *this;
}



template< typename T, int N >
T Vector<T,N>::getSqrLength( void ) const
{
	T total = 0;

	for (int32 i =0; i<N; i++)
	{
		total +=  m_tCoord[i] * m_tCoord[i];
	}

	return total;
}



template< typename T, int N >
T Vector<T,N>::getLength( void ) const
{
	double racine;

	racine = sqrt( (double)getSqrLength() );

	return static_cast< T >(racine);
}



template< typename T, int N >
T Vector<T,N>::normalize( void )
{
	const T length = getLength();

	if ( length != static_cast<T>(0) )
	{
		*this /= length;
	}

	return length;
}



template< typename T, int N >
Vector<T,N> Vector<T,N>::getNormalized( void ) const
{
	Vector v = *this;

	v.normalize();

	return v;
}



template< typename T, int N >
float Vector<T,N>::dot( const Vector& v ) const
{
	float retVal = 0.f;
	
	for( int32 i=0; i<N; i++)
	{
		retVal += this->m_tCoord[i] * v.m_tCoord[i];
	}
	
	return retVal;
}



template< typename T, int N >
const float Vector<T,N>::getAngle( const Vector& v ) const
{
	const Vector a = getNormalized();
	const Vector b = v.getNormalized();

	const float dotValue = a.dot(b);

	// Preconditions for acos
/*	assert( -1.f <= dotValue + vgm::Epsilon<float>::value() && "Out of range (for acos)" );
	assert( dotValue - vgm::Epsilon<float>::value() <= 1.f && "Out of range (for acos)" );*/

	const float dotValueClamped = vgm::clamp(dotValue, -1.f, 1.f);

	return std::acos( dotValueClamped );
}



template< typename T, int N >
const bool Vector<T,N>::isCollinear( const Vector& v, const float tolerance ) const
{
	return cross(v).equals( getNull(), tolerance );
}



template< typename T, int N >
Vector<T,N> Vector<T,N>::getClosestAxis() const
{
	Vec3f	axis(0.0, 0.0, 0.0), bestAxis;
	float	d, max = -21.234;

#define TEST_AXIS()						\
	if ((d = dot(axis)) > max) {		\
	max = d;							\
	bestAxis = axis;					\
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



template< typename T, int N >
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



template< typename T, int N >
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



template< typename T, int N >
bool Vector<T,N>::operator!=( const Vector& v2 ) const
{
/*	const bool retVal = (*this) == v2;
	return !retVal;*/

	for (int32 i =0; i<N; i++)
	{
		if (v2.m_tCoord[i] != m_tCoord[i])
		{
			return true;
		}
	}

	return false;
}



template< typename T, int N >
bool Vector<T,N>::equals( const Vector& v, const float tolerance ) const
{
	Vector	diff = *this - v;

	return ( diff.dot(diff) <= tolerance );
}



template< typename Out, typename In, int32 InSize >
const std::vector< Out > vector_cast( const Vector< In, InSize > & in )
{
	std::vector< Out >	out( InSize );

	for( int32 i = 0; i != InSize; ++i )
	{
		out[i] = static_cast< Out >( in[i] );
	}

	return out;
}



template< typename Out, int32 OutSize, typename In >
const Vector< Out, OutSize > vector_cast( const std::vector< In > & in )
{
	Vector< Out, OutSize >	out;

	const uint minSize = std::min( OutSize, in.size() );

	for( uint i = 0; i != minSize; ++i )
	{
		out[i] = static_cast< Out >( in[i] );
	}

	return out;
}



template< typename Out, int OutSize, typename In, int InSize >
const vgm::Vector< Out, OutSize > VectorCast( const Vector< In, InSize > & in )
{
	vgm::Vector< Out, OutSize > out;

	const uint minSize = std::min( OutSize, InSize );

	for( uint i = 0; i < minSize; ++i )
	{
		out[i] = static_cast< Out >( in[i] );
	}

	return out;
}
