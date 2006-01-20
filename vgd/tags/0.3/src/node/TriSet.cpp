// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/TriSet.hpp"

#include "vgd/field/TAccessors.hpp"



namespace vgd
{

namespace node
{



META_NODE_CPP( TriSet );



TriSet::TriSet( const std::string nodeName ) :
	vgd::node::VertexShape( nodeName )
{
	// Add field
	addField( new FNeighboursType(getFNeighbours()) );
	
	// Add dirty flags.
	addDirtyFlag(getDFNeighbours());

	// Link(s)
	link( getFVertexIndex(), getDFNeighbours() );
	link( getFPrimitive(), getDFNeighbours() );
	link( getDFNode() );	
}



void TriSet::setToDefaults()
{
	VertexShape::setToDefaults();
}



void TriSet::setOptionalsToDefaults()
{
	VertexShape::setOptionalsToDefaults();
}



// NEIGHBOURS
bool TriSet::getNeighbours( NeighboursValueType& value ) const
{
	return ( 
		vgd::field::getParameterValue< NeighboursParameterType, NeighboursValueType >( this, getFNeighbours(), NEIGHBOURS, value )
		);
}



void TriSet::setNeighbours( NeighboursValueType value )
{
	vgd::field::setParameterValue< NeighboursParameterType, NeighboursValueType >( this, getFNeighbours(), NEIGHBOURS, value );
}



void TriSet::eraseNeighbours()
{
	vgd::field::eraseParameterValue< NeighboursParameterType, NeighboursValueType >( this, getFNeighbours(), NEIGHBOURS );
}



const std::string TriSet::getFNeighbours()
{
	return ( "f_neighbours" );
}



const std::string TriSet::getDFNeighbours()
{
	return ( "df_neighbours" );
}



} // namespace node

} // namespace vgd
