// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_TRANSFORMSEPARATOR_HPP
#define _VGD_NODE_TRANSFORMSEPARATOR_HPP

#include "vgd/vgd.hpp"

#include "vgd/field/Integer.hpp"
#include "vgd/node/Group.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Group node that saves and restores transformation state
 *
 * This group node is similar to the Separator node in that it saves state before traversing its children
 * and restores it afterwards. However, it saves only the current transformation matrix (texture, projection or/and 
 * geometrical). All other state is left as is. This node can be useful for positioning a camera, since the 
 * transformations to the camera will not affect the rest of the scene, even through the camera
 * will view the scene. Similarly, this node can be used to isolate transformations to light sources 
 * or other objects.
 * 
 * New fields added by this node :
 *
 * - int32 mask	= GEOMETRICAL_MATRIX_BIT\n
 * 		The \c mask is a bitwise OR operators of masks that indicate the type of matrix to be saved and 
 * restored.\n
 * The three masks are as follows : TEXTURE_MATRIX_BIT (for \c all texture matrix), PROJECTION_MATRIX_BIT and 
 * GEOMETRICAL_MATRIX_BIT.
 *
 * @remarks Unlike Separator, this node can be nested without any limitation.
 * 
 * @todo TEXTURE0-x_MATRIX_BIT for saves/restores only one transformation matrix on for a specified texture unit.
 * 
 * @ingroup g_nodes
 * @ingroup g_groupNodes
 * @ingroup g_transformationNodes
 */
struct VGD_API TransformSeparator : public vgd::node::Group
{
	META_NODE_HPP( TransformSeparator );



	/**
	 * @name Accessors to field mask.
	 */
	//@{
	
	/**
	 * @brief Enumeration of masks values.
	 */
	typedef enum
	{
		TEXTURE_MATRIX_BIT		= 1<<0,			/*!< The texture matrix */
		PROJECTION_MATRIX_BIT	= 1<<1,			/*!< The projection matrix */
		GEOMETRICAL_MATRIX_BIT	= 1<<2,			/*!< The geometrical matrix */

		DEFAULT_MASK = GEOMETRICAL_MATRIX_BIT
	} MaskValue;
	
	/**
	 * @brief Typedef for the \c mask field.
	 */
	typedef vgd::field::SFInt8 FMaskType;
	
	/**
	 * @brief Gets the masks that indicate the matrix type to be saved and restored.
	 */
	int8	getMask() const;
	
	/**
	 * @brief Sets the masks that indicate the matrix type to be saved and restored.
	 * 
	 * @param mask		Bitwise OR operators of masks that indicate the matrix type to be saved and restored.
	 */
	void	setMask( const int8 mask );
	//@}



	/**
	 * @name Fields names enumeration.
	 */
	//@{
	
	/**
	 * @brief Returns the name of field \c mask.
	 * 
	 * @return the name of field \c mask.
	 */
	static const std::string getFMask( void );
	//@}
	
	
	
protected:
	/**
	 * @name Constructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	TransformSeparator( const std::string nodeName );

	void	setToDefaults( void );

	void	setOptionalsToDefaults();
	
	//@}
};


} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_TRANSFORMSEPARATOR_HPP
