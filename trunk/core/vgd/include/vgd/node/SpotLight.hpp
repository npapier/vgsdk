// VGSDK - Copyright (C) 2006, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_SPOTLIGHT_HPP
#define _VGD_NODE_SPOTLIGHT_HPP

#include "vgd/field/TPairAssociativeField.hpp"
#include "vgd/node/PointLight.hpp"
#include "vgd/vgd.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Node representing a spotlight source.
 *
 * This node defines a spotlight style light source. A spotlight is placed at a fixed \c position in 3-space and 
 * illuminates in a cone along a particular \c direction. The illumination is within a cone whose angle is given by 
 * the \c cutOffAngle field. The intensity of the illumination drops off exponentially as a ray of light diverges from 
 * this direction toward the edges of the cone. The rate of drop-off and the angle of the cone are controlled by the 
 * \c dropOffRate and \c cutOffAngle fields. 
 * 
 * All shape nodes that come after this light in the scene graph are illuminated by this light. The light's location is 
 * affected by the current geometrical transformation.
 * 
 * New fields added by this node :
 * 
 * - PAFVec3f	\c [direction] = (0 0 -1)\n
 * 	The direction (center axis of cone) of the light in homogeneous object coordinates.
 * 
 * - PAFFloat 	\c [cutOffAngle] = (180) \n
 * 	The angle (in degree) outside of which intensity is zero, measured from the center axis of the cone to an edge.
 * 	This value must be inside [0, 90] or be equal to 180 (like PointLight node).
 *
 * - PAFFloat	\c [dropOffRate] = (0) \n
 *	Rate of intensity drop-off per change in angle from primary direction. 0 means constant intensity, 1 means very 
 *	sharp drop-off.
 * 
 * @ingroup g_nodes
 * @ingroup g_multiAttributeNodes
 * @ingroup g_coloringAndLightingNodes
 */
struct VGD_API SpotLight : public vgd::node::PointLight
{
	META_NODE_HPP( SpotLight );



	/**
	 * @name Accessors to field direction
	 */
	//@{

	/**
	 * @brief Enumeration of the \c direction parameter.
	 */
	typedef enum
	{
		DIRECTION = 1
	} DirectionParameterType;

	/**
	 * @brief Typedef for the \c direction parameter value.
	 */
	typedef vgm::Vec3f  DirectionValueType;

	/**
	 * @brief Typedef for the \c direction field.
	 */	
	typedef vgd::field::TPairAssociativeField< DirectionParameterType, DirectionValueType > FDirectionType;

	/**
	 * @brief Gets the \c direction value.
	 */
	bool			getDirection( DirectionValueType& value ) const;

	/**
	 * @brief Sets the \c direction value.
	 */
	void 			setDirection( DirectionValueType value );
	
	/**
	 * @brief Erase the \c direction value.
	 */
	void 			eraseDirection();
	//@}



	/**
	 * @name Accessors to field cutOffAngle
	 */
	//@{

	/**
	 * @brief Enumeration of the \c cutOffAngle parameter.
	 */
	typedef enum
	{
		CUTOFFANGLE = 1
	} CutOffAngleParameterType;

	/**
	 * @brief Typedef for the \c cutOffAngle parameter value.
	 */
	typedef float  CutOffAngleValueType;

	/**
	 * @brief Typedef for the \c cutOffAngle field.
	 */	
	typedef vgd::field::TPairAssociativeField< CutOffAngleParameterType, CutOffAngleValueType > FCutOffAngleType;

	/**
	 * @brief Gets the \c cutOffAngle value.
	 */
	bool			getCutOffAngle( CutOffAngleValueType& value ) const;

	/**
	 * @brief Sets the \c cutOffAngle value.
	 */
	void 			setCutOffAngle( CutOffAngleValueType value );
	
	/**
	 * @brief Erase the \c cutOffAngle value.
	 */
	void 			eraseCutOffAngle();
	//@}



	/**
	 * @name Accessors to field dropOffRate
	 */
	//@{

	/**
	 * @brief Enumeration of the \c dropOffRate parameter.
	 */
	typedef enum
	{
		DROPOFFRATE = 1
	} DropOffRateParameterType;

	/**
	 * @brief Typedef for the \c dropOffRate parameter value.
	 */
	typedef float  DropOffRateValueType;

	/**
	 * @brief Typedef for the \c dropOffRate field.
	 */	
	typedef vgd::field::TPairAssociativeField< DropOffRateParameterType, DropOffRateValueType > FDropOffRateType;

	/**
	 * @brief Gets the \c dropOffRate value.
	 */
	bool			getDropOffRate( DropOffRateValueType& value ) const;

	/**
	 * @brief Sets the \c dropOffRate value.
	 */
	void 			setDropOffRate( DropOffRateValueType value );
	
	/**
	 * @brief Erase the \c dropOffRate value.
	 */
	void 			eraseDropOffRate();
	//@}



	/**
	 * @name Fields names enumeration
	 */
	//@{
	
	/**
	 * @brief Returns the name of field \c direction.
	 * 
	 * @return the name of field \c direction.
	 */
	static const std::string getFDirection();
	
	/**
	 * @brief Returns the name of field \c cutOffAngle.
	 * 
	 * @return the name of field \c cutOffAngle.
	 */
	static const std::string getFCutOffAngle();
	
	/**
	 * @brief Returns the name of field \c dropOffRate.
	 * 
	 * @return the name of field \c dropOffRate.
	 */
	static const std::string getFDropOffRate();
	//@}



protected:
	/**
	 * @name Constructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	SpotLight( const std::string nodeName );

	void	setToDefaults( void );
	
	void	setOptionalsToDefaults();

	//@}
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_SPOTLIGHT_HPP
