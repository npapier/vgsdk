// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_CAMERA_HPP
#define _VGD_NODE_CAMERA_HPP

#include "vgd/field/MatrixR.hpp"
#include "vgd/field/Rectangle2i.hpp"
#include "vgd/node/GeometricalTransformation.hpp"
#include "vgd/node/ProjectionTransformation.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Camera node used to set the projection matrix, viewport and scissor box. Camera position and orientation could be specified too.
 *
 * Sets up the projection with an user defined matrix for the viewing frustum (into the world coordinate system).  Sets up the camera position and orientation with 4x4 matrix from lookAt field. Note that some matrices (such as singular ones) may result in errors in bounding boxes, picking, and lighting.  
 *
 * New fields defined by this node :
 * - OFRectangle2i \c [scissor] = empty<br>
 *   Determines the scissor box. It is automatically enabled if this field is defined, otherwise it is disabled. The default value is empty, i.e. scissor test is disabled.<br>
 *<br>
 * - SFMatrixR \c lookAt = vgm::MatrixR(vgm::MatrixR::getIdentity())<br>
 *   Determines the 3D geometric transformation as a 4x4 matrix applied to camera.\nNote that this transformation is applied to engine like any GeometricalTransformation node with composeTransformation field sets to false.\nBy default, the camera is situated at the origin, points down the negative z-axis, and has an up-vector of (0, 1, 0).<br>
 *<br>
 * - SFMatrixR \c projection = vgm::MatrixR(vgm::MatrixR::getIdentity())<br>
 *   Determines the projection matrix.<br>
 *<br>
 * - OFRectangle2i \c [viewport] = vgm::Rectangle2i(0, 0, 1600, 1200)<br>
 *   Determines the viewport.<br>
 *<br>
 *
 * @ingroup g_nodes
 * @ingroup g_singleAttributeNodes
 * @ingroup g_transformationNodes
 */
struct VGD_API Camera : public vgd::node::GeometricalTransformation, public vgd::node::ProjectionTransformation
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
	static vgd::Shp< Camera > create( const std::string nodeName = "NoName" );

	/**
	 *@brief Node factory
	 *
	 * Creates a node with all fields sets to defaults values (optionals fields too).
	 */
	static vgd::Shp< Camera > createWhole( const std::string nodeName = "DefaultWhole" );

	//@}



	/**
	 * @name Accessors to field scissor
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c scissor.
	 */
	typedef vgm::Rectangle2i ScissorValueType;

	/**
	 * @brief Type definition of the field named \c scissor
	 */
	typedef vgd::field::TOptionalField< ScissorValueType > FScissorType;


	/**
	 * @brief Gets the value of field named \c scissor.
	 */
	const bool getScissor( ScissorValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c scissor.
 	 */
	void setScissor( const ScissorValueType& value );

	/**
	 * @brief Erases the field named \c scissor.
	 */
	void eraseScissor();

	/**
	 * @brief Tests if the value of field named \c scissor has been initialized.
	 */
	const bool hasScissor() const;
	//@}



	/**
	 * @name Accessors to field lookAt
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c lookAt.
	 */
	typedef vgm::MatrixR LookAtValueType;

	/**
	 * @brief Type definition of the field named \c lookAt
	 */
	typedef vgd::field::TSingleField< LookAtValueType > FLookAtType;


	/**
	 * @brief Gets the value of field named \c lookAt.
	 */
	const LookAtValueType getLookAt() const;

	/**
	 * @brief Sets the value of field named \c lookAt.
	 */
	void setLookAt( const LookAtValueType value );

	//@}



	/**
	 * @name Accessors to field projection
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c projection.
	 */
	typedef vgm::MatrixR ProjectionValueType;

	/**
	 * @brief Type definition of the field named \c projection
	 */
	typedef vgd::field::TSingleField< ProjectionValueType > FProjectionType;


	/**
	 * @brief Gets the value of field named \c projection.
	 */
	const ProjectionValueType getProjection() const;

	/**
	 * @brief Sets the value of field named \c projection.
	 */
	void setProjection( const ProjectionValueType value );

	//@}



	/**
	 * @name Accessors to field viewport
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c viewport.
	 */
	typedef vgm::Rectangle2i ViewportValueType;

	/**
	 * @brief Type definition of the field named \c viewport
	 */
	typedef vgd::field::TOptionalField< ViewportValueType > FViewportType;


	/**
	 * @brief Gets the value of field named \c viewport.
	 */
	const bool getViewport( ViewportValueType& value ) const;

	/**
	 * @brief Sets the value of field named \c viewport.
 	 */
	void setViewport( const ViewportValueType& value );

	/**
	 * @brief Erases the field named \c viewport.
	 */
	void eraseViewport();

	/**
	 * @brief Tests if the value of field named \c viewport has been initialized.
	 */
	const bool hasViewport() const;
	//@}



	/**
	 * @name Field name accessors
	 */
	//@{

	/**
	 * @brief Returns the name of field \c scissor.
	 *
	 * @return the name of field \c scissor.
	 */
	static const std::string getFScissor( void );

	/**
	 * @brief Returns the name of field \c lookAt.
	 *
	 * @return the name of field \c lookAt.
	 */
	static const std::string getFLookAt( void );

	/**
	 * @brief Returns the name of field \c projection.
	 *
	 * @return the name of field \c projection.
	 */
	static const std::string getFProjection( void );

	/**
	 * @brief Returns the name of field \c viewport.
	 *
	 * @return the name of field \c viewport.
	 */
	static const std::string getFViewport( void );

	//@}
	/**
	 * @name High-level methods
	 *
	 * @todo viewAll()
	 */
	//@{

	/**
	 * @brief Apply the viewport transformation (as defined in OpenGL specification) to a vertex.
	 *
	 * @param vertex	vertex to transform
	 * @return vertex transformed
	 *
	 * @pre hasViewport()
	 */
	const vgm::Vec3f applyViewport( const vgm::Vec3f& vertex );
	//@}



	/**
	 * @name Accessors to field matrix
	 * @deprecated
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c Matrix.
	 * @deprecated
	 */
	typedef vgm::MatrixR MatrixValueType;

	/**
	 * @brief Type definition of the field named \c matrix
	 * @deprecated
	 */
	typedef vgd::field::TSingleField< MatrixValueType > FMatrixType;


	/**
	 * @brief Gets the value of field named \c matrix.
	 * @deprecated
	 */
	vgDEPRECATED( const MatrixValueType getMatrix() const );

	/**
	 * @brief Sets the value of field named \c matrix.
	 * @deprecated
	 */
	vgDEPRECATED( void setMatrix( const MatrixValueType value ) );

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
	Camera( const std::string nodeName );

public:
	IMPLEMENT_INDEXABLE_CLASS_HPP( , Camera );
private:
	static const vgd::basic::RegisterNode<Camera> m_registrationInstance;
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_CAMERA_HPP
