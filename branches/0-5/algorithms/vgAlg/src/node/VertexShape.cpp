// VGSDK - Copyright (C) 2008, 2012, 2013, Pierre-Jean Bensoussan, Nicolas Papier, Alexandre Di Pino.
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

	const uint numVertices	= vertices->size();
	const uint numTris		= vertexIndex->size()/3;

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

	const uint numVertices	= vertices->size();
	const uint numTris		= vertexIndex->size()/3;

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


// Code based on Terathon Software 3D Graphics Library, 2001. http://www.terathon.com/code/tangent.html
// Lengyel, Eric. “Computing Tangent Space Basis Vectors for an Arbitrary Mesh”.
void computeTangentsStandard(	vgd::field::EditorRO< vgd::field::MFVec3f >&	vertices,
								vgd::field::EditorRO< vgd::field::MFUInt32 >&	vertexIndex,
								vgd::field::EditorRW< vgd::field::MFVec3f >&	tangents,
								vgd::field::EditorRO< vgd::field::MFVec3f >&	normals,
								vgd::field::EditorRO< vgd::field::MFVec2f >&	texCoord,
								const int32 numTris )
{
	vgm::Vec3f * tan1 = new vgm::Vec3f[vertices->size()*2];
	vgm::Vec3f * tan2 = tan1 + vertices->size();
	memset(tan1, 0, vertices->size() * sizeof(vgm::Vec3f) * 2 );

	uint viI=0;	// (I)ndex in (v)ertex (i)ndex array
	for( uint a=0; a < static_cast<uint>(numTris); ++a )
	{
		const uint i1 = (*vertexIndex)[viI++];
		const uint i2 = (*vertexIndex)[viI++];
		const uint i3 = (*vertexIndex)[viI++];

		const vgm::Vec3f v1 = (*vertices)[i1];
		const vgm::Vec3f v2 = (*vertices)[i2];
		const vgm::Vec3f v3 = (*vertices)[i3];

		const vgm::Vec2f w1 = (*texCoord)[i1];
		const vgm::Vec2f w2 = (*texCoord)[i2];
		const vgm::Vec2f w3 = (*texCoord)[i3];

		const float x1 = v2[0] - v1[0];
		const float x2 = v3[0] - v1[0];
		const float y1 = v2[1] - v1[1];
		const float y2 = v3[1] - v1[1];
		const float z1 = v2[2] - v1[2];
		const float z2 = v3[2] - v1[2];

		const float s1 = w2[0] - w1[0];
		const float s2 = w3[0] - w1[0];
		const float t1 = w2[1] - w1[1];
		const float t2 = w3[1] - w1[1];

		const float r = 1.0F / (s1 * t2 - s2 * t1);
		/*const*/ vgm::Vec3f sdir(	(t2 * x1 - t1 * x2) * r, (t2 * y1 - t1 * y2) * r, (t2 * z1 - t1 * z2) * r	);
		/*const*/ vgm::Vec3f tdir(	(s1 * x2 - s2 * x1) * r, (s1 * y2 - s2 * y1) * r, (s1 * z2 - s2 * z1) * r	);

		// Take care of texture mirroring
		const float area = (s2*t1) - (t2*s1);
		if ( area < 0.f )
		{
			sdir.negate();
			tdir.negate();
		}

		//
		tan1[i1] += sdir;
		tan1[i2] += sdir;
		tan1[i3] += sdir;

		tan2[i1] += tdir;
		tan2[i2] += tdir;
		tan2[i3] += tdir;
	}

	for (uint a=0; a < vertices->size(); ++a)
	{
		const vgm::Vec3f n = (*normals)[a];
		const vgm::Vec3f t = tan1[a];

		// Gram-Schmidt orthogonalize
		(*tangents)[a] = (t - n * n.dot(t)); //.normalize() => Don't do normalization now.

		// Calculate handedness
		//const float handedness = ( (n.cross(t)).dot(tan2[a]) ) < 0.0F ? -1.0F : 1.0F;
		//tangent[a].w = handedness;
	}

	delete [] tan1;
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
