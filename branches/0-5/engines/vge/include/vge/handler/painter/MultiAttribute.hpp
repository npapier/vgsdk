// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_HANDLER_PAINTER_MULTIATTRIBUTE_HPP
#define _VGE_HANDLER_PAINTER_MULTIATTRIBUTE_HPP

#include "vge/vge.hpp"

#include "vge/basic/TUnitContainer.hpp"
#include "vge/handler/painter/Attribute.hpp"



namespace vge
{
	
namespace handler
{

namespace painter
{


/**
 * @brief Abstract base class for handlers painting multi-attribute.
 */
struct VGE_API MultiAttribute : public Attribute
{
	template< typename MultiAttributeNode, typename State >
	const int computeMultiAttributeIndex( const MultiAttributeNode * node, vge::basic::TUnitContainer< State >& container )
	{
		// Retrieves the current multi-attribute index
		int multiAttributeIndex = node->getMultiAttributeIndex();

		// Tests if automatic computation of index must be done (i.e. special index value -1)
		if ( multiAttributeIndex == -1 )
		{
			// Automatic computation of multi attribute index
			multiAttributeIndex = container.getNum();
			//assert( container.getState(multiAttributeIndex) == 0 );
			// @todo better error handling (container.getMax())
		}
		// else nothing to do

		return multiAttributeIndex;
	}
};


} // namespace painter

} // namespace handler

} // namespace vge

#endif //#ifndef _VGE_HANDLER_PAINTER_MULTIATTRIBUTE_HPP
