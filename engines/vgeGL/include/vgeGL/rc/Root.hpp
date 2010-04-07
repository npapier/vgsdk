// VGSDK - Copyright (C) 2007, 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGEGL_RC_ROOT_HPP
#define _VGEGL_RC_ROOT_HPP

#include <glo/IResource.hpp>
#include <vgd/node/Separator.hpp>
#include "vgeGL/vgeGL.hpp"



namespace vgeGL
{
	
namespace rc
{



/**
 * @brief Root of a scene graph
 *
 * @todo Should be in vge...
 */
struct Root : public ::glo::IResource
{
	/**
	 * @brief Default constructor
	 */
	VGEGL_API Root();

	/**
	 * @brief Gets the root node of the scene graph
	 * 
	 * @return the root node
	 */
	VGEGL_API const vgd::Shp< vgd::node::Separator > getRoot() const;
	
	/**
	 * @brief Gets the root node of the scene graph
	 * 
	 * @return the root node
	 */
	VGEGL_API vgd::Shp< vgd::node::Separator > getRoot();
	
	
	
private:

	vgd::Shp< vgd::node::Separator >	m_root;		///< The root node of the scene graph owned by this class
};



} // namespace rc

} // namespace vgeGL

#endif //#ifndef _VGEGL_RC_ROOT_HPP
