// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgAlg/vertexShape/texGen.hpp"

#include <vgd/node/VertexShape.hpp>



namespace vgAlg
{

namespace vertexShape
{



void computeTexGenObjectLinear( vgd::Shp< vgd::node::VertexShape > vertexShape, const vgm::Vec4f s, const vgm::Vec4f t, const uint texCoordIndex )
{
	// Create texCoord field if needed
	if ( !vertexShape->hasTexCoord( texCoordIndex ) )
	{
		vertexShape->createTexUnits( 2/*dim*/, texCoordIndex, 1 /*num*/ );
	}

	// Edit texCoord field
	vgd::field::EditorRO< vgd::field::MFVec3f >	vertices	= vertexShape->getVertexRO();
	vgd::field::EditorRW< vgd::field::MFVec2f > texCoords	= vertexShape->getTexCoordRW<vgd::field::MFVec2f>( texCoordIndex );

	const uint iEnd = vertices->size();
	for (	uint i=0; 
			i < iEnd;
			++i )
	{
		const vgm::Vec4f vertex( (*vertices)[i], 1.f );

		vgm::Vec2f texCoord;
		texCoord[0] = vertex.dot( s );
		texCoord[1] = vertex.dot( t );

		texCoords->push_back( texCoord );
	}

	vertexShape->setTexCoordBinding( texCoordIndex, vgd::node::BIND_PER_VERTEX );
}

} // namespace vertexShape

} // namespace vgAlg
