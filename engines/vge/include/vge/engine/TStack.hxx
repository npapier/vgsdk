// VGSDK - Copyright (C) 2009, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier



template< typename T, class Container >
TStack< T, Container >::TStack()
{}


template< typename T, class Container >
void TStack< T, Container >::clear()
{
	m_container.clear();
}


template< typename T, class Container >
void TStack< T, Container >::clear( const T& element )
{
	clear();
	push( element );
}


template< typename T, class Container >
const bool TStack< T, Container >::isEmpty() const
{
	return m_container.empty();
}


template< typename T, class Container >
const uint TStack< T, Container >::getSize() const
{
	return m_container.size();
}


template< typename T, class Container >
const T& TStack< T, Container >::getTop() const
{
	return m_container.back();
}


template< typename T, class Container >
T& TStack< T, Container >::getTop()
{
	return m_container.back();
}


template< typename T, class Container >
void TStack< T, Container >::setTop( const T& value )
{
	m_container.back() = value;
}


template< typename T, class Container >
void TStack< T, Container >::push( const T& element )
{
	m_container.push_back( element );
}


template< typename T, class Container >
void TStack< T, Container >::push()
{
	const T& top = getTop();

	m_container.push_back( top );
}


template< typename T, class Container >
const bool TStack< T, Container >::pop()
{
	if ( m_container.size() > 0 )
	{
		m_container.pop_back();

		return true;
	}
	else
	{
		return false;
	}
}



// TStackShp
template< typename T >
TStackShp< T >::TStackShp()
{}


template< typename T >
void TStackShp< T >::push()
{
	const vgd::Shp< T > top = getTop();

	m_container.push_back( vgd::makeShp( new T(*top) ) );
}
