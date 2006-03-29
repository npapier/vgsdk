// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_TEXTURETRANSFORMATION_HPP
#define _VGD_NODE_TEXTURETRANSFORMATION_HPP

#include "vgd/vgd.hpp"

#include "vgd/node/MultiTransformation.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Abstract base class for all texture transformation nodes.
 * 
 * @ingroup g_abstractNodes
 */
struct VGD_API TextureTransformation : public MultiTransformation
{
	//META_NODE_HPP( TextureTransformation ); abstract class.



protected:
	/**
	 * @name Constructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	TextureTransformation( const std::string nodeName );

	void	setToDefaults( void );

	void	setOptionalsToDefaults();

	//@}
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_TEXTURETRANSFORMATION_HPP
