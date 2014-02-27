// VGSDK - Copyright (C) 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGSDKTESTGTK_POSTPROCESSING_HPP
#define _VGSDKTESTGTK_POSTPROCESSING_HPP

#include "helpers.hpp"
#include <vgTest/convenience.hpp>
#include <vgTest/gtest.hpp>

#include "Fixtures.hpp"

// vgsdkNodeTestingSuite
#include <vgd/node/OutputBufferProperty.hpp>
#include <vgd/node/PostProcessing.hpp>
#include <vgd/node/Sphere.hpp>
#include <vgGTK/BasicManipulator.hpp>


/**
 * @brief Fixtures for PostProcessing tests (VgTestPostProcessing testsuite)
 */
class VgTestPostProcessing : public ::testing::TestWithParam<int>
{
protected:
	virtual void SetUp()
	{
		// OUTPUTBUFFERPROPERTY
		using vgd::node::OutputBufferProperty;
		obufProperty = OutputBufferProperty::create("BUF0");
		obufProperty->setFormat( OutputBufferProperty::RGB );
		obufProperty->setType( OutputBufferProperty::INTEGER );
		obufProperty->setCommand( OutputBufferProperty::COLOR );

		//
		using vgd::node::Group;
		using vgd::node::PostProcessing;
		using vgd::node::Switch;

		vgd::Shp< Group >					group;
		vgd::Shp< PostProcessing >			p;

		// SWITCHER
		switcher = Switch::create("TEST.SWITCHER");

		// COLOR_INVERSE
		testDesc.push_back("COLOR_INVERSE");
		group = Group::create("COLOR_INVERSE");
		switcher->addChild( group );

		//
		p = PostProcessing::create("COLOR_INVERSE", 0);
		p->setFilter( PostProcessing::COLOR_INVERSE );
		p->setInput0( PostProcessing::OUTPUT_BUFFER0 );
		group->addChild( p );

		// COLOR_TO_SEPIA
		testDesc.push_back("COLOR_TO_SEPIA");
		group = Group::create("COLOR_TO_SEPIA ");
		switcher->addChild( group );

		//
		p = PostProcessing::create("COLOR_TO_SEPIA ", 0);
		p->setFilter( PostProcessing::COLOR_TO_SEPIA  );
		p->setInput0( PostProcessing::OUTPUT_BUFFER0 );
		p->setParam4f0( vgm::Vec4f( 0.5f, 1.f, 0.f, 0.f ) );
		group->addChild( p );

		// DOWN_FILTER4
		testDesc.push_back("DOWN_FILTER4");
		group = Group::create("DOWN_FILTER4 ");
		switcher->addChild( group );

		//
		p = PostProcessing::create("DOWN_FILTER4 ", 0);
		p->setFilter( PostProcessing::DOWN_FILTER4  );
		p->setInput0( PostProcessing::OUTPUT_BUFFER0 );
		group->addChild( p );

		// COLOR_EDGE_DETECT
		testDesc.push_back("COLOR_EDGE_DETECT");
		group = Group::create("COLOR_EDGE_DETECT ");
		switcher->addChild( group );

		//
		p = PostProcessing::create("COLOR_EDGE_DETECT ", 0);
		p->setFilter( PostProcessing::COLOR_EDGE_DETECT  );
		p->setInput0( PostProcessing::OUTPUT_BUFFER0 );
		group->addChild( p );

		// DOWN_UP_SCALING_FILTER
		testDesc.push_back("DOWN_UP_SCALING_FILTER");
		group = Group::create("DOWN_UP_SCALING_FILTER ");
		switcher->addChild( group );

		//	down
		p = PostProcessing::create("downScaling", 0);
		p->setFilter( PostProcessing::DOWN_FILTER4 );
		p->setInput0( PostProcessing::OUTPUT_BUFFER0 );
		group->addChild( p );

		//	up
		p = PostProcessing::create("upScaling", 1);
		p->setFilter( PostProcessing::UP_FILTER4 );
		group->addChild( p );
	}

	virtual void TearDown() {}

	vgd::Shp< vgd::node::OutputBufferProperty >	obufProperty;
	vgd::Shp< vgd::node::Switch >				switcher;
	std::vector< std::string >					testDesc;
};



/**
 * @brief Rendering a sphere and apply a post processing filter
 */
TEST_P(VgTestPostProcessing, PostProcessingFilter)
{
	BEGIN_TEST("Rendering a sphere and apply a post processing filter")

	// PREPARE SCENE
	base->getCanvas()->getSetup()->addChild( obufProperty );

	base->getCanvas()->getSetup()->addChild( switcher );
	switcher->setWhichChild( GetParam() );

	base->getLog()->add( "Parameters", testDesc[GetParam()] );

	//	sphere
	using vgd::node::Sphere;

	vgd::Shp< Sphere > sphere = Sphere::create("Sphere");
	base->addObject( sphere );

	sphere->initializeGeometry(2);

	// Lights
	base->getCanvas()->createOptionalNode( vgGTK::BasicManipulator::LIGHTS );

	RUN_TEST();
}



#endif // #ifndef _VGSDKTESTGTK_POSTPROCESSING_HPP
