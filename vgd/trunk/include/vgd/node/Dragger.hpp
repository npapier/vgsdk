// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_DRAGGER_H
#define _VGD_NODE_DRAGGER_H

#include <vgm/Matrix.hpp>

#include "vgd/vgd.hpp"
#include "vgd/event/ButtonStateSet.hpp"
#include "vgd/field/Bool.hpp"
#include "vgd/field/Integer.hpp"
#include "vgd/field/Node.hpp"
#include "vgd/node/Kit.hpp"



namespace vgd
{

namespace node
{

struct MatrixTransform;

/**
 * @brief Base class for all draggers.
 * 
 * @todo FIXME : UPDATE DOC ??? !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * 
 * BEGIN FIXME
 * Draggers is a mechanism used to interact with elements in 3D by using devices like mouse and keyboard (see 
 * vgd::event::Source). Scaling, rotating or translating geometry or other instances in the scene 
 * (like Light sources) could be done.
 * 
 * It holds the current motion matrix and offers lots of convenience methods to build from for it's subclasses.
 * The motion matrix is used to modify the geometrical matrix during traversal (like vgd::node::MatrixTransform), and 
 * is applied to all subsequent nodes in the traverse order like usual.
 * All draggers should update the motion matrix during dragging.
 * END FIXME
 * 
 * New field added by this node :
 * 
 * - SFBool \c listener = true\n
 * 	If listener is true, then all events received by this node are processed, otherwise events are just ignored.
 * 
 * - SFNode \c surround = vgd::Shp<vgd::node::Node>(0)\n
 * 	Sets the node that contains the moving shape(s) that must be surrounded. The node must implement a 
 * 	vgd::node::IBoundingBox interface (like a Group or a Shape).
 *
 * - SFInt32 \c currentState	= DRAGGER_DEFAULT\n
 * 	Holds the current state of the dragger. Use it to modify the behavior of the dragger. See classes derived from 
 * 	Dragger for more informations.
 * 
 * - PAF<int32, ButtonStateSet > \c bindings = See classes derived from Dragger for more informations.\n
 * 	A dragger is a state machine (see field \c currentState). It's current state changed when buttons are pressed.
 * 	This field sets the current bindings between the state of the dragger and the button state 
 * 	set (the list of buttons in the DOWN state). It can be changed at run-time and be different for each instance of 
 * 	this node.
 * 	
 * @ingroup g_abstractNodes
 *
 * @todo viewVolume, Projector, viewport.
 * @todo Grab event.
 * @todo bounding box
 * @todo set/get:MinGesture
 * @todo protected: - PAF< string, int8 > states = empty\n
 * 		A state is labeled by a name and an identifier (from 0 to n in the order of the creation of the state).
 * 		This field defines the associations between a state name and its identifier.
 */
struct VGD_API Dragger : public vgd::node::Kit
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
		DRAGGER_DEFAULT = NONE
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
	 * @name Accessors to field bindings.
	 */
	//@{

	/**
	 * @brief Enumeration of the \c bindings parameters.
	 */
	typedef CurrentStateValueType BindingsParameterType;

	/**
	 * @brief Typedef for the \c bindings value.
	 */
	typedef vgd::event::ButtonStateSet BindingsValueType;

	/**
	 * @brief Typedef for the \c bindings field.
	 */	
	typedef vgd::field::TPairAssociativeField< BindingsParameterType, BindingsValueType > FBindingsType;

	/**
	 * @brief Gets the bindings value.
	 */
	bool			getBindings( const BindingsParameterType param, BindingsValueType& value ) const;

	/**
	 * @brief Sets the bindings value.
	 */
	void 			setBindings( const BindingsParameterType param, BindingsValueType value );
	
	/**
	 * @brief Erase the bindings value.
	 */
	void 			eraseBindings( const BindingsParameterType param );
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
	
	/**
	 * @brief Returns the name of field \c bindings.
	 * 
	 * @return the name of field \c bindings.
	 */
	static const std::string getFBindings();	
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



	/**
	 * @name Helpers methods.
	 */
	//@{
	
	/**
	 * @brief Gets the value of the transformation matrix owned by this node.
	 * 
	 * @return a matrix
	 */
	const vgm::MatrixR& getMatrix() const;

// protected: FIXME
	/**
	 * @brief Sets the value of the transformation matrix owned by this node.
	 * 
	 * @param matrix	a matrix
	 * 
	 * @remarks Use by derived class to update the node returned by getMatrixTransform().
	 */
	void setMatrix( const vgm::MatrixR& matrix );	

	//@}


	/**
	 * @name Initialization methods.
	 */
	//@{
	
	/**
	 * @brief Set or reset \c bindings field to its default state.
	 */
	virtual void setBindingsToDefaults()=0;

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
	
	
	
	/**
	 * @name Internal helpers.
	 */
	//@{
	
	/**
	 * @brief Gets the node that contains the transformation owned by this node.
	 * 
	 * @return a MatrixTransform node.
	 */
	vgd::Shp< vgd::node::MatrixTransform > getMatrixTransform() const;
	
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
