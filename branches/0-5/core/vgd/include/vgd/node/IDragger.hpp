// VGSDK - Copyright (C) 2004, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_IDRAGGER_HPP
#define _VGD_NODE_IDRAGGER_HPP

#include <vgm/Matrix.hpp>

#include "vgd/field/Bool.hpp"
#include "vgd/field/Integer.hpp"
#include "vgd/field/NodeShp.hpp"
#include "vgd/node/Kit.hpp"
#include "vgd/node/Switch.hpp"
#include "vgd/node/TransformSeparator.hpp"



namespace vgd
{

namespace node
{

struct MatrixTransform;

/**
 * @brief Common interface for the two kind of draggers (single Dragger and composite draggers MultiDragger).
 * 
 * Draggers is a mechanism used to interact with elements in 3D by using devices like mouse and keyboard (see 
 * vgd::event::Source). Scaling, rotating or translating geometry or other instances in the scene 
 * (like Light sources) could be done.
 * 
 * New field added by this node :
 * 
 * - SFBool \c listener = true\n
 * 	If \c listener is true, then all events received by this node are processed, otherwise events are just ignored.
 * 
 * - SFNode \c surround = vgd::Shp<vgd::node::Node>(0)\n
 * 	Sets the node that contains the moving shape(s) that must be surrounded. 
 * 	The node must implement a vgd::node::IBoundingBox interface (like a Group or a Shape).
 *
 * - SFInt32 \c currentState	= IDRAGGER_DEFAULT\n
 * 	Holds the current state of the dragger. Use it to modify the behavior of the dragger. See classes derived from 
 * 	IDragger for more informations.
 *
 * @ingroup g_abstractNodes
 */
struct VGD_API IDragger : public vgd::node::Kit
{
	/**
	 * @name Accessors to field listener.
	 */
	//@{

	/**
	 * @brief Typedef for the \c listener field.
	 */	
	typedef vgd::field::SFBool FListenerType;
		
	/**
	 * @brief Typedef for the \c listener value.
	 */
	typedef bool ListenerValueType;
	
	/**
	 * @brief Gets the listener of node.
	 */
	const ListenerValueType		getListener() const;

	/**
	 * @brief Sets the listener of node.
	 * 
	 */
	void								setListener( const ListenerValueType value );

	//@}



	/**
	 * @name Accessors to field surround.
	 */
	//@{

	/**
	 * @brief Typedef for the \c surround field.
	 */	
	typedef vgd::field::SFNodeShp FSurroundType;
		
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
	 * @name Accessors to field currentState.
	 */
	//@{

	/**
	 * @brief Typedef for the \c currentState field.
	 */	
	typedef vgd::field::SFInt32 FCurrentStateType;
	
	/**
	 * @brief Enumeration of the different states of this dragger.
	 */
	enum {
		NONE = 0,
		IDRAGGER_DEFAULT = NONE
	};
		
	/**
	 * @brief Typedef for the \c currentState value.
	 */
	typedef int32 CurrentStateValueType;
	
	/**
	 * @brief Gets the currentState of node.
	 */
	const CurrentStateValueType	getCurrentState() const;

	/**
	 * @brief Sets the currentState of node.
	 * 
	 */
	void									setCurrentState( const CurrentStateValueType value );

	//@}



	/**
	 * @name Fields names enumeration.
	 */
	//@{

	/**
	 * @brief Returns the name of field \c listener.
	 * 
	 * @return the name of field \c listener.
	 */
	static const std::string getFListener();
	
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
	static const std::string getFCurrentState();
	//@}



protected:
	/**
	 * @name Constructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 */
	IDragger( const std::string nodeName );

	void	setToDefaults();

	void	setOptionalsToDefaults();

	//@}
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_IDRAGGER_HPP
