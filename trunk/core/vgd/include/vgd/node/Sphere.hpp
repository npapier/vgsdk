// VGSDK - Copyright (C) 2006, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_SPHERE_HPP
#define _VGD_NODE_SPHERE_HPP

#include "vgd/node/VertexShape.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Sphere shape node
 * 
 * This node is a specialized version of vertex shape to easily instanciate a sphere.
 * 
 * By default, the sphere is builded with 20 triangles :
 * 
 * \li centered around the origin (0,0,0).
 * \li unit length (the radius).
 * \li any normals generated point away from the center of sphere.
 *
 * @todo method initializeTexUnits() (li could optionally have texture coordinates (see initializeTex() for more details)).
 * 
 * @ingroup g_nodes
 * @ingroup g_shapeNodes
 */
struct VGD_API Sphere : public vgd::node::VertexShape
{
	META_NODE_HPP( Sphere );


	/**
	 * @name Initialization method
	 */
	//@{
	
	/**
	 * @brief Initialize the geometry of the vertex shape
	 * 
	 * @param levels	specifies how many levels of detail we will have. 
	 * 					There will be 20*4^levels faces in there sphere.
	 * 
	 * @remarks Called automatically during node creation.
	 */
	void initializeGeometry( const uint32 levels = 0 );
	
	/**
	 * brief Initialize texture coordinates and bindings for all specified textures units
	 */
	//void initializeTexUnits( const int32 numTexUnits = 1 );
	
	//@}

protected:
	/**
	 * @name Constructor
	 */
	//@{

	/**
	 * @brief Default constructor
	 */
	Sphere( const std::string nodeName );

	void	setToDefaults( void );
	
	void	setOptionalsToDefaults();

	//@}
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_SPHERE_HPP
