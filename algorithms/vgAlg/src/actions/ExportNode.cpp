// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgAlg/actions/ExportNode.hpp"

#include <vgAlg/actions/SelectedNode.hpp>

#include <vgd/node/Node.hpp>
#include <vgd/Shp.hpp>

#include <vgDebug/convenience.hpp>

#include <vgOpenCOLLADA/exporter/SceneExporter.hpp>

namespace vgAlg
{

namespace actions
{



ExportNode::ExportNode()
{

}



void ExportNode::execute()
{
	vgd::Shp< vgd::node::Node > node = m_node.lock();
	vgd::Shp< vgd::node::Group > parent = m_parent.lock();
	
	bool exportSuccess = false;

	if( node->isAKindOf< vgd::node::Group >() )
	{
		vgOpenCOLLADA::exporter::SceneExporter exporter( m_stringParam, vgd::dynamic_pointer_cast< vgd::node::Group >( node ) );
		exportSuccess = exporter.doExport();
	}
	else
	{
		vgOpenCOLLADA::exporter::SceneExporter exporter( m_stringParam, parent );
		exportSuccess = exporter.doExport();
	}		
	
	if( exportSuccess )
	{
		vgDebug::get().logStatus( "Node %s exported.", node->getName().c_str() );
	}
	else
	{
		vgDebug::get().logStatus( "Node %s failed to export.", node->getName().c_str() );
	}
}



} // namespace actions

} // namespace vgAlg
