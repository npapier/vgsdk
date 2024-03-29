// VGSDK - Copyright (C) 2004, 2008, 2009, 2010, 2011, 2012, 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGE_ENGINE_ENGINE_HPP
#define _VGE_ENGINE_ENGINE_HPP

#include <list>
#include <set>
#include <boost/tuple/tuple.hpp>

#include <vgd/Shp.hpp>
#include <vgd/basic/Time.hpp>
#include <vgd/field/Enum.hpp>
#include <vgd/field/FieldManager.hpp>
#include <vgd/field/TAccessors.hpp>
#include "vgd/field/TOptionalField.hpp"
#include <vgd/node/Camera.hpp>
#include <vgDebug/helpers.hpp>

#include "vge/engine/MultiMatrixStack.hpp"
#include "vge/service/Service.hpp"
#include "vge/visitor/NodeCollectorExtended.hpp"

namespace vgd { namespace node { struct GeoMorph; } }



/**
 * @namespace vge::engine
 * 
 * @brief Engine evaluate scene graph with handlers
 */



namespace vge
{

namespace handler 
{
	struct Handler;
}

namespace engine
{



/**
 * @brief Defines read/write mask of color buffers and depth buffer and the depth function
 */
enum BufferUsagePolicy
{
	BUP_NOT_DEFINED,		///< no policy
	BUP_ONLY_COLOR_NO_CLEAR,///< enables writing to color buffer(s) and disables writing to depth buffer. But only draw if the depth of the incoming fragment is less or equal to the depth already in the depth buffer. Disables the cleaning of buffers done in ClearFrameBuffer handler. Transparency is the typical use case
	BUP_ONLY_DEPTH,			///< disables writing to color buffer(s) and enables writing to depth buffer
	BUP_ONLY_COLOR,			///< enables writing to color buffer(s) and disables writing to depth buffer. But only draw if the depth of the incoming fragment matches the depth already in the depth buffer
	BUP_COLOR_AND_DEPTH,	///< enables writing to color buffer(s) and enables writing to depth buffer
	BUP_DEFAULT = BUP_COLOR_AND_DEPTH
};


/**
 * @brief Defines which eye(s) must be considered (mainly used in ClearFrameBuffer and Camera).
 */
typedef vgd::node::Camera::EyeUsagePolicy EyeUsagePolicy;



/**
 * @brief Evaluate scene graph.
 * 
 * First scene graphs are traversed by NodeCollectorExtended. Next each Node(Shape or Attribute) are evaluated by the 
 * engine.
 * Engine is responsible for associating the correct handler for each node and to maintain a stack of state during 
 * evaluation.
 * @todo updates : At startup, the stack contains a state with all nodes (with theirs fields initialized, even optionals fields).
 * 
 * This process depends on installed Handler for evaluating each single node.
 * This process depends on installed Technique for filtering/multipass algorithms (TODO)
 * 
 * @remarks \b DefaultConstructible.
 * 
 * @todo Clean evaluation( with/without trace ).
 * @todo all StateStack methods should go in another class.
 * 
 * @todo Management(remove, replace, copy) of registered handlers or installed handlers.
 * @todo Copy servicesHandler for another services.
 * @todo use evaluate( state ) for separator ?
 */
struct VGE_API Engine : public vgd::field::FieldManager
{
	/**
	 * @name Typedefs used by the stacks of states.
	 */
	//@{

	typedef std::list<	vgd::node::Node*	>		NodeList;
	
	/**
	 * @brief A map with a (key, list_pnode)
	 * 
	 * The \c key represents the index of the attribute(0 for texture 0, 1 for texture 1...).
	 * The \c list_pnode represents a list of node pointers.
	 * 
	 * @remarks Map only useful for MultiAttribute (multiple attribute active in the same time), but all nodes are 
	 * processed in the same way.
	 */
	/**
	 * @todo Use vgd::node::PNodeList.
	 */
	typedef std::map<		int32, NodeList	>		MultiState;

	typedef std::pair<	int32, NodeList	>			MultiStatePair;

	/**
	 * @brief Table(indexed by node index) of MultiStateStack.
	 * 
	 * This class represents a complete traversal state (without modelview, projection and texture matrix stacks).
	 */
	typedef std::vector< MultiState >				State;

	/**
	 * @brief Stack of State.
	 * 
	 * @remark Useful to implement quickly the Separator node.
	 */
	typedef std::vector< State >					StateStack;

	//@}



	/**
	 * @name Constructor like
	 */
	//@{
	
	/**
	 * @brief Default constructor
	 */
	Engine();

	/**
	 * @brief Reset handlers, state stack and matrix stacks (texture, projection and geometrical).
	 */
	virtual void reset();
	
	/**
	 * @brief Reset state stack and matrix stacks (texture, projection and geometrical).
	 */
	virtual void resetEval();

	//@}



	/**
	 * @name Evaluation
	 */
	//@{


	/**
	 * @brief Evaluation of a node
	 * 
	 * @param	service			service to use during evaluation (Painter...)
	 * @param	pNode			node to evaluate
	 * @param	isPreTraverse	true if preTraverse (when a node is encountered for the first time), false if 
	 * 							postTraverse (when all children of this node have been already encountered)
	 * @param	bTrace			true if the evaluation of the node must be stored in the engine state, false if not.
	 */
	void evaluate(	const vgd::Shp< vge::service::Service > service,
					vgd::node::Node* pNode, 
					const bool isPreTraverse,
					const bool bTrace = true );


	/**
	 * @brief Evaluation of a node
	 * 
	 * @param	service		service to use during evaluation (Painter...)
	 * @param	element	traverse element to evaluate
	 * @param	bTrace		true if the evaluation of the node must be stored in the engine state, false if not.
	 */
	void evaluate(	const vgd::Shp< vge::service::Service > service,
					const vge::visitor::TraverseElement & element,
					const bool bTrace = true );


	void evaluate(	const vgd::Shp< vge::service::Service > service,
					vgd::Shp< vgd::node::Node > node,
					const bool isPreTraverse = true,
					const bool bTrace = true );

	void paint(		const vge::visitor::TraverseElement & element,
					const bool bTrace = true );

	void paint(		vgd::Shp< vgd::node::Node > node,
					const bool isPreTraverse = true,
					const bool bTrace = true );


	void evaluate(	const vgd::Shp< vge::service::Service > service,
					vgd::Shp< vgd::node::Node > node1, vgd::Shp< vgd::node::Node > node2,
					const bool isPreTraverse = true,
					const bool bTrace = true );

	void paint2(	vgd::Shp< vgd::node::Node > node1, vgd::Shp< vgd::node::Node > node2,
					const bool isPreTraverse = true,
					const bool bTrace = true );


	void evaluate(	const vgd::Shp< vge::service::Service > service,
					vgd::Shp< vgd::node::Node > node1, vgd::Shp< vgd::node::Node > node2, vgd::Shp< vgd::node::Node > node3,
					const bool isPreTraverse = true,
					const bool bTrace = true );

	void paint3(	vgd::Shp< vgd::node::Node > node1, vgd::Shp< vgd::node::Node > node2, vgd::Shp< vgd::node::Node > node3,
					const bool isPreTraverse = true,
					const bool bTrace = true );


	/**
	 * @brief Sets if engine need to trace everything.
	 *
	 * @param trace		true if trace is enabled, false otherwise
	 */
	void setTrace( const bool trace = true );

	/**
	 * @brief Tests if trace is active.
	 *
	 * @return true if active, false otherwise
	 */
	const bool isTraceEnabled() const;
	//@}



	/**
	 * @name Handler management
	 * 
	 * @todo More accessors like isRegarded*().
	 * @todo regardIfIsAKindOf() works, but be carefull about multiattribute that comes from vgeGL::engine::populate*()
	 * 		=> multiples test. It could be optimized.
	 * @todo desinstall handler.
	 */
	//@{

	/**
	 * @brief Reset handlers dispatch table.
	 *
	 * @remarks Called by constructor.
	 */
	virtual void resetHandlers();

	/**
	 * @brief Clear handlers dispatch table.
	 */
	virtual void clearHandlers();

	/**
	 * @brief Initialize handlers dispatch table.
	 */
	virtual void initializeHandlers();

	/**
	 * @brief Install an handler in the engine (i.e. in the dispatch matrix).
	 * 
	 * @pre clearHandlers() must have been called at least once before.
	 * 
	 * @param shpHandler	a smart pointer on the handler(from the registry).
	 */
	void install( vgd::Shp< vge::handler::Handler > shpHandler );

	//@}


	/**
	 * @name regard/disregard handler(s)
	 */
	//@{

	/**
	 * @brief Activates the evaluation process for all node type.
	 *
	 * @param enabled	true to activate the evaluation, false to deactivate it
	 */
	void regard( const bool enabled = true );

	/**
	 * @brief Activates the evaluation process for a specific node type.
	 *
	 * @param enabled	true to activate the evaluation, false to deactivate it
	 */
	template< typename nodeType >
	void regardIfIsA( const bool enabled = true );
	
	/**
	 * @brief Activates the evaluation process for all node that inherit from the specified node type.
	 *
	 * @param enabled	true to activate the evaluation, false to deactivate it
	 */
	template< typename nodeType >
	void regardIfIsAKindOf( const bool enabled = true );

	/**
	 * @brief Deactivates the evaluation process for all node type.
	 *
	 * @param disabled	true to deactivate the evaluation, false to activate it
	 */
	void disregard( const bool disabled = true );

	/**
	 * @brief Deactivates the evaluation process for a specific node type.
	 *
	 * @param disabled	true to deactivate the evaluation, false to activate it
	 */
	template< typename nodeType >
	void disregardIfIsA( const bool disabled = true );
	
	/**
	 * @brief Deactivates the evaluation process for all node that inherit from the specified node type.
	 *
	 * @param disabled	true to deactivate the evaluation, false to activate it
	 */
	template< typename nodeType >
	void disregardIfIsAKindOf( const bool disabled = true );
	
	/**
	 * @brief Returns if the evaluation process for a specific node type is enabled.
	 * 
	 * @return true if evaluation is enabled.
	 */
	template< typename nodeType >
	bool isRegardedIfIsA() const;

	//@}



// @todo CLEAN
	/**
	 * @name States management
	 * 
	 * todo Should go in a new class ?
	 * todo push(Node), pop(Node).
	 */
	//@{

	/**
	 * @brief Resets completely the state stack.
	 * 
	 * This method call clearStateStack() and after call initializeStateStack().
	 * 
	 * post		sizeOfStateStack() must return 1.
	 */
	void resetStateStack();

	/**
	 * @brief Clears completely the state stack.
	 * 
	 * After calling this method, one uninitialized state is at the top of the stack.
	 * 
	 * @post		sizeOfStateStack() must return 1.
	 */
	void clearStateStack();

	/**
	 * @brief Initializes completely the state stack.
	 * 
	 * @post		sizeOfStateStack() must return 1.
	 * 
	 * @remarks Initialize the top of the stack with nodes founded in vgd node registry (node with all fields initialized
	 * to theirs defaults values).
	 */
	void initializeStateStack();

	/**
	 * @brief Tests if the state stack is empty.
	 * 
	 * @return true if the stack is empty, false otherwise.
	 */
	bool isStateStackEmpty() const;

	/**
	 * @brief Returns the number of elements in the state stack.
	 * 
	 * @return the number of elements in the stack.
	 */
	const uint sizeOfStateStack() const;

	/**
	 * @brief Sets a node to the top of the state stack.
	 * 
	 * @remarks Add this node to the list of the currently active nodes for this node type (see NodeList in MultiState).
	 */
	void setStateStackTop( vgd::node::Node *pNode );

	/**
	 * @brief Adds an element(a copy of the current top) to the top of the state stack.
	 */
	void pushStateStack();

	/**
	 * @brief Removes the element from the top of the stack.
	 * 
	 * @return true if sucessful, false if size of the stack is already zero.
	 */
	bool popStateStack();

	//@}


	/**
	 * @name State stack accessors
	 */
	//@{

	/**
	 * @brief Retrieves the desired node list from the top of the state stack
	 * 
	 * The return node list is selected by the given \c nodeType and \c multiAttributeIndex.
	 * 
	 * @return Pointer on the desired node list or 0 if not found.
	 */
	template< typename nodeType >
	const NodeList*		getNodeListFromStateStackTop( const int8 multiAttributeIndex = 0 ) const
	{
		const State& 		topState		(	m_state.back()						);
		
		const int32 		nodeClassIndex	(	nodeType::getClassIndexStatic()		);
		const MultiState&	multiState		(	topState[nodeClassIndex]			);

		MultiState::const_iterator iter( multiState.find( multiAttributeIndex ) );

		if ( iter != multiState.end() )
		{
			// Found
			return &(iter->second);
		}
		else
		{
			return static_cast< NodeList* >(0);
		}
	}

	/**
	 * @brief Retrieves the desired node list from the top of the state stack
	 * 
	 * The return node list is selected by the given \c nodeType and \c multiAttributeIndex.
	 * 
	 * @return Pointer on the desired node list or 0 if not found.
	 */
	template< typename nodeType >
	NodeList*		getNodeListFromStateStackTop( const int8 multiAttributeIndex = 0 )
	{
		State& 				topState		(	m_state.back()						);
		
		const int32 		nodeClassIndex	(	nodeType::getClassIndexStatic()		);
		MultiState&			multiState		(	topState[nodeClassIndex]			);

		MultiState::iterator iter( multiState.find( multiAttributeIndex ) );
		
		if ( iter != multiState.end() )
		{
			// Found
			return &(iter->second);
		}
		else
		{
			return static_cast< NodeList* >(0);
		}
	}

	/**
	 * @brief Retrieves the desired node from the top of the state stack
	 * 
	 * The return node is selected by the given \c nodeType and \c multiAttributeIndex.
	 * 
	 * @return Pointer on the desired node or 0 if not found.
	 */
	template< typename nodeType >
	nodeType*		getStateStackTop( const int8 multiAttributeIndex = 0 )
	{
		NodeList *pNodeList = getNodeListFromStateStackTop< nodeType >( multiAttributeIndex );

		if ( pNodeList )
		{
			return dynamic_cast<nodeType*>(pNodeList->back());
		}
		else
		{
			return 0;
		}
	}



	/**
	 * @brief Retrieves the desired optional field \c value from the top of the state stack
	 * 
	 * The desired field is selected using the given \c NodeType, \c multiAttributeIndex, \c strFieldName and \c ValueType.
	 * @return the desired value
	 *
	 * @todo new parameter: check default node => false to ignore default node (iEnd++)
	 */
	template< typename NodeType, typename ValueType >
	const ValueType getOF(	const std::string& strFieldName,
							const int8 multiAttributeIndex = 0 ) const
	{
		ValueType retVal;

		const NodeList *nodeList = getNodeListFromStateStackTop< NodeType >( multiAttributeIndex );
		vgAssertN( nodeList != 0, "Empty node list. Internal error" );
		vgAssertN( nodeList->front()->isField( strFieldName ), "The given fieldname %s is unknown", strFieldName.c_str() );

		for( NodeList::const_reverse_iterator	i			= nodeList->rbegin(),
												iEnd		= nodeList->rend();
				i != iEnd;
				++i )
		{
			using vgd::field::EditorRO;
			typedef vgd::field::TOptionalField<ValueType> MyOptionalField;

			const vgd::node::Node * node = *i;

			EditorRO< MyOptionalField > editRO = node->template getFieldRO< MyOptionalField >( strFieldName );
			const bool bDefined = editRO->getValue( retVal );

			if ( bDefined )
			{
				return retVal;
			}
		}

		vgAssertN( false, "Unable to find field %s", strFieldName.c_str() );
		return retVal;
	}

	/**
	 * @see Helpers for getOF()
	 */
	template< typename NodeType >
	const vgd::field::Enum getOFEnum(	const std::string& strFieldName,
										const int8 multiAttributeIndex = 0 ) const
	{
		return getOF< NodeType, vgd::field::Enum >( strFieldName, multiAttributeIndex );
	}



	/**
	 * brief Gets the desired field value from the top of the state stack
	 * 
	 * Gets the desired field value from a node (selected by his type and his multi-attribute index) from the top of the
	 * state stack that has the key \c ParameterType defined in the 
	 * vgd::field::TPairAssociativeField< ParameterType, ValueType > field named strFieldName.
	 *
	 * return true if found, false otherwise.
	 */
	template< typename nodeType, typename ParameterType, typename ValueType >
	bool getStateStackTop(	const std::string& strFieldName,
							const ParameterType param, ValueType& value,
							const int8 multiAttributeIndex = 0 ) const
	{
		bool bDefined(	false	);

		const NodeList *pNodeList = getNodeListFromStateStackTop< nodeType >( multiAttributeIndex );
		
		if ( pNodeList != 0 )
		{
			for( NodeList::const_reverse_iterator	i			= pNodeList->rbegin(),
													iEnd		= pNodeList->rend();
					i != iEnd;
					++i )
			{
				bDefined = vgd::field::getParameterValue< ParameterType, ValueType >(
					*i,
					strFieldName,
					param, value );

				if ( bDefined )
				{
					break;
				}
			}
		}

		return bDefined;
	}



	/**
	 * @brief Gets the desired single field value from the top of the state stack
	 * 
	 * Gets the desired single field named strFieldName value from a node (selected by his type and his multi-attribute index) from the top of the
	 * state stack.
	 *
	 * return true if found, false otherwise.
	 */
	template< typename nodeType, typename ParameterType, typename ValueType >
	bool getStateStackTopFromSingleField( std::string strFieldName, ValueType& value, const bool checkDefaultNode = true ) const
	{
		bool bDefined(	false	);

		const NodeList *pNodeList = getNodeListFromStateStackTop< nodeType >();

		if ( pNodeList )
		{
			NodeList::const_reverse_iterator i		= pNodeList->rbegin();
			NodeList::const_reverse_iterator iEnd	= pNodeList->rend();
			if( !checkDefaultNode )
			{
				--iEnd;
			}

			for( i;	i != iEnd; ++i )
			{
				bDefined = vgd::field::getParameterValueFromSingleField< ParameterType, ValueType >( (*i), strFieldName, value );

				if ( bDefined )
				{
					break;
				}
			}
		}

		return bDefined;
	}


	/**
	 * @brief Gets the desired optional field value from the top of the state stack
	 * 
	 * Gets the desired optional field named strFieldName value from a node (selected by his type and his multi-attribute index) from the top of the
	 * state stack.
	 *
	 * @param checkDefaultNode true if we check default node, false otherwise.
	 *
	 * return true if found, false otherwise.
	 */
	template< typename nodeType, typename ParameterType, typename ValueType >
	bool getStateStackTopFromOptionalField( const std::string& strFieldName, ValueType& value, const bool checkDefaultNode = true  ) const
	{
		bool bDefined(	false	);

		const NodeList *pNodeList = getNodeListFromStateStackTop< nodeType >();
		
		if ( pNodeList != 0 )
		{
			NodeList::const_reverse_iterator i		= pNodeList->rbegin();
			NodeList::const_reverse_iterator iEnd	= pNodeList->rend();
			if( !checkDefaultNode )
			{
				--iEnd;
			}

			for( ;	i != iEnd; ++i )
			{
				bDefined = vgd::field::getParameterValueFromOptionalField< ParameterType, ValueType >( (*i), strFieldName, value );

				if ( bDefined )
				{
					break;
				}
			}
		}

		return bDefined;
	}

	//@}



	/**
	 * @name Methods to manage stacks for each matrix type (projection, geometrical and texture).
	 */
	//@{

	/**
	 * @brief Resets completely all stacks for each matrix type.
	 * 
	 * @post getProjectionMatrix().getTop().isIdentity()
	 * @post getGeometricalMatrix().getTop().isIdentity()
	 * @post getTextureMatrix().getTop( i ).isIdentity() with i from 0 to getMaxTexUnits().
	 */
	virtual void resetMatrices();

	/**
	 * @brief Returns the projection matrix stacks.
	 */
	MultiMatrixStack&	getProjectionMatrix();

	/**
	 * @brief Returns the geometrical matrix stacks.
	 */
	MultiMatrixStack&	getGeometricalMatrix();

	/**
	 * @brief Returns the texture matrix stacks.
	 */
	MultiMatrixStack&	getTextureMatrix();

	//@}



	/**
	 * @name Built-in state accessors
	 */
	//@{

	/**
	 * @brief Returns the elapsed time between the creation of the engine and the call of this method.
	 *
	 * Use cases: input value for a random generator, time based animation and so on.
	 *
	 * @return a time duration object measuring the elapsed time between the creation of the engine and the call of this method.
	 */
	const vgd::basic::TimeDuration getElapsedTime() const;


	/**
	 * @brief Returns the drawing surface size
	 * 
	 * @return the drawing surface size in pixels
	 */
	const vgm::Vec2i getDrawingSurfaceSize() const;

	/**
	 * @brief Sets the drawing surface size
	 * 
	 * @param	drawingSurfaceSize		the drawing surface size 
	 *
	 * @remarks The drawing surface size is typically the window size (see vge::SceneManager::resize()).
	 */
	void setDrawingSurfaceSize( const vgm::Vec2i drawingSurfaceSize );


	/**
	 * @brief Returns the camera
	 *
	 * @return the last encountered Camera node
	 */
	const vgd::node::Camera * getCamera() const;

	/**
	 * @brief Sets the camera
	 *
	 * @param camera	the camera to set
	 *
	 * @see vge::handler::Camera
	 */
	void setCamera( const vgd::node::Camera * camera );

	/**
	 * @brief Returns the viewport
	 * 
	 * @return the value of \c viewport field for the last encountered Camera node with this field defined
	 */
	const vgm::Rectangle2i& getViewport() const;

	/**
	 * @brief Sets the viewport
	 *
	 * @param viewport	the viewport value
	 *
	 * @see vge::handler::Camera
	 */
	void setViewport( const vgm::Rectangle2i& viewport );

	/**
	 * @brief Returns a vector containing respectively the distances to the near and far depth clipping planes.
	 *
	 * @remark Distances are from the eye located at (0, 0, 0).
	 */
	const vgm::Vec2f getNearFar() const;

	/**
	 * @brief Sets the vector containing respectively the distances to the near and far depth clipping planes.
	 *
	 * @param nearFar	the vector containing near-far values
	 *
	 * @see vge::handler::Camera
	 */
	void setNearFar( const vgm::Vec2f nearFar );


	/**
	 * @brief Returns the last encountered GeoMorph node
	 *
	 * @return the last encountered GeoMorph node
	 */
	/*const*/ vgd::node::GeoMorph * getGeoMorph() /*const*/;

	/**
	 * @brief Sets the last encountered GeoMorph node
	 *
	 * @param geoMorph		the node to set
	 *
	 * @see vge::handler::GeoMorph (@todo vge::handler::GeoMorph actually work done in vgeGL::handler::painter)
	 */
	void setGeoMorph( /*const*/ vgd::node::GeoMorph * geoMorph );


	/**
	 * @brief Returns the geometrical matrix that is current when encountered the ClearFrameBuffer node.
	 *
	 * @return the geometrical matrix
	 *
	 * @todo rename Scene => World, @todo generic container map<string, MatrixR>
	 */
	const vgm::MatrixR& getSceneGeometricalMatrix();

	/**
	 * @brief Sets the geometrical matrix that is current when encountered the ClearFrameBuffer node.
	 *
	 * @param geometricalMatrix		the geometrical matrix
	 *
	 * @see vgeGL::handler::ClearFrameBuffer
	 */
	void setSceneGeometricalMatrix( const vgm::MatrixR& geometricalMatrix );


	/**
	 * @brief Returns the current buffer usage policy.
	 *
	 * @return the current buffer usage policy
	 */
	const BufferUsagePolicy getBufferUsagePolicy() const;

	/**
	 * @brief Sets the current buffer usage policy
	 *
	 * This policy is used by ClearFrameBuffer handler to setup color/depth mask and depth function.
	 *
	 * @remark This state is typically modified by technique between two passes.
	 */
	void setBufferUsagePolicy( const BufferUsagePolicy policy );


	/**
	 * @brief Returns the current eye usage policy.
	 *
	 * @return the current eye usage policy
	 */
	const EyeUsagePolicy getEyeUsagePolicy() const;

	/**
	 * @brief Sets the current eye usage policy
	 *
	 * This policy is used by ClearFrameBuffer handler and Camera handler.
	 *
	 * @remark This state is typically modified by technique between two passes.
	 */
	void setEyeUsagePolicy( const EyeUsagePolicy policy );


	/**
	 * @brief Returns the default maximum degree of anisotropy.
	 */
	const float getDefaultMaxAnisotropy() const;

	/**
	 * @brief Sets the default maximum degree of anisotropy.
	 *
	 * @param value		Preconditions not verified here, but when used by glo::Texture.
	 *
	 * @remark This state is modified by EngineProperties and Texture handlers.
	 * @see glo::Texture
	 */
	virtual void setDefaultMaxAnisotropy( const float value );

	//@}



	/**
	 * @name Implementations specifics capabilities
	 * @todo move to vgeGL
	 */
	//@{

	/**
	 * @brief Returns the maximum viewport dimensions.
	 */
	virtual const vgm::Vec2i getMaxViewportSize() const		{ return vgm::Vec2i(0,0); }

	/**
	 * @brief Returns the maximum number of lights.
	 */
	virtual const int getMaxLights() const					{ return 0; }
	
	/**
	 * @brief Returns the maximum number of texture units.
	 */
	virtual const int getMaxTexUnits() const				{ return 0; }

	/**
	 * @brief Returns the maximum 1D/2D texture image dimension.
	 */
	virtual const int getMaxTexSize() const					{ return 0; }
	
	/**
	 * @brief Returns the maximum 3D texture image dimension.
	 */
	virtual const int getMax3DTexSize() const				{ return 0; }

	/**
	 * @brief Returns the maximum cube map texture image dimension.
	 */
	virtual const int getMaxCubeMapTexSize() const			{ return 0; }
	//@}


	/**
	 * @name Helpers
	 */
	//@{

	/**
	 * @brief Pushes all stacks.
	 */
	virtual void push();

	/**
	 * @brief Pops all stacks.
	 */
	virtual void pop();

	//@}



	// change visibility of this method inherited from vgd::field::FieldManager.
	bool addField( vgd::field::AbstractField* pField );
	// @todo FIXME removeField().



protected:
	/**
	 * @brief Reset the state passed in parameter.
	 */
	void resetState( State& state ) const;



	/** 
	 * @name Typedefs
	 */
	//@{
	
	/**
	 * @brief Table of handlers for a specific service.
	 * 
	 * Index by object type.
	 */
	typedef std::vector< vgd::Shp<vge::handler::Handler> >			DispatchRow;
	
	/**
	 * @brief Table of DispatchRow.
	 * 
 	 * Index by services.
	 */
	typedef std::vector< DispatchRow >								DispatchMatrix;

	/**
	 * @brief Table of boolean.
	 */
	typedef std::vector< bool >										BooleanVector;
	//@}



	/**
	 * @name Dispatch data
	 */
	//@{

	/**
	 * @brief Matrix of handlers.
	 */
	DispatchMatrix		m_dispatch;
	
	/**
	 * @brief Table of boolean to mark an handler \c regared or \c disregarded during the evaluation process.
	 * 
	 * If an handler is regarded (or disregarded), it's true for all services.
	 * An handler (index i) is evaluated only if m_regarded[i] is true, otherwise it is ignored.
	 */
	BooleanVector		m_regarded;
	//@}



	/**
	 * @name Data stored during evaluation.
	 * 
	 * There is two groups of data :
	 * - state stacks.
	 * - matrix stacks.
	 */
	//@{
	
	/**
	 * @brief States stored during evaluation.
	 */
	StateStack								m_state;

	/**
	 * @brief A stack with projection matrix.
	 */
	vge::engine::MultiMatrixStack		m_projections;
	
	/**
	 * @brief A stack with geometrical matrix.
	 */	
	vge::engine::MultiMatrixStack		m_geometricals;

	/**
	 * @brief Multiples stacks with texture matrix.
	 * 
	 * The number of stacks is equal to the number of texture units.
	 */
	vge::engine::MultiMatrixStack		m_textures;
	//@}

	/**
	 * @brief Initial size for StateStack.
	 */
	static const int32					StateStack_SizeHint;


	vgd::basic::Time				m_constructorTime;			///< the time point of the constructor call
	vgm::Vec2i						m_drawingSurfaceSize;		///< the drawing surface size (window size)
	const vgd::node::Camera *		m_camera;					///< the last encountered Camera node
	vgm::Rectangle2i				m_viewport;					///< the value of \c viewport field for the last encountered Camera node with this field defined
	vgm::Vec2f						m_nearFar;					///< a vector containing respectively the distances to the near and far depth clipping planes
	/*const*/ vgd::node::GeoMorph *	m_geoMorph;					///< the last encountered GeoMorph node
	vgm::MatrixR					m_sceneGeometricalMatrix;	///< the geometrical matrix that is current when encountered the ClearFrameBuffer node
	BufferUsagePolicy				m_bufferUsagePolicy;		///< the current buffer usage policy
	EyeUsagePolicy					m_eyeUsagePolicy;			///< the current eye usage policy
	float							m_defaultMaxAnisotropy;		///< the current default maximum degree of anisotropy

	const vgd::Shp< vge::service::Service > m_paintService;	///< a reference on paint service object used by render() methods

	bool							m_trace;
};



template< typename nodeType >
void Engine::regardIfIsA( const bool enabled )
{
	const int32 indexNode( nodeType::getClassIndexStatic() );
	m_regarded[ indexNode ] = enabled;
}



template< typename nodeType >
void Engine::regardIfIsAKindOf( const bool enabled )
{
	vgd::basic::ClassRegistry< vgd::node::Node >& nodeRegistry(	vgd::node::Node::getClassRegistry() );
	
	vgd::basic::ClassRegistry< vgd::node::Node >::ClassSet::iterator i, iEnd;
	for(	boost::tie( i, iEnd ) = nodeRegistry.getIterators();
			i != iEnd;
			++i )
	{
		vgd::Shp< vgd::node::Node > node = *i;
		
		if ( node->template isAKindOf<nodeType>() )
		{
			const int32 indexNode( node->getClassIndex() );
			m_regarded[ indexNode ] = enabled;
		}
	}
}



template< typename nodeType >
void Engine::disregardIfIsA( const bool disabled )
{
	const int32 indexNode( nodeType::getClassIndexStatic() );
	m_regarded[ indexNode ] = !disabled;
}



template< typename nodeType >
void Engine::disregardIfIsAKindOf( const bool disabled )
{
	vgd::basic::ClassRegistry< vgd::node::Node >& nodeRegistry(	vgd::node::Node::getClassRegistry() );
	
	vgd::basic::ClassRegistry< vgd::node::Node >::ClassSet::iterator i, iEnd;
	for(	boost::tie( i, iEnd ) = nodeRegistry.getIterators();
			i != iEnd;
			++i )
	{
		vgd::Shp< vgd::node::Node > node = *i;
		
		if ( node->template isAKindOf<nodeType>() )
		{
			const int32 indexNode( node->getClassIndex() );
			m_regarded[ indexNode ] = !disabled;
		}
	}
}



template< typename nodeType >
bool Engine::isRegardedIfIsA() const
{
	const int32 indexNode( nodeType::getClassIndexStatic() );

	return ( m_regarded[ indexNode ] );
}



} // namespace engine

} // namespace vge

#endif //#ifndef _VGE_ENGINE_ENGINE_HPP
