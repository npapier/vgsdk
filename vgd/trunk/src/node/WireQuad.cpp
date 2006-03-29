// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/WireQuad.hpp"



namespace vgd
{

namespace node
{



META_NODE_CPP( WireQuad );



WireQuad::WireQuad( const std::string nodeName ) :
	vgd::node::WireShape( nodeName )
{
}



void WireQuad::setToDefaults( void )
{
	WireShape::setToDefaults();
	
	initializeGeometry();
}



void WireQuad::setOptionalsToDefaults()
{
	WireShape::setOptionalsToDefaults();
}



void WireQuad::initializeGeometry( const float width, const float height )
{
	// Initialize geometry.

	// VERTEX
	vgd::field::EditorRW< vgd::field::MFVec3f >	vertex = getFVertexRW();
	const float fSizeX = 0.5f * width;
	const float fSizeY = 0.5f * height;
	
	vertex->clear();
	vertex->reserve( 4 );
	vertex->push_back( vgm::Vec3f(-fSizeX,	-fSizeY, 0.f) );
	vertex->push_back( vgm::Vec3f(fSizeX,	-fSizeY, 0.f) );
	vertex->push_back( vgm::Vec3f(fSizeX,	fSizeY, 0.f) );
	vertex->push_back( vgm::Vec3f(-fSizeX,	fSizeY, 0.f) );
	
	// VERTEX INDEX
	vgd::field::EditorRW< vgd::field::MFUInt32>	vertexIndex		= getFVertexIndexRW();	
	vertexIndex->clear();
	vertexIndex->reserve( 4 );
	vertexIndex->push_back(0);
	vertexIndex->push_back(1);
	vertexIndex->push_back(2);
	vertexIndex->push_back(3);
	
	// PRIMITIVE
	vgd::field::EditorRW< vgd::field::MFPrimitive >	primitive	= getFPrimitiveRW();
	vgd::node::Primitive prim( vgd::node::Primitive::LINE_LOOP, 0, vertexIndex->size() );
	primitive->clear();
	primitive->push_back( prim );
	
	vertex.release();
	vertexIndex.release();
	primitive.release();
}



} // namespace node

} // namespace vgd
