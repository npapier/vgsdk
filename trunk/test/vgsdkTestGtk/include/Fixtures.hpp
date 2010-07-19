// VGSDK - Copyright (C) 2009, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGTEST_FIXTURES_HPP
#define _VGTEST_FIXTURES_HPP

#include <boost/assign/list_of.hpp>
#include <gtest/gtest.h>
#include <vector>

#include <vgd/node/VertexShape.hpp>

#include "vgsdkTestGtk/vgTest/convenience.hpp"
#include "vgsdkTestGtk/vgTest/Performance.hpp"


/**
* @brief Fixtures for test on models (VgTestModel testsuite)
*/
class VgTestModel : public ::testing::TestWithParam<std::string>
{
	protected:
	virtual void SetUp();

	virtual void TearDown();
};


/**
* @brief Fixtures for test on COLLADA model (VgTestCollada testsuite)
*/
class VgTestCollada : public ::testing::TestWithParam<std::string>
{
	protected:
	virtual void SetUp();

	virtual void TearDown();
};

std::string files[];


/**
* @brief Fixtures for test on shapes (VgTestShape testsuite)
*/
class VgTestShape : public ::testing::TestWithParam<vgsdkTestGtk::vgTest::Performance>
{
	protected:
	virtual void SetUp();

	virtual void TearDown();
};

//param to test
using namespace boost::assign;

static std::vector<int> level = list_of(4)(5);

static std::vector<vgd::node::VertexShape::BoundingBoxUpdatePolicyValueType> boundingBoxPolicy = list_of(vgd::field::Enum(vgd::node::VertexShape::AUTOMATIC))
	(vgd::node::VertexShape::ONCE);

static std::vector<vgd::node::VertexShape::DeformableHintValueType> deformableHint = list_of(vgd::field::Enum(vgd::node::VertexShape::STATIC))
	(vgd::node::VertexShape::DYNAMIC)
	(vgd::node::VertexShape::STREAM);

#endif // #ifndef _VGTEST_FIXTURES_HPP
