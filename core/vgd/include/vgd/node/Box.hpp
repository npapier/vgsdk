// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_BOX_HPP
#define _VGD_NODE_BOX_HPP

#include "vgd/node/VertexShape.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Define a 3d box.
 * 
 * A specialized version of vertex shape to easily instanciate a 3D box.
 * Boxes represent a rectangular 3D volume. The egdes of a box are parallel to the three main axes.
 * 
 * By default, the box is builded :
 * 
 * \li centered around the origin (0,0,0).
 * \li unit length.
 * \li any normals generated point away from the center of box.
 *
 * @todo method initializeTexUnits() (li could optionally have texture coordinates (see initializeTex() 
 * for more details)).
 * 
 * @ingroup g_nodes
 * @ingroup g_shapeNodes
 */
struct VGD_API Box : public vgd::node::VertexShape
{
	META_NODE_HPP( Box );


	/**
	 * @name Initialization method
	 */
	//@{
	
	/**
	 * @brief Initialize the geometry of the vertex shape.
	 * 
	 * @remarks Called automatically during node creation.
	 */
	void initializeGeometry();
	
	/**
	 * brief Initialize texture coordinates and bindings for all specified textures units.
	 */
	//void initializeTexUnits( const int32 numTexUnits = 1 );
	
	//@}

protected:
	/**
	 * @name Constructor
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	Box( const std::string nodeName );

	void	setToDefaults( void );
	
	void	setOptionalsToDefaults();	

	//@}
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_BOX_HPP
