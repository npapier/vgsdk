// VGSDK - Copyright (C) 2013, 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgm/Segment.hpp"



namespace vgm
{



Segment::Segment()
{}


Segment::Segment( const Vec3f& p0, const Vec3f& p1 )
:	m_begin	( p0 ),
	m_end	( p1 )
{}


void Segment::setValue( const Vec3f& p0, const Vec3f& p1 )
{
	m_begin	= p0;
	m_end	= p1;
}


const Vec3f& Segment::getBegin() const
{
	return m_begin;
}


const Vec3f& Segment::getEnd() const
{
	return m_end;
}


const Vec3f Segment::getDirection() const
{
	return (m_end - m_begin);
}


const bool Segment::isIn( const Vec3f& P ) const
{
	// SEGMENT AB
	const vgm::Vec3f& A = getBegin();
	const vgm::Vec3f& B = getEnd();

	// test if P is lying on AB
	const vgm::Vec3f AB = getDirection();
	const vgm::Vec3f AP = (P - A);

	const bool isCollinear = AB.isCollinear( AP );

	if ( !isCollinear )
	{
		return false;
	}
	else
	{
		float minX;
		float maxX;
		if ( A[0] < B[0] )
		{
			minX = A[0];
			maxX = B[0];
		}
		else
		{
			minX = B[0];
			maxX = A[0];
		}

		return vgm::greaterThanEqual( P[0], minX ) && vgm::lessThanEqual( P[0], maxX );
	}
}


} // namespace vgm
