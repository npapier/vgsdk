// VGSDK - Copyright (C) 2009, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_CAMERA_HPP
#define _VGD_NODE_CAMERA_HPP

#include "vgd/field/MatrixR.hpp"
#include "vgd/field/Rectangle2i.hpp"
#include "vgd/node/ProjectionTransformation.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Camera node used to set the projection matrix, viewport and scissor box
 *
 * Sets up the projection with an user defined matrix for the viewing frustum(into the world coordinate system).  Note that some matrices (such as singular ones) may result in errors in bounding boxes, picking, and lighting.  
 *
 * New fields defined by this node :
 *	- OFRectangle2i \c scissor = empty\n
 *		Determines the scissor box. It is automatically enabled if this field is defined, otherwise it is disabled. The default value is empty, i.e. scissor test is disabled.
 *	- SFMatrixR \c matrix = vgm::MatrixR(vgm::MatrixR::getIdentity())\n
 *		Determines the projection matrix.
 *	- OFRectangle2i \c [viewport] = vgm::Rectangle2i(0, 0, 1600, 1200)\n
 *		Determines the viewport.
 *
 *
 * @ingroup g_nodes
 * @ingroup g_singleAttributeNodes
 * @ingroup g_transformationNodes
 */
struct VGD_API Camera : public vgd::node::ProjectionTransformation
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
	 * @name Accessors to field matrix
	 */
	//@{

	/**
	 * @brief Type definition of the value contained by field named \c matrix.
	 */
	typedef vgm::MatrixR MatrixValueType;

	/**
	 * @brief Type definition of the field named \c matrix
	 */
	typedef vgd::field::TSingleField< MatrixValueType > FMatrixType;


	/**
	 * @brief Gets the value of field named \c matrix.
	 */
	const MatrixValueType getMatrix() const;

	/**
	 * @brief Sets the value of field named \c matrix.
	 */
	void setMatrix( const MatrixValueType value );

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
	 * @brief Returns the name of field \c matrix.
	 *
	 * @return the name of field \c matrix.
	 */
	static const std::string getFMatrix( void );

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
	 * @pre getViewport(...) == true
	 */
	const vgm::Vec3f applyViewport( const vgm::Vec3f& vertex );
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
