// VGSDK - Copyright (C) 2006, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Sphere.hpp"

#include <cmath>
#include <boost/assign/std/vector.hpp>
#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{

namespace
{
	/**
	 * @brief Subdivides one times the icosahedron (i.e. the sphere geometry).
	 * 
	 * @param sphere			the sphere class to be subdivided
	 */
	void subdivide( vgd::node::Sphere *sphere )
	{
		// Retrives field accessors
		vgd::field::EditorRW< vgd::field::MFVec3f >		vertex		= sphere->getFVertexRW();
		vgd::field::EditorRW< vgd::field::MFUInt32>		vertexIndex	= sphere->getFVertexIndexRW();
		vgd::field::EditorRW< vgd::field::MFPrimitive >	primitive	= sphere->getFPrimitiveRW();
		vgd::field::EditorRW< vgd::field::MFVec3f >		normal		= sphere->getFNormalRW();

		// Copies vertex and vertexIndex fields
		std::vector< vgm::Vec3f > vertexOri;
		vertexOri.insert( vertexOri.begin(), vertex->begin(), vertex->end() );

		std::vector< uint32 > vertexIndexOri;
		vertexIndexOri.insert( vertexIndexOri.begin(), vertexIndex->begin(), vertexIndex->end() );		
		
		// Clears original fields
		vertex->reserve( vertex->size() * 2 );
		vertex->clear();

		vertexIndex->reserve( vertexIndex->size() * 4 );
		vertexIndex->clear();
		
		normal->reserve( vertex->size() );
		normal->clear();

		// Starts subdivision
		assert( vertexIndexOri.size() >= 60 );	// at least 20 triangles
		assert( vertexIndexOri.size() % 3 == 0 );// triangles ?
		// @todo Tests more accurately if shape is only composed by triangles

		const uint32 numOfTrianglesOri = vertexIndexOri.size()/3;

		// For each triangle of the original shape, do
		for( uint32 i = 0; i < numOfTrianglesOri; ++i )
		{
			// Retrives the 3 vertices of the current triangle
			const uint32 aIndex = vertexIndexOri[ 3*i		];
			const uint32 bIndex = vertexIndexOri[ 3*i + 1	];
			const uint32 cIndex = vertexIndexOri[ 3*i + 2	];

			const vgm::Vec3f a = vertexOri[ aIndex ];
			const vgm::Vec3f b = vertexOri[ bIndex ];
			const vgm::Vec3f c = vertexOri[ cIndex ];

			// Computes 3 new points on the sphere
			vgm::Vec3f v1 = (a+b)/2.f;
			vgm::Vec3f v2 = (b+c)/2.f;
			vgm::Vec3f v3 = (c+a)/2.f;

			v1.normalize();
			v2.normalize();
			v3.normalize();

			// Splits the original triangle into 4 new triangles
			using namespace boost::assign;
			
			std::vector< vgm::Vec3f > vertexTable;
			vertexTable.reserve(6);
			vertexTable += a, v1, v3, c, v2, b;
			
			const uint32 indexOfNextVertex = vertex->size();
			vertex->push_back( vertexTable );
			normal->push_back( vertexTable );

			std::vector< uint32 > indexTable;
			indexTable.reserve(12);
			indexTable += indexOfNextVertex, indexOfNextVertex+1, indexOfNextVertex+2;
			indexTable += indexOfNextVertex+2, indexOfNextVertex+4, indexOfNextVertex+3;
			indexTable += indexOfNextVertex+2, indexOfNextVertex+1, indexOfNextVertex+4;
			indexTable += indexOfNextVertex+4, indexOfNextVertex+1, indexOfNextVertex+5;

			vertexIndex->push_back( indexTable );
		}
		
		(*primitive)[0].setNumIndices( vertexIndex->size() );
	}
	
	/**
	 * @brief Subdivides the icosahedron (i.e. the sphere geometry).
	 * 
	 * @param sphere			the sphere class to subdivide
	 * @param levels			specifies how many times subdivide must be called
	 * 
	 * @remarks This method could only be applied safely on Sphere node without any modifications on vertex,
	 * vertexIndex, primitive and normal fields.
	 * 
	 * @todo Precomputes subdivisions from 0 to 4.
	 */
	void subdivide( vgd::node::Sphere *sphere, const uint32 levels )
	{
		for( uint32 i=0; i<levels; ++i )
		{
			subdivide( sphere );
		}
	}
}



META_NODE_CPP( Sphere );



Sphere::Sphere( const std::string nodeName ) :
	vgd::node::VertexShape( nodeName )
{}



void Sphere::setToDefaults( void )
{
	VertexShape::setToDefaults();
	
	initializeGeometry();
}



void Sphere::setOptionalsToDefaults()
{
	VertexShape::setOptionalsToDefaults();
}



void Sphere::initializeGeometry( const uint32 levels )
{
	// Initializes the geometry of the vertex shape class
	// i.e. builds an icosahedron and subdivides it levels times

	// VERTEX field

	vgd::field::EditorRW< vgd::field::MFVec3f >	vertex = getFVertexRW();

	const float t	= (1.f + std::sqrt(5.f))/2.f;
	const float s	= std::sqrt(1.f + t*t);

	const float ts	= t/s;

	vertex->clear();
	vertex->reserve( 12 );

	// Creates the 12 vertices
	const vgm::Vec3f v0(	ts,		1.f/s,	0.f	);
	const vgm::Vec3f v1(	-ts,	1.f/s,	0.f	);
	const vgm::Vec3f v2(	ts,		-1.f/s,	0.f	);
	const vgm::Vec3f v3(	-ts,	-1.f/s,	0.f	);

	const vgm::Vec3f v4(	1.f/s,	0.f,	ts	);
	const vgm::Vec3f v5(	1.f/s,	0.f,	-ts	);
	const vgm::Vec3f v6(	-1.f/s,	0.f,	ts	);
	const vgm::Vec3f v7(	-1.f/s,	0.f,	-ts	);
	
	const vgm::Vec3f v8(	0.f,	ts,		1.f/s	);
	const vgm::Vec3f v9(	0.f,	-ts,	1.f/s	);
	const vgm::Vec3f v10(	0.f,	ts,		-1.f/s	);
	const vgm::Vec3f v11(	0.f,	-ts,	-1.f/s	);

	using namespace boost::assign;
	std::vector< vgm::Vec3f > vertexTable;
	vertexTable.reserve(12);
	vertexTable += v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11;

	vertex->push_back( vertexTable );
	vertex.release();

	// VERTEX INDEX field
	vgd::field::EditorRW< vgd::field::MFUInt32>	vertexIndex = getFVertexIndexRW();

	vertexIndex->clear();
	vertexIndex->reserve( 60 );
	
	// Creates the 20 triangles
	std::vector< uint32 > vertexIndexTable;
	vertexIndexTable.reserve(60);

	vertexIndexTable +=
		0, 8, 4,
		1, 10, 7,
		2, 9, 11,
		7, 3, 1,
		0, 5, 10,
		3, 9, 6,
		3, 11, 9,
		8, 6, 4,
		2, 4, 9,
		3, 7, 11,
		4, 2, 0,
		9, 4, 6,    
		2, 11, 5,
		0, 10, 8,
		5, 0, 2,
		10, 5, 7,    
		1, 6, 8,
		1, 8, 10,
		6, 1, 3,
		11, 7, 5;

	vertexIndex->push_back( vertexIndexTable );

	// PRIMITIVE field
	vgd::field::EditorRW< vgd::field::MFPrimitive >	primitive	= getFPrimitiveRW();
	
	const vgd::node::Primitive prim( vgd::node::Primitive::TRIANGLES, 0, vertexIndex->size() );

	primitive->clear();
	primitive->push_back( prim );

	primitive.release();
	vertexIndex.release();

	// NORMAL field
	vgd::field::EditorRW< vgd::field::MFVec3f >	normal = getFNormalRW();
	
	normal->clear();
	normal->reserve( 12 );
	
	normal->push_back( vertexTable );
	normal.release();	

	setNormalBinding( vgd::node::BIND_PER_VERTEX );
	
	subdivide( this, levels );
}



/*void Sphere::initializeTexUnits( const int32 numTexUnits )
{
	assert( false );
	enableTexUnits( numTexUnits );
	
	for(	int32 i=0;
			i<numTexUnits;
			i++ )
	{
		vgd::field::EditorRW< vgd::field::MFVec2f >	texCoord( getFTexCoordRW( i ) );
		
		// TEX COORD
		texCoord->clear();
		texCoord->reserve( 4 );
	
		texCoord->push_back( vgm::Vec2f( 0.f, 1.f) );
		texCoord->push_back( vgm::Vec2f( 1.f, 1.f) );
		texCoord->push_back( vgm::Vec2f( 1.f, 0.f) );
		texCoord->push_back( vgm::Vec2f( 0.f, 0.f) );
		
		setTexCoordBinding( i, vgd::node::BIND_PER_VERTEX );
	}
}*/



} // namespace node

} // namespace vgd
