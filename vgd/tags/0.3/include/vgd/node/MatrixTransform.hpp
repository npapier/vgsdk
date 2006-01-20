// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_MATRIXTRANSFORM_H
#define _VGD_NODE_MATRIXTRANSFORM_H

#include "vgd/vgd.hpp"

#include "vgd/field/Matrix.hpp"
#include "vgd/node/GeometricalTransformation.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief node that specifies a 3D geometric transformation as a matrix.
 * 
 * This node defines a geometric 3D transformation with a single 4x4 matrix.
 * Note that some matrices (such as singular ones) may result in errors in bounding boxes, picking, and lighting.
 * 
 * New fields added by this node :
 *
 * - SFMatrixR \c matrix = identity\n
 * 	Determines the matrix used to transform geometry.
 *
 * 
 * @ingroup g_nodes
 * @ingroup g_singleAttributeNodes
 * @ingroup g_transformationNodes
 */
struct VGD_API MatrixTransform : public vgd::node::GeometricalTransformation
{
	META_NODE_HPP( MatrixTransform );



	/**
	 * @name Accessors to field matrix.
	 */
	//@{

	/**
	 * @brief Typedef for the \c matrix field.
	 */
	typedef vgd::field::SFMatrixR FMatrixType;

	/**
	 * @brief Typedef for the \c matrix field value.
	 */
	typedef vgm::MatrixR MatrixValueType;

	/**
	 * @brief Gets the geometrical transformation.
	 */
	const vgm::MatrixR&	getMatrix( void ) const;

	/**
	 * @brief Sets the geometrical transformation.
	 */
	void						setMatrix( const vgm::MatrixR& matrix );
	
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
	
	//@}
	
	
	
protected:
	/**
	 * @name Constructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	MatrixTransform( const std::string nodeName );

	void	setToDefaults( void );
	
	void	setOptionalsToDefaults();	

	//@}
};


} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_MATRIXTRANSFORM_H
