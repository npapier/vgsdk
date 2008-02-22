// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_NULLDRAGGER_HPP
#define _VGD_NODE_NULLDRAGGER_HPP

#include "vgd/vgd.hpp"

#include "vgd/node/Dragger.hpp"



namespace vgd
{

namespace node
{



/**
 * @brief Dragger without any transformations.
 * 
 * No new field added by this node.
 * 
 * @ingroup g_nodes
 * @ingroup g_nodekits
 * @ingroup g_transformationNodes
 */
struct VGD_API NullDragger : public vgd::node::Dragger
{
	META_NODE_HPP( NullDragger );

	/**
	 * @brief Enumeration of the different states of this dragger.
	 */
	enum {
		NONE = 0,

		NULLDRAGGER_DEFAULT = NONE
	};



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
	 * @name Initialization methods.
	 */
	//@{
	
	/**
	 * @brief Set fields and dirty flags to default values.
	 */
	void	setToDefaults( void );
	
	void setTransformationToDefaults();
	
	/**
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
	NullDragger( const std::string nodeName );

	//@}
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_NULLDRAGGER_HPP
