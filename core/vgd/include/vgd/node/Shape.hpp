// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_SHAPE_HPP
#define _VGD_NODE_SHAPE_HPP

#include "vgd/vgd.hpp"

#include "vgd/node/IBoundingBox.hpp"

#include "vgd/node/IShape.hpp"
#include "vgd/node/Node.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Abstract base class for all shape nodes.
 * 
 * @ingroup g_abstractNodes
 */
struct VGD_API Shape : public vgd::node::Node, public vgd::node::IBoundingBox, public vgd::node::IShape
{
	//META_NODE_HPP( Shape ); abstract class.



protected:

	/**
	 * @name Constructor.
	 */
	//@{
	
	/**
	 * @brief Default constructor.
	 */
	Shape( const std::string nodeName );
	
	void	setToDefaults( void );

	void	setOptionalsToDefaults();

	//@}
};



} // namespace node

} // namespace vgd

#endif // #ifndef _VGD_NODE_SHAPE_HPP
