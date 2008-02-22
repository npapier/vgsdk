// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_LIGHTMODEL_HPP
#define _VGD_NODE_LIGHTMODEL_HPP

#include <vgm/Rectangle.hpp>
#include <vgm/Vector.hpp>

#include "vgd/vgd.hpp"
#include "vgd/field/TPairAssociativeField.hpp"
#include "vgd/node/SingleAttribute.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Lighting model node
 * 
 * This node specifies current lighting mode (off/standard per vertex lighting/standard per pixel lighting) and some 
 * options of the lighting model.
 *
 * New field added by this node :
 * 
 * - PAFInt \c [model] = STANDARD_PER_VERTEX\n
 * 		Sets the lighting model to LIGHTING_OFF, STANDARD_PER_VERTEX or STANDARD_PER_PIXEL.
 * 
 * - PAFVec4f \c [ambient] = (0.2, 0.2, 0.2, 1.0)\n
 * 		Sets the ambient RGBA intensity of the entire scene.
 * 
 * - PAFInt \c [viewer] = AT_INFINITY\n
 * 		Specifies how specular reflection angles are computed. Possible values :
 * 		- AT_INFINITY specular reflections are computed from the origin of the eye coordinate system.
 * 		- AT_EYE specular reflection angles take the view direction to be parallel to and in the direction of the 
 * 			-z axis, regardless of the location of the vertex in eye coordinates.
 * 
 * - PAFBool \c [twoSided] = false\n
 * 	Specifies whether one- or two-sided lighting calculations are done for polygons and triangles.
 * 
 * 
 * @ingroup g_nodes
 * @ingroup g_singleAttributeNodes
 * @ingroup g_coloringAndLightingNodes
 * 
 * @todo field separateSpecularColor(- PAFBool \c [separateSpecularColor] = (false)\n)
 */
struct VGD_API LightModel : public vgd::node::SingleAttribute
{
	META_NODE_HPP( LightModel );



	/**
	 * @name Accessors to field model.
	 */
	//@{

	/**
	 * @brief Enumeration of the \c model parameter.
	 */
	typedef enum
	{
		MODEL = 1
	} ModelParameterType;

	/**
	 * @brief Typedef for the \c model parameter value.
	 */
	typedef enum
	{
		LIGHTING_OFF = 1,
		STANDARD_PER_VERTEX,
		STANDARD_PER_PIXEL,
		DEFAULT_MODEL = STANDARD_PER_VERTEX
	} ModelValueType;

	/**
	 * @brief Typedef for the \c model field.
	 */	
	typedef vgd::field::TPairAssociativeField< ModelParameterType, ModelValueType > FModelType;

	/**
	 * @brief Gets the \c model value.
	 */
	bool			getModel( ModelValueType& value ) const;

	/**
	 * @brief Sets the \c model value.
	 */
	void 			setModel( ModelValueType value /*OFF, STANDARD_PER_VERTEX, STANDARD_PER_PIXEL*/);
	
	/**
	 * @brief Erase the \c model value.
	 */
	void 			eraseModel();
	//@}



	/**
	 * @name Accessors to field ambient.
	 */
	//@{

	/**
	 * @brief Enumeration of the \c ambient parameter.
	 */
	typedef enum
	{
		AMBIENT = 1
	} AmbientParameterType;

	/**
	 * @brief Typedef for the \c ambient parameter value.
	 */
	typedef vgm::Vec4f AmbientValueType;

	/**
	 * @brief Typedef for the \c ambient field.
	 */	
	typedef vgd::field::TPairAssociativeField< AmbientParameterType, AmbientValueType > FAmbientType;

	/**
	 * @brief Gets the \c ambient value.
	 */
	bool			getAmbient( vgm::Vec4f /*AmbientValueType*/& value ) const;

	/**
	 * @brief Sets the \c ambient value.
	 */
	void 			setAmbient( vgm::Vec4f /*AmbientValueType*/ value );
	
	/**
	 * @brief Erase the \c ambient value.
	 */
	void 			eraseAmbient();
	//@}



	/**
	 * @name Accessors to field viewer.
	 */
	//@{

	/**
	 * @brief Enumeration of the \c viewer parameter.
	 */
	typedef enum
	{
		VIEWER = 1
	} ViewerParameterType;

	/**
	 * @brief Typedef for the \c viewer parameter value.
	 */
	typedef enum
	{
		AT_INFINITY = 1,
		AT_EYE,
		DEFAULT_VIEWER = AT_INFINITY
	} ViewerValueType;

	/**
	 * @brief Typedef for the \c viewer field.
	 */	
	typedef vgd::field::TPairAssociativeField< ViewerParameterType, ViewerValueType > FViewerType;

	/**
	 * @brief Gets the \c viewer value.
	 */
	bool			getViewer( ViewerValueType& value ) const;

	/**
	 * @brief Sets the \c viewer value.
	 */
	void 			setViewer( ViewerValueType value );
	
	/**
	 * @brief Erase the \c viewer value.
	 */
	void 			eraseViewer();
	//@}



	/**
	 * @name Accessors to field twoSided.
	 */
	//@{

	/**
	 * @brief Enumeration of the \c twoSided parameter.
	 */
	typedef enum
	{
		TWO_SIDED = 1
	} TwoSidedParameterType;

	/**
	 * @brief Typedef for the \c twoSided parameter value.
	 */
	typedef bool TwoSidedValueType;

	/**
	 * @brief Typedef for the \c twoSided field.
	 */	
	typedef vgd::field::TPairAssociativeField< TwoSidedParameterType, TwoSidedValueType > FTwoSidedType;

	/**
	 * @brief Gets the \c twoSided value.
	 */
	bool			getTwoSided( bool /*TwoSidedValueType*/& value ) const;

	/**
	 * @brief Sets the \c twoSided value.
	 */
	void 			setTwoSided( bool /*TwoSidedValueType*/ value );
	
	/**
	 * @brief Erase the \c twoSided value.
	 */
	void 			eraseTwoSided();
	//@}



	/**
	 * @name Fields names enumeration.
	 */
	//@{
	
	/**
	 * @brief Returns the name of field \c model.
	 * 
	 * @return the name of field \c model.
	 */
	static const std::string getFModel( void );

	/**
	 * @brief Returns the name of field \c ambient.
	 * 
	 * @return the name of field \c ambient.
	 */
	static const std::string getFAmbient( void );
	
	/**
	 * @brief Returns the name of field \c viewer.
	 * 
	 * @return the name of field \c viewer.
	 */
	static const std::string getFViewer( void );	

	/**
	 * @brief Returns the name of field \c twoSided.
	 * 
	 * @return the name of field \c twoSided.
	 */
	static const std::string getFTwoSided( void );
	//@}



protected:
	/**
	 * @name Constructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	LightModel( const std::string nodeName );

	void	setToDefaults( void );
	
	void	setOptionalsToDefaults();	

	//@}
};


} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_LIGHTMODEL_HPP
