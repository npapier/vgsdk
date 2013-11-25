// VGSDK - Copyright (C) 2012, 2013, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include "vgQt/BasicViewer.hpp"

namespace vgQt
{


BasicViewer::BasicViewer( QWidget * parent )
:	GenericCanvas< vgUI::BasicViewer >( parent )
{}


BasicViewer::BasicViewer( vgUI::Canvas * sharedCanvas, QWidget * parent )
:	GenericCanvas< vgUI::BasicViewer >( parent )
{}


} // namespace vgQt
