// VGSDK - Copyright (C) 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_OVERLAY_HPP
#define _VGD_NODE_OVERLAY_HPP

#include "vgd/node/LayerPlan.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Specialized layer plan drawn at the end of the rendering.
 *
 * This node behaves as a MultiAttribute node with an automatic index. Unlike LayerPlan, the rendering is deferred at the end of the rendering pipeline. 
 *
 * No new field defined by this node.
 *
 * Inherited fields from LayerPlan:
 * - SFFloat \c alphaScale = 1.f<br>
 *   Sets the alphaScale value used at each image update to multiply the alpha component of \c iimage by the scale factor. After this operation, the alpha component is clamped to the range [0, 1].<br>
 *<br>
 * - SFVec2f \c position = vgm::Vec2f(0.f, 0.f)<br>
 *   Sets the position of the layer plan in normalized window coordinates system. @see g_coordinatesSystem<br>
 *<br>
 * - SFIImageShp \c image = empty<br>
 *   Determines the image to display in the layer plan. You can set multiple times this field, but only if all successive images have the same format. The data and size of the image can changed, but that's all.<br>
 *<br>
 * - SFVec2f \c size = vgm::Vec2f(1.f, 1.f)<br>
 *   Sets the size of the layer plan in normalized windows coordinates system.@see g_coordinatesSystem\n- A size equal to (1, 1) means that the layer plan must fit the whole window. - A size equal to (0.5, 1) means that the layer plan fit in the half window width and fit in the whole height of the window.<br>
 *<br>
 * @ingroup g_nodes
 * @ingroup g_singleAttributeNodes
 * @ingroup g_multiAttributeNodes
 * @ingroup g_autoMultiAttributeNodes
 * @ingroup g_shapeNodes
 * @ingroup g_layerplan
 */
struct VGD_API Overlay : public vgd::node::LayerPlan
{
	/**
	 * @name Factories
	 */
	//@{

	/**
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values
	 */
	static vgd::Shp< Overlay > create( const std::string nodeName = "NoName" );

	/**
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values and
	 * sets the \c multiAttributeIndex of the multi-attribute.
	 *
	 * @param index		zero-based index of the multi-attribute
	 */
	static vgd::Shp< Overlay > create( const std::string nodeName, const uint8 index );
	
	/**
	 *@brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values (optionals fields too).
	 */
	static vgd::Shp< Overlay > createWhole( const std::string nodeName = "DefaultWhole" );

	//@}



	/**
	 * @name Field name accessors
	 */
	//@{


	//@}


	/**
	 * @name Dirty flags enumeration
	 */
	//@{


	//@}



	/**
	 * @name Constructor and initializer methods
	 */
	//@{

	void	setToDefaults( void );

	void	setOptionalsToDefaults();

	//@}

protected:
	/**
	 * @brief Default constructor
	 */
	Overlay( const std::string nodeName );

public:
	IMPLEMENT_INDEXABLE_CLASS_HPP( , Overlay );
private:
	static const vgd::basic::RegisterNode<Overlay> m_registrationInstance;
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_OVERLAY_HPP
