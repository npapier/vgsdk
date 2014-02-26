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
 * @brief Rendering a sphere with a 2 post processing filters (downFilter and upFilter)
 */
TEST(VgTestPostProcessing, PostProcessingDownUpFilter)
{
	BEGIN_TEST("Rendering a sphere with 2 post processing filters (downFilter and upFilter)")

	// PREPARE SCENE
	using vgd::node::Group;
	using vgd::node::OutputBufferProperty;
	using vgd::node::PostProcessing;

	vgd::Shp< OutputBufferProperty >	obufProperty;
	vgd::Shp< Group >					group;
	vgd::Shp< PostProcessing >			p;

	// OutputBufferProperty
	obufProperty = OutputBufferProperty::create("BUF0"/*, 0*/);
	obufProperty->setFormat( OutputBufferProperty::RGB );
	obufProperty->setType( OutputBufferProperty::INTEGER );
	obufProperty->setCommand( OutputBufferProperty::COLOR );
	//obufProperty->setCustomCommand( "" );
	base->getCanvas()->getSetup()->addChild( obufProperty );

	// PostProcessing
	group = Group::create("DownUpScaling");
	base->getCanvas()->getSetup()->addChild( group );

	//	down
	p = PostProcessing::create("downScaling", 0);
	p->setFilter( PostProcessing::DOWN_FILTER4 );
	p->setInput0( PostProcessing::OUTPUT_BUFFER0 );
	group->addChild( p );

	//	up
	p = PostProcessing::create("upScaling", 1);
	p->setFilter( PostProcessing::UP_FILTER4 );
	group->addChild( p );

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
