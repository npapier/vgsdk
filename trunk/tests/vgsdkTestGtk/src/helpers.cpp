// VGSDK - Copyright (C) 2012, 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "helpers.hpp"

#include <vgCairo/helpers.hpp>
#include <vgCairo/ImageSurface.hpp>
#include <vgd/node/Quad.hpp>
#include <vgd/node/LayerPlan.hpp>
#include <vgd/node/Material.hpp>
#include <vgd/node/Sphere.hpp>
#include <vgd/node/Transform.hpp>
#include <vgm/operations.hpp>



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
	transform->setRotation( vgm::Rotation( vgm::Vec3f(1.f, 0.f, 0.f), vgm::deg2rad(-70.f) ) );
	base->getCanvas()->getSetup()->insertChild( transform, 1 );
}



vgd::Shp< vgd::node::LayerPlan > createLayerPlan()
{
	using vgd::node::LayerPlan;

	// LayerPlan
	vgd::Shp< LayerPlan > layerPlan = LayerPlan::create("layerPlan");

	layerPlan->setPosition( vgm::Vec2f(0.f, 0.f) );
	layerPlan->setSize( vgm::Vec2f(1.f, 1.f) );

	//	image used by LayerPlan
	using vgCairo::ImageSurface;
	vgm::Vec2i size(640/10, 480/10);
	vgd::Shp< ImageSurface > imageSurface( new ImageSurface(size[0], size[1]) );

	// Draws on image surface with cairo
	cairo_t * cr = imageSurface->getContext();

	// Clears image surface with cairo
	cairo_save(cr);
	cairo_set_source_rgba (cr, 0, 0, 0, 1);
	cairo_paint(cr);
	cairo_restore(cr);

	// Draws a disk
	cairo_save(cr);

	cairo_set_source_rgba (cr, 0, 0, 1, 0.5);
	vgCairo::ellipse( cr, 0.f, 0.f, static_cast<float>(size[0]), static_cast<float>(size[1]) );

	cairo_set_operator( cr, CAIRO_OPERATOR_SOURCE );
	cairo_fill( cr );

	cairo_restore (cr);

	layerPlan->setImage( imageSurface );

	return layerPlan;
}
