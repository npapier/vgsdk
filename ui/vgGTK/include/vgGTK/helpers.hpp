// VGSDK - Copyright (C) 2010, 2012, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Guillaume Brocker

#ifndef _VGGTK_HELPERS_HPP_
#define _VGGTK_HELPERS_HPP_

#include <boost/shared_ptr.hpp>

#include "vgGTK/vgGTK.hpp"

namespace sbf {
	namespace pkg {
		struct Module;
	}
}



namespace vgGTK
{


/**
 * @brief Installs the GTK-based logging system and redirects it together with standard outputs to a log file.
 */
VGGTK_API void initLogging( int argc, char** argv, const boost::shared_ptr< sbf::pkg::Module > module, const int maxNumberOfLogFiles );


} // namespace vgGTK



#endif // #ifndef _VGGTK_HELPERS_HPP_
