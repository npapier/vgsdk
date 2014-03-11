// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_COORDINATESYSTEM_HPP
#define _VGD_NODE_COORDINATESYSTEM_HPP

#include <vgm/Matrix.hpp>
#include <vgm/Rectangle.hpp>

#include "vgd/field/Integer.hpp"
#include "vgd/field/TPairAssociativeField.hpp"
#include "vgd/node/SingleAttribute.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Coordinate system node
 * 
 * The coordinate system node keeps track of transformation matrices values (geometrical and projection) and viewport value.
 * These values are updated during scene graph traversing done to compute bounding boxes (see vge::technique::ComputeBoundingBox). 
 *
 * @remarks Sharing this node multiple times in a scene graph is possible although not recommanded. Because it will contain only the last (in traverse order) transformation matrices and viewport. 
 *
 * New fields added by this node :
 *
 * - int8 \c mask = GEOMETRICAL_MATRIX_MASK\n
 * 		The \c mask is a bitwise OR operators of masks that indicate the value(s) to keep track.\n
 * The symbolic mask constants are as follows :
 *		- PROJECTION_MATRIX_MASK : the projection matrix. See \c matrix field of Camera.
 *		- GEOMETRICAL_MATRIX_MASK : the geometrical matrix. See nodes inheriting from GeometricalTransformation.
 *		- VIEWPORT_MASK : the viewport. See \c viewport field of Camera node.
 *		- DEFAULT_MASK : the default value of the mask field.
 *		- ALL_MASK : this special constant can be used to keep track of all values.
 *
 * - PAFMatrix \c matrix\n
 * 	- [PROJECTION]\n
 *		the projection matrix
 * 	- [GEOMETRICAL] \n
 * 		the geometrical matrix
 *
 * - PAFRectangle2i \c	[viewport]\n
 *		the viewport
 * 
 * @ingroup g_nodes
 * @ingroup g_singleAttributeNodes
 * @ingroup g_transformationNodes
 */
struct VGD_API CoordinateSystem : public vgd::node::SingleAttribute
{
	META_NODE_HPP( CoordinateSystem );




	/**
	 * @name Accessors to field mask
	 */
	//@{
	
	/**
	 * @brief Enumeration of masks values.
	 */
	typedef enum
	{
		PROJECTION_MATRIX_MASK	= 1<<0,			///< the projection matrix
		GEOMETRICAL_MATRIX_MASK	= 1<<1,			///< the geometrical matrix
		VIEWPORT_MASK			= 1<<2,			///< the viewport

		DEFAULT_MASK			= GEOMETRICAL_MATRIX_MASK,
		ALL_MASK				= PROJECTION_MATRIX_MASK | GEOMETRICAL_MATRIX_MASK | VIEWPORT_MASK
	} MaskValue;
	
	/**
	 * @brief Typedef for the \c mask field.
	 */
	typedef vgd::field::SFInt8 FMaskType;
	
	/**
	 * @brief Gets the masks that indicate the matrix type to keep track.
	 */
	int8	getMask() const;
	
	/**
	 * @brief Sets the masks that indicate the matrix type to keep track.
	 * 
	 * @param mask		Bitwise OR operators of masks that indicate the matrix type to keep track
	 */
	void	setMask( const int8 mask );
	//@}



	/**
	 * @name Accessors to field matrix
	 */
	//@{

	/**
	 * @brief Enumeration of the \c matrix parameters.
	 */
	typedef enum
	{
		PROJECTION		= 1,
		GEOMETRICAL
	} MatrixParameterType;

	/**
	 * @brief Typedef for the \c matrix value.
	 */
	typedef vgm::MatrixR MatrixValueType;

	/**
	 * @brief Typedef for the \c matrix field.
	 */	
	typedef vgd::field::TPairAssociativeField< MatrixParameterType, MatrixValueType > FMatrixType;

	/**
	 * @brief Gets the matrix value.
	 */
	bool			getMatrix( const MatrixParameterType param, MatrixValueType& value ) const;

	/**
	 * @brief Sets the matrix value.
	 */
	void 			setMatrix( const MatrixParameterType param, MatrixValueType value );
	
	/**
	 * @brief Erase the matrix value.
	 */
	void 			eraseMatrix( const MatrixParameterType param );
	//@}



	/**
	 * @name Accessors to field viewport
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
	 * @name Fields names enumeration
	 */
	//@{

	/**
	 * @brief Returns the name of field \c mask.
	 * 
	 * @return the name of field \c mask.
	 */
	static const std::string getFMask( void );

	/**
	 * @brief Returns the name of field \c matrix.
	 * 
	 * @return the name of field \c matrix.
	 */
	static const std::string getFMatrix();

	/**
	 * @brief Returns the name of field \c viewport.
	 * 
	 * @return the name of field \c viewport.
	 */
	static const std::string getFViewport( void );
	//@}



protected:
	/**
	 * @name Constructor
	 */
	//@{

	/**
	 * @brief Default constructor
	 */
	CoordinateSystem( const std::string nodeName );

	void	setToDefaults();

	void	setOptionalsToDefaults();

	//@}
};


} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_COORDINATESYSTEM_HPP
