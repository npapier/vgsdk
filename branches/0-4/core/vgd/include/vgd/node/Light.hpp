// VGSDK - Copyright (C) 2004, 2006, 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_LIGHT_HPP
#define _VGD_NODE_LIGHT_HPP

#include "vgd/field/Bool.hpp"
#include "vgd/field/Vector.hpp"
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
 * New fields added by this node :
 * 
 * - PAFBool \c [on] = false\n
 * 	Determines whether the source is active or inactive. When inactive, the source does not illuminate at all. 
 *	Set to true to switch on the light, false to switch off the light.
 * 
 * - PAFVec4f \c color
 * 	- [AMBIENT]		= (0 0 0 0)\n
 * 		Ambient intensity of the light.
 * 	- [DIFFUSE]		= (1 1 1 0)\n
 *		Diffuse intensity of the light.
 * 	- [SPECULAR]	= (1 1 1 0)\n
 * 		Specular intensity of the light.
 * 
 * @remarks The maximum number of lights is equal at least to 8 in OpenGL and DirectX. Feel free to use up to 8 lights.
 *
 * @todo Support for attenuation
 * @todo High-level method for changing intensity of color.*
 * 
 * @ingroup g_abstractNodes
 */
struct VGD_API Light : public vgd::node::MultiAttribute
{
	// META_NODE_HPP( Light );



	/**
	 * @name Accessors to field on
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
	typedef vgd::field::TPairAssociativeField< int /*OnParameterType*/, OnValueType > FOnType;

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
	 * @name Accessors to field color
	 */
	//@{

	/**
	 * @brief Enumeration of the \c color parameter.
	 */
	typedef enum
	{
		AMBIENT = 1,
		DIFFUSE,
		SPECULAR,
	} ColorParameterType;

	/**
	 * @brief Typedef for the \c color parameter value.
	 */
	typedef vgm::Vec4f  ColorValueType;

	/**
	 * @brief Typedef for the \c color field.
	 */	
	typedef vgd::field::TPairAssociativeField< int /*ColorParameterType*/, ColorValueType > FColorType;

	/**
	 * @brief Gets the \c color value.
	 */
	bool			getColor( const ColorParameterType param, ColorValueType& value ) const;

	/**
	 * @brief Sets the \c color value.
	 */
	void 			setColor( const ColorParameterType param, ColorValueType value );
	
	/**
	 * @brief Erase the \c color value.
	 */
	void 			eraseColor( const ColorParameterType param );
	//@}



	/**
	 * @name Fields names enumeration
	 */
	//@{
	
	/**
	 * @brief Returns the name of field \c on.
	 * 
	 * @return the name of field \c on.
	 */
	static const std::string getFOn();
	
	/**
	 * @brief Returns the name of field \c color.
	 * 
	 * @return the name of field \c color.
	 */
	static const std::string getFColor();	
	//@}



protected:
	/**
	 * @name Constructor
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

#endif //#ifndef _VGD_NODE_LIGHT_HPP
