// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_TRACKBALL_H
#define _VGD_NODE_TRACKBALL_H

#include "vgd/vgd.hpp"

#include "vgd/field/Vector.hpp"
#include "vgd/field/Rotation.hpp"
#include "vgd/node/Dragger.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Trackball dragger.
 * 
 * This node defines a geometric 3D transformation consisting of (in order) a rotation about an arbitrary point and axis.
 * 
 * New field added by this node :
 * 
 * - SFRotation	\c rotation 			= (0 0 1 0)\n
 * - SFVec3f		\c center 				= (0 0 0)\n
 * 
 * @todo computeFieldsFromMatrix()
 * 
 * @ingroup g_nodes
 * @ingroup g_transformationNodes
 * @ingroup g_singleAttributeNodes
 */
struct VGD_API Trackball : public vgd::node::Dragger
{
	META_NODE_HPP( Trackball );
	
	
	
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
	const vgm::Vec3f		getCenter() const;

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
	const vgm::Rotation	getRotation() const;

	/**
	 * @brief Sets the rotation specification.
	 */
	void						setRotation( const vgm::Rotation rotation );

	//@}



	/**
	 * @name High level accessors.
	 */
	//@{
	
	/**
	 * @brief Compute the geometric 3D transformation of this node from the fields
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
	static const std::string getFCenter();

	/**
	 * @brief Returns the name of field \c rotation.
	 * 
	 * @return the name of field \c rotation.
	 */
	static const std::string getFRotation();
	//@}	

protected:
	/**
	 * @name Constructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	Trackball( const std::string nodeName );

	void	setToDefaults();

	void	setOptionalsToDefaults();

	//@}
};


} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_TRACKBALL_H
