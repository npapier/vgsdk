// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_GEOMETRICALTRANSFORMATION_H
#define _VGD_NODE_GEOMETRICALTRANSFORMATION_H

#include "vgd/vgd.hpp"

#include "vgd/node/SingleTransformation.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Abstract base class for all geometric transformation nodes.
 */
struct VGD_API GeometricalTransformation : public SingleTransformation
{
	//META_NODE_HPP( GeometricalTransformation ); abstract class.



protected:
	/**
	 * @name Constructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	GeometricalTransformation( const std::string nodeName );

	void	setToDefaults( void );
	
	void	setOptionalsToDefaults();
		
	//@}
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_GEOMETRICALTRANSFORMATION_H
