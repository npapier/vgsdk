// VGSDK - Copyright (C) 2012, 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGSDKTESTGTK_HELPERS_HPP
#define _VGSDKTESTGTK_HELPERS_HPP

#include "vgsdkTestGtk/vgTest/myBase.hpp"
#include "vgsdkTestGtk/vgTest/myCanvas.hpp"

namespace vgd { namespace node { struct LayerPlan; } }


#define BEGIN_TEST(givenDescription)	/* prerun Gtk */																						\
vgd::Shp< vgsdkTestGtk::vgTest::myBase > base( new vgsdkTestGtk::vgTest::myBase(vgTest::getImageName(), vgsdkTestGtk::vgTest::SCREENSHOT) );	\
std::string description( givenDescription );																									\
base->getLog()->add( "Description", description );


#define RUN_TEST()	/* run GTK */	\
base->run();						\
base->getLog()->addToGtest();


/**
 * @brief Creates a scene composed of a quad and a matrix of spheres.
 */
void createQuadAndSpheresMatrix(vgd::Shp< vgsdkTestGtk::vgTest::myBase > base );


/**
 * @brief Creates a LayerPlan node containing an image drawn with cairo (draw a blue disk).
 */
vgd::Shp< vgd::node::LayerPlan > createLayerPlan();

#endif // #ifndef _VGSDKTESTGTK_HELPERS_HPP
