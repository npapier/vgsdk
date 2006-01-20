// VGSDK - Copyright (C) 2004, IRCAD.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_GRAPH_DETAIL_GRAPH_H
#define _VGD_GRAPH_DETAIL_GRAPH_H

#include "vgd/vgd.hpp"

#include <functional>

#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/properties.hpp>

#include "vgd/Shp.hpp"

namespace vgd
{
	namespace node
	{
		struct Node;
	}
}



// START "SPECIALIZATION" OF BGL GRAPH
template <class EdgeName>
struct order_by_name : public std::binary_function<EdgeName,EdgeName,bool> 
{
	bool operator()( const EdgeName& e1, const EdgeName& e2 ) const
	{
		// Order by name.
		return boost::get(boost::edge_name, e1) < boost::get(boost::edge_name, e2);
	}
};

#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

	struct ordered_set_by_nameS { };
	namespace boost 
	{
		template <class ValueType>
		struct container_gen<ordered_set_by_nameS, ValueType> 
		{
			typedef std::multiset<ValueType, order_by_name<ValueType> > type;
		};
	}

#else

	struct ordered_set_by_nameS
	{
		template <class T>
		struct bind_ { typedef std::multiset<T, order_by_name<T> > type; };
	};

	namespace boost
	{
		template <> struct container_selector<ordered_set_by_nameS>
		{
			typedef ordered_set_by_nameS type;
		};
	}

#endif

namespace boost
{
	template <>
	struct parallel_edge_traits<ordered_set_by_nameS>
	{
		typedef allow_parallel_edge_tag type;			// of course yes.
	};
}
// END "SPECIALIZATION" OF BGL GRAPH



namespace vgd
{

namespace graph
{

namespace detail
{
	
/**
 * @name Definitions of graph.
 */
//@{

/**
 * @brief Edge name for DAG.
 * 
 * Edge name are used to order edge and store enable/disable state.
 * 
 * @remarks \b Assignable and not DefaultConstructible.
 * 
 * @todo Optimize : Compact in memory(m_value and m_isEnable).
 */
struct VGD_API EdgeName
{
	/**
	 * @brief Constructor.
	 * 
	 * @param value		number used to order edge.
	 * @param isEnable	true if edge is enable, false otherwise(used during traversing).
	 */
	EdgeName( const int32 value = -1, const bool isEnable = true ) : // ???? -1 ???? FIXME
		m_value		(value),
		m_isEnable	(isEnable)
	{
	}

	/**
	 * @brief	Gets the number used to order edge.
	 */
	int32&			value( void ) 			{ return ( m_value ); }

	/**
	 * @brief	Gets the number used to order edge.
	 */	
	const int32		value( void ) const		{ return ( m_value ); }
	
	/**
	 * @brief	Gets the enable/disable state of edge.
	 */
	bool&				enable( void )			{ return ( m_isEnable ); }
	
	/**
	 * @brief	Gets the enable/disable state of edge.
	 */
	const bool		enable( void ) const	{ return ( m_isEnable ); }
	
	/**
	 * @brief	Reverses the enable/disable state of edge.
	 */
	void				negate( void )			{ m_isEnable = !m_isEnable; }

	/**
	 * @brief operator < used for ordering edge.
	 */
	const bool		operator < ( const EdgeName& edge ) const
	{
		return ( m_value < edge.value() );
	}

private:

	/**
	 * @brief Value that store a number used for ordering edge and a bool if edge is enabled/disabled.
	 */
	int32		m_value;
	bool		m_isEnable;
};



/**
 * @brief Vertex name used to store reference to node.
 */
typedef boost::property<boost::vertex_name_t,	vgd::Shp<vgd::node::Node> >	VertexProperty;

/**
 * @brief Edge name used to store edge ordering and enable/disable state.
 */
typedef boost::property<boost::edge_name_t,		EdgeName	>							EdgeProperty;

/**
 * @brief bglGraph store all vgd DAG(directed acyclic graph with edge ordered).
 */
typedef boost::adjacency_list<	
								ordered_set_by_nameS,	// edge ordered
								boost::vecS,				// vertex_descriptor must never be invalidated ???????????????????? listS FIXME
								boost::bidirectionalS,	// for beiing able to get parents
								VertexProperty,			// vertex descriptor to Node
								EdgeProperty				// ordered in edge and enable|disable edge
									>		bglGraph;

typedef boost::graph_traits<bglGraph>	bglGraphTraits;

typedef boost::property_map<bglGraph, boost::vertex_name_t>::type		VertexNamePropertyMap;
typedef boost::property_map<bglGraph, boost::edge_name_t>::type		EdgeNamePropertyMap;
//@}



} // namespace detail

} // namespace graph
	
} // namespace vgd

#endif //#ifndef _VGD_GRAPH_DETAIL_GRAPH_H
