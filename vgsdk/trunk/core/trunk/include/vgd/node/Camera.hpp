// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_CAMERA_HPP
#define _VGD_NODE_CAMERA_HPP

#include "vgd/vgd.hpp"

#include <vgm/Rectangle.hpp>

#include "vgd/field/Matrix.hpp"
#include "vgd/field/TPairAssociativeField.hpp"
#include "vgd/node/ProjectionTransformation.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Camera node used to set the projection matrix, viewport and scissor box.
 * 
 * Sets up the projection with an user defined matrix for the viewing frustum(into the world coordinate system).
 * Note that some matrices (such as singular ones) may result in errors in bounding boxes, picking, and lighting.
 * 
 * New fields added by this node :
 *
 * - SFMatrixR				\c matrix		= identity\n
 *		Determines the projection matrix.
 * - PAFRectangle2i		\c	[viewport]	= (0,0,1600,200).\n
 *		Determines the viewport.
 * - PAFRectangle2i		\c	[scissor]	= empty (i.e. scissor test is disabled).\n
 *		Determines the scissor box (it is automatically enabled if this field is defined, otherwise it is disabled ).
 * 
 * @ingroup g_nodes
 * @ingroup g_singleAttributeNodes
 * @ingroup g_transformationNodes
 */
struct VGD_API Camera : public vgd::node::ProjectionTransformation
{
	META_NODE_HPP( Camera );



	/**
	 * @name Accessors to field matrix.
	 */
	//@{

	/**
	 * @brief Typedef for the \c matrix field.
	 */
	typedef vgd::field::SFMatrixR	FMatrixType;

	/**
	 * @brief Typedef for the \c matrix field value.
	 */
	typedef vgm::MatrixR			MatrixValueType;

	/**
	 * @brief Gets the projection transformation.
	 */
	const vgm::MatrixR&	getMatrix( void ) const;

	/**
	 * @brief Sets the projection transformation.
	 */
	void				setMatrix( const vgm::MatrixR& projection );
	
	//@}



	/**
	 * @name Accessors to field viewport.
	 */
	//@{

	/**
	 * @brief Enumeration of the \c viewport parameter.
	 */
	typedef enum
	{
		VIEWPORT = 1
	} ViewportParameterType;

	/**
	 * @brief Typedef for the \c viewport parameter value.
	 */
	typedef vgm::Rectangle2i ViewportValueType;

	/**
	 * @brief Typedef for the \c viewport field.
	 */	
	typedef vgd::field::TPairAssociativeField< ViewportParameterType, ViewportValueType > FViewportType;

	/**
	 * @brief Gets the \c viewport value.
	 */
	bool			getViewport( vgm::Rectangle2i& value ) const;

	/**
	 * @brief Sets the \c viewport value.
	 */
	void 			setViewport( vgm::Rectangle2i value );
	
	/**
	 * @brief Erase the \c viewport value.
	 */
	void 			eraseViewport();
	//@}



	/**
	 * @name Accessors to field scissor.
	 */
	//@{

	/**
	 * @brief Enumeration of the \c scissor parameter.
	 */
	typedef enum
	{
		SCISSOR = 1
	} ScissorParameterType;

	/**
	 * @brief Typedef for the \c scissor parameter value.
	 */
	typedef vgm::Rectangle2i ScissorValueType;

	/**
	 * @brief Typedef for the \c scissor field.
	 */	
	typedef vgd::field::TPairAssociativeField< ScissorParameterType, ScissorValueType > FScissorType;

	/**
	 * @brief Gets the \c scissor value.
	 */
	bool			getScissor( vgm::Rectangle2i& value ) const;

	/**
	 * @brief Sets the \c scissor value.
	 */
	void 			setScissor( vgm::Rectangle2i value );
	
	/**
	 * @brief Erase the \c scissor value.
	 */
	void 			eraseScissor();
	//@}



	/**
	 * @name Fields names enumeration.
	 */
	//@{

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
	
	/**
	 * @brief Returns the name of field \c scissor.
	 * 
	 * @return the name of field \c scissor.
	 */
	static const std::string getFScissor( void );
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
	vgm::Vec3f applyViewport( const vgm::Vec3f& vertex );
	//@}

protected:
	/**
	 * @name Constructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	Camera( const std::string nodeName );

	void	setToDefaults( void );
	
	void	setOptionalsToDefaults();	

	//@}
};


} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_CAMERA_HPP
