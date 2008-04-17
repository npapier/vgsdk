// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_COORDINATESYSTEM_HPP
#define _VGD_NODE_COORDINATESYSTEM_HPP

#include "vgd/field/Integer.hpp"
#include "vgd/field/TPairAssociativeField.hpp"
#include "vgd/node/SingleAttribute.hpp"
#include <vgm/Matrix.hpp>



namespace vgd
{

namespace node
{



/**
 * @brief Coordinate system node
 * 
 * The coordinate system node keeps track of transformation matrices values (geometrical and projection).
 * These matrices are updated during scene graph traversing done to update bounding boxes (see vge::technique::ComputeBoundingBox). 
 *
 * @remarks Sharing this node multiple times in a scene graph is possible although not recommanded. Because it will contain only the last (in traverse order) transformation matrices. 
 *
 * New field added by this node :
 *
 * - int8 \c mask = GEOMETRICAL_MATRIX_BIT\n
 * 		The \c mask is a bitwise OR operators of masks that indicate the type of matrix to keep track\n
 * The masks are as follows : PROJECTION_MATRIX_BIT and GEOMETRICAL_MATRIX_BIT.
 *
 * - PAFMatrix \c matrix
 * 	- [GEOMETRICAL] \n
 * 		the geometrical transformation matrix.
 * 	- [PROJECTION]\n
 *		the projection transformation matrix.
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
		//TEXTURE_MATRIX_BIT		= 1<<0,			The texture matrix
		PROJECTION_MATRIX_BIT	= 1<<1,			/*!< The projection matrix */
		GEOMETRICAL_MATRIX_BIT	= 1<<2,			/*!< The geometrical matrix */

		DEFAULT_MASK = GEOMETRICAL_MATRIX_BIT
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
		GEOMETRICAL		= 1,
		PROJECTION
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
