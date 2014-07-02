// VGSDK - Copyright (C) 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_MATERIAL_HPP
#define _VGD_NODE_MATERIAL_HPP

#include "vgd/field/Float.hpp"
#include "vgd/field/Vec3f.hpp"
#include "vgd/node/SingleAttribute.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Surface material definition node
 *
 * The Material node specifies current surface material properties for all subsequent shapes nodes  and is used by the lighting equations during rendering. The field \c opacity (alpha value) is used in the lighting computation only for the diffuse alpha component. The field \c transparency is not optional because it is used by others fields (in OpenGL ambient and others use 4 floats). 
 *
 * New fields defined by this node :
 * - SFFloat \c opacity = (1.f)<br>
 *   Sets opacity from 1.0 for being completely opaque until 0.0 for being completely transparent.<br>
 *<br>
 * - OFVec3f \c [ambient] = vgm::Vec3f(0.2f, 0.2f, 0.2f)<br>
 *   Ambient color of the surface.<br>
 *<br>
 * - OFVec3f \c [diffuse] = vgm::Vec3f(0.8f, 0.8f, 0.8f)<br>
 *   Diffuse color of the surface.<br>
 *<br>
 * - OFVec3f \c [specular] = vgm::Vec3f(0.f, 0.f, 0.f)<br>
 *   Specular color of the surface.<br>
 *<br>
 * - OFVec3f \c [emission] = vgm::Vec3f(0.f, 0.f, 0.f)<br>
 *   Emmissive color of the surface.<br>
 *<br>
 * - OFFloat \c [shininess] = (0.f)<br>
 *   Shininess coefficient of the surface. Values can range from 0.0 for no shininess (a diffuse surface) to 1.0 for maximum shininess (a highly polished surface).<br>
 *<br>
 *
 * @ingroup g_nodes
 * @ingroup g_singleAttributeNodes
 * @ingroup g_coloringAndLightingNodes
 */
struct VGD_API Material : public vgd::node::SingleAttribute
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
	static vgd::Shp< Material > create( const std::string nodeName = "NoName" );

	/**
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values and
	 * sets the \c multiAttributeIndex of the multi-attribute.
	 *
	 * @param index		zero-based index of the multi-attribute
	 */
	static vgd::Shp< Material > create( const std::string nodeName, const uint8 index );
	
	/**
	 *@brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values (optionals fields too).
	 */
	static vgd::Shp< Material > createWhole( const std::string nodeName = "DefaultWhole" );

	//@}



	/**
	 * @name Accessors to field opacity
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c opacity.
	 */
	typedef float OpacityValueType;

	/**
	 * @brief The default value of field named \c opacity.
	 */
	static const OpacityValueType DEFAULT_OPACITY;

	/**
	 * @brief Type definition of the field named \c opacity
	 */
	typedef vgd::field::TSingleField< OpacityValueType > FOpacityType;


	/**
	 * @brief Gets the value of field named \c opacity.
	 */
	const OpacityValueType getOpacity() const;

	/**
	 * @brief Sets the value of field named \c opacity.
	 */
	void setOpacity( const OpacityValueType value );

	//@}



	/**
	 * @name Accessors to field ambient
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c ambient.
	 */
	typedef vgm::Vec3f AmbientValueType;

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
	typedef vgm::Vec3f DiffuseValueType;

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
	 * @name Accessors to field specular
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c specular.
	 */
	typedef vgm::Vec3f SpecularValueType;

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
	 * @name Accessors to field emission
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c emission.
	 */
	typedef vgm::Vec3f EmissionValueType;

	/**
	 * @brief The default value of field named \c emission.
	 */
	static const EmissionValueType DEFAULT_EMISSION;

	/**
	 * @brief Type definition of the field named \c emission
	 */
	typedef vgd::field::TOptionalField< EmissionValueType > FEmissionType;


	/**
	 * @brief Gets the value of field named \c emission.
	 */
	const bool getEmission( EmissionValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c emission.
 	 */
	void setEmission( const EmissionValueType& value );

	/**
	 * @brief Erases the field named \c emission.
	 */
	void eraseEmission();

	/**
	 * @brief Tests if the value of field named \c emission has been initialized.
	 */
	const bool hasEmission() const;
	//@}



	/**
	 * @name Accessors to field shininess
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c shininess.
	 */
	typedef float ShininessValueType;

	/**
	 * @brief The default value of field named \c shininess.
	 */
	static const ShininessValueType DEFAULT_SHININESS;

	/**
	 * @brief Type definition of the field named \c shininess
	 */
	typedef vgd::field::TOptionalField< ShininessValueType > FShininessType;


	/**
	 * @brief Gets the value of field named \c shininess.
	 */
	const bool getShininess( ShininessValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c shininess.
 	 */
	void setShininess( const ShininessValueType& value );

	/**
	 * @brief Erases the field named \c shininess.
	 */
	void eraseShininess();

	/**
	 * @brief Tests if the value of field named \c shininess has been initialized.
	 */
	const bool hasShininess() const;
	//@}



	/**
	 * @name Field name accessors
	 */
	//@{

	/**
	 * @brief Returns the name of field \c opacity.
	 *
	 * @return the name of field \c opacity.
	 */
	static const std::string getFOpacity( void );

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
	 * @brief Returns the name of field \c specular.
	 *
	 * @return the name of field \c specular.
	 */
	static const std::string getFSpecular( void );

	/**
	 * @brief Returns the name of field \c emission.
	 *
	 * @return the name of field \c emission.
	 */
	static const std::string getFEmission( void );

	/**
	 * @brief Returns the name of field \c shininess.
	 *
	 * @return the name of field \c shininess.
	 */
	static const std::string getFShininess( void );

	//@}


	/**
	 * @name Dirty flags enumeration
	 */
	//@{


	//@}
	/**
	 * @brief Definition of symbolic values
	 */
	enum
	{
		SHININESS,
		EMISSION,
		SPECULAR,
		AMBIENT,
		DIFFUSE
	};



	/**
	 * @name Accessors to field color
	 *
	 * This accessors emulates the old interface of the field color using the new fields.
	 */
	//@{

	/**
	 * @brief Enumeration of the \c color parameter.
	 */
	typedef int /*vgd::field::EnumType*/ ColorParameterType;

	/**
	 * @brief Typedef for the \c color parameter value.
	 */
	typedef vgm::Vec3f  ColorValueType;

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
	vgDEPRECATED( void 			eraseColor( const ColorParameterType param ) );
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
	Material( const std::string nodeName );

public:
	IMPLEMENT_INDEXABLE_CLASS_HPP( Material );
	//IMPLEMENT_INDEXABLE_CLASS_HPP( , Material );
private:
	static const vgd::basic::RegisterNode<Material> m_registrationInstance;
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_MATERIAL_HPP
