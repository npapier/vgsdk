// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_NODE_NODE_H
#define _VGD_NODE_NODE_H

#include "vgd/vgd.hpp"

#include <vector>

#include "vgd/Shp.hpp"
#include "vgd/basic/ClassRegistry.hpp"
#include "vgd/basic/IndexableClass.hpp"
#include "vgd/basic/Object.hpp"
#include "vgd/basic/RegisterNode.hpp"
#include "vgd/field/FieldManager.hpp"
#include "vgd/field/String.hpp"
#include "vgd/graph/Graph.hpp"



/** 
 * @namespace vgd::node
 * 
 * @brief Major component of scene graph.
 *
 * A scene graph is a directed acyclic graph (DAG) that organizes and stores all of the data needed to render a 3D scene. All 
 * vertex data and state is stored in nodes in the graph.
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

struct Node;



/**
 * @brief Meta helpers.
 */
#define META_NODE_HPP( nodeType )	template< typename nodeType > friend struct vgd::node::Factory; \
 \
/** @brief Node factory.Create a node with all fields sets to defaults values */ \
static vgd::Shp< nodeType > create( const std::string nodeName = "NoName" ); \
 \
/** @brief Node factory. Create a node with all fields sets to defaults values (optionals fiels too).*/ \
static vgd::Shp< nodeType > createWhole( const std::string nodeName = "DefaultWhole" ); \
 \
IMPLEMENT_INDEXABLE_CLASS_HPP( , nodeType ); \
 \
static const vgd::basic::RegisterNode<nodeType> m_registrationInstance;



/**
 * @brief Meta helpers.
 */
#define META_NODE_CPP( nodeType ) vgd::Shp< nodeType > nodeType::create( const std::string nodeName ) \
{ \
	vgd::node::Factory< nodeType > nodeTypeFactory; \
	return ( nodeTypeFactory.create(nodeName) ); \
} \
 \
vgd::Shp< nodeType > nodeType::createWhole( const std::string nodeName ) \
{ \
	vgd::node::Factory< nodeType > nodeTypeFactory; \
	vgd::Shp< nodeType > node( nodeTypeFactory.create(nodeName) ); \
	node->setOptionalsToDefaults(); \
	return ( node ); \
} \
 \
IMPLEMENT_INDEXABLE_CLASS_CPP( , nodeType ); \
 \
const vgd::basic::RegisterNode<nodeType> nodeType::m_registrationInstance;



/**
 * @brief Node factory class.
 */
template< typename nodeType >
struct Factory
{
	vgd::Shp< nodeType > create( const std::string nodeName )
	{
		vgd::Shp< nodeType > node( new nodeType(nodeName) );
		node->setToDefaults();

		node->graph().addNode( node );
		
		return ( node );
	}
};



/**
 * @brief List of node pointers.
 */
typedef std::list< vgd::node::Node* >					PNodeList;

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
typedef std::set< vgd::node::Node* >					PNodeSet;

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
struct VGD_API Node : public vgd::basic::Object, public vgd::field::FieldManager
{
	// META_NODE_HPP( Node ); abstract class.
	
	/**
	 * @brief This abstract base class must have part of the IndexableClass interface.
	 */
	virtual int32& getClassIndex()=0;

	/**
	 * @name Repository for registered nodes.
	 */
	//@{

	/**
	 * @brief Returns the repository of registered nodes.
	 */
	static vgd::basic::ClassRegistry< vgd::node::Node >& getClassRegistry( void );

	//@}



	/**
	 * @name Destructor.
	 */
	//@{
	
	/**
	 * @brief Virtual default destructor.
	 */
	virtual ~Node( void );
	//@}



	/**
	 * @name Accessors to parents.
	 */
	//@{

	/**
	 * @brief Returns the list of parents.
	 * 
	 * @param parents		append parents at the end of this list.
	 */
	void	getParents( NodeList& parents ) const;

	/**
	 * @brief Returns the number of parents.
	 */
	int32	getNumParents( void ) const;

	/**
	 * @brief Returns only enabled or disabled parents nodes.
	 * 
	 * @param parents			append parents at the end of this list.
 	 * @param bGetEnabled	true to get all enabled parents, false to get all disabled parents.
 	 * 
 	 * @remark For more explanation see IGroup::getEnabledChildren().
	 */
	virtual void	getEnabledParents( NodeList& parents, const bool bGetEnabled = true) const;

	/**
	 * @brief Invalidate bounding box dirty flag for each parents of this node.
	 */
	void invalidateParentsBoundingBoxDirtyFlag();
	
	//@}



	/**
	 * @name Accessors to field name.
	 */

	/**
	 * @brief Typedef for the \c name field.
	 */	
	typedef vgd::field::SFString	FNameType;
		
	/**
	 * @brief Typedef for the \c name value.
	 */
	typedef std::string 				NameValueType;
	
	/**
	 * @brief Gets the name of node.
	 */
	const std::string		getName( void ) const;

	/**
	 * @brief Sets the name of node.
	 * 
	 * @param strNodeName	name of node.
	 */
	void						setName( const std::string strNodeName );

	//@}



	/**
	 * @name Accessors to field multiAttributeIndex.
	 */
	//@{

	/**
	 * @brief Gets the \c multiAttributeIndex of the multi-attribute.
	 * 
	 * @return Always zero except for real MultiAttribute classes.
	 */
	virtual int8		getMultiAttributeIndex() const;
	//@}



	/**
	 * @name Fields names enumeration.
	 */
	//@{
	
	/**
	 * @brief Returns the name of field \c name.
	 * 
	 * Each instance of a node have its own name.
	 * 
	 * @return the name of field \c name.
	 */
	static const std::string getFName( void );

	//@}
	

	
	/**
	 * @name Dirty flags enumeration.
	 */
	//@{
	
	/**
	 * @brief Returns name of dirty flag that is invalidate when a modification is done in any fields.
	 */
	static const std::string getDFNode( void );

	//@}

	

protected:
	/**
	 * @name Constructor.
	 */
	//@{

	/**
	 * @brief Default constructor.
	 * 
	 * @internal Add field and dirty flags in the constructor.
	 *
	 */
	Node( const std::string nodeName );

	/**
	 * @brief Set fields and dirty flags to default values.
	 */
	virtual void setToDefaults( void );
	
	/**
	 * @brief Set optionals fields to defaults values.
	 */
	virtual void setOptionalsToDefaults();
	//@}



	/**
	 * @name Graph accessors methods.
	 */
	//@{

	/**
	 * @brief Accessor to graph.
	 */
	static vgd::graph::Graph&	graph( void );

	/**
	 * @brief vgd::graph::Graph must have an access to vertex_descriptor.
	 * 
	 * @todo Remove this.
	 */
	friend struct vgd::graph::Graph;

	/**
	 * @brief Accessor to vertex descriptor of this node.
	 */
	vgd::graph::detail::bglGraphTraits::vertex_descriptor&			vertexDescriptor( void );

	/**
	 * @brief Accessor to vertex descriptor of this node.
	 */
	const vgd::graph::detail::bglGraphTraits::vertex_descriptor&	vertexDescriptor( void ) const;
	//@}



private:
	
	/**
	 * @name Graph typedef.
	 */
	//@{
	
	/**
	 * @brief boost vertex descriptor for this node.
	 */
	vgd::graph::detail::bglGraphTraits::vertex_descriptor	m_vertexDescriptor;	

	//@}
};



} // namespace node

} // namespace vgd

#endif //#ifndef _VGD_NODE_ANODE_H
