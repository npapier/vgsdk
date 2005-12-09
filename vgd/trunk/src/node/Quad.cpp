// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Quad.hpp"



namespace vgd
{

namespace node
{



META_NODE_CPP( Quad );



Quad::Quad( const std::string nodeName ) :
	vgd::node::VertexShape( nodeName )
{
}



void Quad::setToDefaults( void )
{
	VertexShape::setToDefaults();
	
	initializeGeometry();
}



void Quad::setOptionalsToDefaults()
{
	VertexShape::setOptionalsToDefaults();
}



void Quad::initializeGeometry( const float width, const float height )
{
	// Initialize geometry.

	// VERTEX
	vgd::field::EditorRW< vgd::field::MFVec3f >	vertex			= getFVertexRW();
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
	vgd::node::Primitive prim( vgd::node::Primitive::QUADS, 0, vertexIndex->size() );
	primitive->clear();
	primitive->push_back( prim );
	
	vertex.release();
	vertexIndex.release();
	primitive.release();
		
	// NORMAL
	vgd::field::EditorRW< vgd::field::MFVec3f >	normal			= getFNormalRW();	
	normal->clear();
	normal->reserve(4);
	normal->push_back( vgm::Vec3f(0.f, 0.f, 1.f ) );
	normal->push_back( vgm::Vec3f(0.f, 0.f, 1.f ) );
	normal->push_back( vgm::Vec3f(0.f, 0.f, 1.f ) );
	normal->push_back( vgm::Vec3f(0.f, 0.f, 1.f ) );

	setNormalBinding( vgd::node::BIND_PER_VERTEX );
}



void Quad::initializeTexUnits( const int32 numTexUnits, const Corner origin, const bool ccw )
{
	createTexUnits( 2, 0, numTexUnits );
	
	resetTextureCoordinates( numTexUnits, origin, ccw );
}



void Quad::resetTextureCoordinates( const int32 numTexUnits, const Corner origin, const bool ccw )
{
	for(	int32 i = 0;
			i < numTexUnits;
			++i )
	{
		vgd::field::EditorRW< vgd::field::MFVec2f >	texCoord( getFTexCoordRW<vgd::field::MFVec2f>( i ) );
		
		// TEX COORD
		texCoord->clear();
		texCoord->reserve( 4 );
		
		if ( ccw )
		{
			switch ( origin )
			{
				case BOTTOM_LEFT:
					texCoord->push_back( vgm::Vec2f( 0.f, 0.f) );
					texCoord->push_back( vgm::Vec2f( 1.f, 0.f) );
					texCoord->push_back( vgm::Vec2f( 1.f, 1.f) );
					texCoord->push_back( vgm::Vec2f( 0.f, 1.f) );
					break;
	
				case BOTTOM_RIGHT:
					texCoord->push_back( vgm::Vec2f( 1.f, 0.f) );
					texCoord->push_back( vgm::Vec2f( 1.f, 1.f) );
					texCoord->push_back( vgm::Vec2f( 0.f, 1.f) );
					texCoord->push_back( vgm::Vec2f( 0.f, 0.f) );				
					break;
				
				case TOP_RIGHT:
					texCoord->push_back( vgm::Vec2f( 1.f, 1.f) );
					texCoord->push_back( vgm::Vec2f( 0.f, 1.f) );
					texCoord->push_back( vgm::Vec2f( 0.f, 0.f) );				
					texCoord->push_back( vgm::Vec2f( 1.f, 0.f) );
					break;
				
				case TOP_LEFT:
					texCoord->push_back( vgm::Vec2f( 0.f, 1.f) );
					texCoord->push_back( vgm::Vec2f( 0.f, 0.f) );				
					texCoord->push_back( vgm::Vec2f( 1.f, 0.f) );
					texCoord->push_back( vgm::Vec2f( 1.f, 1.f) );
					break;
				
				default:
					assert(false);
			}
		}
		else
		{
			switch ( origin )
			{
				case BOTTOM_LEFT:
					texCoord->push_back( vgm::Vec2f( 0.f, 0.f) );
					texCoord->push_back( vgm::Vec2f( 0.f, 1.f) );
					texCoord->push_back( vgm::Vec2f( 1.f, 1.f) );										
					texCoord->push_back( vgm::Vec2f( 1.f, 0.f) );
					break;
	
				case BOTTOM_RIGHT:
					texCoord->push_back( vgm::Vec2f( 1.f, 0.f) );
					texCoord->push_back( vgm::Vec2f( 0.f, 0.f) );				
					texCoord->push_back( vgm::Vec2f( 0.f, 1.f) );					
					texCoord->push_back( vgm::Vec2f( 1.f, 1.f) );
					break;
				
				case TOP_RIGHT:
					texCoord->push_back( vgm::Vec2f( 1.f, 1.f) );
					texCoord->push_back( vgm::Vec2f( 1.f, 0.f) );
					texCoord->push_back( vgm::Vec2f( 0.f, 0.f) );														
					texCoord->push_back( vgm::Vec2f( 0.f, 1.f) );
					break;
				
				case TOP_LEFT:
					texCoord->push_back( vgm::Vec2f( 0.f, 1.f) );
					texCoord->push_back( vgm::Vec2f( 1.f, 1.f) );
					texCoord->push_back( vgm::Vec2f( 1.f, 0.f) );										
					texCoord->push_back( vgm::Vec2f( 0.f, 0.f) );				
					break;
				
				default:
					assert(false);
			}
		}

		setTexCoordBinding( i, vgd::node::BIND_PER_VERTEX );
	}
}



} // namespace node

} // namespace vgd
