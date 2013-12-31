// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_ISHAPE_HPP
#define _VGD_NODE_ISHAPE_HPP

#include "vgd/vgd.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Abstract base class for all shape nodes
 * @ingroup g_abstractNodes
 */
struct VGD_API IShape
{
	void setToDefaults( void );
	void setOptionalsToDefaults();
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_ISHAPE_HPP
