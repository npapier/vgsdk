// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_SINGLEATTRIBUTE_H
#define _VGD_NODE_SINGLEATTRIBUTE_H

#include "vgd/vgd.hpp"

#include "vgd/node/Attribute.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Abstract class for all single attribute classes.
 */
struct VGD_API SingleAttribute : public vgd::node::Attribute
{
	// META_NODE_HPP( SingleAttribute ); abstract class.



protected:
	/**
	 * @name Constructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	SingleAttribute( const std::string nodeName );
	
	void	setToDefaults( void );	

	void	setOptionalsToDefaults();

	//@}
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_SINGLEATTRIBUTE_H
