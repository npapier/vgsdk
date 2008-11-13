// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_MATERIAL_HPP
#define _VGD_NODE_MATERIAL_HPP

#include "vgd/field/Enum.hpp"
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
 * The Material node specifies current surface material properties for all subsequent shapes nodes  and is used by the lighting equations during rendering. The field \c transparency is not optional because it is used by others fields (in OpenGL ambient and others use 4 floats). 
 *
 * New fields defined by this node :
 *	- PAFFloat \c shininess = 0.f\n
 *		Shininess coefficient of the surface. Values can range from 0.0 for no shininess (a diffuse surface) to 1.0 for maximum shininess (a highly polished surface).
 *	- PAFVec3f \c emission = vgm::Vec3f(0.f, 0.f, 0.f)\n
 *		Emmissive color of the surface.
 *	- PAFVec3f \c specular = vgm::Vec3f(0.f, 0.f, 0.f)\n
 *		Specular color of the surface.
 *	- SFFloat \c transparency = 1.f\n
 *		Sets transparency from 1.0 for being completely opaque until 0.0 for being completely transparent.
 *	- PAFVec3f \c ambient = vgm::Vec3f(0.2f, 0.2f, 0.2f)\n
 *		Ambient color of the surface.
 *	- PAFVec3f \c diffuse = vgm::Vec3f(0.8f, 0.8f, 0.8f)\n
 *		Diffuse color of the surface.
 *
 * Inherited fields :
 * @todo generates this section
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
	 *@brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values (optionals fields too).
	 */
	static vgd::Shp< Material > createWhole( const std::string nodeName = "DefaultWhole" );

	//@}



	/**
	 * @name Accessors to field \c shininess
	 */
	//@{

	/**
	 * @brief Type definition of the parameter contained by field named \c shininess.
	 */
	typedef vgd::field::Enum ShininessParameterType;

	/**
	 * @brief Definition of symbolic values
	 */
	enum
	{
		SHININESS = 267,	///< Shininess coefficient of the surface. Values can range from 0.0 for no shininess (a diffuse surface) to 1.0 for maximum shininess (a highly polished surface).
		DEFAULT_SHININESS = SHININESS	///< Shininess coefficient of the surface. Values can range from 0.0 for no shininess (a diffuse surface) to 1.0 for maximum shininess (a highly polished surface).
	};

	/**
	 * @brief Type definition of the value contained by field named \c shininess.
	 */
	typedef float ShininessValueType;

	/**
	 * @brief Type definition of the field named \c shininess
	 */
	typedef vgd::field::TPairAssociativeField< ShininessParameterType, ShininessValueType > FShininessType;


	/**
	 * @brief Gets the value of field named \c shininess.
	 */
	const bool getShininess( ShininessValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c shininess.
 	 */
	void setShininess( ShininessValueType value );

	/**
	 * @brief Erases the field named \c shininess.
	 */
	void eraseShininess();
	//@}



	/**
	 * @name Accessors to field \c emission
	 */
	//@{

	/**
	 * @brief Type definition of the parameter contained by field named \c emission.
	 */
	typedef vgd::field::Enum EmissionParameterType;

	/**
	 * @brief Definition of symbolic values
	 */
	enum
	{
		EMISSION = 266,	///< Emmissive color of the surface.
		DEFAULT_EMISSION = EMISSION	///< Emmissive color of the surface.
	};

	/**
	 * @brief Type definition of the value contained by field named \c emission.
	 */
	typedef vgm::Vec3f EmissionValueType;

	/**
	 * @brief Type definition of the field named \c emission
	 */
	typedef vgd::field::TPairAssociativeField< EmissionParameterType, EmissionValueType > FEmissionType;


	/**
	 * @brief Gets the value of field named \c emission.
	 */
	const bool getEmission( EmissionValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c emission.
 	 */
	void setEmission( EmissionValueType value );

	/**
	 * @brief Erases the field named \c emission.
	 */
	void eraseEmission();
	//@}



	/**
	 * @name Accessors to field \c specular
	 */
	//@{

	/**
	 * @brief Type definition of the parameter contained by field named \c specular.
	 */
	typedef vgd::field::Enum SpecularParameterType;

	/**
	 * @brief Definition of symbolic values
	 */
	enum
	{
		SPECULAR = 265,	///< Specular color of the surface.
		DEFAULT_SPECULAR = SPECULAR	///< Specular color of the surface.
	};

	/**
	 * @brief Type definition of the value contained by field named \c specular.
	 */
	typedef vgm::Vec3f SpecularValueType;

	/**
	 * @brief Type definition of the field named \c specular
	 */
	typedef vgd::field::TPairAssociativeField< SpecularParameterType, SpecularValueType > FSpecularType;


	/**
	 * @brief Gets the value of field named \c specular.
	 */
	const bool getSpecular( SpecularValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c specular.
 	 */
	void setSpecular( SpecularValueType value );

	/**
	 * @brief Erases the field named \c specular.
	 */
	void eraseSpecular();
	//@}



	/**
	 * @name Accessors to field \c transparency
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c transparency.
	 */
	typedef float TransparencyValueType;

	/**
	 * @brief Type definition of the field named \c transparency
	 */
	typedef vgd::field::SFFloat FTransparencyType;


	/**
	 * @brief Gets the value of field named \c transparency.
	 */
	const TransparencyValueType getTransparency() const;

	/**
	 * @brief Sets the value of field named \c transparency.
	 */
	void setTransparency( const TransparencyValueType value );

	//@}



	/**
	 * @name Accessors to field \c ambient
	 */
	//@{

	/**
	 * @brief Type definition of the parameter contained by field named \c ambient.
	 */
	typedef vgd::field::Enum AmbientParameterType;

	/**
	 * @brief Definition of symbolic values
	 */
	enum
	{
		AMBIENT = 263,	///< Ambient color of the surface.
		DEFAULT_AMBIENT = AMBIENT	///< Ambient color of the surface.
	};

	/**
	 * @brief Type definition of the value contained by field named \c ambient.
	 */
	typedef vgm::Vec3f AmbientValueType;

	/**
	 * @brief Type definition of the field named \c ambient
	 */
	typedef vgd::field::TPairAssociativeField< AmbientParameterType, AmbientValueType > FAmbientType;


	/**
	 * @brief Gets the value of field named \c ambient.
	 */
	const bool getAmbient( AmbientValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c ambient.
 	 */
	void setAmbient( AmbientValueType value );

	/**
	 * @brief Erases the field named \c ambient.
	 */
	void eraseAmbient();
	//@}



	/**
	 * @name Accessors to field \c diffuse
	 */
	//@{

	/**
	 * @brief Type definition of the parameter contained by field named \c diffuse.
	 */
	typedef vgd::field::Enum DiffuseParameterType;

	/**
	 * @brief Definition of symbolic values
	 */
	enum
	{
		DIFFUSE = 264,	///< Diffuse color of the surface.
		DEFAULT_DIFFUSE = DIFFUSE	///< Diffuse color of the surface.
	};

	/**
	 * @brief Type definition of the value contained by field named \c diffuse.
	 */
	typedef vgm::Vec3f DiffuseValueType;

	/**
	 * @brief Type definition of the field named \c diffuse
	 */
	typedef vgd::field::TPairAssociativeField< DiffuseParameterType, DiffuseValueType > FDiffuseType;


	/**
	 * @brief Gets the value of field named \c diffuse.
	 */
	const bool getDiffuse( DiffuseValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c diffuse.
 	 */
	void setDiffuse( DiffuseValueType value );

	/**
	 * @brief Erases the field named \c diffuse.
	 */
	void eraseDiffuse();
	//@}



	/**
	 * @name Field name accessors
	 */
	//@{

	/**
	 * @brief Returns the name of field \c shininess.
	 *
	 * @return the name of field \c shininess.
	 */
	static const std::string getFShininess( void );

	/**
	 * @brief Returns the name of field \c emission.
	 *
	 * @return the name of field \c emission.
	 */
	static const std::string getFEmission( void );

	/**
	 * @brief Returns the name of field \c specular.
	 *
	 * @return the name of field \c specular.
	 */
	static const std::string getFSpecular( void );

	/**
	 * @brief Returns the name of field \c transparency.
	 *
	 * @return the name of field \c transparency.
	 */
	static const std::string getFTransparency( void );

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

	//@}

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
	IMPLEMENT_INDEXABLE_CLASS_HPP( , Material );
private:
	static const vgd::basic::RegisterNode<Material> m_registrationInstance;
};



} // namespace node

} // namespace vgd
#endif //#ifndef _VGD_NODE_MATERIAL_HPP
