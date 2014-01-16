// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include "vgQt/actions/alg/ExportNode.hpp"

#if _MSC_VER <= 1600
#include <vgOpenCOLLADA/actions/ExportNode.hpp>
#endif

#include <vgAlg/actions/SelectedNode.hpp>

#include <vgQt/node/ColladaSettingsDialog.hpp>

#include <QPushButton>
#include <QFileDialog>

namespace vgQt
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
#if _MSC_VER <= 1600
    vgd::Shp< vgd::node::Node > node = vgAlg::actions::SelectedNode::getSelectedNodeObject()->getSelectedNode();
    vgd::Shp< vgd::node::Group > parent = vgAlg::actions::SelectedNode::getSelectedNodeObject()->getParentSelectedNode();

    node::ColladaSettingsDialog dialog;
	vgOpenCOLLADA::Settings  exportSettings;
    if( dialog.exec() == QDialog::Accepted)
	{
        exportSettings = dialog.getSettings();
	}
	else
	{
		return;
	}

    QString fileName = QFileDialog::getSaveFileName(0, QObject::tr("Save As"),
                                "",
                                QObject::tr("COLLADA file (*.DAE)"));

    if(fileName != "")
    {
        vgOpenCOLLADA::actions::ExportNode exportNode;
        exportNode.setNode( node );
        exportNode.setParent( parent );
        exportSettings.setFilename( fileName.toStdString() );
        exportNode.setExportSettings( exportSettings );

        if(node && parent)
        {
            exportNode.execute();
        }
    }
#endif
}


} // namespace alg

} // namespace actions

} // namespace vgQt
