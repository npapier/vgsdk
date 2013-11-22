// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgAlg/intersect/helpers.hpp"

#include <limits>
#include "vgAlg/node/TriSet.hpp"
#include <vgDebug/helpers.hpp>
#include <vgd/node/VertexShape.hpp>
#include <vgm/Line.hpp>
#include <vgm/Plane.hpp>
#include <vgm/Segment.hpp>
#include <vgm/Sphere.hpp>
#include <vgm/Triangle.hpp>



namespace vgAlg
{

namespace intersect
{


const bool getTriangle( const vgm::Vec3f& P, const vgd::node::VertexShape * vertexShape,
	vgm::TriangleExt& oABC, float& oDistance )
{
	bool retVal = false;

	// check precond on vertex shape
	const bool onlyTriangles = vgAlg::node::isATriSet(vertexShape);
	if ( !onlyTriangles )
	{
		vgLogDebug("getHitTriangle() fails. Vertex shape named '%s' contains at least one primitives different from TRIANGLES.", vertexShape->getName().c_str());
		return false;
	}

	// For each triangle,
	vgd::field::EditorRO< vgd::field::MFVec3f >		vertices	= vertexShape->getVertexRO();
	vgd::field::EditorRO< vgd::field::MFUInt >	vertexIndex	= vertexShape->getVertexIndexRO();

	float distanceMin = std::numeric_limits< float >::max();

	const uint	iEndTriangle	= vertexIndex->size()/3;
	uint		iVI				= 0;						// (i)ndex in (V)ertex (I)ndex array
	for( uint iTriangle=0; iTriangle < iEndTriangle; ++iTriangle )
	{
		const uint iA = (*vertexIndex)[iVI++];
		const uint iB = (*vertexIndex)[iVI++];
		const uint iC = (*vertexIndex)[iVI++];

		const vgm::Vec3f A = (*vertices)[iA];
		const vgm::Vec3f B = (*vertices)[iB];
		const vgm::Vec3f C = (*vertices)[iC];

		const vgm::Plane ABC(A,B,C);
		const vgm::Vec3f normalABC = ABC.getNormal();

		const float distanceABCAndP( ABC.distance( P ) );
		const vgm::Vec3f PInABC = ABC.project(P);

		vgm::Vec2f oBarycentricCoordOfP;
		const bool hasIntersect = isPointPInTriangleABC( PInABC, A, B, C, oBarycentricCoordOfP );

		if ( hasIntersect )
		{
			const float absDistanceABCAndP = fabs(distanceABCAndP);
			if ( absDistanceABCAndP < distanceMin )
			{
				retVal = true;
				distanceMin = absDistanceABCAndP;
				const vgm::Vec3f baryCoordOfP( oBarycentricCoordOfP[0], oBarycentricCoordOfP[1], std::numeric_limits<float>::max() );
				oABC.setValue( A, B, C, baryCoordOfP, vgm::Vec3i(iA, iB, iC) );
			}
			//else nothing to do
		}
		//else nothing to do
	}

	//vgLogDebug("distanceMin=%f", distanceMin);
	oDistance = distanceMin;
	return retVal;
}



const bool isPointPInTriangleABC(	const vgm::Vec3f P, const vgm::Vec3f A, const vgm::Vec3f B, const vgm::Vec3f C,
									vgm::Vec2f& oBarycentricCoordP )
{
	// see http://www.blackpawn.com/texts/pointinpoly/default.html

/*#ifdef _DEBUG
	vgAssert( vgm::Plane(A,B,C).isIn(P) );
#endif*/

	// Compute vectors
	const vgm::Vec3f v0 = C - A;
	const vgm::Vec3f v1 = B - A;
	const vgm::Vec3f v2 = P - A;

	// Compute dot products
	const float dot00 = v0.dot(v0);
	const float dot01 = v0.dot(v1);
	const float dot02 = v0.dot(v2);
	const float dot11 = v1.dot(v1);
	const float dot12 = v1.dot(v2);

	// Compute barycentric coordinates
	const float invDenom = 1.f / (dot00 * dot11 - dot01 * dot01);
	const float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
	const float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

	oBarycentricCoordP.setValue( v, u );

	// Check if point is in triangle
	return (u >= 0) && (v >= 0) && (u + v <= 1);
}


const bool getTriangles(	const vgd::node::VertexShape * vertexShape, const vgm::Sphere& sphere,
							std::vector< uint32 >& oTrianglesIndices )
{
	// check precond on vertex shape
	const bool onlyTriangles = vgAlg::node::isATriSet(vertexShape);
	if ( !onlyTriangles )
	{
		vgLogDebug("getTriangles() fails. Vertex shape named '%s' contains at least one primitives different from TRIANGLES.", vertexShape->getName().c_str());
		return false;
	}

	// For each triangle,
	vgd::field::EditorRO< vgd::field::MFVec3f >		vertices	= vertexShape->getVertexRO();
	vgd::field::EditorRO< vgd::field::MFUInt >	vertexIndex	= vertexShape->getVertexIndexRO();

	const uint	iEndTriangle	= vertexIndex->size()/3;
	uint		iVI				= 0;						// (i)ndex in (V)ertex (I)ndex array
	for( uint iTriangle=0; iTriangle < iEndTriangle; ++iTriangle )
	{
		const uint iA = (*vertexIndex)[iVI++];
		const uint iB = (*vertexIndex)[iVI++];
		const uint iC = (*vertexIndex)[iVI++];

		const vgm::Vec3f A = (*vertices)[iA];
		const vgm::Vec3f B = (*vertices)[iB];
		const vgm::Vec3f C = (*vertices)[iC];

		const vgm::Plane ABC(A,B,C);

		// First criterion
		const float distanceABCAndSphereCenter( ABC.distance( sphere.getCenter() ) );
		const float absDistanceABCAndSphereCenter = fabs(distanceABCAndSphereCenter);
		if ( absDistanceABCAndSphereCenter <= sphere.getRadius() )
		{
			if ( sphere.isIn(A) || sphere.isIn(B) || sphere.isIn(C) )
			{
				oTrianglesIndices.push_back( iA );
				oTrianglesIndices.push_back( iB );
				oTrianglesIndices.push_back( iC );
				continue;
			}

			// 
			const vgm::Vec3f i1 = sphere.intersect( vgm::Line(A,B) );
			const vgm::Segment AB(A,B);
			if ( i1.isValid() && AB.isIn(i1) )
			{
				oTrianglesIndices.push_back( iA );
				oTrianglesIndices.push_back( iB );
				oTrianglesIndices.push_back( iC );
				continue;
			}

			const vgm::Vec3f i2 = sphere.intersect( vgm::Line(B,C) );
			const vgm::Segment BC(B,C);
			if ( i2.isValid() && BC.isIn(i2) )
			{
				oTrianglesIndices.push_back( iA );
				oTrianglesIndices.push_back( iB );
				oTrianglesIndices.push_back( iC );
				continue;
			}

			const vgm::Vec3f i3 = sphere.intersect( vgm::Line(C,A) );
			const vgm::Segment CA(C,A);
			if ( i3.isValid() && CA.isIn(i3) )
			{
				oTrianglesIndices.push_back( iA );
				oTrianglesIndices.push_back( iB );
				oTrianglesIndices.push_back( iC );
				continue;
			}
		}
	}

	return oTrianglesIndices.size() > 0;
}


const bool getTriangles(	const vgd::node::VertexShape * vertexShape, const std::vector< uint32 >& trianglesIndicesToFilter,
							const vgm::Plane& plane,
							std::vector< uint32 >& oTrianglesIndices )
{
	// check precond on vertex shape
	const bool onlyTriangles = vgAlg::node::isATriSet(vertexShape);
	if ( !onlyTriangles )
	{
		vgLogDebug("getTriangles() fails. Vertex shape named '%s' contains at least one primitives different from TRIANGLES.", vertexShape->getName().c_str());
		return false;
	}

	// For each triangle,
	vgd::field::EditorRO< vgd::field::MFVec3f >		vertices	= vertexShape->getVertexRO();
	vgd::field::EditorRO< vgd::field::MFUInt >	vertexIndex	= vertexShape->getVertexIndexRO();

	std::vector< uint32 >::const_iterator i;
	std::vector< uint32 >::const_iterator iEnd;

	if ( trianglesIndicesToFilter.size() == 0 )
	{
		// Iterate on vertexIndex field
		i		= vertexIndex->begin();
		iEnd	= vertexIndex->end();
	}
	else
	{
		// Iterate on trianglesIndicesToFilter
		i		= trianglesIndicesToFilter.begin();
		iEnd	= trianglesIndicesToFilter.end();
	}
	vertexIndex.release();

	while ( i != iEnd  )
	{
		const uint iA = *i;
		++i;
		const uint iB = *i;
		++i;
		const uint iC = *i;
		++i;

		const vgm::Vec3f A = (*vertices)[iA];
		const vgm::Vec3f B = (*vertices)[iB];
		const vgm::Vec3f C = (*vertices)[iC];

		// Test criterion
		if (	plane.isInHalfSpace( A ) ||
				plane.isInHalfSpace( B ) ||
				plane.isInHalfSpace( C )	)
		{
				oTrianglesIndices.push_back( iA );
				oTrianglesIndices.push_back( iB );
				oTrianglesIndices.push_back( iC );
				continue;
		}
		// else nothing to do
	}

	return true;
}


} // namespace intersect

} // namespace vgAlg
