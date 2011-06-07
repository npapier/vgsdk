// VGSDK - Copyright (C) 2009, 2011, Maxime Peresson, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson
// Author Nicolas Papier

#ifndef _VGTEST_MODEL_HPP
#define _VGTEST_MODEL_HPP

#include <boost/algorithm/string.hpp>

#include <vgd/ScopedPtr.hpp>
#include <vgd/Shp.hpp>
#include <vgTest/convenience.hpp>

#include "Fixtures.hpp"
#include "gtest.hpp"
#include "vgsdkTestGtk/vgTest/myBase.hpp"
#include "vgsdkTestGtk/vgTest/myCanvas.hpp"

// vgsdkNodeTestingSuite
#include <vgd/node/Quad.hpp>
#include <vgd/node/LightModel.hpp>
#include <vgd/node/Material.hpp>
#include <vgd/node/Sphere.hpp>
#include <vgd/node/Texture2D.hpp>
#include <vgeGL/engine/Engine.hpp>



/**
 * @brief Two shapes. First with a texture. Second without.
 */
TEST(vgsdkNodeTestingSuite, TextureMappingPropagation)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::string filename = vgTest::getImageName(test_info->name());

	// prerun Gtk
	vgd::Shp< vgsdkTestGtk::vgTest::myBase > base( new vgsdkTestGtk::vgTest::myBase(filename, vgsdkTestGtk::vgTest::SCREENSHOT) );

	base->getLog()->add("Description", "Test texture mapping propagation");

	// prepare scene

	// texture
	using vgd::node::Texture;
	vgd::Shp< vgd::node::Texture2D > blackTexture = vgd::node::Texture2D::create( "black" );
	blackTexture->setWrap( Texture::WRAP_S, Texture::REPEAT );
	blackTexture->setWrap( Texture::WRAP_T, Texture::REPEAT );
	blackTexture->setFilter( Texture::MIN_FILTER, Texture::NEAREST );
	blackTexture->setFilter( Texture::MAG_FILTER, Texture::NEAREST );
	blackTexture->sethFunction( Texture::FUN_MODULATE );

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

	//
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











/**
 * @brief Vertex coloring test
 * @todo Generalized => RenderingTest (others PerfTest... )
 */
TEST(vgsdkNodeTestingSuite, DISABLED_PerVertexColoring)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::string filename = vgTest::getImageName(test_info->name());

	// prerun Gtk
	vgd::Shp< vgsdkTestGtk::vgTest::myBase > base( new vgsdkTestGtk::vgTest::myBase(filename, vgsdkTestGtk::vgTest::SCREENSHOT) );

	base->getLog()->add("Description", "Test vertex coloring in VertexShape");

	// prepare scene
	//base->getCanvas()->getGLEngine()->setGLSLEnabled(true);

	/*using vgd::node::LightModel;
	vgd::Shp< LightModel > lightModel = vgd::dynamic_pointer_cast< LightModel >( base->getCanvas()->createOptionalNode(  vgUI::BasicViewer::LIGHT_MODEL ) );
	lightModel->setTwoSided(true);*/

	using vgd::node::VertexShape;

	// material
	using vgd::node::Material;

	vgd::Shp< Material > opaqueMat = Material::create("opaque");
	opaqueMat->setDiffuse( vgm::Vec3f( 0.2f, 0.f, 0.f ) );
	// @todo disable display list for debug in gdebugger
	// @todo core/vgd/gen : setDiffuse( x, y, z );
	opaqueMat->setShininess( 0.5f );
	opaqueMat->setSpecular( vgm::Vec3f( 1.f, 1.f, 1.f ) );
	opaqueMat->setOpacity(1.f);

	vgd::Shp< Material > transparentMat = Material::create("transparent");
	transparentMat->setDiffuse( vgm::Vec3f( 0.f, 1.f, 0.f ) );
	transparentMat->setShininess( 0.5f );
	transparentMat->setSpecular( vgm::Vec3f( 1.f, 1.f, 1.f ) );
	transparentMat->setOpacity(0.1f);

	// quad
	//using vgd::node::Quad;

	//vgd::Shp< Quad > quad = Quad::create("quad.for.PerVertexColoring.test");

	//quad->initializeGeometry( 2.f, 2.f );

	// sphere
	using vgd::node::Sphere;

	vgd::Shp< Sphere > sphere = Sphere::create("Sphere");
	sphere->initializeGeometry(2);
	//sphere->initializeGeometry(0);

	vgd::field::EditorRO< VertexShape::FNormalType > normals = sphere->getFNormalRO();
	vgd::field::EditorRW< VertexShape::FColor4Type > colors4 = sphere->getFColor4RW();

	for( uint i=0; i < normals->size(); ++i )
	{
		vgm::Vec3f normal3 = (*normals)[i];

		vgm::Vec4f color4( normal3 );
		color4[3] = 1.f;
		colors4->push_back( color4 );
	}
	//(*colors4)[0].setValue( 1.f, 0.f, 0.f, 1.f );
	//(*colors4)[4].setValue( 0.f, 1.f, 0.f, 1.f );
	//(*colors4)[8].setValue( 0.f, 0.f, 1.f, 1.f );
	normals.release();
	colors4.release();

	sphere->setColor4Binding( vgd::node::BIND_PER_VERTEX );

	base->addObject( opaqueMat );
	//base->addObject( quad );
	//base->addObject( transparentMat );
	base->addObject( sphere );

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
//

/**
* @brief VgTestModel testsuite
*/

/**
* @brief Compare a generated image and a reference image
*/
TEST_P(VgTestModel, DISABLED_CompareTest)
{	
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::string filename = vgTest::getImageName(test_info->name());

	vgd::ScopedPtr< vgsdkTestGtk::vgTest::myBase > base( new vgsdkTestGtk::vgTest::myBase(filename, vgsdkTestGtk::vgTest::SCREENSHOT) );	

	std::string desc = "Compare a generated image and a reference image.<br/> Object:";
	desc += GetParam();
	base->getLog()->add("Description", desc);
	
	base->getLog()->add("Object", GetParam());

	// prepare scene
	base->addObject(GetParam());

	//run GTK
	base->run();

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


/**
* @brief Test performance with different model
*/
TEST_P(VgTestModel, DISABLED_PerformanceModelTest)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::string filename = vgTest::getImageName(test_info->name());

	vgd::ScopedPtr< vgsdkTestGtk::vgTest::myBase > base( new vgsdkTestGtk::vgTest::myBase(filename, vgsdkTestGtk::vgTest::SCREENSHOT_PERFORMANCE) );	

	std::string desc = "Test performance with different model.<br/> Object:";
	desc += GetParam();
	base->getLog()->add("Description", desc);	
	
	base->getLog()->add("Object", GetParam());

	// prepare scene
	base->addObject(GetParam());

	//run GTK
	base->run();

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

/**
* @brief Compare a generated image and a reference image
*/
//TEST_F(VgTestModel, FailCompareTest)
//{	
//	RecordProperty("Description", "Compare a generated image and a fake reference image ==> MUST FAIL");
//	
//	const ::testing::TestInfo* const test_info =
//	  ::testing::UnitTest::GetInstance()->current_test_info();
//
//	std::string filename = vgTest::getImageName(test_info->name());
//
//	vgd::ScopedPtr< vgTest::myBase > base( new vgTest::myBase(filename, vgTest::SCREENSHOT) );
//	RecordProperty("Object", "cavite.obj");
//
//	// prepare scene
//	base->addObject("cavite.obj");
//
//	//run GTK
//	base->run();
//
//
//	// do the test
//	int diff = vgTest::compare(base->getReferencePath(), base->getScreenShotPath(), base->getDifferencePath());
//	EXPECT_EQ( diff, 0 );
//
//	RecordProperty("PixelDiff", diff);
//
//	if (diff > 0)
//	{
//		RecordProperty("ImagePath", base->getImagesPath(true).c_str());
//	}
//	else
//	{
//		RecordProperty("ImagePath", base->getImagesPath(false).c_str());
//	}
//}



#endif // #ifndef _VGTEST_MODEL_HPP
