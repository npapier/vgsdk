// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_POINTLIGHT_H
#define _VGD_NODE_POINTLIGHT_H

#include <vgm/Vector.hpp>

#include "vgd/vgd.hpp"
#include "vgd/node/Light.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Node representing a point light source.
 *
 * A point source illuminates equally in all directions. It is omni-directional. All shape nodes that come after this 
 * light in the scene graph are illuminated by this light. The light's location is affected by the current geometrical 
 * transformation.
 * 
 * New field added by this node :
 * 
 * - PAFVec3f	\c [position] = (0 0 1)\n
 * 	Location of the light source.
 *
 * @ingroup g_nodes
 * @ingroup g_multiAttributeNodes
 * @ingroup g_coloringAndLightingNodes
 */
struct VGD_API PointLight : public vgd::node::Light
{
	META_NODE_HPP( PointLight );



	/**
	 * @name Accessors to field position.
	 */
	//@{

	/**
	 * @brief Enumeration of the \c position parameter.
	 */
	typedef enum
	{
		POSITION = 1
	} PositionParameterType;

	/**
	 * @brief Typedef for the \c position parameter value.
	 */
	typedef vgm::Vec3f  PositionValueType;

	/**
	 * @brief Typedef for the \c position field.
	 */	
	typedef vgd::field::TPairAssociativeField< PositionParameterType, PositionValueType > FPositionType;

	/**
	 * @brief Gets the \c position value.
	 */
	bool			getPosition( PositionValueType& value ) const;

	/**
	 * @brief Sets the \c position value.
	 */
	void 			setPosition( PositionValueType value );
	
	/**
	 * @brief Erase the \c position value.
	 */
	void 			erasePosition();
	//@}



	/**
	 * @name Fields names enumeration.
	 */
	//@{
	
	/**
	 * @brief Returns the name of field \c position.
	 * 
	 * @return the name of field \c position.
	 */
	static const std::string getFPosition( void );
	//@}
	
	
	
protected:
	/**
	 * @name Constructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	PointLight( const std::string nodeName );

	void	setToDefaults( void );
	
	void	setOptionalsToDefaults();

	//@}
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_POINTLIGHT_H
