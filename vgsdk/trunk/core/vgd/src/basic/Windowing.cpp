// VGSDK - Copyright (C) 2007, Guillaume Brocker, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker, Nicolas Papier

#include "vgd/basic/Windowing.hpp"

#include <cassert>



namespace vgd
{

namespace basic
{
	
	
	
Windowing::Windowing( const int min, const int max )
:	m_min			( min ),
	m_max			( max ),
	m_lowOutput		(   0 ),
	m_lowAlpha		(   0 ),
	m_minOutput		(   0 ),
	m_maxOutput		( 255 ),
	m_minMaxAlpha	( 255 ),
	m_highOutput	(   0 ),
	m_highAlpha		(   0 )
{
	assert( m_min < m_max );
}



void Windowing::setOutputAlpha( const uint8 low, const uint8 minMax, const uint8 high )
{
	m_lowAlpha		= low;
	m_minMaxAlpha	= minMax;
	m_highAlpha		= high;
}



void Windowing::setOutputIntensities( const uint8 low, const uint8 min, const uint8 max, const uint8 high )
{
	m_lowOutput		= low;
	m_minOutput		= min;
	m_maxOutput		= max;
	m_highOutput	= high;
}



void Windowing::setWindow( const int min, const int max )
{
	assert( min < max );
	
	m_min = min;
	m_max = max;			
}



vgd::Shp< vgd::basic::IImage > Windowing::apply( const vgd::Shp< vgd::basic::IImage > image ) const
{
	using ::vgd::basic::IImage;
	
	switch( image->type() )
	{
	case IImage::UINT8:		return doApply<  uint8 >( image );
	case IImage::INT8:		return doApply<   int8 >( image );
	case IImage::UINT16:	return doApply< uint16 >( image );
	case IImage::INT16:		return doApply<  int16 >( image );
	case IImage::UINT32:	return doApply< uint32 >( image );
	case IImage::INT32:		return doApply<  int32 >( image );
	case IImage::FLOAT:		return doApply<  float >( image );
	case IImage::DOUBLE:	return doApply< double >( image );
	default:				assert( false && "Unsupported image type." ); 			
	}						  
}



} // namespace basic

} // namespace vgd
