// VGSDK - Copyright (C) 2007, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgAlg/node/TriSet.hpp"

#include <vgd/node/TriSet.hpp>



namespace vgAlg
{

namespace node
{



void invertTriangleOrientation( vgd::Shp< vgd::node::TriSet > triset )
{
	vgd::field::EditorRW< vgd::field::MFUInt32 >	vertexIndex	= triset->getFVertexIndexRW();
	
	const int32 numTris = vertexIndex->size()/3;	//< number of triangles	

	// compute vertices normals
	for(int32 j=0, i=0; i < numTris; i++)
	{
		// compute face normal
		const int32 indexA = (*vertexIndex)[j];
		//const int32 indexB = (*vertexIndex)[j+1];
		const int32 indexC = (*vertexIndex)[j+2];
		
		(*vertexIndex)[j]	= indexC;
		//(*vertexIndex)[j+1]	= indexB;
		(*vertexIndex)[j+2]	= indexA;

		j += 3;
	}
}



} // namespace node

} // namespace vgAlg
