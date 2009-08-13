// VGSDK - Copyright (C) 2004, 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_PROJECTIONTRANSFORMATION_HPP
#define _VGD_NODE_PROJECTIONTRANSFORMATION_HPP

#include "vgd/vgd.hpp"
//#include "vgd/node/SingleTransformation.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Abstract base class for all projection transformation nodes.
 * 
 * @ingroup g_abstractNodes
 */
struct VGD_API ProjectionTransformation // : public virtual SingleTransformation
{
	//META_NODE_HPP( ProjectionTransformation ); abstract class.



protected:
	/**
	  * @name Constructor
	  */
	//@{

	/**
	  * @brief Default constructor.
	  */
	ProjectionTransformation();

	void setToDefaults( void );

	void setOptionalsToDefaults();

	//@}
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_PROJECTIONTRANSFORMATION_HPP
