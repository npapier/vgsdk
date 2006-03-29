// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_WIREQUAD_HPP
#define _VGD_NODE_WIREQUAD_HPP

#include "vgd/vgd.hpp"

#include "vgd/node/WireShape.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Define a simple wireframe quadrilateral.
 * 
 * A specialized version of vertex shape to easily instanciate a quadrilateral shape drawn in wireframe.
 * 
 * This shape is :
 * \li centered around the origin (0,0,0).
 * \li in the (x,y) plan (i.e. z=0).
 * \li width and height of this quadrilateral are both 1.
 * \li the normal is equal to (0, 0, 1).
 *
 * @ingroup g_nodes
 * @ingroup g_shapeNodes
 */
struct VGD_API WireQuad : public vgd::node::WireShape
{
	META_NODE_HPP( WireQuad );


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

	//@}

protected:
	/**
	 * @name Constructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	WireQuad( const std::string nodeName );

	void	setToDefaults( void );

	void	setOptionalsToDefaults();
	
	//@}
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_WIREQUAD_HPP
