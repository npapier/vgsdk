// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_QUAD_H
#define _VGD_NODE_QUAD_H

#include "vgd/vgd.hpp"

#include "vgd/node/VertexShape.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Define a simple quadrilateral.
 * 
 * A specialized version of vertex shape to easily instanciate a quadrilateral shape.
 * 
 * This shape is :
 * \li centered around the origin (0,0,0).
 * \li in the (x,y) plan (i.e. z=0).
 * \li width and height of this quadrilateral are both 1.
 * \li the normal is equal to (0, 0, 1).
 * \li could optionally have texture coordinates (see initializeTex() for more details).
 *
 * @ingroup g_nodes
 * @ingroup g_shapeNodes
 */
struct VGD_API Quad : public vgd::node::VertexShape
{
	META_NODE_HPP( Quad );


	/**
	 * @name Initialization method.
	 */
	//@{
	
	/**
	 * @brief Initialize the geometry of the vertex shape.
	 * 
	 * @param width		width of the quad.
	 * @param height		height of the quad.
	 * 
	 * @remarks Called automatically during node creation.
	 */
	void initializeGeometry( const float width = 1.f, const float height = 1.f );

	/**
	 * @brief Initialize texture coordinates and bindings for all specified textures units.
	 */
	void initializeTexUnits( const int32 numTexUnits = 1 );
	
	//@}

protected:
	/**
	 * @name Constructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	Quad( const std::string nodeName );

	void	setToDefaults( void );

	void	setOptionalsToDefaults();
	
	//@}
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_QUAD_H
