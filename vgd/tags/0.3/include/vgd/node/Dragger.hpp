// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_DRAGGER_HPP
#define _VGD_NODE_DRAGGER_HPP

#include <vgm/Matrix.hpp>

#include "vgd/vgd.hpp"
#include "vgd/event/ButtonStateSet.hpp"
#include "vgd/node/IDragger.hpp"
#include "vgd/node/SurroundScale.hpp"
#include "vgd/node/Switch.hpp"
#include "vgd/node/TransformSeparator.hpp"



namespace vgd
{

namespace node
{

struct MatrixTransform;

/**
 * @brief Base class for all single draggers.
 * 
 * It holds the current motion matrix and offers lots of convenience methods to build from for it's subclasses.
 * The motion matrix is used to modify the geometrical matrix during traversal (like vgd::node::MatrixTransform), and 
 * is applied to all subsequent nodes in the traverse order like usual.
 * All draggers should update the motion matrix during dragging.
 *
 * New field added by this node :
 * 
 * - SFBool \c feedback = false\n
 * 	If \c feedback is true, then the visual feedback is enabled.
 * 
 * - PAF<int32, ButtonStateSet > \c bindings = See classes derived from Dragger for more informations.\n
 * 	A dragger is a state machine (see field \c currentState). It's current state changed when buttons are pressed.
 * 	This field sets the current bindings between the state of the dragger and the button state 
 * 	set (the list of buttons in the DOWN state). It can be changed at run-time and be different for each instance of 
 * 	this node.
 * 	
 * @ingroup g_abstractNodes
 *
 * @todo Accessors to change the feedback geometry for a specific state.
 * @todo Manipulator to hide Dragger usage.
 * 
 * @todo viewVolume, Projector, viewport.
 * @todo Grab event.
 * @todo set/get:MinGesture
 * @todo protected: - PAF< string, int8 > states = empty\n
 * 		A state is labeled by a name and an identifier (from 0 to n in the order of the creation of the state).
 * 		This field defines the associations between a state name and its identifier.
 */
struct VGD_API Dragger : public vgd::node::IDragger
{
	/**
	 * @name Accessors to field feedback.
	 */
	//@{

	/**
	 * @brief Typedef for the \c feedback field.
	 */	
	typedef vgd::field::SFBool FFeedbackType;
		
	/**
	 * @brief Typedef for the \c feedback value.
	 */
	typedef bool FeedbackValueType;
	
	/**
	 * @brief Gets the feedback of node.
	 */
	const FeedbackValueType		getFeedback() const;

	/**
	 * @brief Sets the feedback of node.
	 * 
	 */
	void								setFeedback( const FeedbackValueType value );
	//@}


	// field state
	// overrides
	void setCurrentState( const CurrentStateValueType value );
	void setSurround( const SurroundValueType value );

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
	 * @name Pure virtual methods.
	 */
	//@{
	
	/**
	 * @brief Compute the geometric 3D transformation of this node from the fields.
	 * 
	 * @return the transformation matrix.
	 */
	virtual vgm::MatrixR			computeMatrixFromFields() const=0;

	//@}
		
		
	
	/**
	 * @name Initialization methods.
	 */
	//@{

	/**
	 * @brief Set or reset the 3D geometric transformation of the dragger to its default state
	 * (by setting all fields used to compute this transformation).
	 */
	virtual void setTransformationToDefaults()=0;
	
	/**
	 * @brief Set or reset \c bindings field to its default state.
	 */
	virtual void setBindingsToDefaults()=0;

	//@}



	/**
	 * @name Fields names enumeration.
	 */
	//@{

	/**
	 * @brief Returns the name of field \c feedback.
	 * 
	 * @return the name of field \c feedback.
	 */
	static const std::string getFFeedback();	
	
	/**
	 * @brief Returns the name of field \c bindings.
	 * 
	 * @return the name of field \c bindings.
	 */
	static const std::string getFBindings();	
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
	vgd::Shp< vgd::node::MatrixTransform > getMatrixTransformNode() const;

	/**
	 * @brief Gets the surround node.
	 * 
	 * @return a surround node.
	 */
	vgd::Shp< vgd::node::SurroundScale > getSurroundNode() const;
	
	/**
	 * @brief Gets the switch node that contains all feedback sub-scene graph.
	 * 
	 * @return a switch node.
	 */
	vgd::Shp< vgd::node::Switch > getFeedbackSwitchNode() const;
	//@}

protected:
	/**
	 * @name Feedback helpers.
	 */
	//@{
	
	void setupNullFeedback( const uint32 numberOfState );

	void setupBoundingBoxFeedback( const uint32 numberOfState );
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

#endif //#ifndef _VGD_NODE_DRAGGER_HPP
