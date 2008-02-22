// VGSDK - Copyright (C) 2007, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_RC_ROOT_HPP
#define _VGE_RC_ROOT_HPP

#include "vge/rc/IResource.hpp"

#include <vgd/node/Separator.hpp>



namespace vge
{
	
namespace rc
{



/**
 * @brief Root of a scene graph
 */
struct Root : public IResource
{
	/**
	 * @brief Default constructor
	 */
	VGE_API Root();

	/**
	 * @brief Gets the root node of the scene graph
	 * 
	 * @return the root node
	 */
	VGE_API const vgd::Shp< vgd::node::Separator > getRoot() const;
	
	/**
	 * @brief Gets the root node of the scene graph
	 * 
	 * @return the root node
	 */
	VGE_API vgd::Shp< vgd::node::Separator > getRoot();
	
	
	
private:

	vgd::Shp< vgd::node::Separator >	m_root;		///< The root node of the scene graph owned by this class
};



} // namespace rc

} // namespace vge

#endif //#ifndef _VGE_RC_ROOT_HPP
