// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_ACTIONS_ICONS_HPP_
#define _VGQT_ACTIONS_ICONS_HPP_

#include <vgUI/actions/Icons.hpp>

#include <QIcon>

namespace vgQt
{


namespace actions
{

/**
 * @brief Convert icon to Qt QIcon.
 *
 * @param icon	Icon name.
 *
 * @return A Qt QIcon.
 */
QIcon getIcon( vgUI::actions::Icons icon );


} // namespace actions

} // namespace vgQt

#endif // _VGQT_ACTIONS_ICONS_HPP_


