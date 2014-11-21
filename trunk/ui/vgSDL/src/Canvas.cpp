// VGSDK - Copyright (C) 2012, 2013, 2014, Guillaume Brocker, Bryan Schuller, Philippe Sengchanpheng
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller
// Author Philippe Sengchanpheng

#include "vgSDL/Canvas.hpp"


namespace vgSDL
{


Canvas::Canvas()
:	GenericCanvas< vgUI::Canvas >()
{}


Canvas::Canvas(vgUI::Canvas * sharedCanvas)
:	GenericCanvas< vgUI::Canvas >( sharedCanvas )
{}


} // namespace vgSDL
