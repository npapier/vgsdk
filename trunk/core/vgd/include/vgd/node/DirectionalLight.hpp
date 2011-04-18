// VGSDK - Copyright (C) 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_DIRECTIONALLIGHT_HPP
#define _VGD_NODE_DIRECTIONALLIGHT_HPP

#include "vgd/field/Vec3f.hpp"
#include "vgd/node/Light.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Node representing a directional light source.
 *
 * This node defines a directional light source that illuminates along rays parallel to a given 3-dimensional vector. 
 *
 * New fields defined by this node :
 * - OFVec3f \c [direction] = vgm::Vec3f(0.f, 0.f, -1.f)<br>
 *   Direction of the light.<br>
 *<br>
 *
 *
 * Inherited fields from Light:
 * - OFVec4f \c [specular] = vgm::Vec4f(1.f, 1.f, 1.f, 0.f)<br>
 *   Specular intensity of the light.<br>
 *<br>
 * - OFBool \c [on] = false<br>
 *   Determines whether the source is active or inactive. When inactive, the source does not illuminate at all. Set to true to switch on the light, false to switch off the light.<br>
 *<br>
 * - OFVec4f \c [ambient] = vgm::Vec4f(0.f, 0.f, 0.f, 0.f)<br>
 *   Ambient intensity of the light.<br>
 *<br>
 * - OFVec4f \c [diffuse] = vgm::Vec4f(1.f, 1.f, 1.f, 0.f)<br>
 *   Diffuse intensity of the light.<br>
 *<br>
 * - SFBool \c castShadow = false<br>
 *   Indicating that this light casts a shadow.<br>
 *<br>
 * @ingroup g_nodes
 * @ingroup g_multiAttributeNodes
 * @ingroup g_coloringAndLightingNodes
 */
struct VGD_API DirectionalLight : public vgd::node::Light
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
	static vgd::Shp< DirectionalLight > create( const std::string nodeName = "NoName" );

	/**
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values and
	 * sets the \c multiAttributeIndex of the multi-attribute.
	 *
	 * @param index		zero-based index of the multi-attribute
	 */
	static vgd::Shp< DirectionalLight > create( const std::string nodeName, const uint8 index );
	
	/**
	 *@brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values (optionals fields too).
	 */
	static vgd::Shp< DirectionalLight > createWhole( const std::string nodeName = "DefaultWhole" );

	//@}



	/**
	 * @name Accessors to field direction
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c direction.
	 */
	typedef vgm::Vec3f DirectionValueType;

	/**
	 * @brief Type definition of the field named \c direction
	 */
	typedef vgd::field::TOptionalField< DirectionValueType > FDirectionType;


	/**
	 * @brief Gets the value of field named \c direction.
	 */
	const bool getDirection( DirectionValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c direction.
 	 */
	void setDirection( const DirectionValueType& value );

	/**
	 * @brief Erases the field named \c direction.
	 */
	void eraseDirection();

	/**
	 * @brief Tests if the value of field named \c direction has been initialized.
	 */
	const bool hasDirection() const;
	//@}



	/**
	 * @name Field name accessors
	 */
	//@{

	/**
	 * @brief Returns the name of field \c direction.
	 *
	 * @return the name of field \c direction.
	 */
	static const std::string getFDirection( void );

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
	DirectionalLight( const std::string nodeName );

public:
	IMPLEMENT_INDEXABLE_CLASS_HPP( , DirectionalLight );
private:
	static const vgd::basic::RegisterNode<DirectionalLight> m_registrationInstance;
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_DIRECTIONALLIGHT_HPP
