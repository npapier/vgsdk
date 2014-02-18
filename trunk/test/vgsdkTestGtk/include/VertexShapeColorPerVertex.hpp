// VGSDK - Copyright (C) 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGSDKTESTGTK_VERTEXSHAPECOLORPERVERTEX_HPP
#define _VGSDKTESTGTK_VERTEXSHAPECOLORPERVERTEX_HPP

#include "helpers.hpp"
#include <vgTest/convenience.hpp>
#include <vgTest/gtest.hpp>

#include "Fixtures.hpp"

// vgsdkNodeTestingSuite
#include <vgd/node/Sphere.hpp>
#include <vgGTK/BasicManipulator.hpp>


/**
 * @brief Rendering a sphere with a color per vertex equal to the normal
 */
TEST(VgTestVertexShapeColorPerVertex, VertexShapeColorPerVertex)
{
	BEGIN_TEST("Rendering a sphere with a color per vertex equal to the normal")

	// PREPARE SCENE

	// sphere
	using vgd::node::Sphere;
	using vgd::node::VertexShape;

	vgd::Shp< Sphere > sphere = Sphere::create("Sphere");
	base->addObject( sphere );

	sphere->initializeGeometry(2);

	vgd::field::EditorRO< VertexShape::FNormalType >	normals = sphere->getNormalRO();
	vgd::field::EditorRW< VertexShape::FColorType >		colors4 = sphere->getColorRW();

	for( uint i=0; i < normals->size(); ++i )
	{
		vgm::Vec3f normal3 = (*normals)[i];

		vgm::Vec4f color4( normal3 );
		color4[3] = 0.f;
		colors4->push_back( color4 );
	}
	normals.release();
	colors4.release();

	sphere->setColorBinding( vgd::node::BIND_PER_VERTEX );

	// Lights
	base->getCanvas()->createOptionalNode( vgGTK::BasicManipulator::LIGHTS );

	RUN_TEST();
}



#endif // #ifndef _VGSDKTESTGTK_VERTEXSHAPECOLORPERVERTEX_HPP
