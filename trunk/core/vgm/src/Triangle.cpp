// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgm/Triangle.hpp"



namespace vgm
{



// Triangle
Triangle::Triangle()
{}


Triangle::Triangle( const Vec3f& A, const Vec3f& B, const Vec3f& C )
{
	setValue( A, B, C );
}


void Triangle::setValue( const Vec3f& A, const Vec3f& B, const Vec3f& C )
{
	m_abc[0] = A;
	m_abc[1] = B;
	m_abc[2] = C;
}


const Vec3f& Triangle::A() const
{
	return m_abc[0];
}

const Vec3f& Triangle::getA() const
{
	return A();
}

void Triangle::setA( const Vec3f A )
{
	m_abc[0] = A;
}


const Vec3f& Triangle::B() const
{
	return m_abc[1];
}

const Vec3f& Triangle::getB() const
{
	return B();
}

void Triangle::setB( const Vec3f B )
{
	m_abc[1] = B;
}


const Vec3f& Triangle::C() const
{
	return m_abc[2];
}

const Vec3f& Triangle::getC() const
{
	return m_abc[2];
}

void Triangle::setC( const Vec3f C )
{
	m_abc[2] = C;
}


const Vec3f Triangle::AB() const
{
	return B() - A();
}

const Vec3f Triangle::BC() const
{
	return C() - B();
}

const Vec3f Triangle::CA() const
{
	return A() - C();
}


const Vec3f Triangle::getNormal() const
{
	const vgm::Vec3f normal( AB().cross( -CA() ) );

	return normal;
}



// TriangleP
TriangleP::TriangleP()
{}


TriangleP::TriangleP( const Vec3f& A, const Vec3f& B, const Vec3f& C, const Vec3f& P )
{
	setValue( A, B, C, P );
}


void TriangleP::setValue( const Vec3f& A, const Vec3f& B, const Vec3f& C, const Vec3f& P )
{
	Triangle::setValue( A, B, C );
	m_p = P;
}


const Vec3f& TriangleP::P() const
{
	return m_p;
}

const Vec3f& TriangleP::getP() const
{
	return m_p;
}

void TriangleP::setP( const Vec3f& P )
{
	m_p = P;
}


const Vec3f TriangleP::computeCartesian( const Vec3f& baryCoord ) const
{
	if ( baryCoord[2] == std::numeric_limits<float>::max() )
	{
		const Vec3f retVal = baryCoord[0] * AB() + baryCoord[1] * BC();
		return retVal;
	}
	else
	{
		const Vec3f retVal = baryCoord[0] * A() + baryCoord[1] * B() + baryCoord[2] * C();
		return retVal;
	}
}


const Vec3f TriangleP::computeCartesian() const
{
	return computeCartesian(m_p);
}


// TriangleExt
TriangleExt::TriangleExt()
{}


TriangleExt::TriangleExt( const Vec3f& A, const Vec3f& B, const Vec3f& C, const Vec3f& P, const Vec3i& indicesOfABC )
{
	setValue( A, B, C, P, indicesOfABC );
}


void TriangleExt::setValue( const Vec3f& A, const Vec3f& B, const Vec3f& C, const Vec3f& P, const Vec3i& indicesOfABC )
{
	TriangleP::setValue( A, B, C, P );
	m_indices = indicesOfABC;
}


const Vec3i& TriangleExt::indices() const
{
	return m_indices;
}

const Vec3i& TriangleExt::getIndices() const
{
	return m_indices;
}

void TriangleExt::setIndices( const Vec3i& indices )
{
	m_indices = indices;
}


} // namespace vgm
