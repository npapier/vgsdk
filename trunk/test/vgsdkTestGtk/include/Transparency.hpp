// VGSDK - Copyright (C) 2010, 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGSDKTESTGTK_TRANSPARENCY_HPP
#define _VGSDKTESTGTK_TRANSPARENCY_HPP

#include "helpers.hpp"
#include <vgTest/convenience.hpp>
#include <vgTest/gtest.hpp>

#include "Fixtures.hpp"

// vgsdkNodeTestingSuite
#include <vgd/node/Material.hpp>
#include <vgd/node/Sphere.hpp>

/**
 * @brief Rendering a red sphere with different transparency level and a green sphere placed behind.
 */
TEST_P(VgTestTransparency, Transparency)
{
	const std::string filename = vgTest::getImageName();

	// prerun Gtk
	vgd::Shp< vgsdkTestGtk::vgTest::myBase > base( new vgsdkTestGtk::vgTest::myBase(filename, vgsdkTestGtk::vgTest::SCREENSHOT) );

	// @todo log()-add()
	std::string description("Rendering a red sphere with different transparency level and a green sphere placed behind.");

	base->getLog()->add( "Description", description );
	// @todo base->getLog()->add("Parameters", opacity.str());

	// PREPARE SCENE
	using vgd::node::Material;
	using vgd::node::Sphere;

	// *** transparent object ***
	// material

	vgd::Shp< Material > material = Material::create("transparent");
	material->setDiffuse( vgm::Vec3f(1.f, 0.f, 0.f) );
	const float opacity = GetParam();
	material->setOpacity(opacity);

	// sphere
	vgd::Shp< Sphere > sphere = Sphere::create("SphereTransparent");
	sphere->initializeGeometry(2);

	base->addObject( material );
	base->addObject( sphere );

	// *** opaque object ***
	// material

	material = Material::create("opaque");
	material->setDiffuse( vgm::Vec3f(0.f, 1.f, 0.f) );

	// sphere
	sphere = Sphere::create("Sphere");
	sphere->initializeGeometry(2);
	vgm::MatrixR transformation;
	transformation.setTranslate( vgm::Vec3f(0.f, 0.f, -2.f) );
	transformation.scale(0.5f);
	sphere->transform(transformation);

	base->addObject( material );
	base->addObject( sphere );

	// @todo base->run() do a viewAll()
	base->getCanvas()->viewAll();

	//run GTK
	base->run();

	base->getLog()->addToGtest();
}



#endif // #ifndef _VGSDKTESTGTK_TRANSPARENCY_HPP
