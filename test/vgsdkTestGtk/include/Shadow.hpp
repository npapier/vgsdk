// VGSDK - Copyright (C) 2011, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGSDKTESTGTK_SHADOW_HPP
#define _VGSDKTESTGTK_SHADOW_HPP

#include "gtest.hpp"
#include <vgTest/convenience.hpp>

#include "Fixtures.hpp"
#include "vgsdkTestGtk/vgTest/myBase.hpp"
#include "vgsdkTestGtk/vgTest/myCanvas.hpp"

// vgsdkNodeTestingSuite
#include <vgd/node/Quad.hpp>
#include <vgd/node/Material.hpp>
#include <vgd/node/Sphere.hpp>
#include <vgd/node/Switch.hpp>
#include <vgd/node/Transform.hpp>
#include <vgm/Utilities.hpp>
#include <vgGTK/BasicManipulator.hpp>



/**
 * @brief Rendering 4 spheres and a quad with shadow mapping.
 */
TEST_P(VgTestShadow, ShadowMapping)
{
	const std::string filename = vgTest::getImageName();

	// prerun Gtk
	vgd::Shp< vgsdkTestGtk::vgTest::myBase > base( new vgsdkTestGtk::vgTest::myBase(filename, vgsdkTestGtk::vgTest::SCREENSHOT) );

	base->getLog()->add("Description", "Rendering 4 spheres and a quad with shadow mapping.");

	// prepare scene
	using vgd::node::LightModel;
	vgd::Shp< LightModel > lightModel = vgd::dynamic_pointer_cast< LightModel >( base->getCanvas()->createOptionalNode( vgUI::BasicViewer::LIGHT_MODEL ) );

	LightModel::ShadowValueType shadow = GetParam();
	base->getLog()->add("shadow", shadow.str());

	lightModel->setShadow( shadow );
	lightModel->setShadowFiltering( LightModel::LINEAR );
	lightModel->setShadowMapSize( LightModel::HIGH );
	lightModel->setShadowMapType( LightModel::INT32 );

	using vgd::node::Quad;
	using vgd::node::Material;
	using vgd::node::Sphere;

	// Quad
	vgd::Shp< Quad > quad = Quad::create("quad");
	quad->initializeGeometry( 10.f, 10.f );

	base->addObject( quad );

	// Material
	using vgd::node::Material;
	vgd::Shp< Material > material = Material::create("material");
	material->setDiffuse( vgm::Vec3f(0.f, 1.f, 0.f ) );
	base->addObject( material );

	vgd::Shp< Sphere > sphere = Sphere::create("sphere");
	sphere->initializeGeometry( 3 );
	sphere->transform( vgm::Vec3f( 2.75f, 2.75f, 1.5f ) );
	base->addObject( sphere );

	material = Material::create("material");
	material->setDiffuse( vgm::Vec3f(1.f, 0.f, 0.f ) );
	base->addObject( material );

	sphere = Sphere::create("sphere1");
	sphere->initializeGeometry( 3 );
	sphere->transform( vgm::Vec3f( -3.f, -3.f, 5.f ) );
	base->addObject( sphere );

	sphere = Sphere::create("sphere2");
	sphere->initializeGeometry( 3 );
	sphere->transform( vgm::Vec3f( -3.f, 3.f, 5.f ) );
	base->addObject( sphere );

	sphere = Sphere::create("sphere3");
	sphere->initializeGeometry( 3 );
	sphere->transform( vgm::Vec3f( 3.f, 3.f, 5.f ) );
	base->addObject( sphere );

	sphere = Sphere::create("sphere4");
	sphere->initializeGeometry( 3 );
	sphere->transform( vgm::Vec3f( 3.f, -3.f, 5.f ) );
	base->addObject( sphere );

//
	base->getCanvas()->destroyOptionalNode( vgGTK::BasicManipulator::LIGHTS );
	using vgd::node::Switch;
	vgd::Shp< Switch > lightSwitcher = base->getCanvas()->createOptionalNodeAs<Switch>( vgGTK::BasicManipulator::LIGHTS );
	if ( lightSwitcher )
	{
		lightSwitcher->setWhichChild( 1 );
	}
//

	// Transform
	using vgd::node::Transform;
	vgd::Shp< Transform > transform = Transform::create("rotation");
	transform->setRotation( vgm::Rotation( vgm::Vec3f(1.f, 0.f, 0.f), vgm::Utilities::deg2rad(-70.f) ) );
	base->getCanvas()->getSetup()->insertChild( transform, 1 );

	// @todo base->run() do a viewAll()
	base->getCanvas()->viewAll();

	//run GTK
	base->run();

	// Finalized test
	if ( vgsdkTestGtk::vgTest::getCreateReference() )
	{
		base->moveToReference();
	}
	else
	{
		// do the test
		base->compareScreenShots();
	}

	base->getLog()->addToGtest();
}



#endif // #ifndef _VGSDKTESTGTK_SHADOW_HPP
