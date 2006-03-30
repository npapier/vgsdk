// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGSDK_VERSIONS_HPP
#define _VGSDK_VERSIONS_HPP

#include <string>

#include "vgsdk/vgsdk.hpp"



namespace vgsdk
{
	
/**
 * @brief Returns a release number.
 * 
 * @return a string that contains major.minor release number.
 */
VGSDK_API std::string getVersion();

} // namespace vgsdk

#endif //#ifndef _VGSDK_VERSIONS_HPP
