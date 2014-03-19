// VGSDK - Copyright (C) 2008, 2012, 2013, 2014, Pierre-Jean Bensoussan, Nicolas Papier, Alexandre Di Pino.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Pierre-Jean Bensoussan
// Author Alexandre Di Pino
// Author Nicolas Papier

#include "vgAlg/node/VertexShape.hpp"

//#define GLM_MESSAGES
#include <glm/glm.hpp>
#include <glm/gtx/fast_square_root.hpp>
#include <glm/gtx/simd_vec4.hpp>

#include <vgd/basic/Time.hpp>
#include <vgd/basic/TimeDuration.hpp>
#include <vgd/node/VertexShape.hpp>

// @todo change algo at runtime
#define USE_GLM_SIMD	1



// @todo move to vgm
vgm::Vec4f Vec4f_cast( glm::simdVec4 const & x )
{
	vgm::Vec4f retVal;
	_mm_storeu_ps(&retVal[0], x.Data);
	return retVal;
}


vgm::Vec3f Vec3f_cast( glm::simdVec4 const & x )
{
	vgm::Vec4f retVal = Vec4f_cast(x);
	return vgm::Vec3f( retVal );
}



namespace
{
	static vgAlg::node::COMPUTE_NORMAL_METHOD			m_normal	= vgAlg::node::DEFAULT_COMPUTE_NORMAL;
	static vgAlg::node::COMPUTE_TANGENT_METHOD			m_tangent	= vgAlg::node::DEFAULT_COMPUTE_TANGENT;
	static vgAlg::node::COMPUTE_NORMALIZATION_METHOD	m_normalize	= vgAlg::node::DEFAULT_COMPUTE_NORMALIZATION;

	static bool											m_orthogonalize = true; // @todo use it in computeTangent...()
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
	vgd::field::EditorRW< vgd::field::MFUInt > vertexIndexRW = vertexShape->getVertexIndexRW();
	vgd::field::EditorRO< vgd::field::TMultiField< vgd::node::Primitive > > primitiveRO = vertexShape->getPrimitiveRO();

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
	vgd::field::EditorRW< vgd::field::MFVec3f >	normals = vertexShape->getNormalRW();

	for( uint i = 0; i < normals->size(); ++i )
	{
		(*normals)[i].negate();
	}
}


void triangulate( vgd::Shp< vgd::node::VertexShape > vertexShape )
{
	vgd::field::EditorRW< vgd::field::MFUInt > vertexIndexRW = vertexShape->getVertexIndexRW();
	std::vector< uint32 > newVertexIndexRW;

	vgd::field::EditorRW< vgd::field::TMultiField< vgd::node::Primitive > > primitiveRW = vertexShape->getPrimitiveRW();

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
	vgd::field::EditorRO< vgd::field::MFVec3f >		vertices	= vertexShape->getVertexRO();
	vgd::field::EditorRO< vgd::field::MFUInt >	vertexIndex	= vertexShape->getVertexIndexRO();
	vgd::field::EditorRW< vgd::field::MFVec3f >		normals		= vertexShape->getNormalRW();

	const uint numVertices	= vertices->size();
	const uint numTris		= vertexIndex->size()/3;

	// Stage initialization of normals field
#ifdef _VGSDK_PROFILE
	vgd::basic::Time init;
#endif

	if ( normals->size() != numVertices )	normals->resize(numVertices);
	/*if ( value == vgAlg::node::COMPUTE_NORMAL_METHOD::SIMPLE_SIMD)
	{
		tbb::task_scheduler_init tb(4);
	}*/

	// initialize normals to (0,0,0)
	memset(&normals->front(), 0, numVertices * sizeof(vgm::Vec3f) );

#ifdef _VGSDK_PROFILE
	vgLogDebug("computeNormals(): Reset normals field: %i\n", init.getElapsedTime().ms());
#endif

	// Stage normals computation
#ifdef _VGSDK_PROFILE
	vgd::basic::Time compute;
#endif

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
		return;
	}

	//
	vgd::field::EditorRO< vgd::field::MFVec3f >		vertices	= vertexShape->getVertexRO();
	vgd::field::EditorRO< vgd::field::MFUInt >	vertexIndex	= vertexShape->getVertexIndexRO();
	vgd::field::EditorRW< vgd::field::MFVec3f >		tangents	= vertexShape->getTangentRW();
	vgd::field::EditorRO< vgd::field::MFVec3f >		normals		= vertexShape->getNormalRO();
	vgd::field::EditorRO< vgd::field::MFVec2f >		textCoords	= vertexShape->getTexCoordRO< vgd::field::MFVec2f >();

	const uint numVertices	= vertices->size();
	const uint numTris		= vertexIndex->size()/3;

	// Stage initialization of tangents field
#ifdef _VGSDK_PROFILE
	vgd::basic::Time init;
#endif

	if ( tangents->size() != numVertices )	tangents->resize(numVertices);
	// initialize tangents to (0,0,0)
	memset(&tangents->front(), 0, numVertices * sizeof(vgm::Vec3f) );

#ifdef _VGSDK_PROFILE
	vgLogDebug("computeTangents(): Reset tangents field: %i\n", init.getElapsedTime().ms());
#endif

	// Stage tangents computation
#ifdef _VGSDK_PROFILE
	vgd::basic::Time compute;
#endif

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
	// normalization is not needed for rendering (but could be useful to show tangents with DrawStyle node).
/*	if ( vgAlg::node::getNormalizationMethod() != vgAlg::node::NO_COMPUTE_NORMALIZATION )
	{
		normalizeField(tangents);
	}*/

	//
	if ( vertexShape->getTangentBinding() != vgd::node::BIND_PER_VERTEX )
	{
		vertexShape->setTangentBinding( vgd::node::BIND_PER_VERTEX );
	}
}



void normalizeNormals( vgd::Shp< vgd::node::VertexShape > vertexShape/*, const vgAlg::node::COMPUTE_NORMAL_METHOD value todo */ )
{
	vgd::field::EditorRW< vgd::field::MFVec3f > field = vertexShape->getNormalRW();
	normalizeField( field );
}


void normalizeTangents( vgd::Shp< vgd::node::VertexShape > vertexShape/*, const vgAlg::node::COMPUTE_NORMAL_METHOD value todo */ )
{
	vgd::field::EditorRW< vgd::field::MFVec3f > field = vertexShape->getTangentRW();
	normalizeField( field );
}


void normalizeField( vgd::field::EditorRW< vgd::field::MFVec3f >& field/*, const vgAlg::node::COMPUTE_NORMAL_METHOD value todo */)
{
	normalizeFieldStandard( field );
}



void computeNormalsStandard(	vgd::field::EditorRO< vgd::field::MFVec3f >&	vertices,
								vgd::field::EditorRO< vgd::field::MFUInt >&	vertexIndex,
								vgd::field::EditorRW< vgd::field::MFVec3f >&	normals,
								const int32 numTris )
{
#ifdef USE_GLM_SIMD
	#pragma message("computeNormalsStandard() USE_GLM_SIMD implementation")
	int32 indexA, indexB, indexC;
	int32 j = 0;

	for( int32 i = 0; i < numTris; ++i )
	{
		indexA = (*vertexIndex)[j];
		indexB = (*vertexIndex)[j+1];
		indexC = (*vertexIndex)[j+2];

		glm::simdVec4	ma((*vertices)[indexA][0], (*vertices)[indexA][1], (*vertices)[indexA][2], 0);
		glm::simdVec4	mb((*vertices)[indexB][0], (*vertices)[indexB][1], (*vertices)[indexB][2], 0);
		glm::simdVec4	mc((*vertices)[indexC][0], (*vertices)[indexC][1], (*vertices)[indexC][2], 0);

		// compute face normal
		glm::simdVec4 faceNormal = glm::cross(mb - ma, mc - ma);

		// add this face normal to each vertex normal
		glm::simdVec4	oldNormal((*normals)[indexA][0], (*normals)[indexA][1], (*normals)[indexA][2], 0);
		(*normals)[indexA]	= Vec3f_cast(oldNormal + faceNormal);

		oldNormal = glm::simdVec4((*normals)[indexB][0], (*normals)[indexB][1], (*normals)[indexB][2], 0);
		(*normals)[indexB]	= Vec3f_cast(oldNormal + faceNormal);

		oldNormal = glm::simdVec4((*normals)[indexC][0], (*normals)[indexC][1], (*normals)[indexC][2], 0);
		(*normals)[indexC]	= Vec3f_cast(oldNormal + faceNormal);

		j += 3;
	}
#else
	#pragma message("computeNormalsStandard() default implementation")

	int32 indexA, indexB, indexC;
	int32 j = 0;

	for( int32 i = 0; i < numTris; ++i )
	{
		indexA = (*vertexIndex)[j];
		indexB = (*vertexIndex)[j+1];
		indexC = (*vertexIndex)[j+2];

		/*const*/ vgm::Vec3f A = (*vertices)[indexA];
		/*const*/ vgm::Vec3f B = (*vertices)[indexB];
		/*const*/ vgm::Vec3f C = (*vertices)[indexC];

		// compute face normal
		const vgm::Vec3f v1 = B - A;
		const vgm::Vec3f v2 = C - A;
		const vgm::Vec3f faceNormal = v1.cross( v2 );

		// add this face normal to each vertex normal
		(*normals)[indexA]	+= faceNormal;
		(*normals)[indexB]	+= faceNormal;
		(*normals)[indexC]	+= faceNormal;

		j += 3;
	}
#endif
}


// Code based on Terathon Software 3D Graphics Library, 2001. http://www.terathon.com/code/tangent.html
// Lengyel, Eric. “Computing Tangent Space Basis Vectors for an Arbitrary Mesh”.
void computeTangentsStandard(	vgd::field::EditorRO< vgd::field::MFVec3f >&	vertices,
								vgd::field::EditorRO< vgd::field::MFUInt >&	vertexIndex,
								vgd::field::EditorRW< vgd::field::MFVec3f >&	tangents,				// @todo move to last parameter
								vgd::field::EditorRO< vgd::field::MFVec3f >&	normals,
								vgd::field::EditorRO< vgd::field::MFVec2f >&	texCoord,
								const int32 numTris )
{
	//static std::vector< vgm::Vec3f > memory;
	static std::vector< vgm::Vec4f > memory;
	const uint desiredSized = vertices->size(); // * 2;
	if ( memory.size() < desiredSized )
	{
		vgLogDebug("computeTangentsStandard(): memory resize(%i)", desiredSized);
		memory.resize( desiredSized );
	}

	//vgm::Vec3f * tan1 = &memory.front();
	vgm::Vec4f * tan1 = &memory.front();
	//vgm::Vec3f * tan2 = tan1 + vertices->size();
	//memset(tan1, 0, desiredSized * sizeof(vgm::Vec3f) );
	memset(tan1, 0, desiredSized * sizeof(vgm::Vec4f) );

	/*static int numElements		= 0;
	static glm::simdVec4 * tan1	= 0;
	//static glm::simdVec4 * tan2	= 0;

	const int desiredSized = vertices->size();
	if ( numElements < desiredSized )
	{
		if ( tan1 )		delete [] tan1;
		//if ( tan2 )		delete [] tan2;
		//if ( tan2 )		delete [] tan2;
		tan1 = new glm::simdVec4[desiredSized];
		numElements = desiredSized;
		//tan2 = new glm::simdVec4[desiredSized];
	}

	for( uint i=0; i!=numElements; ++i )
	{
		tan1[i] = glm::simdVec4(0);
		//tan2[i] = glm::simdVec4(0);
	}*/
	/*memset(tan1, 0, desiredSized * sizeof(glm::simdVec4) );
	memset(tan2, 0, desiredSized * sizeof(glm::simdVec4) );*/

#ifdef USE_GLM_SIMD
	#pragma message("computeTangentsStandard() USE_GLM_SIMD implementation")

	uint viI=0;	// (I)ndex in (v)ertex (i)ndex array
	for( uint a=0; a < static_cast<uint>(numTris); ++a )
	{
		const uint i1 = (*vertexIndex)[viI++];
		const uint i2 = (*vertexIndex)[viI++];
		const uint i3 = (*vertexIndex)[viI++];

		//const vgm::Vec3f v1 = (*vertices)[i1];
		//const vgm::Vec3f v2 = (*vertices)[i2];
		//const vgm::Vec3f v3 = (*vertices)[i3];
		glm::simdVec4 v1( (*vertices)[i1][0], (*vertices)[i1][1], (*vertices)[i1][2], 0 );
		glm::simdVec4 v2( (*vertices)[i2][0], (*vertices)[i2][1], (*vertices)[i2][2], 0 );
		glm::simdVec4 v3( (*vertices)[i3][0], (*vertices)[i3][1], (*vertices)[i3][2], 0 );

		//const vgm::Vec2f w1 = (*texCoord)[i1];
		//const vgm::Vec2f w2 = (*texCoord)[i2];
		//const vgm::Vec2f w3 = (*texCoord)[i3];
		glm::simdVec4 w1( (*texCoord)[i1][0], (*texCoord)[i1][1], (*texCoord)[i1][0], (*texCoord)[i1][1] );
		glm::simdVec4 w23( (*texCoord)[i2][0], (*texCoord)[i2][1], (*texCoord)[i3][0], (*texCoord)[i3][1] );

		//const vgm::Vec3f p1 = v2 - v1;
		//const vgm::Vec3f p2 = v3 - v1;
		glm::simdVec4 p1 = v2 - v1;
		glm::simdVec4 p2 = v3 - v1;

		//const vgm::Vec2f u1 = w2 - w1;
		//const vgm::Vec2f u2 = w3 - w1;
		glm::simdVec4 u12 = w23 - w1;
		const vgm::Vec4f u = Vec4f_cast( u12 );

		//const float r = 1.0F / (u1[0] * u2[1] - u2[0] * u1[1]);
		//const float r = 1.0F / (u[0] * u[3] - u[2] * u[1]);
		const float diff = (u[0] * u[3]) - (u[2] * u[1]);	// @todo OPTME
		const float r = 1.0F / diff;						// @todo OPTME

		//const vgm::Vec3f sdir = (u2[1] * p1 - u1[1] * p2) * r;
		/*const*/ glm::simdVec4 sdir = (u[3] * p1 - u[1] * p2) * r;

		//const vgm::Vec3f tdir = (u1[0]*p2 - u2[0] * p1) * r;
//		const gl::simdVec4 tdir = (u[0]*p2 - u[2] * p1) * r;

		// Take care of texture mirroring
		//const float area = (s2*t1) - (t2*s1);
		//const float area = (u[2]*u[1]) - (u[3]*u[0]);
		const float area = -diff;
		if ( area < 0.f )
		{
			sdir *= -1.f;
			//tdir *= -1.f;
		}

		//
		//const vgm::Vec3f _sdir = glm::vec4_cast(sdir);

		//tan1[i1] += _sdir;
		glm::simdVec4 oldValue( tan1[i1][0], tan1[i1][1], tan1[i1][2], 0 );
		tan1[i1] = Vec4f_cast(oldValue + sdir);

		//tan1[i2] += _sdir;
		oldValue = glm::simdVec4( tan1[i2][0], tan1[i2][1], tan1[i2][2], 0 );
		tan1[i2] = Vec4f_cast(oldValue + sdir);

		//tan1[i3] += _sdir;
		oldValue = glm::simdVec4( tan1[i3][0], tan1[i3][1], tan1[i3][2], 0 );
		tan1[i3] = Vec4f_cast(oldValue + sdir);

		//vgm::Vec3f _tdir = glm::vec4_cast(tdir);
		//oldValue = glm::simdVec4( tan2[i1][0], tan2[i1][1], tan2[i1][2], 0 );
		//tan2[i1] = glm::vec4_cast(oldValue + tdir);
		//tan2[i1] += _tdir;
//		tan2[i1] += tdir;

		//oldValue = glm::simdVec4( tan2[i2][0], tan2[i2][1], tan2[i2][2], 0 );
		//tan2[i2] = glm::vec4_cast(oldValue + tdir);
		//tan2[i2] += _tdir;
//		tan2[i2] += tdir;

		//oldValue = glm::simdVec4( tan2[i3][0], tan2[i3][1], tan2[i3][2], 0 );
		//tan2[i3] = glm::vec4_cast(oldValue + tdir);
		//tan2[i3] += _tdir;
//		tan2[i3] += tdir;
	}

	for (uint a=0; a < vertices->size(); ++a)
	{
		glm::simdVec4 n( (*normals)[a][0], (*normals)[a][1], (*normals)[a][2], 0 );
		//const vgm::Vec3f n = (*normals)[a];

		glm::simdVec4 t( tan1[a][0], tan1[a][1], tan1[a][2], 0 );
		//const vgm::Vec3f t = tan1[a];

		// Gram-Schmidt orthogonalize
		//(*tangents)[a] = (t - n * n.dot(t)); //.normalize() => Don't do normalization now.
		(*tangents)[a] = Vec3f_cast( t - n * glm::dot( n, t ) );
		//(*tangents)[a] = glm::vec4_cast( tan1[a] - n * glm::dot( n, tan1[a] ) );

		// Calculate handedness
		//const float handedness = ( (n.cross(t)).dot(tan2[a]) ) < 0.0F ? -1.0F : 1.0F;
		//tangent[a].w = handedness;
	}
#else
	#pragma message("computeTangentsStandard() default implementation")

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
#endif
	//delete [] tan1;
}




void normalizeFieldStandard( vgd::field::EditorRW< vgd::field::MFVec3f >& field )
{
	const int numElements = field->size();
	for(int i = 0; i < numElements; ++i)
	{
#ifdef USE_GLM_SIMD
		glm::simdVec4 ret = glm::fastNormalize( glm::simdVec4((*field)[i][0], (*field)[i][1], (*field)[i][2], 0) );
		(*field)[i] = Vec3f_cast( ret );
#elif USE_GLM
		(*field)[i] = vgm::Vec3f( glm::fastNormalize( glm::vec3((*field)[i][0], (*field)[i][1], (*field)[i][2]) ) );
#else
		(*field)[i].normalize();
#endif
	}
}



} // namespace node

} // namespace vgAlg
