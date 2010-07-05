// VGSDK - Copyright (C) 2010, Nicolas Papier and Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "vgGTK/actions/alg/ExportNode.hpp"

#include <gtkmm/filechooserdialog.h>
#include <gtkmm/stock.h>

#include <vgAlg/actions/ExportNode.hpp>

namespace vgGTK
{

namespace actions
{

namespace alg
{


ExportNode::ExportNode()
{

}



ExportNode::~ExportNode()
{

}


void ExportNode::execute()
{
	vgd::Shp< vgd::node::Node > node = m_node.lock();
	vgd::Shp< vgd::node::Group > parent = m_parent.lock();

	Gtk::FileChooserDialog	chooser( "Save As", Gtk::FILE_CHOOSER_ACTION_SAVE );
	Gtk::FileFilter			dotFilter;

	dotFilter.set_name( "COLLADA file (*.DAE)" );
	dotFilter.add_pattern( "*.DAE" );

	chooser.add_filter( dotFilter );
	chooser.add_button( Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL );
	chooser.add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK );
	chooser.set_do_overwrite_confirmation( true );

	const int result = chooser.run();
	if( result == Gtk::RESPONSE_OK )
	{
		vgAlg::actions::ExportNode exportNode;
		exportNode.setNode( node );
		exportNode.setParent( parent );
		exportNode.setStringParam( chooser.get_filename() );
		exportNode.execute();
	}	
}



} // namespace alg

} // namespace actions

} // namespace vgGTK
