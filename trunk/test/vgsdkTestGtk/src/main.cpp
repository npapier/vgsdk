// VGSDK - Copyright (C) 2009, 2012, 2013, Maxime Peresson, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson
// Author Guillaume Brocker
// Author Nicolas Papier

#include <gtest/gtest.h>
#include "vgsdkTestGtk/vgTest/TestEnvironment.hpp"
#include "vgsdkTestGtk/vgTest/convenience.hpp"

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

#include <sbf/pkg/Package.hpp>
#include <sbf/pkg/Module.hpp>


// @todo accepts gtest command-line option.
int main(int argc, char **argv) 
{
	// get application name (without the full path)
	namespace bfs=boost::filesystem;
	const bfs::path pathFilename( argv[0] );
	const std::string appName = pathFilename.filename().string();

	const bfs::path bfsXmlPath = sbf::pkg::Module::get()->getPath(sbf::pkg::VarPath) / "googletest";
	const std::string xmlPath = bfsXmlPath.string() + "\\";
	boost::filesystem::create_directories(xmlPath);

	try
	{
		namespace po = boost::program_options;
		po::options_description desc("Allowed options");
		desc.add_options()
			("help", "Produce help message")
			("saveRef", "Creates references for all tests")
		;

		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, desc), vm);
		po::notify(vm); 

		if (vm.count("help")) 
		{
			std::cout << "Usage: vgSDK tests [options]\n";
			std::cout << desc;
			return 0;
		}

		if (vm.count("saveRef")) 
		{
			vgsdkTestGtk::vgTest::setCreateReference(true);
			::testing::FLAGS_gtest_output = "xml:" + xmlPath + "createRef-" + appName + ".xml";
		}
		else 
		{
			::testing::FLAGS_gtest_output = "xml:" + xmlPath + appName + ".xml";
		}
	}
	catch(std::exception& e)
	{
		std::cout << e.what() << "\n";
		return 1;
	}

	::testing::FLAGS_gtest_catch_exceptions = true;
	testing::InitGoogleTest(&argc, argv);

	//run the environnement (do it AFTER googletest init, or you may have problem (gtk init must be after googletest init))
	::testing::AddGlobalTestEnvironment( new vgsdkTestGtk::vgTest::TestEnvironment( argc, argv ));

	// Should be : return RUN_ALL_TESTS();
	// RUN_ALL_TESTS doesn't return 0 if a test fail. We want 0 if the execution is completely done.
	RUN_ALL_TESTS();
	return 0;
}
