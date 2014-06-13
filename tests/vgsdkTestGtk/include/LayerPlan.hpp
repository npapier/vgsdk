// VGSDK - Copyright (C) 2011, 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGSDKTESTGTK_LAYERPLAN_HPP
#define _VGSDKTESTGTK_LAYERPLAN_HPP

#include "helpers.hpp"
#include <vgTest/convenience.hpp>
#include <vgTest/gtest.hpp>

#include "Fixtures.hpp"

// vgsdkNodeTestingSuite
#include <vgd/node/LayerPlan.hpp>
#include <vgGTK/BasicManipulator.hpp>


/**
 * @brief Rendering a layer plan
 */
TEST(VgTestLayerPlan, LayerPlan)
{
	const std::string filename = vgTest::getImageName();

	// prerun Gtk
	vgd::Shp< vgsdkTestGtk::vgTest::myBase > base( new vgsdkTestGtk::vgTest::myBase(filename, vgsdkTestGtk::vgTest::SCREENSHOT) );

// @todo log()-add()
	std::string description("Rendering a layer plan.");

	vgd::Shp< vgd::node::LayerPlan > layerPlan = createLayerPlan();

	base->getLog()->add( "Description", description );

	// PREPARE SCENE
	base->getCanvas()->getScene()->addChild( layerPlan );

	//run GTK
	base->run();

	base->getLog()->addToGtest();
}

#endif // #ifndef _VGSDKTESTGTK_LAYERPLAN_HPP
