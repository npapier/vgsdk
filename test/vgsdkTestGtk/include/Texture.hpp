// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGSDKTESTGTK_TEXTURE_HPP
#define _VGSDKTESTGTK_TEXTURE_HPP

#include "gtest.hpp"
#include "helpers.hpp"
#include <vgTest/convenience.hpp>

#include "Fixtures.hpp"

// vgsdkNodeTestingSuite
#include <vgd/basic/Image.hpp>
#include <vgd/node/Quad.hpp>
#include <vgd/node/LightModel.hpp>
#include <vgd/node/Material.hpp>
#include <vgd/node/Texture2D.hpp>



/**
 * @brief Two shapes. First with a texture. Second without.
 */
TEST(vgsdkNodeTestingSuite, TextureMappingPropagation)
{
	const std::string filename = vgTest::getImageName();

	// prerun Gtk
	vgd::Shp< vgsdkTestGtk::vgTest::myBase > base( new vgsdkTestGtk::vgTest::myBase(filename, vgsdkTestGtk::vgTest::SCREENSHOT) );

// @todo log()-add()
	std::string description("Test texture mapping propagation (have to see a green quad)");

	base->getLog()->add( "Description", description );

	// PREPARE SCENE
	// texture
	using vgd::node::Texture;
	vgd::Shp< vgd::node::Texture2D > blackTexture = vgd::node::Texture2D::create( "black" );
	blackTexture->sethDefaults();

	using vgd::basic::Image;
	uint8 imageData = 0;
	vgd::Shp< Image > image( new Image( 1, 1, 1, Image::LUMINANCE, Image::UINT8, &imageData ) );
	blackTexture->setImage( image );

	// First shape
	using vgd::node::Quad;
	vgd::Shp< Quad > quad1 = Quad::create("quad1");
	quad1->initializeGeometry( 10.f, 10.f );
	quad1->initializeTexUnits();

	using vgd::node::Material;
	vgd::Shp< Material > mat1 = Material::create("red");
	mat1->setDiffuse( vgm::Vec3f( 1.f, 0.f, 0.f ) );

	base->addObject( blackTexture );
	base->addObject( mat1 );
	base->addObject( quad1 );

	// Second shape
	vgd::Shp< Quad > quad2 = Quad::create("quad2");
	quad2->initializeGeometry( 5.f, 5.f );
	quad2->transform( vgm::Vec3f(0.f, 0.f, 10.f) );

	using vgd::node::Material;
	vgd::Shp< Material > mat2 = Material::create("green");
	mat2->setDiffuse( vgm::Vec3f( 0.f, 1.f, 0.f ) );

	base->addObject( mat2 );
	base->addObject( quad2 );

	// @todo base->run() do a viewAll()
	base->getCanvas()->viewAll();

	//run GTK
	base->run();

	base->getLog()->addToGtest();
}



#endif // #ifndef _VGSDKTESTGTK_TEXTURE_HPP
