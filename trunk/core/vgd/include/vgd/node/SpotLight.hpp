// VGSDK - Copyright (C) 2012, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_SPOTLIGHT_HPP
#define _VGD_NODE_SPOTLIGHT_HPP

#include "vgd/field/Float.hpp"
#include "vgd/field/Vec3f.hpp"
#include "vgd/node/PointLight.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Node representing a spotlight source.
 *
 * This node defines a spotlight style light source. A spotlight is placed at a fixed \c position in 3-space and illuminates in a cone along a particular \c direction. The illumination is within a cone whose angle is given by the \c cutOffAngle field. The intensity of the illumination drops off exponentially as a ray of light diverges from this direction toward the edges of the cone. The rate of drop-off and the angle of the cone are controlled by the \c dropOffRate and \c cutOffAngle fields. All shape nodes that come after this light in the scene graph are illuminated by this light. The light's location is affected by the current geometrical transformation. 
 *
 * New fields defined by this node :
 * - OFFloat \c [dropOffRate] = (0.f)<br>
 *   Rate of intensity drop-off per change in angle from primary direction. 0 means constant intensity, 1 means very sharp drop-off.<br>
 *<br>
 * - OFVec3f \c [direction] = vgm::Vec3f(0.f, 0.f, -1.f)<br>
 *   The direction (center axis of cone) of the light in homogeneous object coordinates.<br>
 *<br>
 * - OFFloat \c [cutOffAngle] = (90.f)<br>
 *   The angle (in degree) outside of which intensity is zero, measured from the center axis of the cone to an edge. This value must be inside [0, 90] or be equal to 180 (like PointLight node).<br>
 *<br>
 *
 *
 * Inherited fields from PointLight:
 * - OFVec3f \c [position] = vgm::Vec3f(0.f, 0.f, 1.f)<br>
 *   Location of the light source.<br>
 *<br>
 *
 * Inherited fields from Light:
 * - OFVec4f \c [specular] = vgm::Vec4f(1.f, 1.f, 1.f, 0.f)<br>
 *   Specular intensity of the light.<br>
 *<br>
 * - OFBool \c [on] = (false)<br>
 *   Determines whether the source is active or inactive. When inactive, the source does not illuminate at all. Set to true to switch on the light, false to switch off the light.<br>
 *<br>
 * - OFVec4f \c [ambient] = vgm::Vec4f(0.f, 0.f, 0.f, 0.f)<br>
 *   Ambient intensity of the light.<br>
 *<br>
 * - OFVec4f \c [diffuse] = vgm::Vec4f(1.f, 1.f, 1.f, 0.f)<br>
 *   Diffuse intensity of the light.<br>
 *<br>
 * - SFBool \c castShadow = (false)<br>
 *   Indicating that this light casts a shadow.<br>
 *<br>
 * @ingroup g_nodes
 * @ingroup g_multiAttributeNodes
 * @ingroup g_coloringAndLightingNodes
 */
struct VGD_API SpotLight : public vgd::node::PointLight
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
	static vgd::Shp< SpotLight > create( const std::string nodeName = "NoName" );

	/**
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values and
	 * sets the \c multiAttributeIndex of the multi-attribute.
	 *
	 * @param index		zero-based index of the multi-attribute
	 */
	static vgd::Shp< SpotLight > create( const std::string nodeName, const uint8 index );
	
	/**
	 *@brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values (optionals fields too).
	 */
	static vgd::Shp< SpotLight > createWhole( const std::string nodeName = "DefaultWhole" );

	//@}



	/**
	 * @name Accessors to field dropOffRate
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c dropOffRate.
	 */
	typedef float DropOffRateValueType;

	/**
	 * @brief The default value of field named \c dropOffRate.
	 */
	static const DropOffRateValueType DEFAULT_DROPOFFRATE;

	/**
	 * @brief Type definition of the field named \c dropOffRate
	 */
	typedef vgd::field::TOptionalField< DropOffRateValueType > FDropOffRateType;


	/**
	 * @brief Gets the value of field named \c dropOffRate.
	 */
	const bool getDropOffRate( DropOffRateValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c dropOffRate.
 	 */
	void setDropOffRate( const DropOffRateValueType& value );

	/**
	 * @brief Erases the field named \c dropOffRate.
	 */
	void eraseDropOffRate();

	/**
	 * @brief Tests if the value of field named \c dropOffRate has been initialized.
	 */
	const bool hasDropOffRate() const;
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
	 * @brief The default value of field named \c direction.
	 */
	static const DirectionValueType DEFAULT_DIRECTION;

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
	 * @name Accessors to field cutOffAngle
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c cutOffAngle.
	 */
	typedef float CutOffAngleValueType;

	/**
	 * @brief The default value of field named \c cutOffAngle.
	 */
	static const CutOffAngleValueType DEFAULT_CUTOFFANGLE;

	/**
	 * @brief Type definition of the field named \c cutOffAngle
	 */
	typedef vgd::field::TOptionalField< CutOffAngleValueType > FCutOffAngleType;


	/**
	 * @brief Gets the value of field named \c cutOffAngle.
	 */
	const bool getCutOffAngle( CutOffAngleValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c cutOffAngle.
 	 */
	void setCutOffAngle( const CutOffAngleValueType& value );

	/**
	 * @brief Erases the field named \c cutOffAngle.
	 */
	void eraseCutOffAngle();

	/**
	 * @brief Tests if the value of field named \c cutOffAngle has been initialized.
	 */
	const bool hasCutOffAngle() const;
	//@}



	/**
	 * @name Field name accessors
	 */
	//@{

	/**
	 * @brief Returns the name of field \c dropOffRate.
	 *
	 * @return the name of field \c dropOffRate.
	 */
	static const std::string getFDropOffRate( void );

	/**
	 * @brief Returns the name of field \c direction.
	 *
	 * @return the name of field \c direction.
	 */
	static const std::string getFDirection( void );

	/**
	 * @brief Returns the name of field \c cutOffAngle.
	 *
	 * @return the name of field \c cutOffAngle.
	 */
	static const std::string getFCutOffAngle( void );

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
	SpotLight( const std::string nodeName );

public:
	IMPLEMENT_INDEXABLE_CLASS_HPP( , SpotLight );
private:
	static const vgd::basic::RegisterNode<SpotLight> m_registrationInstance;
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_SPOTLIGHT_HPP
