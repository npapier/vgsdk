// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_QUAD_HPP
#define _VGD_NODE_QUAD_HPP

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
 * @remarks Vertices are pulled to GPU in counter-clockwise mode and the first vertex is the BOTTOM_LEFT corner.
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
	 * @param height	height of the quad.
	 * 
	 * @remarks Called automatically during node creation.
	 */
	void initializeGeometry( const float width = 1.f, const float height = 1.f );

	/**
	 * @brief The four corners of the quad.
	 */
	enum Corner {
		BOTTOM_LEFT,
		BOTTOM_RIGHT,
		TOP_RIGHT,
		TOP_LEFT
	};

	/**
	 * @brief Initialize texture coordinates and bindings for all specified textures units.
	 * 
	 * @param numTexunits	number of desired texture coordinates and bindings
	 * @param origin		defines the origin of the texture coordinates.
	 * @param ccw			true to pull texture coordinates into the GPU in counter-clockwise mode, false to pull them
	 * 						in clockwise mode.
	 * 
	 * @remarks The parameter, named \c origin, permits to apply four different rotations (0, 90, 180, 270 degree) on the
	 * texture image.
	 * @remarks The parameter, named \c ccw, permits to flip the texture image.
	 * 
	 * @remarks This method could only be called one time.
	 */
	void initializeTexUnits( const int32 numTexUnits = 1, const Corner origin = BOTTOM_LEFT, const bool ccw = true );

	/**
	 * @brief Reset the texture coordinates and bindings for all specified textures units.
	 * 
	 * @param numTexunits	number of desired texture coordinates and bindings
	 * @param origin		defines the origin of the texture coordinates.
	 * @param ccw			true to pull texture coordinates into the GPU in counter-clockwise mode, false to pull them
	 * 						in clockwise mode.
	 * 
	 * @remarks The parameter, named \c origin, permits to apply four different rotations (0, 90, 180, 270 degree) on the
	 * texture image.
	 * @remarks The parameter, named \c ccw, permits to flip the texture image.
	 * 
	 * @pre initializeTexUnits() must have been called before.
	 */
	void resetTextureCoordinates( const int32 numTexUnits = 1, const Corner origin = BOTTOM_LEFT, const bool ccw = true );
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

#endif //#ifndef _VGD_NODE_QUAD_HPP
