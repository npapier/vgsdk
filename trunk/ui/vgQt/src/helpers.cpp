// VGSDK - Copyright (C) 2010, 2012, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Clément Forest

#include "vgQt/helpers.hpp"

#include <iostream>
#include <sbf/log/GlobalLogger.hpp>
#include <vgDebug/helpers.hpp>
#include "vgQt/Logging.hpp"
#include <QDebug>


namespace
{

void logHandler( QtMsgType type, const char *msg )
{
	std::cerr << msg << std::endl;
}

}

namespace vgQt
{


void initLogging( int argc, char** argv, const boost::shared_ptr< sbf::pkg::Module > module, const int maxNumberOfLogFiles )
{
	// Installs the Qt-based logging system.
	sbf::log::GlobalLogger::set< vgQt::Logging >();

	// Redirects output to cerr.
	qInstallMsgHandler( logHandler );


	vgDebug::Log::logStandardOutputs( module );
	vgDebug::Log::logBasicInfo( argc, argv, module );
	vgDebug::Log::limitLogFileHistory( maxNumberOfLogFiles );
}



} // namespace vgQt
