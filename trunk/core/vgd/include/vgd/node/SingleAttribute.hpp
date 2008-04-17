// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_SINGLEATTRIBUTE_HPP
#define _VGD_NODE_SINGLEATTRIBUTE_HPP

#include "vgd/node/Attribute.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Abstract class for all single attribute classes.
 * 
 * @ingroup g_abstractNodes
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

#endif //#ifndef _VGD_NODE_SINGLEATTRIBUTE_HPP
