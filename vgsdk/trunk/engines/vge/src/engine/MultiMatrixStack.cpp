// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vge/engine/MultiMatrixStack.hpp"



namespace vge
{

namespace engine
{


MultiMatrixStack::MultiMatrixStack( const uint32 size, const uint32 matrixStackSizeHint ) :
	m_matrixStackSizeHint( matrixStackSizeHint )
{
	resize( size );
}



void MultiMatrixStack::resize( const uint32 size )
{
	m_stacks.resize( size );
	
	for(	uint32	i = 0;
			i < size;
			++i )
	{
		reset( i );
	}
}



int32 MultiMatrixStack::size() const
{
	return ( m_stacks.size() );
}



void MultiMatrixStack::reset( const int32 index )
{
	m_stacks[index].reserve( m_matrixStackSizeHint );
	m_stacks[index].resize( 1 );

	m_stacks[index].back().setIdentity();
}



bool MultiMatrixStack::isEmpty( const int32 index ) const
{
	return ( m_stacks[index].size() == 0 );
}



int32 MultiMatrixStack::sizeOf( const int32 index ) const
{
	return ( m_stacks[index].size() );
}



void MultiMatrixStack::setTop( const vgm::MatrixR& value, const int32 index )
{
	m_stacks[index].back() = value;
}



const vgm::MatrixR& MultiMatrixStack::getTop( const int32 index ) const
{
	return ( m_stacks[index].back() );
}



vgm::MatrixR& MultiMatrixStack::getTop( const int32 index )
{
	return ( m_stacks[index].back() );
}



void MultiMatrixStack::push( const int32 index )
{
	vgm::MatrixR topMatrix	( m_stacks[index].back() );
	
	m_stacks[index].push_back( topMatrix );
}



void MultiMatrixStack::pushAll()
{
	for(	uint32	i		= 0,
						iMax	= m_stacks.size();
			i < iMax;
			++i )
	{
		push( i );
	}
}



bool MultiMatrixStack::pop( const int32 index )
{
	if ( m_stacks[index].size() > 0 )
	{
		m_stacks[index].pop_back();
		return ( true );
	}
	else
	{
		return ( false );
	}
}



bool MultiMatrixStack::popAll()
{
	bool bRetVal(	true	);

	for(	uint32	i		= 0,
						iMax	= m_stacks.size();
			i < iMax;
			++i )
	{
		bRetVal &= pop( i );
	}
	
	return ( bRetVal );
}



void MultiMatrixStack::setMatrixStackSizeHint( const uint32 size )
{
	m_matrixStackSizeHint = size;
}



const uint32 MultiMatrixStack::getMatrixStackSizeHint() const
{
	return ( m_matrixStackSizeHint );
}



} // namespace engine

} // namespace vge
