// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_VISITOR_EXCEPTIONS_HPP
#define _VGD_VISITOR_EXCEPTIONS_HPP

#include "vgd/vgd.hpp"



namespace vgd
{
	
namespace visitor
{



/**
 * @brief Cycle detector exception.
 */
struct VGD_API HasCycle
{
};



/**
 * @brief Desired stop traverse exception.
 */
struct VGD_API DesiredStop
{
};



} // namespace visitor

} // namespace vgd

#endif //#ifndef _VGD_VISITOR_EXCEPTIONS_HPP
