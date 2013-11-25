// VGSDK - Copyright (C) 2012, 2013, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include "vgQt/Canvas.hpp"


namespace vgQt
{


Canvas::Canvas( QWidget * parent )
:	GenericCanvas< vgUI::Canvas >( parent )
{}


Canvas::Canvas( vgUI::Canvas * sharedCanvas, QWidget * parent )
:	GenericCanvas< vgUI::Canvas >( sharedCanvas, parent )
{}


} // namespace vgQt
