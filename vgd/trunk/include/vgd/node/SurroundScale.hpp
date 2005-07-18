// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_SURROUNDSCALE_H
#define _VGD_NODE_SURROUNDSCALE_H

#include "vgd/vgd.hpp"

#include "vgd/field/Node.hpp"
#include "vgd/node/GeometricalTransformation.hpp"



namespace vgd
{

namespace node
{


/**
 * @brief Automatically scale geometry to surround other geometry.
 * 
 * This node calculates a transformation (a translation, a scale and a rotation) which will, when the node is traversed,
 * be appended to the current geometrical matrix, making a default cube placed directly after (in the traverse order) 
 * surround the specified geometry.
 * 
 * New field added by this node :
 * 
 * - SFNode \c surround = vgd::Shp<vgd::node::Node>(0)\n
 * 	Sets the node that contains the moving shape(s) that must be surrounded. 
 * 	The node must implement a vgd::node::IBoundingBox interface (like a Group or a Shape).
 *		Be careful, \c surround field must NEVER be equal to one of its own parent node (infinite loop).
 *
 * @todo The sub scene graph reference by the \c surround field is used to compute bounding box. So at this time
 * (must be fix) bounding boxes for this sub scene graph are 'local' to this sub scene graph (not the same if computation
 * is done from root node).
 * 
 * @ingroup g_nodes
 * @ingroup g_singleAttributeNodes
 * @ingroup g_transformationNodes
 */
struct VGD_API SurroundScale : public vgd::node::GeometricalTransformation
{
	META_NODE_HPP( SurroundScale );




	/**
	 * @name Accessors to field surround.
	 */
	//@{

	/**
	 * @brief Typedef for the \c surround field.
	 */	
	typedef vgd::field::SFNode FSurroundType;
		
	/**
	 * @brief Typedef for the \c surround value.
	 */
	typedef vgd::Shp< vgd::node::Node > SurroundValueType;
	
	/**
	 * @brief Gets the surround of node.
	 */
	const SurroundValueType		getSurround() const;

	/**
	 * @brief Sets the surround of node.
	 * 
	 */
	void								setSurround( const SurroundValueType value );

	//@}
	
	
	
	/**
	 * @name Fields names enumeration.
	 */
	//@{

	/**
	 * @brief Returns the name of field \c surround.
	 * 
	 * @return the name of field \c surround.
	 */
	static const std::string getFSurround();
	//@}



protected:
	/**
	 * @name Constructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	SurroundScale( const std::string nodeName );

	void	setToDefaults();

	void	setOptionalsToDefaults();

	//@}
};


} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_SURROUNDSCALE_H
