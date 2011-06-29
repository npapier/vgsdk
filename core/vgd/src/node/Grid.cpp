// VGSDK - Copyright (C) 2004, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Grid.hpp"

#include "vgd/node/detail/Node.hpp"



namespace vgd
{

namespace node
{



META_NODE_CPP( Grid );



Grid::Grid( const std::string nodeName ) :
	vgd::node::VertexShape( nodeName )
{
}



void Grid::setToDefaults( void )
{
	VertexShape::setToDefaults();

	initializeGeometry();
}



void Grid::setOptionalsToDefaults()
{
	VertexShape::setOptionalsToDefaults();
}



void Grid::initializeGeometry( const float width, const float height, const int widthSlices, const int heightSlices )
{
	vgAssert( widthSlices >= 1 );
	vgAssert( heightSlices >= 1 );

	// Initialize geometry
	const float fSizeX = 0.5f * width;
	const float fSizeY = 0.5f * height;

	const float fStepX = width / widthSlices;
	const float fStepY = height / heightSlices;

	// VERTEX
	vgd::field::EditorRW< vgd::field::MFVec3f > vertex = getFVertexRW();

	vertex->clear();

	for( int y=0; y < heightSlices; ++y )
	{
		const float bottom	= -fSizeY + y*fStepY;
		const float top		= -fSizeY + (y+1)*fStepY;
		const float left	= -fSizeX;
		const float right	= -fSizeX + fStepX;
		vgm::Vec3f leftBottom	( left,		bottom,		0.f	);
		vgm::Vec3f leftTop		( left,		top,		0.f	);
		vgm::Vec3f rightBottom	( right,	bottom,		0.f	);
		vgm::Vec3f rightTop		( right,	top,		0.f	);

		for( int x=0; x < widthSlices; ++x )
		{
			vertex->push_back( leftBottom );
			vertex->push_back( rightBottom );
			vertex->push_back( rightTop );
			vertex->push_back( leftTop );

			leftBottom[0]	+= fStepX;
			rightBottom[0]	+= fStepX;
			rightTop[0]		+= fStepX;
			leftTop[0]		+= fStepX;
		}
	}

	// VERTEX INDEX
	vgd::field::EditorRW< vgd::field::MFUInt32>	vertexIndex = getFVertexIndexRW();
	vertexIndex->clear();

	vertexIndex->reserve( vertex->size() );
	for( uint i=0; i < vertex->size(); ++i )
	{
		vertexIndex->push_back(i);
	}

	// PRIMITIVE
	vgd::field::EditorRW< vgd::field::MFPrimitive >	primitive = getFPrimitiveRW();
	vgd::node::Primitive prim( vgd::node::Primitive::QUADS, 0, vertexIndex->size() );
	primitive->clear();
	primitive->push_back( prim );

	// NORMAL
	vgd::field::EditorRW< vgd::field::MFVec3f >	normal = getFNormalRW();
	normal->clear();
	normal->reserve( vertex->size() );
	for( uint i=0; i < vertex->size(); ++i )
	{
		normal->push_back( vgm::Vec3f(0.f, 0.f, 1.f ) );
	}

	setNormalBinding( vgd::node::BIND_PER_VERTEX );
}



void Grid::initializeTexUnits( const int32 numTexUnits, const int widthSlices, const int heightSlices )
{
	createTexUnits( 2, 0, numTexUnits );

	resetTextureCoordinates( numTexUnits, widthSlices, heightSlices );
}



void Grid::resetTextureCoordinates( const int32 numTexUnits, const int widthSlices, const int heightSlices )
{
	for(	int i = 0;
			i < numTexUnits;
			++i )
	{
		vgd::field::EditorRW< vgd::field::MFVec2f >	texCoord( getFTexCoordRW<vgd::field::MFVec2f>( i ) );

		// TEX COORD
		const float fSizeX = 1.f;
		const float fSizeY = 1.f;

		const float fStepX = 1.f / widthSlices;
		const float fStepY = 1.f / heightSlices;

		texCoord->clear();

		for( int y=0; y < heightSlices; ++y )
		{
			const float bottom	= 0.f + y*fStepY;
			const float top		= 0.f + (y+1)*fStepY;
			const float left	= 0.f;
			const float right	= 0.f + fStepX;

			vgm::Vec2f leftBottom	( left,		bottom	);
			vgm::Vec2f leftTop		( left,		top		);
			vgm::Vec2f rightBottom	( right,	bottom	);
			vgm::Vec2f rightTop		( right,	top		);

			for( int x=0; x < widthSlices; ++x )
			{
				texCoord->push_back( leftBottom );
				texCoord->push_back( rightBottom );
				texCoord->push_back( rightTop );
				texCoord->push_back( leftTop );

				leftBottom[0]	+= fStepX;
				rightBottom[0]	+= fStepX;
				rightTop[0]		+= fStepX;
				leftTop[0]		+= fStepX;
			}
		}

		setTexCoordBinding( i, vgd::node::BIND_PER_VERTEX );
	}
}



} // namespace node

} // namespace vgd
