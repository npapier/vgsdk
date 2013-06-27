// VGSDK - Copyright (C) 2012, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "helpers.hpp"

#include <vgd/node/Quad.hpp>
#include <vgd/node/Material.hpp>
#include <vgd/node/Sphere.hpp>
#include <vgd/node/Transform.hpp>
#include <vgm/Utilities.hpp>



void createQuadAndSpheresMatrix( vgd::Shp< vgsdkTestGtk::vgTest::myBase > base )
{
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

	for( float x = -6.f; x < 6.f; x += 1.5f )
	{
		for( float y = -6.f; y < 6.f; y += 1.5f )
		{
			vgd::Shp< Sphere > sphere = Sphere::create("sphere");
			sphere->initializeGeometry( 3 );
			sphere->transform( vgm::Vec3f( x, y, 5.f ) );
			base->addObject( sphere );
		}
	}

	// Transform
	using vgd::node::Transform;
	vgd::Shp< Transform > transform = Transform::create("rotation");
	transform->setRotation( vgm::Rotation( vgm::Vec3f(1.f, 0.f, 0.f), vgm::Utilities::deg2rad(-70.f) ) );
	base->getCanvas()->getSetup()->insertChild( transform, 1 );
}
