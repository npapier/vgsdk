// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_ATTRIBUTE_H
#define _VGD_NODE_ATTRIBUTE_H

#include "vgd/vgd.hpp"

#include "vgd/node/Node.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Abstract class for all attribute classes.
 */
struct VGD_API Attribute : public vgd::node::Node
{
	// META_NODE_HPP( Attribute ); abstract class.



protected:
	/**
	 * @name Constructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	Attribute( const std::string nodeName );
	
	void	setToDefaults( void );
	
	void	setOptionalsToDefaults();	

	//@}
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_ATTRIBUTE_H
