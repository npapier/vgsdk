// VGSDK - Copyright (C) 2008, Pierre-Jean Bensoussan, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Pierre-Jean Bensoussan
// Author Nicolas Papier

#include "vgAlg/node/VertexShape.hpp"

#include <vgd/node/VertexShape.hpp>



namespace vgAlg
{

namespace node
{



void invertPrimitiveOrientation( vgd::Shp< vgd::node::VertexShape > vertexShape )
{
	vgd::field::EditorRW< vgd::field::MFUInt32 > vertexIndexRW = vertexShape->getFVertexIndexRW();
	vgd::field::EditorRO< vgd::field::TMultiField< vgd::node::Primitive > > primitiveRO = vertexShape->getFPrimitiveRO();

	int32 j = 0;

	// For each primitive, do
	for (uint32 i = 0; i < primitiveRO->size(); i++)
	{
		vgd::node::Primitive curPrim = (*primitiveRO)[i];

		if (curPrim.getType() == vgd::node::Primitive::TRIANGLES)
		{
			int32 numTris = curPrim.getNumIndices() / 3;
			
			for(int32 i = 0; i < numTris; i++)
			{
				// Retrieves indices
				const int32 indexA = (*vertexIndexRW)[j];
				//	const int32 indexB = (*vertexIndexRW)[j+1];
				const int32 indexC = (*vertexIndexRW)[j+2];

				// Reverses the orientation
				(*vertexIndexRW)[j]		= indexC;
				//	(*vertexIndexRW)[j+1]	= indexB;
				(*vertexIndexRW)[j+2]	= indexA;

				j += 3;
			}
		}
		else if (curPrim.getType() == vgd::node::Primitive::QUADS)
		{
			int32 numQuads = curPrim.getNumIndices() / 4;
			
			for(int32 i = 0; i < numQuads; i++)
			{
				// Retrieves indices
				const int32 indexA = (*vertexIndexRW)[j];
				const int32 indexB = (*vertexIndexRW)[j+1];
				const int32 indexC = (*vertexIndexRW)[j+2];
				const int32 indexD = (*vertexIndexRW)[j+3];

				// Reverses the orientation
				//	(*vertexIndexRW)[j]		= indexA;
				(*vertexIndexRW)[j+1]	= indexD;
				//	(*vertexIndexRW)[j+2]	= indexC;
				(*vertexIndexRW)[j+3]	= indexB;

				j += 4;
			}
		}
		else
		{
			assert( false && "Unsupported primitive type" );
		}
	}
}



} // namespace node

} // namespace vgAlg
