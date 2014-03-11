// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_ATTRIBUTE_HPP
#define _VGD_NODE_ATTRIBUTE_HPP

#include "vgd/node/Node.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Abstract class for all attribute classes.
 * 
 * @ingroup g_abstractNodes
 */
struct VGD_API Attribute : public vgd::node::Node
{
	// META_NODE_HPP( Attribute ); abstract class.



protected:
	/**
	 * @name Constructor
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	Attribute( const std::string nodeName );

	void setToDefaults( void );

	void setOptionalsToDefaults();

	//@}
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_ATTRIBUTE_HPP
