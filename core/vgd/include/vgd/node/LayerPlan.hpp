// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_LAYERPLAN_HPP
#define _VGD_NODE_LAYERPLAN_HPP

#include "vgd/field/Float.hpp"
#include "vgd/field/IImageShp.hpp"
#include "vgd/field/Vec2f.hpp"
#include "vgd/node/MultiAttribute.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Defines a single layer plan (overlay or underlay).
 *
 * This node defines a layer plan that could be displayed just before the rendering (UNDERLAY) or just after (OVERLAY). In fact, the behavior depends of its position in the scene graph. It could even be displayed at any time during the rendering. todo More advanced transformation (a field \c matrixTransform) todo Support multiple layer planes at the same time and do rendering in one pass. => This class should be a multiattribute. 
 *
 * New fields defined by this node :
 * - SFFloat \c alphaScale = (1.f)<br>
 *   Sets the alphaScale value used at each image update to multiply the alpha component of \c iimage by the scale factor. After this operation, the alpha component is clamped to the range [0, 1].<br>
 *<br>
 * - SFVec2f \c position = vgm::Vec2f(0.f, 0.f)<br>
 *   Sets the position of the layer plan in normalized window coordinates system. @see g_coordinatesSystem<br>
 *<br>
 * - SFIImageShp \c image = vgd::basic::IImageShp()<br>
 *   Determines the image to display in the layer plan. You can set multiple times this field, but only if all successive images have the same format. The data and size of the image can changed, but that's all.<br>
 *<br>
 * - SFVec2f \c size = vgm::Vec2f(1.f, 1.f)<br>
 *   Sets the size of the layer plan in normalized windows coordinates system.@see g_coordinatesSystem\n - A size equal to (1, 1) means that the layer plan must fit the whole window. - A size equal to (0.5, 1) means that the layer plan fit in the half window width and fit in the whole height of the window.<br>
 *<br>
 *
 * @ingroup g_nodes
 * @ingroup g_singleAttributeNodes
 * @ingroup g_shapeNodes
 * @ingroup g_layerplan
 */
struct VGD_API LayerPlan : public vgd::node::MultiAttribute
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
	static vgd::Shp< LayerPlan > create( const std::string nodeName = "NoName" );

	/**
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values and
	 * sets the \c multiAttributeIndex of the multi-attribute.
	 *
	 * @param index		zero-based index of the multi-attribute
	 */
	static vgd::Shp< LayerPlan > create( const std::string nodeName, const uint8 index );
	
	/**
	 *@brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values (optionals fields too).
	 */
	static vgd::Shp< LayerPlan > createWhole( const std::string nodeName = "DefaultWhole" );

	//@}



	/**
	 * @name Accessors to field alphaScale
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c alphaScale.
	 */
	typedef float AlphaScaleValueType;

	/**
	 * @brief The default value of field named \c alphaScale.
	 */
	static const AlphaScaleValueType DEFAULT_ALPHASCALE;

	/**
	 * @brief Type definition of the field named \c alphaScale
	 */
	typedef vgd::field::TSingleField< AlphaScaleValueType > FAlphaScaleType;


	/**
	 * @brief Gets the value of field named \c alphaScale.
	 */
	const AlphaScaleValueType getAlphaScale() const;

	/**
	 * @brief Sets the value of field named \c alphaScale.
	 */
	void setAlphaScale( const AlphaScaleValueType value );

	//@}



	/**
	 * @name Accessors to field position
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c position.
	 */
	typedef vgm::Vec2f PositionValueType;

	/**
	 * @brief The default value of field named \c position.
	 */
	static const PositionValueType DEFAULT_POSITION;

	/**
	 * @brief Type definition of the field named \c position
	 */
	typedef vgd::field::TSingleField< PositionValueType > FPositionType;


	/**
	 * @brief Gets the value of field named \c position.
	 */
	const PositionValueType getPosition() const;

	/**
	 * @brief Sets the value of field named \c position.
	 */
	void setPosition( const PositionValueType value );

	//@}



	/**
	 * @name Accessors to field image
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c image.
	 */
	typedef vgd::basic::IImageShp ImageValueType;

	/**
	 * @brief The default value of field named \c image.
	 */
	static const ImageValueType DEFAULT_IMAGE;

	/**
	 * @brief Type definition of the field named \c image
	 */
	typedef vgd::field::TSingleField< ImageValueType > FImageType;


	/**
	 * @brief Gets the value of field named \c image.
	 */
	const ImageValueType getImage() const;

	/**
	 * @brief Sets the value of field named \c image.
	 */
	void setImage( const ImageValueType value );

	//@}



	/**
	 * @name Accessors to field size
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c size.
	 */
	typedef vgm::Vec2f SizeValueType;

	/**
	 * @brief The default value of field named \c size.
	 */
	static const SizeValueType DEFAULT_SIZE;

	/**
	 * @brief Type definition of the field named \c size
	 */
	typedef vgd::field::TSingleField< SizeValueType > FSizeType;


	/**
	 * @brief Gets the value of field named \c size.
	 */
	const SizeValueType getSize() const;

	/**
	 * @brief Sets the value of field named \c size.
	 */
	void setSize( const SizeValueType value );

	//@}



	/**
	 * @name Field name accessors
	 */
	//@{

	/**
	 * @brief Returns the name of field \c alphaScale.
	 *
	 * @return the name of field \c alphaScale.
	 */
	static const std::string getFAlphaScale( void );

	/**
	 * @brief Returns the name of field \c position.
	 *
	 * @return the name of field \c position.
	 */
	static const std::string getFPosition( void );

	/**
	 * @brief Returns the name of field \c image.
	 *
	 * @return the name of field \c image.
	 */
	static const std::string getFImage( void );

	/**
	 * @brief Returns the name of field \c size.
	 *
	 * @return the name of field \c size.
	 */
	static const std::string getFSize( void );

	//@}


	/**
	 * @name Dirty flags enumeration
	 */
	//@{

	/**
	 * @brief Returns name of dirty flag that is invalidate when \c image field is modified.
	 */
	static const std::string getDFImage();

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
	LayerPlan( const std::string nodeName );

public:
	IMPLEMENT_INDEXABLE_CLASS_HPP( , LayerPlan );
private:
	static const vgd::basic::RegisterNode<LayerPlan> m_registrationInstance;
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_LAYERPLAN_HPP
