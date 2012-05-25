// VGSDK - Copyright (C) 2012, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_POINTLIGHT_HPP
#define _VGD_NODE_POINTLIGHT_HPP

#include "vgd/field/Vec3f.hpp"
#include "vgd/node/Light.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Node representing a point light source.
 *
 * A point source illuminates equally in all directions. It is omni-directional. All shape nodes that come after this light in the scene graph are illuminated by this light. The light's location is affected by the current geometrical transformation. 
 *
 * New fields defined by this node :
 * - OFVec3f \c [position] = vgm::Vec3f(0.f, 0.f, 1.f)<br>
 *   Location of the light source.<br>
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
struct VGD_API PointLight : public vgd::node::Light
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
	static vgd::Shp< PointLight > create( const std::string nodeName = "NoName" );

	/**
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values and
	 * sets the \c multiAttributeIndex of the multi-attribute.
	 *
	 * @param index		zero-based index of the multi-attribute
	 */
	static vgd::Shp< PointLight > create( const std::string nodeName, const uint8 index );
	
	/**
	 *@brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values (optionals fields too).
	 */
	static vgd::Shp< PointLight > createWhole( const std::string nodeName = "DefaultWhole" );

	//@}



	/**
	 * @name Accessors to field position
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c position.
	 */
	typedef vgm::Vec3f PositionValueType;

	/**
	 * @brief Type definition of the field named \c position
	 */
	typedef vgd::field::TOptionalField< PositionValueType > FPositionType;


	/**
	 * @brief Gets the value of field named \c position.
	 */
	const bool getPosition( PositionValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c position.
 	 */
	void setPosition( const PositionValueType& value );

	/**
	 * @brief Erases the field named \c position.
	 */
	void erasePosition();

	/**
	 * @brief Tests if the value of field named \c position has been initialized.
	 */
	const bool hasPosition() const;
	//@}



	/**
	 * @name Field name accessors
	 */
	//@{

	/**
	 * @brief Returns the name of field \c position.
	 *
	 * @return the name of field \c position.
	 */
	static const std::string getFPosition( void );

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
	PointLight( const std::string nodeName );

public:
	IMPLEMENT_INDEXABLE_CLASS_HPP( , PointLight );
private:
	static const vgd::basic::RegisterNode<PointLight> m_registrationInstance;
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_POINTLIGHT_HPP
