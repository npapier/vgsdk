// VGSDK - Copyright (C) 2006, 2010, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgm/operations.hpp"

#include <cmath>



namespace vgm
{


const double round( const double inputValue )
{
	return floor(inputValue + 0.5f);
}


const float roundf( const float inputValue )
{
	return floorf(inputValue + 0.5f);
}


} // namespace vgm
