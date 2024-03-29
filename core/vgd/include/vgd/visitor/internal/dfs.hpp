// VGSDK - Copyright (C) 2004, 2007, 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

// This file is a modified version of depth_first_search.hpp (founded in boost 1.31).
// Comment:	depth_first_search.hpp from boost 1.32 is almost the same.
// ADD 1:	could stop the traverse to the first DAG(see visitForest()).
// ADD 2:	could traverse only edges with EdgeName.enable() sets to true(see useEdgeName()).
// ADD 3:	call depth_first_search() for forward_or_cross_edge.

#ifndef _VGD_VISITOR_INTERNAL_DFS_HPP
#define _VGD_VISITOR_INTERNAL_DFS_HPP

//
//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// This file is part of the Boost Graph Library
//
// You should have received a copy of the License Agreement for the
// Boost Graph Library along with the software; see the file LICENSE.
// If not, contact Office of Research, University of Notre Dame, Notre
// Dame, IN 46556.
//
// Permission to modify the code and to distribute modified code is
// granted, provided the text of this NOTICE is retained, a notice that
// the code was modified is included with the above COPYRIGHT NOTICE and
// with the COPYRIGHT NOTICE in the LICENSE file, and that the LICENSE
// file is distributed with the modified code.
//
// LICENSOR MAKES NO REPRESENTATIONS OR WARRANTIES, EXPRESS OR IMPLIED.
// By way of example, but not limitation, Licensor MAKES NO
// REPRESENTATIONS OR WARRANTIES OF MERCHANTABILITY OR FITNESS FOR ANY
// PARTICULAR PURPOSE OR THAT THE USE OF THE LICENSED SOFTWARE COMPONENTS
// OR DOCUMENTATION WILL NOT INFRINGE ANY PATENTS, COPYRIGHTS, TRADEMARKS
// OR OTHER RIGHTS.
//=======================================================================
//
//#ifndef BOOST_GRAPH_RECURSIVE_DFS_HPP				// modification for vgsdk
//#define BOOST_GRAPH_RECURSIVE_DFS_HPP				// modification for vgsdk

#include <stack>
#include <boost/config.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graph_concepts.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/graph/named_function_params.hpp>
#include <vector>



namespace boost {									// modification for vgsdk

  template <class Visitor, class Graph>
  class vgsdkDFSVisitorConcept {
  
  vgsdkDFSVisitorConcept() {} 						// modification for vgsdk
//  vgsdkDFSVisitorConcept( DFS) {} 							// modification for vgsdk   
												// to remove warnings (level 4) C4510 and C4610 under VS7.x.
  public:
    void constraints() {
      //function_requires< CopyConstructibleConcept<Visitor> >();     modification for vgsdk    FIXME
      vis.initialize_vertex(u, g);
      vis.start_vertex(u, g);
      vis.discover_vertex(u, g);
      vis.examine_edge(e, g);
      vis.tree_edge(e, g);
      vis.back_edge(e, g);
      vis.forward_or_cross_edge(e, g);
      vis.finish_vertex(u, g);
    }
  private:
    Visitor vis;
    Graph g;
    typename boost::graph_traits<Graph>::vertex_descriptor u;
    typename boost::graph_traits<Graph>::edge_descriptor e;
  };

  namespace detail {

    template <class IncidenceGraph, class DFSVisitor, class ColorMap>
    void vgsdk_depth_first_visit_impl
      (const IncidenceGraph& g,
       typename boost::graph_traits<IncidenceGraph>::vertex_descriptor u, 
       DFSVisitor& vis,  // pass-by-reference here, important!
       ColorMap color)
    {
      function_requires<IncidenceGraphConcept<IncidenceGraph> >();
      function_requires<vgsdkDFSVisitorConcept<DFSVisitor, IncidenceGraph> >();
      typedef typename graph_traits<IncidenceGraph>::vertex_descriptor Vertex;
      function_requires< ReadWritePropertyMapConcept<ColorMap, Vertex> >();
      typedef typename property_traits<ColorMap>::value_type ColorValue;
      function_requires< ColorValueConcept<ColorValue> >();
      typedef color_traits<ColorValue> Color;
      typename graph_traits<IncidenceGraph>::out_edge_iterator ei, ei_end;

      put(color, u, Color::gray());          vis.discover_vertex(u, g);
      for (boost::tie(ei, ei_end) = out_edges(u, g); ei != ei_end; ++ei) {
        Vertex v = target(*ei, g);           vis.examine_edge(*ei, g);

        if ( vis.visitVertex() ) {											// ADD 2 : vgsdk modification

	        ColorValue v_color = get(color, v);
	        if (v_color == Color::white()) {     vis.tree_edge(*ei, g);
	          vgsdk_depth_first_visit_impl(g, v, vis, color);
	        } else if (v_color == Color::gray()) vis.back_edge(*ei, g);
	        else
	        {
	        	vgsdk_depth_first_visit_impl(g, v, vis, color);					// ADD 3 : vgsdk modification
	        	
	        	vis.forward_or_cross_edge(*ei, g);
	        }
      	}

      }																		// vgsdk modification
      put(color, u, Color::black());         vis.finish_vertex(u, g);
    }
  } // namespace detail

} // namespace boost



namespace vgd
{

namespace visitor
{

namespace internal
{

  template <class VertexListGraph, class DFSVisitor, class ColorMap, 
            class Vertex>
  void
  depth_first_search(const VertexListGraph& g, DFSVisitor& vis, ColorMap color,		// vgsdk modification(add ref to visitors)
                     Vertex start_vertex)
  {
    boost::function_requires<boost::vgsdkDFSVisitorConcept<DFSVisitor, VertexListGraph> >();
    typedef typename boost::property_traits<ColorMap>::value_type ColorValue;
    typedef boost::color_traits<ColorValue> Color;

    typename boost::graph_traits<VertexListGraph>::vertex_iterator ui, ui_end;
    for (boost::tie(ui, ui_end) = vertices(g); ui != ui_end; ++ui) {
      put(color, *ui, Color::white());       vis.initialize_vertex(*ui, g);
    }

    /*if (start_vertex != *vertices(g).first){*/ vis.start_vertex(start_vertex, g);					// vgsdk modification
      boost::detail::vgsdk_depth_first_visit_impl(g, start_vertex, vis, color);
    /*}*/																				// vgsdk modification

	if ( vis.visitForest() ) 														// vgsdk: ADD 1
	{
	    for (boost::tie(ui, ui_end) = vertices(g); ui != ui_end; ++ui) {
	      ColorValue u_color = get(color, *ui);
	      if (u_color == Color::white()) {       vis.start_vertex(*ui, g);
	        boost::detail::vgsdk_depth_first_visit_impl(g, *ui, vis, color);
	      }
	    }
	}																			// vgsdk: ADD 1
  }

/*  template <class VertexListGraph, class DFSVisitor, class ColorMap>			// vgsdk modification
  void
  depth_first_search(const VertexListGraph& g, DFSVisitor vis, ColorMap color)
  {
    depth_first_search(g, vis, color, *vertices(g).first);
  }

  namespace detail {
    template <class ColorMap>
    struct dfs_dispatch {

      template <class VertexListGraph, class Vertex, class DFSVisitor, 
                class P, class T, class R>
      static void
      apply(const VertexListGraph& g, DFSVisitor vis, Vertex start_vertex,
            const bgl_named_params<P, T, R>&,
            ColorMap color)
      {
        depth_first_search(g, vis, color, start_vertex);
      }
    };

    template <>
    struct dfs_dispatch<boost::detail::error_property_not_found> {					// modification for vgsdk
      template <class VertexListGraph, class Vertex, class DFSVisitor,
                class P, class T, class R>
      static void
      apply(const VertexListGraph& g, DFSVisitor vis, Vertex start_vertex,
            const bgl_named_params<P, T, R>& params,
            boost::detail::error_property_not_found)								// modification for vgsdk
      {
        std::vector<default_color_type> color_vec(num_vertices(g));
        default_color_type c = white_color; // avoid warning about un-init
        depth_first_search
          (g, vis, make_iterator_property_map
           (color_vec.begin(),
            choose_const_pmap(get_param(params, vertex_index),
                              g, vertex_index), c), 
           start_vertex);
      }
    };

  } // namespace detail*/
  

  template <class Visitors = boost::null_visitor>
  class dfs_visitor {
  public:
    dfs_visitor() { }
    dfs_visitor(Visitors vis) : m_vis(vis) { }

    template <class Vertex, class Graph>
    void initialize_vertex(Vertex u, const Graph& g) {
      invoke_visitors(m_vis, u, g, boost::on_initialize_vertex());      
    }
    template <class Vertex, class Graph>
    void start_vertex(Vertex u, const Graph& g) {
      invoke_visitors(m_vis, u, g, boost::on_start_vertex());      
    }
    template <class Vertex, class Graph>
    void discover_vertex(Vertex u, const Graph& g) {
      invoke_visitors(m_vis, u, g, boost::on_discover_vertex());      
    }
    template <class Edge, class Graph>
    void examine_edge(Edge u, const Graph& g) {
      invoke_visitors(m_vis, u, g, boost::on_examine_edge());
    }
    template <class Edge, class Graph>
    void tree_edge(Edge u, const Graph& g) {
      invoke_visitors(m_vis, u, g, boost::on_tree_edge());      
    }
    template <class Edge, class Graph>
    void back_edge(Edge u, const Graph& g) {
      invoke_visitors(m_vis, u, g, boost::on_back_edge());
    }
    template <class Edge, class Graph>
    void forward_or_cross_edge(Edge u, const Graph& g) {
      invoke_visitors(m_vis, u, g, boost::on_forward_or_cross_edge());
    }
    template <class Vertex, class Graph>
    void finish_vertex(Vertex u, const Graph& g) {
      invoke_visitors(m_vis, u, g, boost::on_finish_vertex());      
    }
  protected:
    Visitors m_vis;
  };
  template <class Visitors>
  dfs_visitor<Visitors>
  make_dfs_visitor(Visitors vis) {
    return dfs_visitor<Visitors>(vis);
  }
  typedef dfs_visitor<> default_dfs_visitor;


  /*// Named Parameter Variant
  template <class VertexListGraph, class P, class T, class R>
  void
  depth_first_search(const VertexListGraph& g, 
                     const bgl_named_params<P, T, R>& params)
  {
    typedef typename property_value< bgl_named_params<P, T, R>, 
      vertex_color_t>::type C;
    detail::dfs_dispatch<C>::apply
      (g,
       choose_param(get_param(params, graph_visitor),
                    make_dfs_visitor(null_visitor())),
       choose_param(get_param(params, root_vertex_t()),
                    *vertices(g).first),
       params,
       get_param(params, vertex_color)
       );
  }*/
  

  /*template <class IncidenceGraph, class DFSVisitor, class ColorMap>
  void depth_first_visit
    (const IncidenceGraph& g,
     typename boost::graph_traits<IncidenceGraph>::vertex_descriptor u, 
     DFSVisitor vis, ColorMap color)
  {
    detail::vgsdk_depth_first_visit_impl(g, u, vis, color);
  }*/


} // namespace internal

} // namespace visitor

} // namespace vgd				// end: modification for vgsdk

#endif //#ifndef _VGD_VISITOR_INTERNAL_DFS_HPP
