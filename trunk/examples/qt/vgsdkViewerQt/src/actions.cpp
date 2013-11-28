// VGSDK - Copyright (C) 2013, Guillaume Brocker
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker

#include "vgsdkViewerQt/actions.hpp"


namespace vgsdkViewerQt
{


QAction * newNewWindowAction( QObject * parent )
{
	QAction	* action = new QAction( QIcon(":/images/window-new.png"), "New window", parent );
	return action;
}


} // namespace vgsdkViewerQt
