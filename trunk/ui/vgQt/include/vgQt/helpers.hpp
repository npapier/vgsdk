// VGSDK - Copyright (C) 2010, 2012, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Clément Forest

#ifndef _VGQT_HELPERS_HPP_
#define _VGQT_HELPERS_HPP_

#include <boost/shared_ptr.hpp>

#include "vgQt/vgQt.hpp"

namespace sbf {
	namespace pkg {
		struct Module;
	}
}



namespace vgQt
{


/**
 * @brief Installs the Qt-based logging system and redirects it together with standard outputs to a log file.
 */
VGQT_API void initLogging( int argc, char** argv, const boost::shared_ptr< sbf::pkg::Module > module, const int maxNumberOfLogFiles );


} // namespace vgQt



#endif // #ifndef _VGQT_HELPERS_HPP_
