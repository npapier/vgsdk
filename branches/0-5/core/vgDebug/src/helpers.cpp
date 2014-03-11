// VGSDK - Copyright (C) 2010, 2011, 2012, Clement Forest, Nicolas Papier
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Clement Forest
// Author Guillaume Brocker

#include "vgDebug/helpers.hpp"

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/time_formatters.hpp>
#include <boost/filesystem/convenience.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <fstream>
#include <iostream>
#include <sbf/pkg/Module.hpp>
#include <set>
#include <vgd/Shp.hpp>
#include <vgDebug/StreamTee.hpp>



namespace
{

vgd::Shp<vgDebug::StreamTee> outRedirection;
vgd::Shp<vgDebug::StreamTee> errRedirection;
vgd::Shp<vgDebug::StreamTee> logRedirection;

std::string				g_logFilePrefix;
std::string				g_logFileSuffix;
std::string				g_currentLogFile;

boost::filesystem::path	g_logDirectory;
}



namespace vgDebug
{



void Log::logStandardOutputs( boost::shared_ptr< sbf::pkg::Module > module )
{
	namespace bfs = boost::filesystem;
 	namespace bpx = boost::posix_time;

	// Resets previous redirection (if any)
	outRedirection.reset();
 	errRedirection.reset();
 	logRedirection.reset();

	// Creates log directory
	g_logDirectory = module->getPathSafe(sbf::pkg::VarPath) / "log";
	try 
	{
		boost::filesystem::create_directory(g_logDirectory);
	}
	catch(const std::exception& e) 
	{
		std::cerr << e.what( ) << std::endl;

	}

	// log-ulis2-0-2010-11-16_15h25m48s.txt
	g_logFilePrefix = std::string("log_") + module->getName() + module->getVersion() + "_";
	g_logFileSuffix = ".txt";

	std::stringstream ss;
	bpx::time_facet * outputFacet = new bpx::time_facet(); 
	ss.imbue( std::locale(std::locale::classic(), outputFacet) );
	// Monday-29-02-2009_14h30m12s
	outputFacet->format("%Y-%m-%d_%Hh%Mm%Ss");
	ss << g_logFilePrefix << bpx::second_clock::local_time() << g_logFileSuffix;
	g_currentLogFile = ss.str();

	static std::ofstream logFile( (g_logDirectory / g_currentLogFile ).string().c_str() );
	if(logFile.good())
	{
		outRedirection.reset(new vgDebug::StreamTee(&std::cout, &logFile));
		errRedirection.reset(new vgDebug::StreamTee(&std::cerr, &logFile));
		logRedirection.reset(new vgDebug::StreamTee(&std::clog, &logFile));
	}
}


void Log::limitLogFileHistory( const int maxNumber )
{
	namespace bfs = boost::filesystem;

	try
	{
		if( ( !bfs::exists( g_logDirectory ) )
			|| ( !bfs::is_directory( g_logDirectory ) ) )
			return;

		// Retreive log files
		std::set<bfs::path> existingLogFiles;
		for( bfs::directory_iterator i( g_logDirectory ); i != bfs::directory_iterator(); ++i )
		{
			bfs::path currentPath( *i );
			if( ( !bfs::is_directory( currentPath ) )
				&& ( currentPath.filename().string().compare( 0, g_logFilePrefix.size(), g_logFilePrefix ) == 0 )
				&& ( currentPath.filename().string().compare( currentPath.filename().string().size() - g_logFileSuffix.size(), g_logFileSuffix.size(), g_logFileSuffix ) == 0 )
				&& ( currentPath.filename() != g_currentLogFile) )
			{
				existingLogFiles.insert( currentPath );
			}
		}
		// remove superfluous files
		int nbToRemove = std::max( 0, (int)existingLogFiles.size() - maxNumber );
		for(int i = 1 ; i <= nbToRemove; ++i )
		{
			std::clog << "Removing log file " << *existingLogFiles.begin() << std::endl;
			bfs::remove( *existingLogFiles.begin() );
			existingLogFiles.erase( existingLogFiles.begin() );
		}
	}
	catch( const std::exception & e )
	{
		std::cerr << "Error while limiting log file history. " << e.what() << std::endl;
	}
}


void Log::logBasicInfo(int argc, char** argv, boost::shared_ptr< sbf::pkg::Module > module)
{
	std::clog << "Starting " << module->getName() << module->getVersion() << " as ";
	for(int i=0;i<argc;++i)
	{
		std::clog << argv[i] <<" ";
	}
	std::clog << std::endl;
	// Current directory
	std::clog << "In directory " << boost::filesystem::initial_path().string() << std::endl;
}


} // namespace vgDebug
