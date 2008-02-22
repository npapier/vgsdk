// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_RC_BUTTONSTATESET_HPP
#define _VGE_RC_BUTTONSTATESET_HPP

#include <vgd/event/ButtonStateSet.hpp>
#include "vge/vge.hpp"
#include "vge/rc/IResource.hpp"



namespace vge
{
	
namespace rc
{

/**
 * @brief An encapsulation of a vgd::event::ButtonStateSet.
 */
struct VGE_API ButtonStateSet : public IResource, vgd::event::ButtonStateSet
{
};



} // namespace rc

} // namespace vge

#endif //#ifndef _VGE_RC_BUTTONSTATESET_HPP
