// VGSDK - Copyright (C) 2008, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#ifndef _VGGTK_GRAPH_TREEMODELFILLVISITOR_HPP_
#define _VGGTK_GRAPH_TREEMODELFILLVISITOR_HPP_

#include <vector>

#include <gtkmm/treestore.h>

#include <vgd/node/Node.hpp>
#include <vgd/visitor/Traverse.hpp>

#include "vgGTK/graph/TreeModelColumnRecord.hpp"



namespace vgGTK
{

namespace graph
{



/**
 * @brief	Implements vgSDK graph visitor that will walk through a graph and fill
 * 			a given GTK tree model.
 */
struct TreeModelFillVisitor : public vgd::visitor::Traverse< boost::null_visitor >
{
	/**
	 * @brief	Constructor
	 *
	 * @param	treeStore		a reference to the tree store to fill
	 * @param	columnRecord	a reference to the column record associated to the given tree store
	 */
	TreeModelFillVisitor( Glib::RefPtr< Gtk::TreeStore > treeStore, const TreeModelColumnRecord & columnRecord );

	/**
	 * @name	Overrides
	 */
	//@{
	template<class Vertex, class Graph>
	void discover_vertex(Vertex u, const Graph &g)
	{
		// Creates a new tree model row for the current node.
		Gtk::TreeModel::iterator	ancestor = m_ancestors.empty() ? Gtk::TreeModel::iterator() : m_treeStore->get_iter( m_ancestors.back() );
		Gtk::TreeModel::iterator	current = ancestor ? m_treeStore->append(ancestor->children()) : m_treeStore->append();
		const Gtk::TreeModel::Row	& row	= *current;


		// Retrieves the vgd::node::Node from the current vertex.
		vgd::Shp< vgd::node::Node >	node = getNode( u );


		// Prepares the type string of the node.
		// We remove the "struct " prefix.
		// @todo Since typeid may not return same strings among plateforms, this peace of code may be not portable.
		static const Glib::ustring	prefix( "struct " );
		Glib::ustring				type( typeid(*node.get()).name() );
		Glib::ustring::size_type	found = type.find( prefix );

		if( found != Glib::ustring::npos )
		{
			type.erase( found, found+prefix.length() );
		}


		// Looks if the node is shared (has several parent nodes).
		bool					shared = false;
		vgd::node::NodeList		parents;

		node->getParents( parents );
		shared = parents.size() > 1;


		// Updates the row values using the current node.
		row[ m_columnRecord.m_nodeColumn ]		= node;
		row[ m_columnRecord.m_nameColumn ]		= Glib::ustring( node->getName() );
		row[ m_columnRecord.m_typeColumn ]		= type;
		row[ m_columnRecord.m_activeColumn ]	= m_active;
		row[ m_columnRecord.m_sharedColumn ]	= shared;

		// Stores the current row's path in the ancestors list.
		m_ancestors.push_back( m_treeStore->get_string(current) );
	}

	template<class Vertex, class Graph>
	void finish_vertex (Vertex u, const Graph &g)
	{
		m_ancestors.pop_back();
	}

	template<class Edge, class Graph>
	void examine_edge(Edge e, const Graph & g)
	{
		const vgd::graph::detail::EdgeName	edgeName = getEdgeName(e);

		m_active = edgeName.enable();

		vgd::visitor::Traverse< boost::null_visitor >::examine_edge( e, g );
	}
	//@}


private:

	typedef std::vector< Glib::ustring >	PathContainer;	///< Defines the container of tree model paths.

	Glib::RefPtr< Gtk::TreeStore >	m_treeStore;		///< Refrences the tree store to fill.
	const TreeModelColumnRecord		& m_columnRecord;	///< Refereces the tree model column record.
	PathContainer					m_ancestors;		///< Contains all ancestors' paths.
	bool							m_active;			///< Tells if the node is active or not.

};



} // namespace graph

} // namespace vgGTK



#endif /*_VGGTK_GRAPH_TREEMODELFILLVISITOR_HPP_*/
