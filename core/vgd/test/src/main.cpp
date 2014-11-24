

#include "vgdTest/ImageTest.hpp"
#include <gtest/gtest.h>
#include <gtest/gtest-spi.h>

#include <vgd/Shp.hpp>

int main( int argc, char ** argv )
{
	//char *option[] = { "test.exe", "--gtest_output=xml:report_TEST.xml" };
	//vgSofa::setDtSofaModelsAsDefaultModels();
	::testing::InitGoogleTest( &argc, argv );
	RUN_ALL_TESTS();
	return 0;
}
