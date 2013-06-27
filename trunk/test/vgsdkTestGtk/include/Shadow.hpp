// VGSDK - Copyright (C) 2011, 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGSDKTESTGTK_SHADOW_HPP
#define _VGSDKTESTGTK_SHADOW_HPP

#include "gtest.hpp"
#include "helpers.hpp"
#include <vgTest/convenience.hpp>

#include "Fixtures.hpp"

// vgsdkNodeTestingSuite
#include <vgd/node/Quad.hpp>
#include <vgd/node/Material.hpp>
#include <vgd/node/Sphere.hpp>
#include <vgd/node/SpotLight.hpp>
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

// @todo log()-add()
	std::string description("Rendering 4 spheres and a quad with shadow mapping");

	using vgd::node::LightModel;
	LightModel::ShadowValueType shadow = GetParam();
	description += " (" + shadow.str() + ").";
	base->getLog()->add( "Description", description );
	base->getLog()->add("Parameters", shadow.str());

	// PREPARE SCENE
	// LightModel
	vgd::Shp< LightModel > lightModel = vgd::dynamic_pointer_cast< LightModel >( base->getCanvas()->createOptionalNode( vgUI::BasicViewer::LIGHT_MODEL ) );

	lightModel->setShadow( shadow );
	lightModel->setShadowFiltering( LightModel::LINEAR );
	lightModel->setShadowMapSize( LightModel::HIGH );
	lightModel->setShadowMapType( LightModel::INT32 );

	// Lights
	base->getCanvas()->destroyOptionalNode( vgGTK::BasicManipulator::LIGHTS );

	using vgd::node::SpotLight;
	vgd::Shp< SpotLight > spot = SpotLight::create("spot");
	spot->setOn( true );
	spot->setPosition( vgm::Vec3f(0.f, 0.f, 28.f) );
	spot->setDirection( vgm::Vec3f(0.f, 0.f, -1.f) );
	spot->setCutOffAngle( 45.f );
	spot->setCastShadow( true );

	const int lightModelIndex = base->getCanvas()->getSetup()->findChild( lightModel );
	base->getCanvas()->getSetup()->insertChild( spot, lightModelIndex );

	//
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

	// Transform
	using vgd::node::Transform;
	vgd::Shp< Transform > transform = Transform::create("rotation");
	transform->setRotation( vgm::Rotation( vgm::Vec3f(1.f, 0.f, 0.f), vgm::Utilities::deg2rad(-70.f) ) );
	base->getCanvas()->getSetup()->insertChild( transform, 1 );

	// @todo base->run() do a viewAll()
	base->getCanvas()->viewAll();

	//run GTK
	base->run();

	base->getLog()->addToGtest();
}



#endif // #ifndef _VGSDKTESTGTK_SHADOW_HPP
