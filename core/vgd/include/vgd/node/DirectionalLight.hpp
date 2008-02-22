// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_DIRECTIONALLIGHT_HPP
#define _VGD_NODE_DIRECTIONALLIGHT_HPP

#include "vgd/vgd.hpp"

#include <vgm/Vector.hpp>

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
 * New field added by this node :
 * 
 * - PAFVec3f	\c [direction] = (0 0 -1)\n
 * 	Direction of the light.
 * 
 * @ingroup g_nodes
 * @ingroup g_multiAttributeNodes
 * @ingroup g_coloringAndLightingNodes
 */
struct VGD_API DirectionalLight : public vgd::node::Light
{
	META_NODE_HPP( DirectionalLight );



	/**
	 * @name Accessors to field direction.
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
	 * @name Fields names enumeration.
	 */
	//@{
	
	/**
	 * @brief Returns the name of field \c direction.
	 * 
	 * @return the name of field \c direction.
	 */
	static const std::string getFDirection( void );
	//@}
	
	
	
protected:
	/**
	 * @name Constructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	DirectionalLight( const std::string nodeName );

	void	setToDefaults( void );
	
	void	setOptionalsToDefaults();	

	//@}
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_DIRECTIONALLIGHT_HPP
