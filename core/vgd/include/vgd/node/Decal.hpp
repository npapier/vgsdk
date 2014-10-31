// VGSDK - Copyright (C) 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_DECAL_HPP
#define _VGD_NODE_DECAL_HPP

#include "vgd/field/Bool.hpp"
#include "vgd/field/Texture2DShp.hpp"
#include "vgd/field/VertexShapeShp.hpp"
#include "vgd/node/MultiAttribute.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Project a texture onto a shape.
 *
 * Decals are typically used to create hit effects or to add local details to a shape. TODO explain how the create the decal proxy geometry (the vertex shape) TODO explain how to apply the texture to the vertex shape TODO explain deferred rendering 
 *
 * New fields defined by this node :
 * - SFTexture2DShp \c texture = vgd::node::Texture2DShp()<br>
 *   Texture to apply to the shape defined by field 'shape'<br>
 *<br>
 * - SFVertexShapeShp \c shape = vgd::node::VertexShapeShp()<br>
 *   Surface of the decal<br>
 *<br>
 * - SFBool \c alphaTest = (true)<br>
 *   True to enable alpha test passing if the incoming alpha value is greater than 0, false to disable alpha test<br>
 *<br>
 * - SFBool \c blending = (false)<br>
 *   True to enable blending using function defined by glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA), false to disable blending.<br>
 *<br>
 *
 * @ingroup g_nodes
 * @ingroup g_multiAttributeNodes
 * @ingroup g_autoMultiAttributeNodes
 * @ingroup g_texturingNodes
 * @ingroup g_shapeNodes
 */
struct VGD_API Decal : public vgd::node::MultiAttribute
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
	static vgd::Shp< Decal > create( const std::string nodeName = "NoName" );

	/**
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values and
	 * sets the \c multiAttributeIndex of the multi-attribute.
	 *
	 * @param index		zero-based index of the multi-attribute
	 */
	static vgd::Shp< Decal > create( const std::string nodeName, const uint8 index );
	
	/**
	 *@brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values (optionals fields too).
	 */
	static vgd::Shp< Decal > createWhole( const std::string nodeName = "DefaultWhole" );

	//@}



	/**
	 * @name Accessors to field texture
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c texture.
	 */
	typedef vgd::node::Texture2DShp TextureValueType;

	/**
	 * @brief The default value of field named \c texture.
	 */
	static const TextureValueType DEFAULT_TEXTURE;

	/**
	 * @brief Type definition of the field named \c texture
	 */
	typedef vgd::field::TSingleField< TextureValueType > FTextureType;


	/**
	 * @brief Gets the value of field named \c texture.
	 */
	const TextureValueType getTexture() const;

	/**
	 * @brief Sets the value of field named \c texture.
	 */
	void setTexture( const TextureValueType value );

	//@}



	/**
	 * @name Accessors to field shape
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c shape.
	 */
	typedef vgd::node::VertexShapeShp ShapeValueType;

	/**
	 * @brief The default value of field named \c shape.
	 */
	static const ShapeValueType DEFAULT_SHAPE;

	/**
	 * @brief Type definition of the field named \c shape
	 */
	typedef vgd::field::TSingleField< ShapeValueType > FShapeType;


	/**
	 * @brief Gets the value of field named \c shape.
	 */
	const ShapeValueType getShape() const;

	/**
	 * @brief Sets the value of field named \c shape.
	 */
	void setShape( const ShapeValueType value );

	//@}



	/**
	 * @name Accessors to field alphaTest
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c alphaTest.
	 */
	typedef bool AlphaTestValueType;

	/**
	 * @brief The default value of field named \c alphaTest.
	 */
	static const AlphaTestValueType DEFAULT_ALPHATEST;

	/**
	 * @brief Type definition of the field named \c alphaTest
	 */
	typedef vgd::field::TSingleField< AlphaTestValueType > FAlphaTestType;


	/**
	 * @brief Gets the value of field named \c alphaTest.
	 */
	const AlphaTestValueType getAlphaTest() const;

	/**
	 * @brief Sets the value of field named \c alphaTest.
	 */
	void setAlphaTest( const AlphaTestValueType value );

	//@}



	/**
	 * @name Accessors to field blending
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c blending.
	 */
	typedef bool BlendingValueType;

	/**
	 * @brief The default value of field named \c blending.
	 */
	static const BlendingValueType DEFAULT_BLENDING;

	/**
	 * @brief Type definition of the field named \c blending
	 */
	typedef vgd::field::TSingleField< BlendingValueType > FBlendingType;


	/**
	 * @brief Gets the value of field named \c blending.
	 */
	const BlendingValueType getBlending() const;

	/**
	 * @brief Sets the value of field named \c blending.
	 */
	void setBlending( const BlendingValueType value );

	//@}



	/**
	 * @name Field name accessors
	 */
	//@{

	/**
	 * @brief Returns the name of field \c texture.
	 *
	 * @return the name of field \c texture.
	 */
	static const std::string getFTexture( void );

	/**
	 * @brief Returns the name of field \c shape.
	 *
	 * @return the name of field \c shape.
	 */
	static const std::string getFShape( void );

	/**
	 * @brief Returns the name of field \c alphaTest.
	 *
	 * @return the name of field \c alphaTest.
	 */
	static const std::string getFAlphaTest( void );

	/**
	 * @brief Returns the name of field \c blending.
	 *
	 * @return the name of field \c blending.
	 */
	static const std::string getFBlending( void );

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
	Decal( const std::string nodeName );

public:
	IMPLEMENT_INDEXABLE_CLASS_HPP( Decal );
private:
	static const vgd::basic::RegisterNode<Decal> m_registrationInstance;
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_DECAL_HPP
