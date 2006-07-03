// VGSDK - Copyright (C) 2004, 2006 Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGD_GRAPH_GRAPHVIZ_HPP
#define _VGD_GRAPH_GRAPHVIZ_HPP

#include <iostream>

#include "vgd/vgd.hpp"



namespace vgd
{
	
namespace graph
{



struct VGD_API Graphviz
{
	/**
	 * @name Definitions for graphwiz.
	 */
	//@{
	
	template <class Name>
	class my_vertex_label_writer 
	{
	public:
		my_vertex_label_writer(Name name) : m_name(name) 
		{}
	
		template <class VertexOrEdge>
		void operator()(std::ostream& out, const VertexOrEdge& v) const 
		{
			vgd::Shp< vgd::node::Node > node( m_name[v] );

			out << "[label=\"" << typeid(*node.get()).name() << ", " << node->getName() << "\"]";
		}
	private:
		Name m_name;
	};
	
	template <class Name>
	inline my_vertex_label_writer<Name>
	my_make_vertex_label_writer(Name n) 
	{
		return my_vertex_label_writer<Name>(n);
	}
	
	
	
	template <class Name>
	class my_edge_label_writer 
	{
	public:
		my_edge_label_writer(Name name) : m_name(name) 
		{}
	
		template <class VertexOrEdge>
		void operator()(std::ostream& out, const VertexOrEdge& v) const 
		{
			out << "[label=\"" << m_name[v].value() << ", ";
			if ( m_name[v].enable() )
			{
				out << "e";
			}
			else
			{
				out << "d";
			}
			out << "\"]";
		}
	private:
		Name m_name;
	};
	
	template <class Name>
	inline my_edge_label_writer<Name>
	my_make_edge_label_writer(Name n) 
	{
		return my_edge_label_writer<Name>(n);
	}
	//@}
};



} // namespace graph

} // namespace vgd

#endif //#ifndef _VGD_GRAPH_GRAPHVIZ_HPP
