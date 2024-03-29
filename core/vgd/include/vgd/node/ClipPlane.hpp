// VGSDK - Copyright (C) 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_CLIPPLANE_HPP
#define _VGD_NODE_CLIPPLANE_HPP

#include "vgd/field/Bool.hpp"
#include "vgd/field/Plane.hpp"
#include "vgd/node/MultiAttribute.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Clipping plane node
 *
 * All subsequent shapes in the scene graph will be clipped to the half-space defined by the \c plane field. The half-space is the side of the plane in the direction of the plane normal. Any number of clipping planes may be active simultaneously, although the graphics library may place a limit on this number during rendering (i.e. 6 for OpenGL). 
 *
 * New fields defined by this node :
 * - SFPlane \c plane = vgm::Plane(vgm::Vec3f(1.f, 0.f, 0.f), 0.f )<br>
 *   Specifies the clipping plane.<br>
 *<br>
 * - OFBool \c [on] = (true)<br>
 *   Specifies if the clipping plane is enabled or disabled.<br>
 *<br>
 *
 * @ingroup g_nodes
 * @ingroup g_multiAttributeNodes
 * @ingroup g_transformationNodes
 */
struct VGD_API ClipPlane : public vgd::node::MultiAttribute
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
	static vgd::Shp< ClipPlane > create( const std::string nodeName = "NoName" );

	/**
	 * @brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values and
	 * sets the \c multiAttributeIndex of the multi-attribute.
	 *
	 * @param index		zero-based index of the multi-attribute
	 */
	static vgd::Shp< ClipPlane > create( const std::string nodeName, const uint8 index );
	
	/**
	 *@brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values (optionals fields too).
	 */
	static vgd::Shp< ClipPlane > createWhole( const std::string nodeName = "DefaultWhole" );

	//@}



	/**
	 * @name Accessors to field plane
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c plane.
	 */
	typedef vgm::Plane PlaneValueType;

	/**
	 * @brief The default value of field named \c plane.
	 */
	static const PlaneValueType DEFAULT_PLANE;

	/**
	 * @brief Type definition of the field named \c plane
	 */
	typedef vgd::field::TSingleField< PlaneValueType > FPlaneType;


	/**
	 * @brief Gets the value of field named \c plane.
	 */
	const PlaneValueType getPlane() const;

	/**
	 * @brief Sets the value of field named \c plane.
	 */
	void setPlane( const PlaneValueType value );

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
	 * @name Field name accessors
	 */
	//@{

	/**
	 * @brief Returns the name of field \c plane.
	 *
	 * @return the name of field \c plane.
	 */
	static const std::string getFPlane( void );

	/**
	 * @brief Returns the name of field \c on.
	 *
	 * @return the name of field \c on.
	 */
	static const std::string getFOn( void );

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
	ClipPlane( const std::string nodeName );

public:
	IMPLEMENT_INDEXABLE_CLASS_HPP( ClipPlane );
private:
	static const vgd::basic::RegisterNode<ClipPlane> m_registrationInstance;
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_CLIPPLANE_HPP
