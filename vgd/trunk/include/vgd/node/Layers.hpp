// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_LAYERS_H
#define _VGD_NODE_LAYERS_H

#include "vgd/node/ILayers.hpp"
#include "vgd/vgd.hpp"



namespace vgd
{

namespace node
{

struct Quad;
struct Switch;

/**
 * @brief Layers definition node.
 * 
 * This node is used to compose any number of images on a quadrilateral object. This is a simplified version of layout 
 * management that you can founded in Gimp, but the quadrilateral is drawn in a three dimension space.
 * Images are indexed from 0 to the number of image minus one and are drawn in this order. The first image is blended 
 * with the framebuffer using a function specifing the pixel arithmetic between the two. The result is send to 
 * the framebuffer. The same process occurs the second and the following images. More informations about image 
 * composition are given below.
 * 
 * To simulate 2D layout management, move the quadrilateral in front of the rendering window and align it to axis \c x 
 * and \axis \c y.
 * 
 * @par Compose functions.
 * 
 * See vgd::node::ILayers
 * 
 * @par Masking.
 * 
 * See vgd::node::ILayers
 * 
 * @bug	when a scissor composite operator is changed to another one. All following images must be invalidate.
 * @todo [MUST BE DONE] Palette texture (very useful for “fênetrage” and decrease the memory requirements).
 * @todo BOTTLENECK: SCISSOR is partially done in software !!!
 * @todo [MUST BE DONE] Allow transformation to be applied to each layer.
 * 
 * @todo Hints about usage on image (STATIC and DYNAMIC).
 * @todo Mipmapping (useful only for STATIC images).
 * @todo Texture compression.
 * @todo Use multitexturing and more... (rendering speed).
 * @todo Computing the resulting image (useful in 3D mode to not recompute Layers for each new frame).
 * @todo Add support for grayscale and boolean image (RGBA is very memory hungry).
 * @todo Support image that are not stored contiguously in memory (this is the case for inrimage).
 * @todo Allow dynamic modification for the number of layer in a vgd::node::Layers.
 * @todo Support images with differents sizes.
 * @todo Polish the current implementation
 * @todo Add an UNSCISSOR composite operator to disable scissor.
 * @todo “Fênetrage” is not done by the Layers node.
 * @todo Destruction of field (removeLayers())
 * 
 * @ingroup g_nodes
 * @ingroup g_nodekits
 */
struct VGD_API Layers : public vgd::node::ILayers
{
	META_NODE_HPP( Layers );


	// Overloaded method.
	void createLayers( const int32 num = 1 );


	/**
	 * @name Geometry accessors.
	 */
	//@{
	
	/**
	 * @brief Reset the proxy geometry of this node to its initial state.
	 */
	void resetGeometry();
	
	/**
	 * @copydoc VertexShape::transform(const vgm::MatrixR&,const bool);
	 */
	void transform( const vgm::MatrixR& matrix, const bool normalize = true );
	
	/**
	 * @copydoc VertexShape::transform(const vgm::Vec3f);
	 */	
	void transform( const vgm::Vec3f translation );	

	//@}



	/**
	 * @name Bounding box.
	 */
	//@{

	/**
	 * @remarks This method is overridden, because the sub scene graph of the Layers node
	 * is not used like others (the paint service is done partially with C++/OpenGL code and evaluation
	 * of node, so the sub scene graph is used only like a hidden repository).
	 */
	bool computeBoundingBox( const vgm::MatrixR& transformation );

	//@}
	
	

protected:
	/**
	 * @name Constructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	Layers( const std::string nodeName );

	void	setToDefaults( void );

	void	setOptionalsToDefaults();

	//@}
	
private:
	vgd::Shp< vgd::node::Switch>	getSwitch();
	vgd::Shp< vgd::node::Quad >	getQuad();
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_LAYERS_H
