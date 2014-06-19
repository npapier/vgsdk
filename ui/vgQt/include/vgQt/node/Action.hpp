// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_NODE_ACTION_HPP_
#define _VGQT_NODE_ACTION_HPP_

#include <vgUI/actions/ActionsRegistry.hpp>

#include <QAction>

namespace vgQt
{

namespace node
{

class Action : public QAction
{
    Q_OBJECT
public :
    Action( QIcon icon, QString name, QObject* parent, vgAlg::actions::IAction* action );
    Action( QString name, QObject* parent, vgAlg::actions::IAction* action );
    Action( std::string name, std::string className, QObject* parent );

Q_SIGNALS:
    void triggered(std::string);

public Q_SLOTS:
    void onTriggered();

private:
    vgAlg::actions::IAction* m_action;
    std::string m_className;
};

} // namespace node

} // namespace vgQt

#endif // _VGQT_NODE_ACTION_HPP_
