// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGSDKTESTGTK_TRANSPARENCY_HPP
#define _VGSDKTESTGTK_TRANSPARENCY_HPP

#include "gtest.hpp"

#include <vgd/Shp.hpp>
#include <vgTest/convenience.hpp>

#include "Fixtures.hpp"
#include "vgsdkTestGtk/vgTest/myBase.hpp"
#include "vgsdkTestGtk/vgTest/myCanvas.hpp"

// vgsdkNodeTestingSuite
#include <vgd/node/Material.hpp>
#include <vgd/node/Sphere.hpp>

/**
 * @brief Rendering a red sphere with different transparency level and a green sphere placed behind.
 */
TEST_P(VgTestTransparency, Transparency)
{
	const ::testing::TestInfo* const test_info = ::testing::UnitTest::GetInstance()->current_test_info();

	const std::string filename = vgTest::getImageName(test_info->name());

	// prerun Gtk
	vgd::Shp< vgsdkTestGtk::vgTest::myBase > base( new vgsdkTestGtk::vgTest::myBase(filename, vgsdkTestGtk::vgTest::SCREENSHOT) );

	base->getLog()->add("Description", "Rendering a red sphere with different transparency level and a green sphere placed behind.");

	// prepare scene
	/*using vgd::node::LightModel;
	vgd::Shp< LightModel > lightModel = vgd::dynamic_pointer_cast< LightModel >( base->getCanvas()->createOptionalNode( vgUI::BasicViewer::LIGHT_MODEL ) );
	lightModel->setTwoSided(true);*/

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

	// Finalized test
	if (vgsdkTestGtk::vgTest::getCreateReference())
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



#endif // #ifndef _VGSDKTESTGTK_TRANSPARENCY_HPP
