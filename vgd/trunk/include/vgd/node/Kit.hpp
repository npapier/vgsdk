// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_KIT_H
#define _VGD_NODE_KIT_H

#include "vgd/vgd.hpp"

#include "vgd/node/Separator.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Abstract base class for all node kits.
 */
struct VGD_API Kit : public Separator
{
	//META_NODE_HPP( Kit ); abstract class.



protected:
	/**
	 * @name Constructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	Kit( const std::string nodeName );

	void	setToDefaults( void );
	
	void	setOptionalsToDefaults();

	//@}
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_KIT_H
