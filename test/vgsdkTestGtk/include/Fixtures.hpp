// VGSDK - Copyright (C) 2009, 2010, 2011, 2012, 2013, Nicolas Papier, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Maxime Peresson

#ifndef _VGTEST_FIXTURES_HPP
#define _VGTEST_FIXTURES_HPP

#include <boost/assign/list_of.hpp>
#include <vector>

#include <vgd/node/Antialiasing.hpp>
#include <vgd/node/LightModel.hpp>
#include <vgd/node/VertexShape.hpp>

#include "vgsdkTestGtk/vgTest/convenience.hpp"
#include "vgsdkTestGtk/vgTest/Performance.hpp"
#include <vgTest/gtest.hpp>


using namespace boost::assign;


/**
 * @brief Fixtures for test on antialiasing (VgTestAntialiasing)
 */
class VgTestAntialiasing : public ::testing::TestWithParam<vgd::node::Antialiasing::TechniqueValueType>
{
protected:
	virtual void SetUp() {}

	virtual void TearDown() {}
};


/**
 * @brief Fixtures for test on depth of field (VgTestDepthOfField)
 */
class VgTestDepthOfField : public ::testing::TestWithParam<bool>
{
protected:
	virtual void SetUp() {}

	virtual void TearDown() {}
};


/**
* @brief Fixtures for shadow tests (VgTestShadow testsuite)
*/
class VgTestShadow : public ::testing::TestWithParam<vgd::node::LightModel::ShadowValueType>
{
protected:
	virtual void SetUp() {}
	virtual void TearDown() {}
};

static std::vector<vgd::node::LightModel::ShadowValueType> shadowType = list_of(vgd::field::Enum(vgd::node::LightModel::SHADOW_OFF ))
	(vgd::node::LightModel::SHADOW_MAPPING)
	(vgd::node::LightModel::SHADOW_MAPPING_9U);






/**
 * @brief Fixtures for test on transparency (VgTestTransparency)
 */
class VgTestTransparency : public ::testing::TestWithParam<float>
{
protected:
	virtual void SetUp() {}

	virtual void TearDown() {}
};


/**
* @brief Fixtures for test on models (VgTestModel testsuite)
*/
class VgTestModel : public ::testing::TestWithParam<std::string>
{
	protected:
	virtual void SetUp() {}

	virtual void TearDown() {}
};

/**
* @brief Fixtures for test on COLLADA model (VgTestCollada testsuite)
*/
class VgTestCollada : public ::testing::TestWithParam<std::string>
{
	protected:
	virtual void SetUp() {}

	virtual void TearDown() {}
};

/**
* @brief Fixtures for test on compressed and/or crpyted model (VgTestCompression testsuite)
*/
class VgTestCompression : public ::testing::TestWithParam<std::string>
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
static std::vector<int> level = list_of(4)(5);

static std::vector<vgd::node::VertexShape::BoundingBoxUpdatePolicyValueType> boundingBoxPolicy = list_of(vgd::field::Enum(vgd::node::VertexShape::AUTOMATIC))
	(vgd::node::VertexShape::ONCE);

static std::vector<vgd::node::VertexShape::DeformableHintValueType> deformableHint = list_of(vgd::field::Enum(vgd::node::VertexShape::STATIC))
	(vgd::node::VertexShape::DYNAMIC)
	(vgd::node::VertexShape::STREAM);

#endif // #ifndef _VGTEST_FIXTURES_HPP
