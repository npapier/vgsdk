// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgd/basic/MinMax.hpp"

namespace vgd
{
	
namespace basic
{

MinMax::MinMax()
 :	m_min( std::numeric_limits<float>::max() ),
	m_max( std::numeric_limits<float>::min() )
{}


MinMax::MinMax( const float min, const float max )
 :	m_min( min ),
	m_max( max )
{
	assert( min <= max );
}


const bool MinMax::isValid() const
{
	return (	(m_min != std::numeric_limits<float>::max()) &&
				(m_max != std::numeric_limits<float>::min())	);
}


void MinMax::invalidate()
{
	m_min = std::numeric_limits<float>::max();
	m_max = std::numeric_limits<float>::min();
}


const float MinMax::getMin() const
{
	return ( m_min );
}


void MinMax::setMin( const float min )
{ 
	assert( min <= getMax() );
	m_min = min;
}


const float MinMax::getMax() const 
{ 
	return ( m_max ); 
}


void MinMax::setMax( const float max ) 
{
	assert( getMin() <= max );
	m_max = max;
}


void MinMax::set( const float min, const float max )
{
	assert( min <= max );
	
	m_min = min;
	m_max = max;
}


const float MinMax::getDelta() const
{ 
	assert( isValid() ); 
	return m_max - m_min; 
}


} // namespace basic

} // namespace vgd
