// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGGTK_HELPERS_HPP_
#define _VGGTK_HELPERS_HPP_

#include <sbf/Module.hpp>
#include "vgGTK/vgGTK.hpp"



namespace vgGTK
{


/**
 * @brief Installs the GTK-based logging system and redirects it together with standard outputs to a log file.
 */
VGGTK_API void initLogging( int argc, char** argv, const sbf::Module& module, const int maxNumberOfLogFiles );


} // namespace vgGTK



#endif // #ifndef _VGGTK_HELPERS_HPP_
