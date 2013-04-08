// VGSDK - Copyright (C) 2004, 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/WireBox.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



META_NODE_CPP( WireBox );



WireBox::WireBox( const std::string nodeName ) :
	vgd::node::WireShape( nodeName )
{
}



void WireBox::setToDefaults( void )
{
	WireShape::setToDefaults();
	
	initializeGeometry();
}



void WireBox::setOptionalsToDefaults()
{
	WireShape::setOptionalsToDefaults();
}



void WireBox::initializeGeometry( const vgm::Box3f box )
{
	// Initialize geometry.

	// VERTEX
	vgd::field::EditorRW< vgd::field::MFVec3f >	vertex = getFVertexRW();
	const vgm::Vec3f min = box.getMin();
	const vgm::Vec3f max = box.getMax();
	vertex->clear();
	vertex->reserve( 24 );

	// back
	vertex->push_back( vgm::Vec3f(min[0], min[1], min[2]) );
	vertex->push_back( vgm::Vec3f(max[0], min[1], min[2]) );
	vertex->push_back( vgm::Vec3f(max[0], max[1], min[2]) );
	vertex->push_back( vgm::Vec3f(min[0], max[1], min[2]) );

	// front
	vertex->push_back( vgm::Vec3f(min[0], min[1], max[2]) );
	vertex->push_back( vgm::Vec3f(max[0], min[1], max[2]) );
	vertex->push_back( vgm::Vec3f(max[0], max[1], max[2]) );
	vertex->push_back( vgm::Vec3f(min[0], max[1], max[2]) );

	// VERTEX INDEX
	vgd::field::EditorRW< vgd::field::MFUInt32>	vertexIndex = getFVertexIndexRW();
	vertexIndex->clear();
	vertexIndex->reserve( 16 );

	// back
	vertexIndex->push_back(0);
	vertexIndex->push_back(1);
	vertexIndex->push_back(2);
	vertexIndex->push_back(3);
	vertexIndex->push_back(0);

	// down
	vertexIndex->push_back(4);
	vertexIndex->push_back(5);
	vertexIndex->push_back(1);
	vertexIndex->push_back(2); // 1-2 already drawn
	
	// up
	vertexIndex->push_back(6);
	vertexIndex->push_back(7);
	vertexIndex->push_back(3);

	// left-right
	vertexIndex->push_back(7); // 3-7 already drawn
	vertexIndex->push_back(4);
	vertexIndex->push_back(5); // 4-5 already drawn
	vertexIndex->push_back(6);

	// PRIMITIVE
	vgd::field::EditorRW< vgd::field::MFPrimitive >	primitive = getFPrimitiveRW();
	vgd::node::Primitive prim( vgd::node::Primitive::LINE_STRIP, 0, vertexIndex->size() );
	primitive->clear();
	primitive->push_back( prim );

	vertex.release();
	vertexIndex.release();
	primitive.release();
}



} // namespace node

} // namespace vgd
