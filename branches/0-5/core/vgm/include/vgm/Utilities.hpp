// VGSDK - Copyright (C) 2004-2006, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGM_UTILITIES_HPP
#define _VGM_UTILITIES_HPP

#include "vgm/vgm.hpp"



namespace vgm
{



/**
 * @brief Some useful utility methods.
 * 
 * @ingroup vgmGroup
 */
struct Utilities
{
	/**
	 * @brief Returns the next power of 2 for non power of 2 number, otherwise returns the same value.
	 *
	 * @param	num : a number.
	 * @return	the next power of 2 for non power of 2 number, otherwise returns the same value.
	 *
	 */
	VGM_API static int32 nextPower2( const int32 num );

	VGM_API vgDEPRECATED( static float deg2rad( const float deg ) );
	VGM_API vgDEPRECATED( static float rad2deg( const float rad ) );
};



} // namespace vgm

#endif // #ifndef _VGM_UTILITIES_HPP
