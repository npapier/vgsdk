// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_TEXTUREMATRIXTRANSFORM_HPP
#define _VGD_NODE_TEXTUREMATRIXTRANSFORM_HPP

#include "vgd/vgd.hpp"

#include "vgd/field/Matrix.hpp"
#include "vgd/node/TextureTransformation.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Node that specifies a texture transformation as a matrix.
 * 
 * This node defines a texture transformation with a single 4x4 matrix.
 * 
 * New fields added by this node :
 *
 * - SFMatrixR \c matrix = identity\n
 * 	Determines the matrix used to transform texture coordinates.
 *
 * 
 * @ingroup g_nodes
 * @ingroup g_multiAttributeNodes
 * @ingroup g_transformationNodes
 * @ingroup g_texturingNodes
 */
struct VGD_API TextureMatrixTransform : public vgd::node::TextureTransformation
{
	META_NODE_HPP( TextureMatrixTransform );



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
	TextureMatrixTransform( const std::string nodeName );

	void	setToDefaults( void );

	void	setOptionalsToDefaults();
	//@}
};


} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_TEXTUREMATRIXTRANSFORM_HPP
