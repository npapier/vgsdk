// VGSDK - Copyright (C) 2007, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_LAYERPLAN_HPP
#define _VGD_NODE_LAYERPLAN_HPP

#include "vgd/field/Enum.hpp"
#include "vgd/field/Image.hpp"
#include "vgd/field/Vector.hpp"
#include "vgd/node/MultiAttribute.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Defines a single layer plan (overlay or underlay).
 * 
 * This node defines a layer plan that could be displayed just before the rendering (UNDERLAY) or just after (OVERLAY).
 * 
 * Althought this class is a node, adding it to a scene graph is not allowed (an exception is raised). Layer plan must 
 * be attached to canvas.
 * 
 * New fields added by this node :
 * 
 * - SFEnum \c type = (OVERLAY)\n
 * 		Sets the type of layer plan. Choose one value among OVERLAY or UNDERLAY.
 * 
 * - SFVec2f \c position = (0, 0)\n
 * 		Sets the position of the layer plan in normalized window coordinates system.
 * 		@see g_coordinatesSystem\n
 * 
 * - SFVec2f \c size = (1, 1)\n
 * 		Sets the size of the layer plan in normalized windows coordinates system.
 * 		@see g_coordinatesSystem\n
 * 		- A size equal to (1, 1) means that the layer plan must fit the whole window.
 * 		- A size equal to (0.5, 1) means that the layer plan fit in the half window width and fit in the whole
 * 			height of the window.
 * 
 * - SFIImage \c iimage = 0\n
 * 		Determines the image to display in the layer plan.
 * 		You can set multiple times this field, but only if all successive images have the same format.
 * 		The data and size of the image can changed, but that's all.
 * 
 * @ingroup g_nodes
 * @ingroup g_multiAttributeNodes
 * 
 * @todo More advanced transformation (a field \c matrixTransform)
 * @todo Support of multiple layer planes, because this class is a multiattribute.
 */
struct VGD_API LayerPlan : public vgd::node::MultiAttribute
{
	META_NODE_HPP( LayerPlan );



	/**
	 * @name Accessors to field type
	 */
	//@{

	/**
	 * @brief Typedef for the \c type value.
	 */
	enum TypeValueType
	{
		OVERLAY = 0,
		UNDERLAY,
		DEFAULT_TYPE = OVERLAY
	};

	/**
	 * @brief Typedef for the \c type field.
	 */	
	typedef vgd::field::TSingleField< TypeValueType > FTypeType;

	/**
	 * @brief Gets the type of node.
	 */
	const TypeValueType	getType() const;

	/**
	 * @brief Sets the type of node.
	 * 
	 */
	void				setType( const TypeValueType value );

	//@}



	/**
	 * @name Accessors to field position
	 */
	//@{

	/**
	 * @brief Typedef for the \c position field.
	 */	
	typedef vgd::field::SFVec2f  FPositionType;
		
	/**
	 * @brief Typedef for the \c position value.
	 */
	typedef vgm::Vec2f PositionValueType;
	
	/**
	 * @brief Gets the position of node.
	 */
	const PositionValueType	getPosition() const;

	/**
	 * @brief Sets the position of node.
	 */
	void					setPosition( const PositionValueType value );

	//@}



	/**
	 * @name Accessors to field size
	 */
	//@{

	/**
	 * @brief Typedef for the \c size field.
	 */	
	typedef vgd::field::SFVec2f FSizeType;
		
	/**
	 * @brief Typedef for the \c size value.
	 */
	typedef vgm::Vec2f SizeValueType;
	
	/**
	 * @brief Gets the size of node.
	 */
	const SizeValueType	getSize() const;

	/**
	 * @brief Sets the size of node.
	 * 
	 */
	void				setSize( const SizeValueType value );

	//@}



	/**
	 * @name Accessors to field iimage
	 */
	//@{

	/**
	 * @brief Typedef for the \c iimage field.
	 */	
	typedef vgd::field::SFIImage FIImageType;
		
	/**
	 * @brief Typedef for the \c iimage value.
	 */
	typedef vgd::Shp< vgd::basic::IImage > IImageValueType;
	
	/**
	 * @brief Gets the iimage of node.
	 */
	const IImageValueType	getIImage() const;

	/**
	 * @brief Sets the iimage of node.
	 * 
	 */
	void				setIImage( const IImageValueType value );

	//@}



	/**
	 * @name Fields names enumeration
	 */
	//@{
	
	/**
	 * @brief Returns the name of field \c type.
	 * 
	 * @return the name of field \c type.
	 */
	static const std::string getFType();

	/**
	 * @brief Returns the name of field \c position.
	 * 
	 * @return the name of field \c position.
	 */
	static const std::string getFPosition();

	/**
	 * @brief Returns the name of field \c size.
	 * 
	 * @return the name of field \c size.
	 */
	static const std::string getFSize();

	/**
	 * @brief Returns the name of field \c iimage.
	 * 
	 * @return the name of field \c iimage.
	 */
	static const std::string getFIImage();

	//@}



	/**
	 * @name Dirty flags enumeration
	 */
	//@{

	/**
	 * @brief Returns name of dirty flag that is invalidate when iimage field is modified.
	 */
	static const std::string getDFIImage();

	//@}



protected:
	/**
	 * @name Constructor
	 */
	//@{

	/**
	 * @brief Default constructor
	 */
	LayerPlan( const std::string nodeIImage );

	void	setToDefaults( void );

	void	setOptionalsToDefaults();
	
	//@}
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_LAYERPLAN_HPP
