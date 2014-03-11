// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgAlg/vertexShape/operations.hpp"

#include <vgd/node/VertexShape.hpp>



namespace vgAlg
{

namespace vertexShape
{



vgd::Shp< vgd::node::VertexShape > createSubTriSet( const vgd::node::VertexShape * vertexShape, const std::vector< uint32 >& trianglesIndices, const bool ignoreNormals  )
{
	// inputs
	vgd::field::EditorRO< vgd::field::MFVec3f >	inVertex	= vertexShape->getFVertexRO();
	vgd::field::EditorRO< vgd::field::MFVec3f >	inNormal	= vertexShape->getFNormalRO();

	// output
	//	Create new vertex shape
	using vgd::node::VertexShape;
	vgd::Shp< VertexShape > outVertexShape = VertexShape::create("");

	vgd::field::EditorRW< vgd::field::MFVec3f >		outVertex		= outVertexShape->getFVertexRW();
	vgd::field::EditorRW< vgd::field::MFUInt32>		outVertexIndex	= outVertexShape->getFVertexIndexRW();
	vgd::field::EditorRW< vgd::field::MFPrimitive >	outPrimitive	= outVertexShape->getFPrimitiveRW();

	vgd::field::EditorRW< vgd::field::MFVec3f >		outNormal		= outVertexShape->getFNormalRW();

	// Filter the given vertex shape using triangles indices
	const bool hasNormals = ignoreNormals ? false : (vertexShape->getNormalBinding() == vgd::node::BIND_PER_VERTEX);

	for( uint i=0; i < trianglesIndices.size(); )
	{
		outVertexIndex->push_back( i );
		const int32 iA = trianglesIndices[i++];

		outVertexIndex->push_back( i );
		const int32 iB = trianglesIndices[i++];

		outVertexIndex->push_back( i );
		const int32 iC = trianglesIndices[i++];

		outVertex->push_back( (*inVertex)[iA] );
		outVertex->push_back( (*inVertex)[iB] );
		outVertex->push_back( (*inVertex)[iC] );
		if ( hasNormals )
		{
			outNormal->push_back( (*inNormal)[iA] );
			outNormal->push_back( (*inNormal)[iB] );
			outNormal->push_back( (*inNormal)[iC] );
		}
	}

	// PRIMITIVE
	vgd::node::Primitive prim( vgd::node::Primitive::TRIANGLES, 0, outVertexIndex->size() );
	outPrimitive->push_back( prim );

	return outVertexShape;
}


} // namespace vertexShape

} // namespace vgAlg
