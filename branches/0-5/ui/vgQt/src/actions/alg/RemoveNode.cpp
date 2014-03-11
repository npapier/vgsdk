// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include "vgQt/actions/alg/RemoveNode.hpp"

#include <vgAlg/actions/RemoveNode.hpp>
#include <vgAlg/actions/SelectedNode.hpp>

#include <QMessageBox>

namespace vgQt
{

namespace actions
{

namespace alg
{


RemoveNode::RemoveNode()
{

}



RemoveNode::~RemoveNode()
{

}



void RemoveNode::execute()
{
    vgd::Shp< vgd::node::Node > node = vgAlg::actions::SelectedNode::getSelectedNodeObject()->getSelectedNode();
    vgd::Shp< vgd::node::Group > parent = vgAlg::actions::SelectedNode::getSelectedNodeObject()->getParentSelectedNode();

    if( node && parent )
    {
        QString nodeName = QString::fromStdString(node->getName());

        QMessageBox messageDialog;
        messageDialog.setText("Do you really want to remove the node" + nodeName + " ?");
        messageDialog.setInformativeText("This can break then rendering or may even cause the program to crash.");
        messageDialog.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
        messageDialog.setDefaultButton(QMessageBox::Cancel);
        messageDialog.setIcon(QMessageBox::Warning);
        if(messageDialog.exec() == QMessageBox::Ok)
        {
            ::vgAlg::actions::RemoveNode removeNode;

            removeNode.setNode( node );
            removeNode.setParent( parent );
            removeNode.execute();
        }
    }
}


} // namespace alg

} // namespace actions

} // namespace vgGTK
