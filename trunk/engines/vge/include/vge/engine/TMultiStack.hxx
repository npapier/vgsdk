// VGSDK - Copyright (C) 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier



template< typename T >
TMultiStack<T>::TMultiStack( const uint numberOfStacks )
{
	resize( numberOfStacks );
}


template< typename T >
void TMultiStack<T>::clear()
{
	m_stacks.resize( 0 );
}


template< typename T >
void TMultiStack<T>::resize( const uint numberOfStacks )
{
	m_stacks.resize( numberOfStacks );

	for( uint i = 0; i < numberOfStacks; ++i )
	{
		(*this)[i].clear();
	}
}


template< typename T >
const bool TMultiStack<T>::isEmpty() const
{
	return m_stacks.size() == 0;
}


template< typename T >
const uint TMultiStack<T>::getSize() const
{
	return m_stacks.size();
}


template< typename T >
typename TMultiStack<T>::StackType& TMultiStack<T>::operator []( const uint index )
{
	return m_stacks[index];
}


template< typename T >
const typename TMultiStack<T>::StackType& TMultiStack<T>::operator []( const uint index ) const
{
	return m_stacks[index];
}


template< typename T >
void TMultiStack<T>::setTop( const T& value )
{
	for( uint i = 0; i < getSize(); ++i )
	{
		(*this)[i].setTop( value );
	}
}


template< typename T >
void TMultiStack<T>::push( const T& element )
{
	for( uint i = 0; i < getSize(); ++i )
	{
		(*this)[i].push( element );
	}
}


template< typename T >
void TMultiStack<T>::push()
{
	for( uint i = 0; i < getSize(); ++i )
	{
		(*this)[i].push();
	}
}


template< typename T >
const bool TMultiStack<T>::pop()
{
	for( uint i = 0; i < getSize(); ++i )
	{
		(*this)[i].pop();
	}
}
