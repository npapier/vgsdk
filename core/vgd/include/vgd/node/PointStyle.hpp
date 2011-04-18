// VGSDK - Copyright (C) 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_POINTSTYLE_HPP
#define _VGD_NODE_POINTSTYLE_HPP

#include "vgd/field/Bool.hpp"
#include "vgd/field/Float.hpp"
#include "vgd/field/Vec3f.hpp"
#include "vgd/node/SingleAttribute.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Defines the style to use when rendering points
 *
 * 
 *
 * New fields defined by this node :
 * - OFBool \c [smooth] = false<br>
 *   If enabled, draw antialiased points, otherwise draw aliased points. Ignored when point sprite is enabled.<br>
 *<br>
 * - OFVec3f \c [distanceAttenuation] = vgm::Vec3f(1.f, 0.f, 0.f)<br>
 *   a vector of three floating-point values that specify the coefficients used for scaling the computed point size. The default values are (1 0 0).<br>
 *<br>
 * - OFBool \c [pointSprite] = false<br>
 *   See GL_ARB_point_sprite extension for details (http://oss.sgi.com/projects/ogl-sample/registry/ARB/point_sprite.txt).<br>
 *<br>
 * - OFFloat \c [size] = 1.f<br>
 *   Specifies the rasterized diameter of both aliased and antialiased points<br>
 *<br>
 *
 * @ingroup g_nodes
 * @ingroup g_singleAttributeNodes
 * @ingroup g_propertiesNodes
 */
struct VGD_API PointStyle : public vgd::node::SingleAttribute
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
	static vgd::Shp< PointStyle > create( const std::string nodeName = "NoName" );

	/**
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values and
	 * sets the \c multiAttributeIndex of the multi-attribute.
	 *
	 * @param index		zero-based index of the multi-attribute
	 */
	static vgd::Shp< PointStyle > create( const std::string nodeName, const uint8 index );
	
	/**
	 *@brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values (optionals fields too).
	 */
	static vgd::Shp< PointStyle > createWhole( const std::string nodeName = "DefaultWhole" );

	//@}



	/**
	 * @name Accessors to field smooth
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c smooth.
	 */
	typedef bool SmoothValueType;

	/**
	 * @brief Type definition of the field named \c smooth
	 */
	typedef vgd::field::TOptionalField< SmoothValueType > FSmoothType;


	/**
	 * @brief Gets the value of field named \c smooth.
	 */
	const bool getSmooth( SmoothValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c smooth.
 	 */
	void setSmooth( const SmoothValueType& value );

	/**
	 * @brief Erases the field named \c smooth.
	 */
	void eraseSmooth();

	/**
	 * @brief Tests if the value of field named \c smooth has been initialized.
	 */
	const bool hasSmooth() const;
	//@}



	/**
	 * @name Accessors to field distanceAttenuation
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c distanceAttenuation.
	 */
	typedef vgm::Vec3f DistanceAttenuationValueType;

	/**
	 * @brief Type definition of the field named \c distanceAttenuation
	 */
	typedef vgd::field::TOptionalField< DistanceAttenuationValueType > FDistanceAttenuationType;


	/**
	 * @brief Gets the value of field named \c distanceAttenuation.
	 */
	const bool getDistanceAttenuation( DistanceAttenuationValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c distanceAttenuation.
 	 */
	void setDistanceAttenuation( const DistanceAttenuationValueType& value );

	/**
	 * @brief Erases the field named \c distanceAttenuation.
	 */
	void eraseDistanceAttenuation();

	/**
	 * @brief Tests if the value of field named \c distanceAttenuation has been initialized.
	 */
	const bool hasDistanceAttenuation() const;
	//@}



	/**
	 * @name Accessors to field pointSprite
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c pointSprite.
	 */
	typedef bool PointSpriteValueType;

	/**
	 * @brief Type definition of the field named \c pointSprite
	 */
	typedef vgd::field::TOptionalField< PointSpriteValueType > FPointSpriteType;


	/**
	 * @brief Gets the value of field named \c pointSprite.
	 */
	const bool getPointSprite( PointSpriteValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c pointSprite.
 	 */
	void setPointSprite( const PointSpriteValueType& value );

	/**
	 * @brief Erases the field named \c pointSprite.
	 */
	void erasePointSprite();

	/**
	 * @brief Tests if the value of field named \c pointSprite has been initialized.
	 */
	const bool hasPointSprite() const;
	//@}



	/**
	 * @name Accessors to field size
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c size.
	 */
	typedef float SizeValueType;

	/**
	 * @brief Type definition of the field named \c size
	 */
	typedef vgd::field::TOptionalField< SizeValueType > FSizeType;


	/**
	 * @brief Gets the value of field named \c size.
	 */
	const bool getSize( SizeValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c size.
 	 */
	void setSize( const SizeValueType& value );

	/**
	 * @brief Erases the field named \c size.
	 */
	void eraseSize();

	/**
	 * @brief Tests if the value of field named \c size has been initialized.
	 */
	const bool hasSize() const;
	//@}



	/**
	 * @name Field name accessors
	 */
	//@{

	/**
	 * @brief Returns the name of field \c smooth.
	 *
	 * @return the name of field \c smooth.
	 */
	static const std::string getFSmooth( void );

	/**
	 * @brief Returns the name of field \c distanceAttenuation.
	 *
	 * @return the name of field \c distanceAttenuation.
	 */
	static const std::string getFDistanceAttenuation( void );

	/**
	 * @brief Returns the name of field \c pointSprite.
	 *
	 * @return the name of field \c pointSprite.
	 */
	static const std::string getFPointSprite( void );

	/**
	 * @brief Returns the name of field \c size.
	 *
	 * @return the name of field \c size.
	 */
	static const std::string getFSize( void );

	//@}


	/**
	 * @name Dirty flags enumeration
	 */
	//@{


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
	PointStyle( const std::string nodeName );

public:
	IMPLEMENT_INDEXABLE_CLASS_HPP( , PointStyle );
private:
	static const vgd::basic::RegisterNode<PointStyle> m_registrationInstance;
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_POINTSTYLE_HPP
