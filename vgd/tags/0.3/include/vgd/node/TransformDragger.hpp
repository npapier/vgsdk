// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_TRANSFORMDRAGGER_H
#define _VGD_NODE_TRANSFORMDRAGGER_H

#include "vgd/vgd.hpp"

#include "vgd/field/Vector.hpp"
#include "vgd/field/Rotation.hpp"

#include "vgd/node/Dragger.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Dragger to rotate and translate objects.
 * 
 * This node defines a geometric 3D transformation consisting of (in order) a rotation about an arbitrary point and axis
 * and a translation.
 * 
 * New field added by this node :
 * 
 * - SFVec3f		\c translation			= (0 0 0)\n
 * - SFRotation	\c rotation 			= (0 0 1 0)\n
 * - SFVec3f		\c center 				= (0 0 0)\n
 *
 * This node is a light version of vgd::node::Transform.
 * 
 * @ingroup g_nodes
 * @ingroup g_nodekits
 * @ingroup g_transformationNodes
 */
struct VGD_API TransformDragger : public vgd::node::Dragger
{
	META_NODE_HPP( TransformDragger );



	/**
	 * @brief Enumeration of the different states of this dragger.
	 */
	enum {
		NONE = 0,
		ROTATION_XY,
		ROTATION_XY_ACTIVE,		
		TRANSLATION_XY,
		TRANSLATION_XY_ACTIVE,
		TRANSLATION_Z,
		TRANSLATION_Z_ACTIVE,
		ROTATION_Z,
		ROTATION_Z_ACTIVE,
		TRANSFORMDRAGGER_DEFAULT = ROTATION_XY
	};

		

	/**
	 * @name Accessors to field center.
	 */
	//@{

	/**
	 * @brief Typedef for the \c center field.
	 */	
	typedef vgd::field::SFVec3f 	FCenterType;
		
	/**
	 * @brief Typedef for the \c center value.
	 */
	typedef vgm::Vec3f 				CenterValueType;

	/**
	 * @brief Gets the origin for scale and rotation.
	 */
	const vgm::Vec3f		getCenter( void ) const;

	/**
	 * @brief Sets the origin for scale and rotation.
	 */
	void						setCenter( const vgm::Vec3f center );
	//@}



	/**
	 * @name Accessors to field rotation.
	 */
	//@{

	/**
	 * @brief Typedef for the \c rotation field.
	 */	
	typedef vgd::field::SFRotation	FRotationType;
		
	/**
	 * @brief Typedef for the \c rotation value.
	 */
	typedef vgm::Rotation				RotationValueType;

	/**
	 * @brief Gets the rotation specification.
	 */
	const vgm::Rotation	getRotation( void ) const;

	/**
	 * @brief Sets the rotation specification.
	 */
	void						setRotation( const vgm::Rotation rotation );

	//@}



	/**
	 * @name Accessors to field translation.
	 */
	//@{

	/**
	 * @brief Typedef for the \c translation field.
	 */	
	typedef vgd::field::SFVec3f	FTranslationType;
		
	/**
	 * @brief Typedef for the \c translation value.
	 */
	typedef vgm::Vec3f				TranslationValueType;

	/**
	 * @brief Gets the translation vector.
	 */
	const vgm::Vec3f		getTranslation( void ) const;

	/**
	 * @brief Sets the translation vector.
	 */
	void						setTranslation( const vgm::Vec3f translation );

	//@}



	/**
	 * @name Overridden method.
	 */
	//@{
	
	/**
	 * @brief Compute the geometric 3D transformation of this node from the fields.
	 * 
	 * @return the transformation matrix.
	 */
	vgm::MatrixR			computeMatrixFromFields() const;

	//@}

	
	
	/**
	 * @name Fields names enumeration.
	 */
	//@{
	
	/**
	 * @brief Returns the name of field \c center.
	 * 
	 * @return the name of field \c center.
	 */
	static const std::string getFCenter( void );

	/**
	 * @brief Returns the name of field \c rotation.
	 * 
	 * @return the name of field \c rotation.
	 */
	static const std::string getFRotation( void );

	/**
	 * @brief Returns the name of field \c translation.
	 * 
	 * @return the name of field \c translation.
	 */
	static const std::string getFTranslation( void );
	
	//@}
	
	

	/**
	 * @name Initialization methods.
	 */
	//@{
	
	/**
	 * @brief Set fields and dirty flags to default values.
	 */
	void	setToDefaults( void );
	
	void	setTransformationToDefaults();

	/**
	 * @brief Using CTRL + SHIFT + Mouse (1 button).
	 * 
	 * @todo Complete documentation.
	 */
	void setBindingsToDefaults();

	/**
	 * @brief Using only the mouse (3 buttons).
	 * 
	 * @todo Complete documentation.
	 */
	void setBindingsToDefaults2();
	
	/**
	 * @brief Disable all visual feedback.
	 */
	void setNullFeedback();
	
	/**
	 * @brief Enable visual feedback (with bounding box surrounding \c surround sub scene graph).
	 */
	void setBoundingBoxFeedback();

protected:
	void	setOptionalsToDefaults();
	
	//@}
	
	
	
	/**
	 * @name Constructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	TransformDragger( const std::string nodeName );

	//@}
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_TRANSFORMDRAGGER_H
