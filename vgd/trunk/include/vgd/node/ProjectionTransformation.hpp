// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_PROJECTIONTRANSFORMATION_H
#define _VGD_NODE_PROJECTIONTRANSFORMATION_H

#include "vgd/vgd.hpp"

#include "vgd/node/SingleTransformation.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Abstract base class for all projection transformation nodes.
 * 
 * @ingroup g_abstractNodes
 */
struct VGD_API ProjectionTransformation : public SingleTransformation
{
	//META_NODE_HPP( ProjectionTransformation ); abstract class.



protected:
	/**
	 * @name Constructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	ProjectionTransformation( const std::string nodeName );

	void	setToDefaults( void );
	
	void	setOptionalsToDefaults();

	//@}
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_PROJECTIONTRANSFORMATION_H
