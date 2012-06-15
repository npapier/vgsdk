// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include "vgQt/node/Action.hpp"

#include <QAction>

namespace vgQt
{

namespace node
{

Action::Action( QIcon icon, QString name, QObject* parent, vgAlg::actions::IAction* action )
    : QAction(icon, name, parent)
{
    connect(this, SIGNAL(triggered()), this, SLOT(onTriggered()));
    m_action = action;
    m_className = "";
}

Action::Action( QString name, QObject* parent, vgAlg::actions::IAction* action )
    : QAction(name, parent)
{
    connect(this, SIGNAL(triggered()), this, SLOT(onTriggered()));
    m_action = action;
    m_className = "";
}

Action::Action( std::string name, std::string className, QObject* parent )
    : QAction(QString::fromStdString(name), parent)
{
    connect(this, SIGNAL(triggered()), this, SLOT(onTriggered()));
    m_action = 0;
    m_className = className;
}

void Action::onTriggered()
{
    if(m_action)
    {
        m_action->execute();
    }
    Q_EMIT triggered(m_className);
}

} // namespace node

} // namespace vgQt
