// VGSDK - Copyright (C) 2009, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGTEST_GRAPH_HPP
#define _VGTEST_GRAPH_HPP

#include <gtest/gtest.h>
#include <vgd/ScopedPtr.hpp>
#include <vgd/Shp.hpp>
#include <vgd/node/Group.hpp>
#include <vgTest/convenience.hpp>

#include "Fixtures.hpp"
#include "vgsdkTestGtk/vgTest/myBase.hpp"
#include "vgsdkTestGtk/vgTest/myCanvas.hpp"



/**
* @brief VgTestGraph testsuite
*/


/**
* @brief	Search an object in a scene graph
*			Test when there is a loop in the scene graph
*/
TEST(VgTestGraph, SearchInSceneGraph)
{	
	RecordProperty("Description", "Search an object in a scene graph. Test when there is a loop in the scene graph");
	
	//Create / prepare scene
	vgd::Shp<vgd::node::Group> root = vgd::node::Group::create("root");
	vgd::Shp<vgd::node::Group> n1 = vgd::node::Group::create("n1");
	vgd::Shp<vgd::node::Group> n2 = vgd::node::Group::create("n2");
	vgd::Shp<vgd::node::Group> n11 = vgd::node::Group::create("n11");
	vgd::Shp<vgd::node::Group> n12 = vgd::node::Group::create("n12");

	root->addChild(n1);
	root->addChild(n2);
	n1->addChild(n11);
	n1->addChild(n12);

	vgd::Shp<vgd::node::VertexShape> vs = vgd::node::VertexShape::create("Test");
	
	n12->addChild(vs);

	//Test
	vgd::Shp<vgd::node::VertexShape> vsOk = vgd::visitor::findFirstByName< vgd::node::VertexShape >(root, "Test");
	EXPECT_EQ(vs, vsOk);	

	vgd::Shp<vgd::node::VertexShape> vsEmpty = vgd::visitor::findFirstByName< vgd::node::VertexShape >(root, "find nothing");
	EXPECT_NE(vs, vsEmpty);

	n2->addChild(root);
	EXPECT_THROW(
		{	
			vsOk = vgd::visitor::findFirstByName< vgd::node::VertexShape >(root, "find nothing");
		}, vgd::visitor::HasCycle);
	
	n2->removeChild(root);
}

#endif // #ifndef _VGTEST_GRAPH_HPP