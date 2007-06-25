// VGSDK - Copyright (C) 2004, 2006, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_RC_IRESOURCE_HPP
#define _VGE_RC_IRESOURCE_HPP

#include "vge/vge.hpp"



namespace vge
{
	
namespace rc
{



struct VGE_CLASS_API IResource
{
	/**
	 * @brief Virtual destructor
	 */
	VGE_API virtual ~IResource();
};



} // namespace rc

} // namespace vge

#endif //#ifndef _VGE_RC_IRESOURCE_HPP
