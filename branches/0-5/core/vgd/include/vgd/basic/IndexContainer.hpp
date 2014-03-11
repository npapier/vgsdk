// VGSDK - Copyright (C) 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_BASIC_INDEXCONTAINER_HPP
#define _VGD_BASIC_INDEXCONTAINER_HPP

#include <vector>
#include <utility>


namespace vgd
{

namespace basic
{



/**
 * @name Container of index
 */
//@{
typedef std::vector< int >														IndexContainer;

typedef std::vector< int >::const_iterator										IndexContainerConstIterator;
typedef std::vector< int >::iterator											IndexContainerIterator;

typedef std::pair< IndexContainerConstIterator, IndexContainerConstIterator >	IndexContainerConstIterators;
typedef std::pair< IndexContainerIterator, IndexContainerIterator >				IndexContainerIterators;

//@}



} // namespace basic

} // namespace vgd

#endif //#ifndef _VGD_BASIC_INDEXCONTAINER_HPP
