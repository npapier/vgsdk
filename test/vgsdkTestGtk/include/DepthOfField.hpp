// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGSDKTESTGTK_DEPTHOFFIELD_HPP
#define _VGSDKTESTGTK_DEPTHOFFIELD_HPP

#include "gtest.hpp"
#include "helpers.hpp"
#include <vgTest/convenience.hpp>

#include "Fixtures.hpp"

// vgsdkNodeTestingSuite
#include <vgd/node/DepthOfField.hpp>
#include <vgd/node/Quad.hpp>
#include <vgd/node/Material.hpp>
#include <vgd/node/Sphere.hpp>
#include <vgd/node/SpotLight.hpp>
#include <vgd/node/Transform.hpp>
#include <vgm/Utilities.hpp>
#include <vgGTK/BasicManipulator.hpp>


/**
 * @brief Rendering a matrix of spheres and a quad with depth of field
 */
TEST_P(VgTestDepthOfField, DepthOfField)
{
	const std::string filename = vgTest::getImageName();

	// prerun Gtk
	vgd::Shp< vgsdkTestGtk::vgTest::myBase > base( new vgsdkTestGtk::vgTest::myBase(filename, vgsdkTestGtk::vgTest::SCREENSHOT) );

// @todo log()-add()
	std::string description("Rendering a matrix of spheres and a quad with depth of field.");

	using vgd::node::DepthOfField;
	vgd::Shp< DepthOfField > dof = DepthOfField::create("DOF");
	bool enabled = GetParam();
	if ( enabled )
	{
		dof->setCameraModel( DepthOfField::THIN_LENS );
	}
	else
	{
		dof->setCameraModel( DepthOfField::PINHOLE );
	}

	description += " (" + dof->getCameraModel().str() + ").";
	base->getLog()->add( "Description", description );
	base->getLog()->add("Parameters", dof->getCameraModel().str());

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
	base->getCanvas()->getSetup()->addChild( dof );

	dof->setFocus( 22.f );
	dof->setFocusToFar( 5.f );
	dof->setFocusToNear( 5.f );
	dof->setFarMaximumBlurriness( 1.f );
	dof->setNearMaximumBlurriness( 1.f );

	// @todo base->run() do a viewAll()
	base->getCanvas()->viewAll();

	//run GTK
	base->run();

	base->getLog()->addToGtest();
}



#endif // #ifndef _VGSDKTESTGTK_DEPTHOFFIELD_HPP
