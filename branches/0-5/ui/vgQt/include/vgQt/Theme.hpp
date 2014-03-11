// VGSDK - Copyright (C) 2012, Alexandre Di Pino.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Alexandre Di Pino


#include "vgQt/vgQt.hpp"

#ifndef _VGQT_THEME_HPP_
#define _VGQT_THEME_HPP_

#include <map>
#include <string>

namespace vgQt
{

const std::map<int, int>&	getThemeForeground(const std::string& name);

const std::map<int, int>&	getThemeBackground(const std::string& name);

}

#endif
