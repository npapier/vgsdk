// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_LIGHT_H
#define _VGD_NODE_LIGHT_H

#include "vgd/vgd.hpp"

#include "vgd/field/TPairAssociativeField.hpp"
#include "vgd/node/MultiAttribute.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Abstract base class for all light source nodes.
 * 
 * Light is the abstract base class for all light nodes. A light node defines an illumination
 * source that may affect subsequent shapes in the scene graph, depending on the current lighting 
 * style. Light sources are affected by the current transformation. A light node under a separator 
 * does not affect any objects outside that separator.
 * 
 * New field added by this node :
 * 
 * - PAFBool \c [on] = false\n
 * 	Determines whether the source is active or inactive. When inactive, the
 * 	source does not illuminate at all. Set to true to switch on the light, false to switch off the light.
 * 
 * @remarks The maximum number of lights is equal at least to 8 in OpenGL and DirectX. Feel free to use up to 8 lights.
 *
 * @todo SoSFColor color, SoSFFloat 	intensity.
 */
struct VGD_API Light : public vgd::node::MultiAttribute
{
	// META_NODE_HPP( Light );



	/**
	 * @name Accessors to field on.
	 */
	//@{

	/**
	 * @brief Enumeration of the \c on parameter.
	 */
	typedef enum
	{
		ON = 1
	} OnParameterType;

	/**
	 * @brief Typedef for the \c on parameter value.
	 */
	typedef bool  OnValueType;

	/**
	 * @brief Typedef for the \c on field.
	 */	
	typedef vgd::field::TPairAssociativeField< OnParameterType, OnValueType > FOnType;

	/**
	 * @brief Gets the \c on value.
	 */
	bool			getOn( OnValueType& value ) const;

	/**
	 * @brief Sets the \c on value.
	 */
	void 			setOn( OnValueType value );
	
	/**
	 * @brief Erase the \c on value.
	 */
	void 			eraseOn();
	//@}



	/**
	 * @name Fields names enumeration.
	 */
	//@{
	
	/**
	 * @brief Returns the name of field \c on.
	 * 
	 * @return the name of field \c on.
	 */
	static const std::string getFOn( void );
	//@}



protected:
	/**
	 * @name Constructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	Light( const std::string nodeName );

	void	setToDefaults( void );
	
	void	setOptionalsToDefaults();	

	//@}
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_ALIGHT_H
