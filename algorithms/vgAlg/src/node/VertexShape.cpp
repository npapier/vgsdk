// VGSDK - Copyright (C) 2008, 2012, Pierre-Jean Bensoussan, Nicolas Papier, Alexandre Di Pino.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Pierre-Jean Bensoussan
// Author Alexandre Di Pino
// Author Nicolas Papier

#include "vgAlg/node/VertexShape.hpp"

#include <vgd/basic/Time.hpp>
#include <vgd/node/VertexShape.hpp>

namespace
{
	static vgAlg::node::COMPUTE_NORMAL_METHOD			m_normal	= vgAlg::node::DEFAULT_COMPUTE_NORMAL;
	static vgAlg::node::COMPUTE_TANGENT_METHOD			m_tangent	= vgAlg::node::DEFAULT_COMPUTE_TANGENT;
	static vgAlg::node::COMPUTE_NORMALIZATION_METHOD	m_normalize	= vgAlg::node::DEFAULT_COMPUTE_NORMALIZATION;

	static bool											m_orthogonalize = true;
}



namespace vgAlg
{

namespace node
{



// COMPUTING METHODS ACCESSORS
const vgAlg::node::COMPUTE_NORMAL_METHOD getComputeNormalMethod()
{
	return m_normal;
}

void setComputeNormalMethod( const vgAlg::node::COMPUTE_NORMAL_METHOD value )
{
	m_normal = value;
}


const vgAlg::node::COMPUTE_TANGENT_METHOD getComputeTangentMethod()
{
	return m_tangent;
}

void setComputeTangentMethod( const vgAlg::node::COMPUTE_TANGENT_METHOD value )
{
	m_tangent = value;
}


const vgAlg::node::COMPUTE_NORMALIZATION_METHOD getNormalizationMethod()
{
	return m_normalize;
}

void setNormalizationMethod( const vgAlg::node::COMPUTE_NORMALIZATION_METHOD value )
{
	m_normalize = value;
}


const bool getOrthogonalize()
{
	return m_orthogonalize;
}

void setOrthogonalize( const bool value )
{
	m_orthogonalize = value;
}



// ALGORITHMS ON VERTEX SHAPE
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
			vgAssertN( false, "Unsupported primitive type" );
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
			const int32 numQuads = curPrim.getNumIndices() / 4;

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
			vgAssertN( false, "Unsupported primitive type" );
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


void computeNormals( vgd::Shp< vgd::node::VertexShape > vertexShape )
{
	const vgAlg::node::COMPUTE_NORMAL_METHOD value = vgAlg::node::getComputeNormalMethod();
#ifdef _VGSDK_PROFILE
	vgLogDebug("computeNormals(%s) using %i.\n", vertexShape->getName().c_str(), (int)value); // @todo
#endif
	if ( value == vgAlg::node::NO_COMPUTE_NORMAL )	return ;

	//
	vgd::field::EditorRO< vgd::field::MFVec3f >		vertices	= vertexShape->getFVertexRO();
	vgd::field::EditorRO< vgd::field::MFUInt32 >	vertexIndex	= vertexShape->getFVertexIndexRO();
	vgd::field::EditorRW< vgd::field::MFVec3f >		normals		= vertexShape->getFNormalRW();

	const int32 numVertices	= vertices->size();
	const int32 numTris		= vertexIndex->size()/3;

	// Stage initialization of normals field
	vgd::basic::Time init;
	normals->resize(0);
	normals->reserve(numVertices);

	// initialize normals to (0,0,0)
	for( uint i = 0; i < numVertices; ++i )
	{
		normals->push_back( vgm::Vec3f( 0.f, 0.f, 0.f ) );
	}
#ifdef _VGSDK_PROFILE
	vgLogDebug("computeNormals(): Reset normals field: %i\n", init.getElapsedTime().ms());
#endif

	// Stage normals computation
	vgd::basic::Time compute;

	switch( value )
	{
		case vgAlg::node::COMPUTE_NORMAL_STANDARD:
			vgAlg::node::computeNormalsStandard(vertices, vertexIndex, normals, numTris);
			#ifdef _VGSDK_PROFILE
			vgLogDebug("computeNormals(): standard : %i", compute.getElapsedTime().ms());
			#endif
			break;

		default:
			vgAssert(false);
	}


	// Normalization stage
	if ( vgAlg::node::getNormalizationMethod() != vgAlg::node::NO_COMPUTE_NORMALIZATION )
	{
		normalizeField(normals);
	}

	//
	if ( vertexShape->getNormalBinding() != vgd::node::BIND_PER_VERTEX )
	{
		vertexShape->setNormalBinding( vgd::node::BIND_PER_VERTEX );
	}
}


void computeTangents( vgd::Shp< vgd::node::VertexShape > vertexShape )
{
	const vgAlg::node::COMPUTE_TANGENT_METHOD value = vgAlg::node::getComputeTangentMethod();
#ifdef _VGSDK_PROFILE
	vgLogDebug("computeTangents(%s) using %i.\n", vertexShape->getName().c_str(), (int)value); // @todo
#endif

	if ( value == vgAlg::node::NO_COMPUTE_TANGENT || (vertexShape->getNumTexUnits() == 0) )
	{
		return ;
	}

	//
	vgd::field::EditorRO< vgd::field::MFVec3f >		vertices	= vertexShape->getFVertexRO();
	vgd::field::EditorRO< vgd::field::MFUInt32 >	vertexIndex	= vertexShape->getFVertexIndexRO();
	vgd::field::EditorRW< vgd::field::MFVec3f >		tangents	= vertexShape->getFTangentRW();
	vgd::field::EditorRO< vgd::field::MFVec3f >		normals		= vertexShape->getFNormalRO();
	vgd::field::EditorRO< vgd::field::MFVec2f >		textCoords	= vertexShape->getFTexCoordRO< vgd::field::MFVec2f >();

	const int32 numVertices	= vertices->size();
	const int32 numTris		= vertexIndex->size()/3;

	// Stage initialization of tangents field
	vgd::basic::Time init;
	tangents->resize(0);
	tangents->reserve(numVertices);

	// initialize tangents to (0,0,0)
	for( uint i = 0; i < numVertices; ++i)
	{
		tangents->push_back( vgm::Vec3f( 0.f, 0.f, 0.f ) ); 
	}
#ifdef _VGSDK_PROFILE
	vgLogDebug("computeTangents(): Reset tangents field: %i\n", init.getElapsedTime().ms());
#endif

	// Stage tangents computation
	vgd::basic::Time compute;

	switch ( value )
	{
		case vgAlg::node::COMPUTE_TANGENT_STANDARD:
			computeTangentsStandard(vertices, vertexIndex, tangents, normals, textCoords, numTris);
			#ifdef _VGSDK_PROFILE
			vgLogDebug("computeTangents(): standard : %i", compute.getElapsedTime().ms());
			#endif
			break;

		default:
			vgAssert(false);
	}

	// Normalization stage
	if ( vgAlg::node::getNormalizationMethod() != vgAlg::node::NO_COMPUTE_NORMALIZATION )
	{
		normalizeField(tangents);
	}

	//
	if ( vertexShape->getTangentBinding() != vgd::node::BIND_PER_VERTEX )
	{
		vertexShape->setTangentBinding( vgd::node::BIND_PER_VERTEX );
	}
}



void normalizeNormals( vgd::Shp< vgd::node::VertexShape > vertexShape/*, const vgAlg::node::COMPUTE_NORMAL_METHOD value todo */ )
{
	vgd::field::EditorRW< vgd::field::MFVec3f > field = vertexShape->getFNormalRW();
	normalizeField( field );
}


void normalizeTangents( vgd::Shp< vgd::node::VertexShape > vertexShape/*, const vgAlg::node::COMPUTE_NORMAL_METHOD value todo */ )
{
	vgd::field::EditorRW< vgd::field::MFVec3f > field = vertexShape->getFTangentRW();
	normalizeField( field );
}


void normalizeField( vgd::field::EditorRW< vgd::field::MFVec3f >& field/*, const vgAlg::node::COMPUTE_NORMAL_METHOD value todo */)
{
	normalizeFieldStandard( field );
}



void computeNormalsStandard(	vgd::field::EditorRO< vgd::field::MFVec3f >&	vertices,
								vgd::field::EditorRO< vgd::field::MFUInt32 >&	vertexIndex,
								vgd::field::EditorRW< vgd::field::MFVec3f >&	normals,
								const int32 numTris )
{
	vgm::Vec3f faceNormal;		// a temp face normal
	vgm::Vec3f v1, v2;

	int32 indexA, indexB, indexC;
	int32 j = 0;

	for( int32 i = 0; i < numTris; ++i )
	{
		indexA = (*vertexIndex)[j];
		indexB = (*vertexIndex)[j+1];
		indexC = (*vertexIndex)[j+2];

		// compute face normal
		v1 = (*vertices)[indexB] - (*vertices)[indexA];
		v2 = (*vertices)[indexC] - (*vertices)[indexA];
		faceNormal = v1.cross(v2);

		// add this face normal to each vertex normal
		(*normals)[indexA]	+= faceNormal;
		(*normals)[indexB]	+= faceNormal;
		(*normals)[indexC]	+= faceNormal;
		j += 3;
	}
}


void computeTangentsStandard(	vgd::field::EditorRO< vgd::field::MFVec3f >&	vertices,
								vgd::field::EditorRO< vgd::field::MFUInt32 >&	vertexIndex,
								vgd::field::EditorRW< vgd::field::MFVec3f >&	tangents,
								vgd::field::EditorRO< vgd::field::MFVec3f >&	normals,
								vgd::field::EditorRO< vgd::field::MFVec2f >&	texCoord,
								const int32 numTris )
{
	vgm::Vec3f faceTangent;		// a temp face tangent
	int32 indexA, indexB, indexC;
	vgm::Vec3f v1, v2;
	vgm::Vec2f t1, t2;
	float coef;
	int32 j = 0;

	int numVert = vertices->size();

	for( int32 i = 0; i < numTris; ++i )
	{
		indexA = (*vertexIndex)[j];
		indexB = (*vertexIndex)[j+1];
		indexC = (*vertexIndex)[j+2];

		// compute face normal
		v1 = (*vertices)[indexB] - (*vertices)[indexA];
		v2 = (*vertices)[indexC] - (*vertices)[indexA];
		t1 = (*texCoord)[indexB] - (*texCoord)[indexA];
		t2 = (*texCoord)[indexC] - (*texCoord)[indexA];

		coef = 1.f / (t1[0] * t2[1] - t1[1] * t2[0]);

		faceTangent[0] = (t2[1] * v1[0] - t1[1] * v2[0]) * coef;
		faceTangent[1] = (t2[1] * v1[1] - t1[1] * v2[1]) * coef;
		faceTangent[2] = (t2[1] * v1[2] - t1[1] * v2[2]) * coef;

		// add this face tangent to each vertex tangent
		(*tangents)[indexA]	+= faceTangent;
		(*tangents)[indexB]	+= faceTangent;
		(*tangents)[indexC]	+= faceTangent;

		j += 3;
	}

	if ( getOrthogonalize() )
	{
		for( int32 i = 0; i < numVert; ++i)
		{
			(*tangents)[i] =  (*tangents)[i] - (*normals)[i] * ((*normals)[i].dot((*tangents)[i]));
		}
	}
}


void normalizeFieldStandard( vgd::field::EditorRW< vgd::field::MFVec3f >& field )
{
	const int numElements = field->size();
	for(int32 i = 0; i < numElements; ++i)
	{
		(*field)[i].normalize();
	}
}



} // namespace node

} // namespace vgAlg
