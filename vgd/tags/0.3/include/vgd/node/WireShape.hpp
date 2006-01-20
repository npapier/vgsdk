// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_WIRESHAPE_H
#define _VGD_NODE_WIRESHAPE_H

#include "vgd/vgd.hpp"

#include "vgd/node/VertexShape.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Abstract class for all wireframe shape classes.
 * 
 * @ingroup g_abstractNodes
 */
struct VGD_API WireShape : public vgd::node::VertexShape
{
protected:
	/**
	 * @name Constructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	WireShape( const std::string nodeName );
	
	void	setToDefaults( void );
	
	void	setOptionalsToDefaults();	

	//@}
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_WIRESHAPE_H
