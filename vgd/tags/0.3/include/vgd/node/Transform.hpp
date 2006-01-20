// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_TRANSFORM_H
#define _VGD_NODE_TRANSFORM_H

#include "vgd/vgd.hpp"

#include "vgd/field/Vector.hpp"
#include "vgd/field/Rotation.hpp"

#include "vgd/node/GeometricalTransformation.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief General 3D geometric transformation node.
 * 
 * This node defines a geometric 3D transformation consisting of (in order) a (possibly) non-uniform scale about an 
 * arbitrary point, a rotation about an arbitrary point and axis, and a translation. 
 * While the transformations can be thought of as being applied in that order, matrices are actually premultiplied in 
 * the opposite order.
 * 
 * New field added by this node :
 * 
 * - SFVec3f		\c translation		= (0 0 0)\n
 * - SFRotation	\c rotation 			= (0 0 1 0)\n
 * - SFVec3f		\c scaleFactor 		= (1 1 1)\n
 * - SFRotation	\c scaleOrientation		= (0 0 1 0)\n
 * - SFVec3f		\c center 			= (0 0 0)\n
 *
 * This node is very similar to the Transform node in VRML 97.
 * 
 * @sa http://www.web3d.org/x3d/specifications/vrml/ISO_IEC_14772-All/part1/nodesRef.html#Transform
 * 
 * @remarks Transform = T * C * R * Sorientation * Sfactor * -Sorientation * -C.
 * 
 * @ingroup g_nodes
 * @ingroup g_singleAttributeNodes
 * @ingroup g_transformationNodes
 */
struct VGD_API Transform : public vgd::node::GeometricalTransformation
{
	META_NODE_HPP( Transform );



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
	void					setCenter( const vgm::Vec3f center );
	//@}



	/**
	 * @name Accessors to field scaleOrientation.
	 */
	//@{

	/**
	 * @brief Typedef for the \c scaleOrientation field.
	 */	
	typedef vgd::field::SFRotation	FScaleOrientationType;
		
	/**
	 * @brief Typedef for the \c scaleOrientation value.
	 */
	typedef vgm::Rotation			ScaleOrientationValueType;
	
	/**
	 * @brief Gets the rotational orientation for scale.
	 */
	const vgm::Rotation	getScaleOrientation( void ) const;

	/**
	 * @brief Sets the rotational orientation for scale.
	 */
	void				setScaleOrientation( const vgm::Rotation scaleOrientation );
	
	//@}



	/**
	 * @name Accessors to field scaleFactor.
	 */
	//@{

	/**
	 * @brief Typedef for the \c scaleFactor field.
	 */	
	typedef vgd::field::SFVec3f	FScaleFactorType;
		
	/**
	 * @brief Typedef for the \c scaleFactor value.
	 */
	typedef vgm::Vec3f			ScaleFactorValueType;
	
	/**
	 * @brief Gets the scale factors.
	 */
	const vgm::Vec3f		getScaleFactor( void ) const;

	/**
	 * @brief Sets the scale factors.
	 */
	void					setScaleFactor( const vgm::Vec3f scaleFactor );
	
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
	typedef vgm::Rotation			RotationValueType;

	/**
	 * @brief Gets the rotation specification.
	 */
	const vgm::Rotation	getRotation( void ) const;

	/**
	 * @brief Sets the rotation specification.
	 */
	void				setRotation( const vgm::Rotation rotation );

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
	typedef vgm::Vec3f			TranslationValueType;

	/**
	 * @brief Gets the translation vector.
	 */
	const vgm::Vec3f		getTranslation( void ) const;

	/**
	 * @brief Sets the translation vector.
	 */
	void					setTranslation( const vgm::Vec3f translation );

	//@}



	/**
	 * @name High level accessors.
	 */
	//@{
	
	/**
	 * @brief Compute the geometric 3D transformation of this node
	 * 
	 * @return the transformation matrix.
	 */
	vgm::MatrixR			gethMatrix() const;
	
	/**
	 * @brief Sets the geometric 3D transformation of this node.
	 * 
	 * vgm::MatrixR::getTransform is used (read the documentation for more informations).
	 * 
	 * @param	matrix		the transformation matrix.
	 * @param	center		center point for rotation and scaling, which is optional as the last parameter
	 */
	void 					sethMatrix( const vgm::MatrixR& matrix, const vgm::Vec3f& center = vgm::Vec3f(0.f, 0.f, 0.f) );	 
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
	 * @brief Returns the name of field \c scaleOrientation.
	 * 
	 * @return the name of field \c scaleOrientation.
	 */
	static const std::string getFScaleOrientation( void );
	
	/**
	 * @brief Returns the name of field \c scaleFactor.
	 * 
	 * @return the name of field \c scaleFactor.
	 */
	static const std::string getFScaleFactor( void );

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

	void	setOptionalsToDefaults();
	
	//@}
	
	
	
protected:
	/**
	 * @name Constructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	Transform( const std::string nodeName );

	//@}
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_TRANSFORM_H
