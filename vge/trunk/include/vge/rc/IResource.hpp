// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_RC_IRESOURCE_H
#define _VGE_RC_IRESOURCE_H

#include "vge/vge.hpp"



namespace vge
{
	
namespace rc
{



struct VGE_API IResource
{
	/**
	 * @brief Virtual destructor.
	 */
	virtual ~IResource() {}
};



} // namespace rc

} // namespace vge

#endif //#ifndef _VGE_RC_IRESOURCE_H
