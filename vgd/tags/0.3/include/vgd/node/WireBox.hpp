// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_WIREBOX_H
#define _VGD_NODE_WIREBOX_H

#include "vgd/vgd.hpp"

#include "vgd/node/WireShape.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Define a 3d wireframe box.
 * 
 * A specialized version of vertex shape to easily instanciate a 3D wireframe box.
 * Boxes represent a rectangular 3D volume. The egdes of a box are parallel to the three main axes.
 * 
 * By default, the box is builded :
 * 
 * \li centered around the origin (0,0,0).
 * \li unit length.
 * \li any normals generated point away from the center of box.
 *
 * @ingroup g_nodes
 * @ingroup g_shapeNodes
 */
struct VGD_API WireBox : public vgd::node::WireShape
{
	META_NODE_HPP( WireBox );


	/**
	 * @name Initialization method.
	 */
	//@{
	
	/**
	 * @brief Initialize the geometry of the vertex shape.
	 * 
	 * @remarks Called automatically during node creation.
	 */
	void initializeGeometry();
	
	//@}

protected:
	/**
	 * @name Constructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	WireBox( const std::string nodeName );

	void	setToDefaults( void );
	
	void	setOptionalsToDefaults();	

	//@}
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_WIREBOX_H
