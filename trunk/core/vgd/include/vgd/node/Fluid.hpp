// VGSDK - Copyright (C) 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_FLUID_HPP
#define _VGD_NODE_FLUID_HPP

#include "vgd/field/NodeWkp.hpp"
#include "vgd/field/Vec2i.hpp"
#include "vgd/field/Vec4f.hpp"
#include "vgd/node/Shape.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Fluid allow the simulation of liquids
 *
 * Liquids are simulated using several height maps (sceneHeightMap computed from \c scene, fluidHeightMap containing height of the fluid and deltaHeightMap to add/remove liquid). A tessellated quad with displacement mapping is used for the rendering. 
 *
 * New fields defined by this node :
 * - SFVec2i \c heightMapSize = vgm::Vec2i(256, 256)<br>
 *   Specifies the size of the textures used to store scene and fluid height map.<br>
 *<br>
 * - SFNodeWkp \c scene = empty<br>
 *   Specifies the root of the scene graph used by the fluid simulation.<br>
 *<br>
 * - SFVec4f \c gravity = vgm::Vec4f(0.f, -1.f, 0.f, 9.8f)<br>
 *   Specifies the direction of the gravity (the first three components) and the intensity (the last component).<br>
 *<br>
 *
 * @ingroup g_nodes
 * @ingroup g_shapeNodes
 * @ingroup g_propertiesNodes
 */
struct VGD_API Fluid : public vgd::node::Shape
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
	static vgd::Shp< Fluid > create( const std::string nodeName = "NoName" );

	/**
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values and
	 * sets the \c multiAttributeIndex of the multi-attribute.
	 *
	 * @param index		zero-based index of the multi-attribute
	 */
	static vgd::Shp< Fluid > create( const std::string nodeName, const uint8 index );
	
	/**
	 *@brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values (optionals fields too).
	 */
	static vgd::Shp< Fluid > createWhole( const std::string nodeName = "DefaultWhole" );

	//@}



	/**
	 * @name Accessors to field heightMapSize
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c heightMapSize.
	 */
	typedef vgm::Vec2i HeightMapSizeValueType;

	/**
	 * @brief Type definition of the field named \c heightMapSize
	 */
	typedef vgd::field::TSingleField< HeightMapSizeValueType > FHeightMapSizeType;


	/**
	 * @brief Gets the value of field named \c heightMapSize.
	 */
	const HeightMapSizeValueType getHeightMapSize() const;

	/**
	 * @brief Sets the value of field named \c heightMapSize.
	 */
	void setHeightMapSize( const HeightMapSizeValueType value );

	//@}



	/**
	 * @name Accessors to field scene
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c scene.
	 */
	typedef vgd::node::NodeWkp SceneValueType;

	/**
	 * @brief Type definition of the field named \c scene
	 */
	typedef vgd::field::TSingleField< SceneValueType > FSceneType;


	/**
	 * @brief Gets the value of field named \c scene.
	 */
	const SceneValueType getScene() const;

	/**
	 * @brief Sets the value of field named \c scene.
	 */
	void setScene( const SceneValueType value );

	//@}



	/**
	 * @name Accessors to field gravity
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c gravity.
	 */
	typedef vgm::Vec4f GravityValueType;

	/**
	 * @brief Type definition of the field named \c gravity
	 */
	typedef vgd::field::TSingleField< GravityValueType > FGravityType;


	/**
	 * @brief Gets the value of field named \c gravity.
	 */
	const GravityValueType getGravity() const;

	/**
	 * @brief Sets the value of field named \c gravity.
	 */
	void setGravity( const GravityValueType value );

	//@}



	/**
	 * @name Field name accessors
	 */
	//@{

	/**
	 * @brief Returns the name of field \c heightMapSize.
	 *
	 * @return the name of field \c heightMapSize.
	 */
	static const std::string getFHeightMapSize( void );

	/**
	 * @brief Returns the name of field \c scene.
	 *
	 * @return the name of field \c scene.
	 */
	static const std::string getFScene( void );

	/**
	 * @brief Returns the name of field \c gravity.
	 *
	 * @return the name of field \c gravity.
	 */
	static const std::string getFGravity( void );

	//@}


	/**
	 * @name Dirty flags enumeration
	 */
	//@{


	//@}



	bool computeBoundingBox( const vgm::MatrixR& transformation );	///< overridden method

	bool isBoundingBoxValid() const;								///< overridden method

	void invalidateBoundingBox( bool bInvalidate = true );			///< overridden method



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
	Fluid( const std::string nodeName );

public:
	IMPLEMENT_INDEXABLE_CLASS_HPP( , Fluid );
private:
	static const vgd::basic::RegisterNode<Fluid> m_registrationInstance;
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_FLUID_HPP
