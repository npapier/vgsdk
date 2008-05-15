// VGSDK - Copyright (C) 2004-2006, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgm/Utilities.hpp"



namespace vgm
{



int32 Utilities::nextPower2( const int32 num )
{
	if (num == 0) return 1;

	int32 power2 = 1;
	for (; power2<num; power2 <<= 1);
	return power2;
}



float Utilities::deg2rad( const float deg )
{
	return ( static_cast< float >(deg * (vgm::PI / 180.f)) );
}



float Utilities::rad2deg( const float rad )
{
	return ( static_cast< float >(rad * (180.f / vgm::PI)) );
}



const float Utilities::linearInterpolation( const float x1, const float y1, const float x2, const float y2, const float x )
{
	assert( x2-x1 != 0 );
	
	// y = a*x + b
	const float a = (y2 - y1) / (x2 - x1);
	
	const float b = y1 - a*x1;
	
	const float y = a*x+b;
	
	return y;
}



void Utilities::linearInterpolation(	const float x1, const float y1, const float x2, const float y2,
										float& a, float& b )
{
	assert( x2-x1 != 0 );
	
	// y = a*x + b
	a = (y2 - y1) / (x2 - x1);
	
	b = y1 - a*x1;
}



const float Utilities::linearInterpolation( const float a, const float b, const float x )
{
	const float y = a*x+b;
	
	return y;
}



} // namespace vgm
