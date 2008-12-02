// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_SCALE1DRAGGER_HPP
#define _VGD_NODE_SCALE1DRAGGER_HPP

#include "vgd/vgd.hpp"

#include "vgd/field/Float.hpp"
#include "vgd/node/Dragger.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Dragger to scale in one dimension.
 * 
 * This node defines a geometric 3D transformation consisting of a scale along the x-axis.
 * Use a transformation node to position and re-orient it to be able to scale along an arbitrary vector.
 * 
 * New field added by this node :
 * 
 * - SFFloat		\c scale			= 1\n
 * 	Sets the current vector of scaling along the X axes.
 *
 * 
 * @ingroup g_nodes
 * @ingroup g_nodekits
 * @ingroup g_transformationNodes
 */
struct VGD_API Scale1Dragger : public vgd::node::Dragger
{
	META_NODE_HPP( Scale1Dragger );




	/**
	 * @brief Enumeration of the different states of this dragger.
	 */
	enum {
		NONE = 0,
		
		SCALE_X,
		SCALE_X_ACTIVE,

		SCALE1DRAGGER_DEFAULT = SCALE_X
	};



	/**
	 * @name Accessors to field scale.
	 */
	//@{

	/**
	 * @brief Typedef for the \c scale field.
	 */	
	typedef vgd::field::SFFloat 	FScaleType;
		
	/**
	 * @brief Typedef for the \c scale value.
	 */
	typedef float						ScaleValueType;

	/**
	 * @brief Gets the origin for scale and rotation.
	 */
	const float getScale( void ) const;

	/**
	 * @brief Sets the origin for scale and rotation.
	 */
	void			setScale( const float scale );
	//@}



	/**
	 * @name Overridden method.
	 */
	//@{
	
	/**
	 * @brief Compute the geometric 3D transformation of this node from the fields.
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
	 * @brief Returns the name of field \c scale.
	 * 
	 * @return the name of field \c scale.
	 */
	static const std::string getFScale( void );
	
	//@}



	/**
	 * @name Initialization methods.
	 */
	//@{
	
	/**
	 * @brief Set fields and dirty flags to default values.
	 */
	void	setToDefaults( void );
	
	void	setTransformationToDefaults();	
	
	/**
	 * @brief Using CTRL + SHIFT + Mouse (1 button).
	 * 
	 * @todo Complete documentation.
	 */
	void setBindingsToDefaults();
	
	/**
	 * @brief Disable all visual feedback.
	 */
	void setNullFeedback();
	
	/**
	 * @brief Enable visual feedback (with bounding box surrounding \c surround sub scene graph).
	 */
	void setBoundingBoxFeedback();

	/**
	 * @brief Enable visual feedback (with bounding box surrounding \c surround sub scene graph and axis).
	 */
	void setBoundingBoxAndAxisFeedback();

protected:
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
	Scale1Dragger( const std::string nodeName );

	//@}
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_SCALE1DRAGGER_HPP
