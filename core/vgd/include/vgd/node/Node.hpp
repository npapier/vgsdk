// VGSDK - Copyright (C) 2004-2006, 2009, 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_NODE_HPP
#define _VGD_NODE_NODE_HPP

///@todo pragma warning for signals.hpp
#ifdef WIN32
	#pragma warning (push)
	#pragma warning(disable:4251 4275 4511 4512)
#endif

#include <boost/signals.hpp>

#ifdef WIN32
	#pragma warning (pop)
#endif

#include <vector>

#include "vgd/EnableShpFromThis.hpp"
#include "vgd/basic/IndexableClass.hpp"
#include "vgd/basic/Object.hpp"
#include "vgd/basic/RegisterNode.hpp"
#include "vgd/field/FieldManager.hpp"
#include "vgd/field/String.hpp"
#include "vgd/graph/detail/Graph.hpp"

namespace vgd
{
	template<class T> struct Shp;

	namespace basic
	{
		template< typename baseClassType > struct ClassRegistry;
	}

	namespace graph
	{
		struct Graph;
	}

	namespace node
	{
		struct Group;
		struct Node;
	}
}



/** 
 * @namespace vgd::node
 * 
 * @brief Major component of scene graph.
 *
 * A scene graph is a directed acyclic graph (DAG) that organizes and stores all of the data needed to render a 3D scene. 
 * All vertex data and state is stored in nodes in the graph.
 * 
 * Nodes are organize in a scene graph.
 * 
 * Node types can be divided into three parts :
 * \li Group nodes (like Group, Separator, Switch, MultiSwitch...).
 * \li Shape nodes (like VertexShape, TriSet...).
 * \li Attribute nodes (like Transformation, Light, FrameBuffer...).
 * \li Kit nodes (like Dragger, Layers...).
 * 
 * \sa g_nodes for more details.
 */
namespace vgd
{

namespace node
{



/**
 * @brief Meta helpers.
 */
#define META_NODE_HPP( nodeType )	/** \@brief Node factory\n
* Create a node with all fields sets to defaults values */								\
static vgd::Shp< nodeType > create( const std::string nodeName = "NoName" );			\
																						\
/** \@brief Node factory\n
 *  Create a node with all fields sets to defaults values (optionals fields too).*/		\
static vgd::Shp< nodeType > createWhole( const std::string nodeName = "DefaultWhole" );	\
																						\
IMPLEMENT_INDEXABLE_CLASS_HPP( , nodeType );											\
																						\
static const vgd::basic::RegisterNode<nodeType> m_registrationInstance;



/**
 * @brief List of node pointers.
 */
typedef std::list< vgd::node::Node* >				PNodeList;

/**
 * @brief List of nodes (useful for children list).
 */
typedef std::list< vgd::Shp<vgd::node::Node> >		NodeList;

/**
 * @brief Vector of node pointers.
 */
typedef std::vector< vgd::node::Node* >				PNodeVector;

/**
 * @brief Vector of nodes (useful for children list).
 */
typedef std::vector< vgd::Shp<vgd::node::Node> >	NodeVector;

/**
 * @brief Set of node pointers.
 */
typedef std::set< vgd::node::Node* >				PNodeSet;

/**
 * @brief Set of nodes.
 */
typedef std::set< vgd::Shp<vgd::node::Node> >		NodeSet;



/**
 * @brief Abstract base class for node in the scene graph.
 * 
 * New fields added by this node :
 *
 * - SFString \c name = "NoName"\n
 * 	Name of a node.
 *
 * This is the abstract base class from which all scene graph node classes are derived.
 * 
 * @remarks All node could be shared multiple times in the same DAG and even in other DAG.
 * 
 * @remarks A node contains some fields managed by a vgd::field::FieldManager.
 * @remarks Constructor is in protected section for limiting the possibility to instanciate a node directly.
 * 
 * @ingroup g_abstractNodes
 */
struct VGD_API Node : public vgd::basic::Object, public vgd::field::FieldManager, public vgd::EnableShpFromThis<Node>
{
	// META_NODE_HPP( Node ); abstract class.
	
	/**
	 * @brief This abstract base class must have part of the IndexableClass interface.
	 */
	virtual int32& getClassIndex()=0;

	/**
	 * @name Repository for registered nodes
	 */
	//@{

	/**
	 * @brief Returns the repository of registered nodes.
	 */
	static vgd::basic::ClassRegistry< vgd::node::Node >& getClassRegistry( void );

	//@}



	/**
	 * @name Destructor
	 */
	//@{

	/**
	 * @brief Virtual default destructor
	 */
	virtual ~Node();
	//@}



	/**
	 * @name Accessors to parents
	 *
	 * @todo adds vgd::Shp< vgd::node::Group > getParent()
	 * @todo adds getParents( GroupList ), same getEnabledParents()
	 */
	//@{

	/**
	 * @brief Returns the first parent
	 *
	 * @return a shared pointer on the first parent, otherwise an empty shared pointer
	 */
	vgd::Shp< vgd::node::Group > getParent();

	/**
	 * @brief Returns the list of parents.
	 * 
	 * @param parents		append parents at the end of this list.
	 */
	void	getParents( NodeList& parents ) const;

	/**
	 * @brief Returns the number of parents.
	 */
	int32	getNumParents() const;

	/**
	 * @brief Returns only enabled or disabled parents nodes.
	 * 
	 * @param parents		append parents at the end of this list.
 	 * @param bGetEnabled	true to get all enabled parents, false to get all disabled parents.
 	 * 
 	 * @remark For more explanation see IGroup::getEnabledChildren().
	 * @todo why this method is virtual ?
	 */
	virtual void	getEnabledParents( NodeList& parents, const bool bGetEnabled = true ) const;

	/**
	 * @brief Returns the number of parents.
	 *
 	 * @param bGetEnabled	true to only take care of enabled parents, false to only take care of disabled parents.
	 */
	const int32 getNumEnabledParents( const bool bGetEnabled = true ) const;

	/**
	 * @brief Invalidate bounding box dirty flag for each parents of this node.
	 */
	void invalidateParentsBoundingBoxDirtyFlag();

	//@}



	/**
	 * @name Accessors to field name
	 */

	/**
	 * @brief Typedef for the \c name field.
	 */	
	typedef vgd::field::SFString	FNameType;

	/**
	 * @brief Typedef for the \c name value.
	 */
	typedef std::string 			NameValueType;

	/**
	 * @brief Gets the name of node.
	 */
	const std::string	getName( void ) const;

	/**
	 * @brief Sets the name of node.
	 * 
	 * @param strNodeName	name of node.
	 */
	void				setName( const std::string strNodeName );

	//@}



	/**
	 * @name Accessors to field multiAttributeIndex
	 */
	//@{

	/**
	 * @brief Gets the \c multiAttributeIndex of the multi-attribute.
	 * 
	 * @return Always zero except for real MultiAttribute classes.
	 */
	virtual int8		getMultiAttributeIndex() const;

	/**
	 * @brief Sets the \c multiAttributeIndex of the multi-attribute.
	 *
	 * @param index		zero-based index of the multi-attribute
	 */
	virtual void 		setMultiAttributeIndex( const int8 index );
	//@}



	/**
	 * @name Fields names enumeration
	 */
	//@{

	/**
	 * @brief Returns the name of field \c name.
	 * 
	 * Each instance of a node have its own name.
	 * 
	 * @return the name of field \c name.
	 */
	static const std::string getFName();

	//@}



	/**
	 * @name Dirty flags enumeration
	 */
	//@{
	
	/**
	 * @brief Returns name of dirty flag that is invalidate when a modification is done in any fields.
	 */
	static const std::string getDFNode();

	//@}



	/**
	 * @name Signals
	 */
	//@{

	/**
	 * @brief Alias on signal associated to the destructor of node (i.e. ~Node).
	 */
	typedef boost::signal< void (vgd::node::Node*) >	DestructorSignalType;

	/**
	 * @brief Alias on signal connection.
	 */
	typedef boost::signals::connection					ConnectionType;

	/**
	 * @brief Connects the signal (SignalDestructorType) to the incoming slot.
	 * 
	 * @param slot	incoming slot
	 *
	 * @return the connection object associated to the signal
	 */
	static ConnectionType connect( DestructorSignalType::slot_function_type slot );

	//@}



protected:
	/**
	 * @name Constructor
	 */
	//@{

	/**
	 * @brief Default constructor.
	 * 
	 * @internal Add field and dirty flags in the constructor.
	 *
	 */
	Node( const std::string nodeName );

public:
	/**
	 * @brief Set fields and dirty flags to default values.
	 */
	virtual void setToDefaults( void );

	/**
	 * @brief Set optionals fields to defaults values.
	 */
	virtual void setOptionalsToDefaults();
protected:
	//@}



	/**
	 * @name Graph accessors methods
	 */
	//@{

	/**
	 * @brief Accessor to graph.
	 */
	static vgd::graph::Graph&	graph();

	/**
	 * @brief vgd::graph::Graph must have an access to vertex_descriptor.
	 * 
	 * @todo Remove this.
	 */
	friend struct vgd::graph::Graph;

	/**
	 * @brief Alias on vertex descriptor.
	 */
	typedef vgd::graph::detail::bglGraphTraits::vertex_descriptor		vertex_descriptor;

	/**
	 * @brief Accessor to vertex descriptor of this node.
	 */
	vertex_descriptor&			vertexDescriptor();

	/**
	 * @brief Accessor to vertex descriptor of this node.
	 */
	const vertex_descriptor&	vertexDescriptor() const;
	//@}


private:

	/**
	 * @name Graph
	 */
	//@{
	
	/**
	 * @brief boost vertex descriptor for this node.
	 */
	vertex_descriptor	m_vertexDescriptor;

	//@}



	/**
	 * @name Signals
	 */
	//@{

	/**
	 * @brief Signal for destructor
	 */
	static DestructorSignalType& destructorSignal();

protected:
	/**
	 * @brief Copy constructor
	 */
	Node( const vgd::node::Node& );
	
	/**
	 * @brief Assignment operator
	 */
	Node& operator =( const vgd::node::Node& );
	//@}

private:
#ifdef _DEBUG
	std::string m_nodeName; ///< this attribute contains the name of node like field 'name'. But this one could be seen in debugger easily.
#endif
};



typedef vgd::Shp< vgd::node::Node > NodeShp; ///< type definition for shared pointer on a Node



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_NODE_HPP
