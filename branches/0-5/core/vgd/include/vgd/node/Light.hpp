// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_LIGHT_HPP
#define _VGD_NODE_LIGHT_HPP

#include "vgd/field/Bool.hpp"
#include "vgd/field/Vec4f.hpp"
#include "vgd/node/MultiAttribute.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Abstract base class for all light source nodes
 *
 * Light is the abstract base class for all light nodes. A light node defines an illumination source that may affect subsequent shapes in the scene graph, depending on the current lighting style. Light sources are affected by the current transformation. A light node under a separator does not affect any objects outside that separator. @remarks The maximum number of lights is equal at least to 8 in OpenGL and DirectX. Feel free to use up to 8 lights. @todo Removes this limits @todo Support for attenuation @todo High-level method for changing intensity of color. 
 *
 * New fields defined by this node :
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
 *
 * @ingroup g_abstractNodes
 */
struct VGD_API Light : public vgd::node::MultiAttribute
{



	/**
	 * @name Accessors to field specular
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c specular.
	 */
	typedef vgm::Vec4f SpecularValueType;

	/**
	 * @brief The default value of field named \c specular.
	 */
	static const SpecularValueType DEFAULT_SPECULAR;

	/**
	 * @brief Type definition of the field named \c specular
	 */
	typedef vgd::field::TOptionalField< SpecularValueType > FSpecularType;


	/**
	 * @brief Gets the value of field named \c specular.
	 */
	const bool getSpecular( SpecularValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c specular.
 	 */
	void setSpecular( const SpecularValueType& value );

	/**
	 * @brief Erases the field named \c specular.
	 */
	void eraseSpecular();

	/**
	 * @brief Tests if the value of field named \c specular has been initialized.
	 */
	const bool hasSpecular() const;
	//@}



	/**
	 * @name Accessors to field on
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c on.
	 */
	typedef bool OnValueType;

	/**
	 * @brief The default value of field named \c on.
	 */
	static const OnValueType DEFAULT_ON;

	/**
	 * @brief Type definition of the field named \c on
	 */
	typedef vgd::field::TOptionalField< OnValueType > FOnType;


	/**
	 * @brief Gets the value of field named \c on.
	 */
	const bool getOn( OnValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c on.
 	 */
	void setOn( const OnValueType& value );

	/**
	 * @brief Erases the field named \c on.
	 */
	void eraseOn();

	/**
	 * @brief Tests if the value of field named \c on has been initialized.
	 */
	const bool hasOn() const;
	//@}



	/**
	 * @name Accessors to field ambient
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c ambient.
	 */
	typedef vgm::Vec4f AmbientValueType;

	/**
	 * @brief The default value of field named \c ambient.
	 */
	static const AmbientValueType DEFAULT_AMBIENT;

	/**
	 * @brief Type definition of the field named \c ambient
	 */
	typedef vgd::field::TOptionalField< AmbientValueType > FAmbientType;


	/**
	 * @brief Gets the value of field named \c ambient.
	 */
	const bool getAmbient( AmbientValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c ambient.
 	 */
	void setAmbient( const AmbientValueType& value );

	/**
	 * @brief Erases the field named \c ambient.
	 */
	void eraseAmbient();

	/**
	 * @brief Tests if the value of field named \c ambient has been initialized.
	 */
	const bool hasAmbient() const;
	//@}



	/**
	 * @name Accessors to field diffuse
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c diffuse.
	 */
	typedef vgm::Vec4f DiffuseValueType;

	/**
	 * @brief The default value of field named \c diffuse.
	 */
	static const DiffuseValueType DEFAULT_DIFFUSE;

	/**
	 * @brief Type definition of the field named \c diffuse
	 */
	typedef vgd::field::TOptionalField< DiffuseValueType > FDiffuseType;


	/**
	 * @brief Gets the value of field named \c diffuse.
	 */
	const bool getDiffuse( DiffuseValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c diffuse.
 	 */
	void setDiffuse( const DiffuseValueType& value );

	/**
	 * @brief Erases the field named \c diffuse.
	 */
	void eraseDiffuse();

	/**
	 * @brief Tests if the value of field named \c diffuse has been initialized.
	 */
	const bool hasDiffuse() const;
	//@}



	/**
	 * @name Accessors to field castShadow
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c castShadow.
	 */
	typedef bool CastShadowValueType;

	/**
	 * @brief The default value of field named \c castShadow.
	 */
	static const CastShadowValueType DEFAULT_CASTSHADOW;

	/**
	 * @brief Type definition of the field named \c castShadow
	 */
	typedef vgd::field::TSingleField< CastShadowValueType > FCastShadowType;


	/**
	 * @brief Gets the value of field named \c castShadow.
	 */
	const CastShadowValueType getCastShadow() const;

	/**
	 * @brief Sets the value of field named \c castShadow.
	 */
	void setCastShadow( const CastShadowValueType value );

	//@}



	/**
	 * @name Field name accessors
	 */
	//@{

	/**
	 * @brief Returns the name of field \c specular.
	 *
	 * @return the name of field \c specular.
	 */
	static const std::string getFSpecular( void );

	/**
	 * @brief Returns the name of field \c on.
	 *
	 * @return the name of field \c on.
	 */
	static const std::string getFOn( void );

	/**
	 * @brief Returns the name of field \c ambient.
	 *
	 * @return the name of field \c ambient.
	 */
	static const std::string getFAmbient( void );

	/**
	 * @brief Returns the name of field \c diffuse.
	 *
	 * @return the name of field \c diffuse.
	 */
	static const std::string getFDiffuse( void );

	/**
	 * @brief Returns the name of field \c castShadow.
	 *
	 * @return the name of field \c castShadow.
	 */
	static const std::string getFCastShadow( void );

	//@}


	/**
	 * @name Dirty flags enumeration
	 */
	//@{


	//@}
	/**
	 * @name Accessors to field color
	 *
	 * This accessors emulates the old interface of the field color using the new fields (ambient, diffuse and specular).
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
	vgDEPRECATED( bool			getColor( const ColorParameterType param, ColorValueType& value ) const );

	/**
	 * @brief Sets the \c color value.
	 */
	vgDEPRECATED( void 			setColor( const ColorParameterType param, ColorValueType value ) );

	/**
	 * @brief Erase the \c color value.
	 */
vgDEPRECATED( 	void 			eraseColor( const ColorParameterType param ) );
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
	Light( const std::string nodeName );

};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_LIGHT_HPP
