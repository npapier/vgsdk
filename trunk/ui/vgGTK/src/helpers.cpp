// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "vgGTK/helpers.hpp"

#include <gtkmm.h>
#include <iostream>
#include <sbf/log/GlobalLogger.hpp>
#include <vgDebug/helpers.hpp>
#include <vgGTK/Logging.hpp>


namespace vgGTK
{



namespace
{
	void logHandler( const gchar *log_domain, GLogLevelFlags log_level, const gchar *message, gpointer user_data )
	{
		std::cout << message << std::endl;
	}
}



void initLogging( int argc, char** argv, const sbf::Module& module, const int maxNumberOfLogFiles )
{
	// Installs the GTK-based logging system.
	sbf::log::GlobalLogger::set< vgGTK::Logging >();
	//vgDebug::set< vgGTK::Logging >();

	// Redirects it together with standard outputs to a log file.
	g_log_set_handler(
			0, (GLogLevelFlags) G_LOG_LEVEL_MASK,
			logHandler, 0 );

	vgDebug::Log::logStandardOutputs( module );
	vgDebug::Log::logBasicInfo( argc, argv, module );
	vgDebug::Log::limitLogFileHistory( maxNumberOfLogFiles );
}



} // namespace vgGTK
