// VGSDK - Copyright (C) 2009, 2010, 2011, 2012, 2013, Nicolas Papier, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier
// Author Maxime Peresson

#include "Fixtures.hpp"

#include <vgTest/convenience.hpp>

// Test antialiasing (VgTestAntialiasing)
static std::vector<vgd::node::Antialiasing::TechniqueValueType> aaTechnique = list_of(vgd::node::Antialiasing::NONE)
	(vgd::node::Antialiasing::FXAA1);
INSTANTIATE_TEST_CASE_P( BoolList, VgTestAntialiasing, testing::ValuesIn(aaTechnique) );


// Test depth of field (VgTestDepthOfField)
//INSTANTIATE_TEST_CASE_P( BoolList, VgTestDepthOfField, testing::Values(false, true) );
INSTANTIATE_TEST_CASE_P( BoolList, VgTestDepthOfField, testing::Values(false, true) );


//Test Suite VgTestShadow
INSTANTIATE_TEST_CASE_P(ShadowList, VgTestShadow, testing::ValuesIn(shadowType));


// Test Transparency (VgTestTransparency)
INSTANTIATE_TEST_CASE_P( FloatList, VgTestTransparency, testing::Values(1.f, 0.8f, 0.6f, 0.4f, 0.2f, 0.f) );






//Test Suite VgTestModel
INSTANTIATE_TEST_CASE_P(FileList, VgTestModel, testing::ValuesIn(vgTest::createModelList()));

//Test Suite VgTestCollada
INSTANTIATE_TEST_CASE_P(FileList, VgTestCollada, testing::ValuesIn(vgTest::createModelList( "collada" )));


//Test Suite VgTestCompression
void VgTestCompression::SetUp()
{
}

void VgTestCompression::TearDown()
{
}
INSTANTIATE_TEST_CASE_P(FileList, VgTestCompression, testing::ValuesIn(vgTest::createModelList( "compression" )));

//Test Suite VgTestShape
void VgTestShape::SetUp()
{
}

void VgTestShape::TearDown()
{
}

INSTANTIATE_TEST_CASE_P(PerformanceList, VgTestShape, testing::ValuesIn( vgsdkTestGtk::vgTest::getPerformance(level, deformableHint, boundingBoxPolicy) ));
