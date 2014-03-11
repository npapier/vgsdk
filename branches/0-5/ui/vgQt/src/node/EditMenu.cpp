// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include "vgQt/node/EditMenu.hpp"

#include <boost/bind.hpp>
#include <boost/signals.hpp>

#include <vgAlg/actions/IAction.hpp>
#include <vgAlg/actions/input/INodeInput.hpp>
#include <vgAlg/actions/input/IParentInput.hpp>
#include <vgAlg/actions/SelectedNode.hpp>
#include <vgUI/actions/IActionUI.hpp>
#include <vgQt/node/Action.hpp>
#include <vgQt/actions/Icons.hpp>

namespace vgQt
{

namespace node
{

EditMenu::EditMenu()
    : QMenu("&Edit")
{
    vgd::Shp< vgUI::actions::ActionsRegistry > actionsRegistry = vgUI::actions::ActionsRegistry::getActionsRegistry();

    m_actionList.append( actionsRegistry->getAction( "CutNode" ) );
    m_actionList.append( actionsRegistry->getAction( "CopyNode" ) );
    m_actionList.append( actionsRegistry->getAction( "PasteNode" ) );
    m_actionList.append( actionsRegistry->getAction( "NextNode" ) );
    m_actionList.append( actionsRegistry->getAction( "PreviousNode" ) );
    m_actionList.append( actionsRegistry->getAction( "RemoveNode" ) );
    m_actionList.append( actionsRegistry->getAction( "EncryptFile" ) );

    Q_FOREACH (vgd::Shp< vgUI::actions::IActionUI > action, m_actionList) {
        Action* actionCreated = new Action( actions::getIcon(action->getIcon()), QString::fromStdString(action->getName()), this, action->getAction());
        addAction(actionCreated);

        if(action == actionsRegistry->getAction( "PasteNode") ||
           action == actionsRegistry->getAction( "PreviousNode") ||
           action == actionsRegistry->getAction( "RemoveNode")
           )
        {
            addSeparator();
        }

        if(action->getAccelKey() != "")
        {
            QString shortcut = QString::fromStdString(action->getAccelKey());
            shortcut.replace("<control>","Ctrl+");
            actionCreated->setShortcut(QKeySequence(shortcut));
        }
    }

    //modify action when selection changed.
    vgAlg::actions::SelectedNode::getSelectedNodeObject()->signal_selection_changed.connect( boost::bind( &EditMenu::onSelectionChanged, this ) );
}

EditMenu::~EditMenu()
{
}

void EditMenu::onSelectionChanged()
{
    vgAlg::actions::input::INodeInput*		nodeInput;
    vgAlg::actions::input::IParentInput*	parentInput;

    Q_FOREACH (vgd::Shp< vgUI::actions::IActionUI > action, m_actionList)
    {
        vgAlg::actions::IAction* action2 = action->getAction();
        if( nodeInput = dynamic_cast< vgAlg::actions::input::INodeInput* >( action2 ) )
        {
            nodeInput->setNode( vgAlg::actions::SelectedNode::getSelectedNodeObject()->getSelectedNode() );
        }
        if( parentInput = dynamic_cast< vgAlg::actions::input::IParentInput* >( action2 ) )
        {
            parentInput->setParent( vgAlg::actions::SelectedNode::getSelectedNodeObject()->getParentSelectedNode() );
        }
    }
}

} // namespace node

} // namespace vgQt
