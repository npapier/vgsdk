// VGSDK - Copyright (C) 2004, 2012, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/node/Primitive.hpp"



namespace vgd
{

namespace node
{



Primitive::Primitive( const Type type, const int32 index, const int32 numIndices ) :
	m_type		( type ),
	m_index		( index ),
	m_numIndices( numIndices )
{
}



void Primitive::setType( const Type type )
{
	m_type = type;
}



const Primitive::Type Primitive::getType() const
{
	return ( m_type );
}



void Primitive::setIndex( const int32 index )
{
	m_index = index;
}



const int32 Primitive::getIndex() const
{
	return ( m_index );
}



void Primitive::setNumIndices( const int32 numIndices )
{
	m_numIndices = numIndices;
}



const int32 Primitive::getNumIndices() const
{
	return ( m_numIndices );
}



void Primitive::addToNumIndices( const int32 value )
{
	m_numIndices += value;
}


} // namespace node

} // namespace vgd
