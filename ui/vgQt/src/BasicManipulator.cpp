// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include "vgQt/BasicManipulator.hpp"


namespace vgQt
{


BasicManipulator::BasicManipulator( QWidget * parent, const uint devices )
:    TBasicManipulator< vgUI::BasicManipulator >(parent, devices)
{}


} // namespace vgQt
