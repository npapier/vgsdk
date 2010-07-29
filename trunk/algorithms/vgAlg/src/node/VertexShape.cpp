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
				//const int32 indexA = (*vertexIndexRW)[j];
				const int32 indexB = (*vertexIndexRW)[j+1];
				//const int32 indexC = (*vertexIndexRW)[j+2];
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



void invertNormalOrientation( vgd::Shp< vgd::node::VertexShape > vertexShape )
{
	vgd::field::EditorRW< vgd::field::MFVec3f >	normals = vertexShape->getFNormalRW();

	for( uint i = 0; i < normals->size(); ++i )
	{
		(*normals)[i].negate();
	}
}



void triangulate( vgd::Shp< vgd::node::VertexShape > vertexShape )
{
	vgd::field::EditorRW< vgd::field::MFUInt32 > vertexIndexRW = vertexShape->getFVertexIndexRW();
	std::vector< uint32 > newVertexIndexRW;

	vgd::field::EditorRW< vgd::field::TMultiField< vgd::node::Primitive > > primitiveRW = vertexShape->getFPrimitiveRW();

	int32 j = 0;
	int32 k = 0;

	// For each primitive, do
	for (uint32 i = 0; i < primitiveRW->size(); i++)
	{
		vgd::node::Primitive curPrim = (*primitiveRW)[i];
		if (curPrim.getType() == vgd::node::Primitive::TRIANGLES)
		{
			int32 numIndices = curPrim.getNumIndices();

			for(int32 indice = 0; indice < numIndices; indice++)
			{
				// Retrieves indices and add it to new vertex index vector.
				const int32 index = (*vertexIndexRW)[j];
				newVertexIndexRW.push_back( index );

				++j;
				++k;
			}

		}
		else if (curPrim.getType() == vgd::node::Primitive::QUADS)
		{
			int32 numQuads = curPrim.getNumIndices() / 4;

			for(int32 indice = 0; indice < numQuads; indice++)
			{
				// Retrieves indices, create 2 triangle with the quad, and add them to new vertex index vector.
				const int32 indexA = (*vertexIndexRW)[j];
				const int32 indexB = (*vertexIndexRW)[j+1];
				const int32 indexC = (*vertexIndexRW)[j+2];
				const int32 indexD = (*vertexIndexRW)[j+3];

				newVertexIndexRW.push_back( indexA );
				newVertexIndexRW.push_back( indexB );
				newVertexIndexRW.push_back( indexC );

				newVertexIndexRW.push_back( indexA );
				newVertexIndexRW.push_back( indexC );
				newVertexIndexRW.push_back( indexD );

				j += 4;
				k += 6;
			}

		}
		else
		{
			assert( false && "Unsupported primitive type" );
		}
	}

	//clear primitive list and create an unique triangle primitive.
	vgd::node::Primitive newPrim;
	newPrim.setIndex( 0 );
	newPrim.setType( vgd::node::Primitive::TRIANGLES );
	newPrim.setNumIndices( k );
	(*primitiveRW).clear();
	(*primitiveRW).push_back( newPrim );

	vertexIndexRW->swap( newVertexIndexRW );
}



} // namespace node

} // namespace vgAlg

