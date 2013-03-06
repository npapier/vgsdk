// VGSDK - Copyright (C) 2007, 2008, 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgAlg/node/TriSet.hpp"

#include <vgd/node/TriSet.hpp>



namespace vgAlg
{

namespace node
{



const bool isATriSet( const vgd::node::VertexShape * vertexShape )
{
	vgd::field::EditorRO< vgd::field::TMultiField< vgd::node::Primitive > > primitiveRO = vertexShape->getFPrimitiveRO();

	// For each primitive, do
	for (uint32 i = 0; i < primitiveRO->size(); ++i)
	{
		const vgd::node::Primitive curPrim = (*primitiveRO)[i];

		if (curPrim.getType() != vgd::node::Primitive::TRIANGLES)
		{
			return false;
		}
	}
	return true;
}



void invertTriangleOrientation( vgd::Shp< vgd::node::TriSet > triset )
{
	vgd::field::EditorRW< vgd::field::MFUInt32 >	vertexIndex	= triset->getFVertexIndexRW();

	const int32 numTris = vertexIndex->size()/3;	//< number of triangles

	// For each triangle, do
	for(int32 j=0, i=0; i < numTris; i++)
	{
		// Retrieves indices
		const int32 indexA = (*vertexIndex)[j];
		//const int32 indexB = (*vertexIndex)[j+1];
		const int32 indexC = (*vertexIndex)[j+2];

		// Reverses the triangle orientation
		(*vertexIndex)[j]	= indexC;
		//(*vertexIndex)[j+1]	= indexB;
		(*vertexIndex)[j+2]	= indexA;

		j += 3;
	}
}



} // namespace node

} // namespace vgAlg
