// VGSDK - Copyright (C) 2014, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#include "PostProcessing.hpp"


// Test Suite VgTestPostProcessing
INSTANTIATE_TEST_CASE_P(PostProcessingList, VgTestPostProcessing, ::testing::Range(0, 20) );