// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_DRAGGER_H
#define _VGD_NODE_DRAGGER_H

#include "vgd/vgd.hpp"

#include "vgd/field/Bool.hpp"
#include "vgd/field/Integer.hpp"
#include "vgd/field/Node.hpp"
#include "vgd/node/MatrixTransform.hpp"



namespace vgd
{

namespace node
{

/**
 * @brief Base class for all draggers.
 * 
 * Draggers is a mechanism used to interact with elements in 3D by using devices like mouse, keyboard (vgd::event::Source).
 * Scaling, rotating or translating geometry or other instances in the scene (like cameras or lightsources) could be done.
 * 
 * It holds the current motion matrix and offers lots of convenience methods to build from for it's subclasses.
 * The motion matrix is used to modify the geometrical matrix during traversal (like vgd::node::MatrixTransform), and 
 * is applied to all subsequent nodes in the traverse order like usual.
 * All draggers should update the motion matrix during dragging.
 *
 * New field added by this node :
 * 
 * - SFBool \c activate = true\n
 * 	If activate is true, then all events received by this node are processed, otherwise events are ignored.
 * 
 * - SFNode \c surround = vgd::Shp<vgd::node::Node>(0)\n
 * 	Sets the node that surrounded the 3d elements with which interations are done. The node must be have a
 * 	vgd::node::IBoundingBox interface.
 *
 * - SFInt32 \c state	= 0\n
 * 	Holds the current state of the dragger. Use it to modify the behavior of the dragger. See classes derived from 
 * 	Dragger for more informations.
 * 
 * @ingroup g_nodes
 * @ingroup g_transformationNodes
 * @ingroup g_singleAttributeNodes
 * 
 * @todo use nodeKit
 * @todo viewVolume, Projector, viewport.
 * @todo Grab event.
 * @todo bounding box
 * @todo set/get:MinGesture
 */
struct VGD_API Dragger : public vgd::node::MatrixTransform
{
	/**
	 * @name Accessors to field activate.
	 */
	//@{

	/**
	 * @brief Typedef for the \c activate field.
	 */	
	typedef vgd::field::SFBool FActivateType;
		
	/**
	 * @brief Typedef for the \c activate value.
	 */
	typedef bool ActivateValueType;
	
	/**
	 * @brief Gets the activate of node.
	 */
	const ActivateValueType		getActivate() const;

	/**
	 * @brief Sets the activate of node.
	 * 
	 */
	void								setActivate( const ActivateValueType value );

	//@}



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
	 * @name Accessors to field state.
	 */
	//@{

	/**
	 * @brief Typedef for the \c state field.
	 */	
	typedef vgd::field::SFInt32 FStateType;
		
	/**
	 * @brief Typedef for the \c state value.
	 */
	typedef int32 StateValueType;
	
	/**
	 * @brief Gets the state of node.
	 */
	const StateValueType		getState() const;

	/**
	 * @brief Sets the state of node.
	 * 
	 */
	void							setState( const StateValueType value );

	//@}



	/**
	 * @name Fields names enumeration.
	 */
	//@{

	/**
	 * @brief Returns the name of field \c activate.
	 * 
	 * @return the name of field \c activate.
	 */
	static const std::string getFActivate();
	
	/**
	 * @brief Returns the name of field \c surround.
	 * 
	 * @return the name of field \c surround.
	 */
	static const std::string getFSurround();
	
	/**
	 * @brief Returns the name of field \c state.
	 * 
	 * @return the name of field \c state.
	 */
	static const std::string getFState();
	//@}



	/**
	 * @name Accessors to some temporary datas.
	 */
	//@{
	
	/**
	 * @brief Gets the starting point for a drag.
	 */
	const vgm::Vec2f&	getStartingPoint() const;
	
	/**
	 * @brief Sets the starting point for a drag.
	 */
	void					setStartingPoint( const vgm::Vec2f& startingPoint );
	
	/**
	 * @brief Returns if the starting point has been initialized by the user (at least one time).
	 */
	bool					isStartingPoint() const;

	//@}



protected:
	/**
	 * @name Constructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	Dragger( const std::string nodeName );

	void	setToDefaults();

	void	setOptionalsToDefaults();

	//@}

private:

	/**
	 * @name Datas.
	 */
	//@{
	vgm::Vec2f		m_startingPoint;
	//@}
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_DRAGGER_H
