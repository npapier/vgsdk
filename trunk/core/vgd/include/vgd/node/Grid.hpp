// VGSDK - Copyright (C) 2004, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_GRID_HPP
#define _VGD_NODE_GRID_HPP

#include "vgd/basic/Corner.hpp"
#include "vgd/node/VertexShape.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Define a grid shape.
 * 
 * A specialized version of vertex shape to easily instanciate a grid shape.
 * 
 * This shape is :
 * \li centered around the origin (0,0,0).
 * \li in the (x,y) plan (i.e. z=0).
 * \li width and height of this quadrilateral are both 1.
 * \li the normal is equal to (0, 0, 1).
 * \li could optionally have texture coordinates (see initializeTex() for more details).
 * 
 * @remarks Vertices are pulled to GPU in counter-clockwise mode and the first vertex is the BOTTOM_LEFT corner.
 *
 * @ingroup g_nodes
 * @ingroup g_shapeNodes
 */
struct VGD_API Grid : public vgd::node::VertexShape
{
	META_NODE_HPP( Grid );


	/**
	 * @name Initialization method
	 */
	//@{
	
	/**
	 * @brief Initialize the geometry of the vertex shape.
	 * 
	 * @param width			width of the grid
	 * @param height		height of the grid
	 * @param widthSlices	the grid is subdivided along the width into a number of slices given by this parameter
	 * @param heightSlices	the grid is subdivided along the height into a number of slices given by this parameter
	 * @param ccw			specifies the orientation of each quad of the grid
	 * 
	 * @remarks Called automatically during node creation.
	 */
	void initializeGeometry( const float width = 1.f, const float height = 1.f, const int widthSlices = 1, const int heightSlices = 1, const bool ccw = true );

	/**
	 * @brief Initialize texture coordinates and bindings for all specified textures units.
	 * 
	 * @param numTexUnits	number of desired texture coordinates and bindings
	 * @param widthSlices	the grid is subdivided along the width into a number of slices given by this parameter
	 * @param heightSlices	the grid is subdivided along the height into a number of slices given by this parameter
	 * @param ccw			specifies the texture coordinates orientation of each quad of the grid
	 *
	 * @remarks This method could only be called one time.
	 */
	void initializeTexUnits( const int32 numTexUnits = 1, const int widthSlices = 1, const int heightSlices = 1, const bool ccw = true );

	/**
	 * @brief Reset the texture coordinates and bindings for all specified textures units.
	 * 
	 * @param numTexUnits	number of desired texture coordinates and bindings
	 * @param widthSlices	the grid is subdivided along the width into a number of slices given by this parameter
	 * @param heightSlices	the grid is subdivided along the height into a number of slices given by this parameter
	 * @param ccw			specifies the texture coordinates orientation of each quad of the grid
	 *
	 * @pre initializeTexUnits() must have been called before.
	 */
	void resetTextureCoordinates( const int32 numTexUnits = 1, const int widthSlices = 1, const int heightSlices = 1, const bool ccw = true );
	//@}


protected:
	/**
	 * @name Constructor
	 */
	//@{

	/**
	 * @brief Default constructor
	 */
	Grid( const std::string nodeName );

	void setToDefaults( void );

	void setOptionalsToDefaults();

	//@}
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_GRID_HPP
