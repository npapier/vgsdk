// VGSDK - Copyright (C) 2009, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#include "Fixtures.hpp"

//Test Suite VgTestModel
void VgTestModel::SetUp()
{
}

void VgTestModel::TearDown()
{
}

std::string files[] = {	"box.trian", "cavite.obj", "geosphere.trian"};

INSTANTIATE_TEST_CASE_P(FileList, VgTestModel, testing::ValuesIn(files));

//Test Suite VgTestShape
void VgTestShape::SetUp()
{
}

void VgTestShape::TearDown()
{
}

INSTANTIATE_TEST_CASE_P(PerformanceList, VgTestShape, testing::ValuesIn( vgTest::getPerformance(level, deformableHint, boundingBoxPolicy) ));