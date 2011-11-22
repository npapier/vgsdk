// VGSDK - Copyright (C) 2010, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson


#include "vgOpenCOLLADA/actions/ExportNode.hpp"



#include <vgOpenCOLLADA/exporter/SceneExporter.hpp>

namespace vgOpenCOLLADA
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
		vgOpenCOLLADA::exporter::SceneExporter exporter( m_exportSettings, vgd::dynamic_pointer_cast< vgd::node::Group >( node ) );
		exportSuccess = exporter.doExport();
	}
	else
	{
		vgOpenCOLLADA::exporter::SceneExporter exporter( m_exportSettings, parent );
		exportSuccess = exporter.doExport();
	}		
	
	if( exportSuccess )
	{
		vgLogStatus( "Node %s exported.", node->getName().c_str() );
	}
	else
	{
		vgLogStatus( "Node %s failed to export.", node->getName().c_str() );
	}
}



void ExportNode::setExportSettings( vgOpenCOLLADA::Settings exportSettings )
{
	m_exportSettings = exportSettings;
}



} // namespace actions

} // namespace vgOpenCOLLADA
