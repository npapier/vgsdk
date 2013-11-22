// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Box.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



META_NODE_CPP( Box );



Box::Box( const std::string nodeName ) :
	vgd::node::VertexShape( nodeName )
{
}



void Box::setToDefaults( void )
{
	VertexShape::setToDefaults();
	
	initializeGeometry();
}



void Box::setOptionalsToDefaults()
{
	VertexShape::setOptionalsToDefaults();
}



/**
 * @todo Minimize VertexIndex.size() => use QUADS_STRIP
 */
void Box::initializeGeometry()
{
	// Initialize geometry.

	// VERTEX
	vgd::field::EditorRW< vgd::field::MFVec3f >	vertex			= getVertexRW();
	const float fSize= 0.5f;
	vertex->clear();
	vertex->reserve( 24 );
	
	// front
	vertex->push_back( vgm::Vec3f(-fSize, -fSize, fSize) );
	vertex->push_back( vgm::Vec3f(fSize, -fSize, fSize) );
	vertex->push_back( vgm::Vec3f(fSize, fSize, fSize) );
	vertex->push_back( vgm::Vec3f(-fSize, fSize, fSize) );
	
	// back
	vertex->push_back( vgm::Vec3f(-fSize, -fSize, -fSize) );
	vertex->push_back( vgm::Vec3f(fSize, -fSize, -fSize) );
	vertex->push_back( vgm::Vec3f(fSize, fSize, -fSize) );
	vertex->push_back( vgm::Vec3f(-fSize, fSize, -fSize) );
	
	// right
	vertex->push_back( vgm::Vec3f(fSize, -fSize, fSize) );
	vertex->push_back( vgm::Vec3f(fSize, -fSize, -fSize) );
	vertex->push_back( vgm::Vec3f(fSize, fSize, -fSize) );
	vertex->push_back( vgm::Vec3f(fSize, fSize, fSize) );
	
	// left
	vertex->push_back( vgm::Vec3f(-fSize, -fSize, fSize) );
	vertex->push_back( vgm::Vec3f(-fSize, -fSize, -fSize) );
	vertex->push_back( vgm::Vec3f(-fSize, fSize, -fSize) );
	vertex->push_back( vgm::Vec3f(-fSize, fSize, fSize) );

	// up
	vertex->push_back( vgm::Vec3f(fSize, fSize, fSize) );
	vertex->push_back( vgm::Vec3f(fSize, fSize, -fSize) );
	vertex->push_back( vgm::Vec3f(-fSize, fSize, -fSize) );
	vertex->push_back( vgm::Vec3f(-fSize, fSize, fSize) );
	
	// down	
	vertex->push_back( vgm::Vec3f(fSize, -fSize, fSize) );
	vertex->push_back( vgm::Vec3f(fSize, -fSize, -fSize) );
	vertex->push_back( vgm::Vec3f(-fSize, -fSize, -fSize) );
	vertex->push_back( vgm::Vec3f(-fSize, -fSize, fSize) );
	
	// VERTEX INDEX
	vgd::field::EditorRW< vgd::field::MFUInt >	vertexIndex		= getVertexIndexRW();
	vertexIndex->clear();
	vertexIndex->reserve( 24 );

	// front	
	vertexIndex->push_back(0);
	vertexIndex->push_back(1);
	vertexIndex->push_back(2);
	vertexIndex->push_back(3);
	
	// back
	vertexIndex->push_back(4);
	vertexIndex->push_back(5);
	vertexIndex->push_back(6);
	vertexIndex->push_back(7);
	
	// right
	vertexIndex->push_back(8);
	vertexIndex->push_back(9);
	vertexIndex->push_back(10);
	vertexIndex->push_back(11);
	
	// left
	vertexIndex->push_back(12);
	vertexIndex->push_back(13);
	vertexIndex->push_back(14);
	vertexIndex->push_back(15);

	// up
	vertexIndex->push_back(16);
	vertexIndex->push_back(17);
	vertexIndex->push_back(18);
	vertexIndex->push_back(19);
	
	// down
	vertexIndex->push_back(20);
	vertexIndex->push_back(21);
	vertexIndex->push_back(22);
	vertexIndex->push_back(23);

	// PRIMITIVE
	vgd::field::EditorRW< vgd::field::MFPrimitive >	primitive	= getPrimitiveRW();
	vgd::node::Primitive prim( vgd::node::Primitive::QUADS, 0, vertexIndex->size() );
	primitive->clear();
	primitive->push_back( prim );
	
	vertex.release();
	vertexIndex.release();
	primitive.release();
		
	// NORMAL
	vgd::field::EditorRW< vgd::field::MFVec3f >	normal			= getNormalRW();	
	normal->clear();
	normal->reserve(24);
	
	// front
	normal->push_back( vgm::Vec3f(0.f, 0.f, 1.f ) );
	normal->push_back( vgm::Vec3f(0.f, 0.f, 1.f ) );
	normal->push_back( vgm::Vec3f(0.f, 0.f, 1.f ) );
	normal->push_back( vgm::Vec3f(0.f, 0.f, 1.f ) );
	
	// back
	normal->push_back( vgm::Vec3f(0.f, 0.f, -1.f ) );
	normal->push_back( vgm::Vec3f(0.f, 0.f, -1.f ) );
	normal->push_back( vgm::Vec3f(0.f, 0.f, -1.f ) );
	normal->push_back( vgm::Vec3f(0.f, 0.f, -1.f ) );
	
	// right
	normal->push_back( vgm::Vec3f(1.f, 0.f, 0.f ) );
	normal->push_back( vgm::Vec3f(1.f, 0.f, 0.f ) );
	normal->push_back( vgm::Vec3f(1.f, 0.f, 0.f ) );
	normal->push_back( vgm::Vec3f(1.f, 0.f, 0.f ) );

	// left
	normal->push_back( vgm::Vec3f(-1.f, 0.f, 0.f ) );
	normal->push_back( vgm::Vec3f(-1.f, 0.f, 0.f ) );
	normal->push_back( vgm::Vec3f(-1.f, 0.f, 0.f ) );
	normal->push_back( vgm::Vec3f(-1.f, 0.f, 0.f ) );
	
	// up
	normal->push_back( vgm::Vec3f(0.f, 1.f, 0.f ) );
	normal->push_back( vgm::Vec3f(0.f, 1.f, 0.f ) );
	normal->push_back( vgm::Vec3f(0.f, 1.f, 0.f ) );
	normal->push_back( vgm::Vec3f(0.f, 1.f, 0.f ) );
	
	//down
	normal->push_back( vgm::Vec3f(0.f, -1.f, 0.f ) );
	normal->push_back( vgm::Vec3f(0.f, -1.f, 0.f ) );
	normal->push_back( vgm::Vec3f(0.f, -1.f, 0.f ) );
	normal->push_back( vgm::Vec3f(0.f, -1.f, 0.f ) );

	setNormalBinding( vgd::node::BIND_PER_VERTEX );
}



/*void Box::initializeTexUnits( const int32 numTexUnits )
{
	assert( false );
	enableTexUnits( numTexUnits );
	
	for(	int32 i=0;
			i<numTexUnits;
			i++ )
	{
		vgd::field::EditorRW< vgd::field::MFVec2f >	texCoord( getTexCoordRW( i ) );
		
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
