// VGSDK - Copyright (C) 2009, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGTEST_COLLADA_HPP
#define _VGTEST_COLLADA_HPP

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>


#include <vgd/ScopedPtr.hpp>
#include <vgd/Shp.hpp>
#include <vgd/node/LightModel.hpp>
#include <vgTest/convenience.hpp>

#include "Fixtures.hpp"
#include "gtest.hpp"
#include "vgsdkTestGtk/vgTest/myBase.hpp"
#include "vgsdkTestGtk/vgTest/myCanvas.hpp"

#include <vgeGL/engine/Engine.hpp>


/**
* @brief VgTestCollada testsuite
*/

/**
* @brief Compare a generated image and a reference image
*/
TEST_P(VgTestCollada, DISABLED_LoadTest)
{	
	//list of untested models, add to make them fail!
	std::vector< std::string > failedModels;
	failedModels.push_back( "mirror.DAE" ); 
	
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	//std::string filename = vgTest::getImageName(test_info->name());
	boost::filesystem::path path( GetParam() );
	std::string filename = vgTest::getImageName( path.filename().string() );

	vgd::ScopedPtr< vgsdkTestGtk::vgTest::myBase > base( new vgsdkTestGtk::vgTest::myBase(filename, vgsdkTestGtk::vgTest::SCREENSHOT) );	

	std::string desc = "Compare a generated image and a reference image of a COLLADA model.<br/> Object:";
	desc += GetParam();
	base->getLog()->add("Description", desc);
	
	base->getLog()->add("Object", GetParam());

	// prepare scene
	base->addObject(GetParam());

	using vgd::node::LightModel;
	vgd::Shp< LightModel > lightModel = vgd::dynamic_pointer_cast< LightModel >( base->getCanvas()->createOptionalNode( vgUI::BasicViewer::LIGHT_MODEL ) );
	lightModel->setModel( LightModel::LIGHTING_OFF );

	//run GTK
	base->run();

	if (vgsdkTestGtk::vgTest::getCreateReference())
	{
		base->moveToReference();
	}
	else
	{
		// do the test
		base->compareScreenShots();

		std::vector< std::string >::iterator it;
		it = find( failedModels.begin(), failedModels.end(), path.filename() );

		if( it != failedModels.end() )
		{
			FAIL();
		}
	}

	base->getLog()->addToGtest();
}



#endif // #ifndef _VGTEST_COLLADA_HPP