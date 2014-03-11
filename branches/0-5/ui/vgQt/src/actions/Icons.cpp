// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include "vgQt/actions/Icons.hpp"


namespace vgQt
{

namespace actions
{


QIcon getIcon( vgUI::actions::Icons icon )
{
    switch( icon )
    {
        case vgUI::actions::COPY :
            return QIcon(":/images/edit-copy.png");
        case vgUI::actions::CUT:
            return QIcon(":/images/edit-cut.png");
        case vgUI::actions::PASTE:
            return QIcon(":/images/edit-paste.png");
        case vgUI::actions::REMOVE:
            return QIcon(":/images/edit-delete.png");
        case vgUI::actions::NEXT:
            return QIcon(":/images/go-next-ltr.png");
        case vgUI::actions::PREVIOUS:
            return QIcon(":/images/go-previous-ltr.png");
        case vgUI::actions::DEFAULT:
            return QIcon(":/images/gtk-ok.png");
        default:
            return QIcon(":/images/gtk-ok.png");
    }
}



} // namespace actions

} // namespace vgQt

