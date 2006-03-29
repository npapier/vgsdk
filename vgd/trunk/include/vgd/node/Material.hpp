// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_MATERIAL_HPP
#define _VGD_NODE_MATERIAL_HPP

#include "vgd/vgd.hpp"

#include "vgd/field/Float.hpp"
#include "vgd/field/Vector.hpp"
#include "vgd/field/TPairAssociativeField.hpp"
#include "vgd/node/SingleAttribute.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Surface material definition node
 * 
 * The Material node specifies current surface material properties for all subsequent shapes nodes and is used by the 
 * lighting equations during rendering.
 * 
 * New fields added by this node :
 *
 * - PAFVec3f \c color
 * 	- [AMBIENT]		= (0.2 0.2 0.2)\n
 * 		Ambient color of the surface.
 * 	- [DIFFUSE]		= (0.8 0.8 0.8)\n
 *			Diffuse color of the surface.
 * 	- [SPECULAR]	= (0.0 0.0 0.0)\n
 * 		Specular color of the surface.
 * 	- [EMISSION]	= (0.0 0.0 0.0)\n
 * 		Emissive color of the surface.
 *
 * - PAFFloat \c [shininess]	= (0.0)\n
 * 		Shininess coefficient of the surface. Values can range from 0.0 for no shininess (a diffuse surface) to 
 * 		1.0 for maximum shininess (a highly polished surface).
 * 
 * - SFFloat \c transparency = (1.0)\n
 * 		Sets transparency from 1.0 for being completely opaque until 0.0 for being completely transparent.
 * 
 * @remarks field \c transparency is not optional because it is used by others fields (in OpenGL ambient and others use 
 * 4 floats).
 * 
 * @ingroup g_nodes
 * @ingroup g_singleAttributeNodes
 * @ingroup g_coloringAndLightingNodes
 */
struct VGD_API Material : public vgd::node::SingleAttribute
{
	META_NODE_HPP( Material );



	/**
	 * @name Accessors to field color.
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
		EMISSION
	} ColorParameterType;

	/**
	 * @brief Typedef for the \c color parameter value.
	 */
	typedef vgm::Vec3f  ColorValueType;

	/**
	 * @brief Typedef for the \c color field.
	 */	
	typedef vgd::field::TPairAssociativeField< ColorParameterType, ColorValueType > FColorType;

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
	 * @name Accessors to field shininess.
	 */
	//@{

	/**
	 * @brief Enumeration of the \c shininess parameter.
	 */
	typedef enum
	{
		SHININESS = 1
	} ShininessParameterType;

	/**
	 * @brief Typedef for the \c shininess parameter value.
	 */
	typedef float ShininessValueType;

	/**
	 * @brief Typedef for the \c shininess field.
	 */	
	typedef vgd::field::TPairAssociativeField< ShininessParameterType, ShininessValueType > FShininessType;

	/**
	 * @brief Gets the \c shininess value.
	 */
	bool			getShininess( float& value ) const;

	/**
	 * @brief Sets the \c shininess value.
	 */
	void 			setShininess( float value );
	
	/**
	 * @brief Erase the \c shininess value.
	 */
	void 			eraseShininess();
	//@}



	/**
	 * @name Accessors to field transparency.
	 */

	/**
	 * @brief Typedef for the \c transparency value.
	 */
	typedef float TransparencyValueType;

	/**
	 * @brief Typedef for the \c transparency field.
	 */	
	typedef vgd::field::SFFloat FTransparencyType;

	/**
	 * @brief Gets the \c transparency value.
	 */
	float	getTransparency( void ) const;

	/**
	 * @brief Sets the \c transparency value.
	 */
	void	setTransparency( float transparency );
	//@}


	
	/**
	 * @name Fields names enumeration.
	 */
	//@{
	
	/**
	 * @brief Returns the name of field \c color.
	 * 
	 * @return the name of field \c color.
	 */
	static const std::string getFColor( void );

	/**
	 * @brief Returns the name of field \c shininess.
	 * 
	 * @return the name of field \c shininess.
	 */
	static const std::string getFShininess( void );
	
	/**
	 * @brief Returns the name of field \c transparency.
	 * 
	 * @return the name of field \c transparency.
	 */
	static const std::string getFTransparency( void );
	//@}

	
	
protected:
	/**
	 * @name Constructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	Material( const std::string nodeName );

	void	setToDefaults( void );
	
	void	setOptionalsToDefaults();	

	//@}
};


} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_MATERIAL_HPP
