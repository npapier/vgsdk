// VGSDK - Copyright (C) 2004, IRCAD.
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
	return ( static_cast< float >(deg * (M_PI / 180.f)) );
}



float Utilities::rad2deg( const float rad )
{
	return ( static_cast< float >(rad * (180.f / M_PI)) );
}



} // namespace vgm
