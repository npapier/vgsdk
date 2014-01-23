// VGSDK - Copyright (C) 2012, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGSDKTESTGTK_ANTIALIASING_HPP
#define _VGSDKTESTGTK_ANTIALIASING_HPP

#include "helpers.hpp"
#include <vgTest/convenience.hpp>
#include <vgTest/gtest.hpp>

#include "Fixtures.hpp"

// vgsdkNodeTestingSuite
#include <vgd/node/Antialiasing.hpp>
#include <vgd/node/SpotLight.hpp>
#include <vgGTK/BasicManipulator.hpp>



/**
 * @brief Rendering a matrix of spheres and a quad with antialiasing.
 */
TEST_P(VgTestAntialiasing, Antialiasing)
{
	const std::string filename = vgTest::getImageName();

	// prerun Gtk
	vgd::Shp< vgsdkTestGtk::vgTest::myBase > base( new vgsdkTestGtk::vgTest::myBase(filename, vgsdkTestGtk::vgTest::SCREENSHOT) );

// @todo log()-add()
	std::string description("Rendering a matrix of spheres and a quad with antialiasing.");

	using vgd::node::Antialiasing;
	vgd::Shp< Antialiasing > aa = base->getCanvas()->getOptionalNodeAs<Antialiasing>( vgUI::BasicViewer::ANTIALIASING );
	Antialiasing::TechniqueValueType technique = GetParam();
	aa->setTechnique( technique );

	description += " (" + aa->getTechnique().str() + ").";
	base->getLog()->add( "Description", description );
	base->getLog()->add("Parameters", aa->getTechnique().str());

	// PREPARE SCENE
	// LightModel
	using vgd::node::LightModel;
	vgd::Shp< LightModel > lightModel = vgd::dynamic_pointer_cast< LightModel >( base->getCanvas()->createOptionalNode( vgUI::BasicViewer::LIGHT_MODEL ) );

	// Lights
	base->getCanvas()->destroyOptionalNode( vgGTK::BasicManipulator::LIGHTS );

	using vgd::node::SpotLight;
	vgd::Shp< SpotLight > spot = SpotLight::create("spot");
	spot->setOn( true );
	spot->setPosition( vgm::Vec3f(0.f, 0.f, 28.f) );
	spot->setDirection( vgm::Vec3f(0.f, 0.f, -1.f) );
	spot->setCutOffAngle( 45.f );
	//spotLight1->setDropOffRate( 0.5f );
	spot->setCastShadow( true );

	const int lightModelIndex = base->getCanvas()->getSetup()->findChild( lightModel );
	base->getCanvas()->getSetup()->insertChild( spot, lightModelIndex );

	//
	createQuadAndSpheresMatrix( base );

	//run GTK
	base->run();

	base->getLog()->addToGtest();
}



#endif // #ifndef _VGSDKTESTGTK_ANTIALIASING_HPP
