// VGSDK - Copyright (C) 2009, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include <gtest/gtest.h>
#include "vgsdkTestGtk/vgTest/TestEnvironment.hpp"
#include "vgsdkTestGtk/vgTest/convenience.hpp"

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/program_options.hpp>

#include <sbf/path.hpp>


int main(int argc, char **argv) 
{
	//get application name (without the full path)
	std::vector<std::string> vec;
	boost::algorithm::split(vec, argv[0], boost::algorithm::is_any_of("\\"));
	std::string appName = vec[vec.size()-1];
	std::string xmlPath = sbf::path::getTopLevel(sbf::path::Var).string() + "\\googletest\\0-0\\";
	boost::algorithm::replace_all(xmlPath, "/", "\\");
	sbf::path::mkdirs(xmlPath);

    try {
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
