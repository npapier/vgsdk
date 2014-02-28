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
#include <vgd/node/Material.hpp>
#include <vgd/node/OutputBufferProperty.hpp>
#include <vgd/node/OutputBuffers.hpp>
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
		//	outputBufferProperty0
		using vgd::node::OutputBufferProperty;
		obufProperty0 = OutputBufferProperty::create("BUF0");
		obufProperty0->setFormat( OutputBufferProperty::RGB );
		obufProperty0->setType( OutputBufferProperty::INTEGER );
		obufProperty0->setCommand( OutputBufferProperty::COLOR );

		//	outputBufferProperty1
		obufProperty1 = OutputBufferProperty::create("BUF1", 1);
		obufProperty1->setFormat( OutputBufferProperty::RGB );
		obufProperty1->setType( OutputBufferProperty::INTEGER );
		obufProperty1->setCommand( OutputBufferProperty::COLOR );

		//
		using vgd::node::Group;
		using vgd::node::PostProcessing;
		using vgd::node::Switch;

		vgd::Shp< Group >					group;
		vgd::Shp< PostProcessing >			p;

		// SWITCHER
		switcher = Switch::create("TEST.SWITCHER");


		// SUB
		testDesc.push_back("SUB");
		group = Group::create("SUB");
		switcher->addChild( group );

		p = PostProcessing::create("SUB");
		p->setFilter( PostProcessing::SUB );
		p->setInput0( PostProcessing::OUTPUT_BUFFER0 );
		p->setInput1( PostProcessing::OUTPUT_BUFFER1 );
		group->addChild( p );


		// OVER
		testDesc.push_back("OVER");
		group = Group::create("OVER");
		switcher->addChild( group );

		p = PostProcessing::create("OVER");
		p->setFilter( PostProcessing::OVER );
		p->setInput0( PostProcessing::OUTPUT_BUFFER0 );
		p->setInput1( PostProcessing::OUTPUT_BUFFER1 );
		group->addChild( p );


		// COMBINE2_AND_SCALE 
		testDesc.push_back("COMBINE2_AND_SCALE( 0.5, 0.5, 1.0 )");
		group = Group::create("COMBINE2_AND_SCALE");
		switcher->addChild( group );

		p = PostProcessing::create("COMBINE2_AND_SCALE ");
		p->setFilter( PostProcessing::COMBINE2_AND_SCALE  );
		p->setInput0( PostProcessing::OUTPUT_BUFFER0 );
		p->setInput1( PostProcessing::OUTPUT_BUFFER1 );
		p->setParam4f0( vgm::Vec4f( 0.5f, 0.5f, 1.f, 0.f ) );
		group->addChild( p );


		// DOWN_FILTER4
		testDesc.push_back("DOWN_FILTER4");
		group = Group::create("DOWN_FILTER4");
		switcher->addChild( group );

		p = PostProcessing::create("DOWN_FILTER4 ", 0);
		p->setFilter( PostProcessing::DOWN_FILTER4  );
		p->setInput0( PostProcessing::OUTPUT_BUFFER0 );
		group->addChild( p );


		// DOWN_FILTER4_UP_FILTER4
		testDesc.push_back("DOWN_FILTER4, UP_FILTER4");
		group = Group::create("DOWN_FILTER4_UP_FILTER4");
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


		// DOWN_FILTER4_UP_FILTER4_LINEAR
		testDesc.push_back("DOWN_FILTER4, UP_FILTER4_LINEAR");
		group = Group::create("DOWN_FILTER4_UP_FILTER4_LINEAR");
		switcher->addChild( group );

		//	down
		p = PostProcessing::create("downScaling", 0);
		p->setFilter( PostProcessing::DOWN_FILTER4 );
		p->setInput0( PostProcessing::OUTPUT_BUFFER0 );
		group->addChild( p );

		//	up
		p = PostProcessing::create("upLinearScaling", 1);
		p->setFilter( PostProcessing::UP_FILTER4_LINEAR );
		group->addChild( p );


		// COLOR_INVERSE
		testDesc.push_back("COLOR_INVERSE");
		group = Group::create("COLOR_INVERSE");
		switcher->addChild( group );

		p = PostProcessing::create("COLOR_INVERSE", 0);
		p->setFilter( PostProcessing::COLOR_INVERSE );
		p->setInput0( PostProcessing::OUTPUT_BUFFER0 );
		group->addChild( p );


		// MIX_AND_SCALE 
		testDesc.push_back("MIX_AND_SCALE (0.2, 1.0)");
		group = Group::create("MIX_AND_SCALE");
		switcher->addChild( group );

		p = PostProcessing::create("MIX_AND_SCALE");
		p->setFilter( PostProcessing::MIX_AND_SCALE  );
		p->setInput0( PostProcessing::OUTPUT_BUFFER0 );
		p->setInput1( PostProcessing::OUTPUT_BUFFER1 );
		p->setParam4f0( vgm::Vec4f( 0.2f, 1.f, 0.f, 0.f ) );
		group->addChild( p );


		// BLOOM_HORIZ
		testDesc.push_back("BLOOM_HORIZ");
		group = Group::create("BLOOM_HORIZ");
		switcher->addChild( group );

		p = PostProcessing::create("BLOOM_HORIZ(4.0)", 0);
		p->setFilter( PostProcessing::BLOOM_HORIZ );
		p->setInput0( PostProcessing::OUTPUT_BUFFER0 );
		p->setParam1f0( 4.f );
		group->addChild( p );


		// BLOOM_VERT
		testDesc.push_back("BLOOM_VERT");
		group = Group::create("BLOOM_VERT(4.0)");
		switcher->addChild( group );

		p = PostProcessing::create("BLOOM_VERT", 0);
		p->setFilter( PostProcessing::BLOOM_VERT );
		p->setInput0( PostProcessing::OUTPUT_BUFFER0 );
		p->setParam1f0( 4.f );
		group->addChild( p );


		// @todo BLOOM_HORIZ + BLOOM_VERT


		// SCALE_AND_BIAS 
		testDesc.push_back("SCALE_AND_BIAS");
		group = Group::create("SCALE_AND_BIAS");
		switcher->addChild( group );

		p = PostProcessing::create("SCALE_AND_BIAS( (0.5, 0.5, 0.5), (0.2, 0.2, 0.2)", 0);
		p->setFilter( PostProcessing::SCALE_AND_BIAS );
		p->setInput0( PostProcessing::OUTPUT_BUFFER0 );
		p->setParam4f0( vgm::Vec4f( 0.5f, 0.5f, 0.5f, 0.f ) );
		p->setParam4f1( vgm::Vec4f( 0.2f, 0.2f, 0.2f, 0.f ) );
		group->addChild( p );


		// @todo COMBINE3_AND_SCALE


		// BLUR_HORIZ
		testDesc.push_back("BLUR_HORIZ");
		group = Group::create("BLUR_HORIZ");
		switcher->addChild( group );

		p = PostProcessing::create("BLUR_HORIZ", 0);
		p->setFilter( PostProcessing::BLUR_HORIZ );
		p->setInput0( PostProcessing::OUTPUT_BUFFER0 );
		group->addChild( p );


		// BLUR_VERT
		testDesc.push_back("BLUR_VERT");
		group = Group::create("BLUR_VERT");
		switcher->addChild( group );

		p = PostProcessing::create("BLUR_VERT", 0);
		p->setFilter( PostProcessing::BLUR_VERT );
		p->setInput0( PostProcessing::OUTPUT_BUFFER0 );
		group->addChild( p );


		// @todo BLUR_HORIZ + BLUR_VERT


		// COLOR_TO_MONOCHROME 
		testDesc.push_back("COLOR_TO_MONOCHROME ");
		group = Group::create("COLOR_TO_MONOCHROME");
		switcher->addChild( group );

		p = PostProcessing::create("COLOR_TO_MONOCHROME ", 0);
		p->setFilter( PostProcessing::COLOR_TO_MONOCHROME );
		p->setInput0( PostProcessing::OUTPUT_BUFFER0 );
		group->addChild( p );


		// ADD
		testDesc.push_back("ADD");
		group = Group::create("ADD");
		switcher->addChild( group );

		p = PostProcessing::create("ADD");
		p->setFilter( PostProcessing::ADD );
		p->setInput0( PostProcessing::OUTPUT_BUFFER0 );
		p->setInput1( PostProcessing::OUTPUT_BUFFER1 );
		group->addChild( p );


		// @todo ALPHAMIX_AND_SCALE


		// COLOR_TO_SEPIA
		testDesc.push_back("COLOR_TO_SEPIA(0.5, 1.0)");
		group = Group::create("COLOR_TO_SEPIA");
		switcher->addChild( group );

		p = PostProcessing::create("COLOR_TO_SEPIA", 0);
		p->setFilter( PostProcessing::COLOR_TO_SEPIA  );
		p->setInput0( PostProcessing::OUTPUT_BUFFER0 );
		p->setParam4f0( vgm::Vec4f( 0.5f, 1.f, 0.f, 0.f ) );
		group->addChild( p );


		// IDENTITY 
		testDesc.push_back("IDENTITY");
		group = Group::create("IDENTITY");
		switcher->addChild( group );

		p = PostProcessing::create("IDENTITY", 0);
		p->setFilter( PostProcessing::IDENTITY );
		p->setInput0( PostProcessing::OUTPUT_BUFFER0 );
		group->addChild( p );


		// MEDIAN3x3
		testDesc.push_back("MEDIAN3x3");
		group = Group::create("MEDIAN3x3");
		switcher->addChild( group );

		p = PostProcessing::create("MEDIAN3x3", 0);
		p->setFilter( PostProcessing::MEDIAN3x3 );
		p->setInput0( PostProcessing::OUTPUT_BUFFER0 );
		group->addChild( p );


		// COLOR_EDGE_DETECT
		testDesc.push_back("COLOR_EDGE_DETECT");
		group = Group::create("COLOR_EDGE_DETECT");
		switcher->addChild( group );

		p = PostProcessing::create("COLOR_EDGE_DETECT", 0);
		p->setFilter( PostProcessing::COLOR_EDGE_DETECT  );
		p->setInput0( PostProcessing::OUTPUT_BUFFER0 );
		group->addChild( p );


		// NO_FILTER
		testDesc.push_back("NO_FILTER");
		group = Group::create("NO_FILTER");
		switcher->addChild( group );

		p = PostProcessing::create("NO_FILTER", 0);
		p->setFilter( PostProcessing::NO_FILTER  );
		p->setInput0( PostProcessing::OUTPUT_BUFFER0 );
		group->addChild( p );
	}

	virtual void TearDown() {}

	vgd::Shp< vgd::node::OutputBufferProperty >	obufProperty0;
	vgd::Shp< vgd::node::OutputBufferProperty >	obufProperty1;
	vgd::Shp< vgd::node::Switch >				switcher;
	std::vector< std::string >					testDesc;
};



/**
 * @brief Rendering side by side two orange spheres. Left one is outputted in buffer 0, right one is outputted in buffer 1. At least on post processing filter is applied.
 */
TEST_P(VgTestPostProcessing, PostProcessingFilter)
{
	BEGIN_TEST("Rendering a sphere and apply a post processing filter")

	// PREPARE SCENE
	base->getCanvas()->getSetup()->addChild( obufProperty0 );
	base->getCanvas()->getSetup()->addChild( obufProperty1 );

	base->getCanvas()->getSetup()->addChild( switcher );
	switcher->setWhichChild( GetParam() );

	base->getLog()->add( "Parameters", testDesc[GetParam()] );

	//	outputBuffers 0
	using vgd::node::OutputBuffers;

	vgd::Shp< OutputBuffers > outputBuffers = OutputBuffers::create("outputbuffers");
	base->addObject( outputBuffers );

	outputBuffers->setCurrent( 0 );

	//	sphere0
	using vgd::node::Material;
	using vgd::node::Sphere;

	vgd::Shp< Material > material = Material::create("Orange");
	base->addObject( material );
	material->setDiffuse( vgm::Vec3f( 1.f, 0.5f, 0.f ) );

	vgd::Shp< Sphere > sphere = Sphere::create("Sphere0");
	base->addObject( sphere );

	sphere->initializeGeometry(2);

	//	outputBuffers 1
	outputBuffers = OutputBuffers::create("outputbuffers");
	base->addObject( outputBuffers );

	outputBuffers->setCurrent( 1 );

	//	sphere1
	material = Material::create("Orange");
	base->addObject( material );
	material->setDiffuse( vgm::Vec3f( 1.f, 0.5f, 0.f ) );

	sphere = Sphere::create("Sphere1");
	base->addObject( sphere );

	sphere->initializeGeometry(2);
	sphere->transform( vgm::Vec3f(1.f, 0.f, 0.f) );

	// Lights
	base->getCanvas()->createOptionalNode( vgGTK::BasicManipulator::LIGHTS );

	RUN_TEST();
}



#endif // #ifndef _VGSDKTESTGTK_POSTPROCESSING_HPP
