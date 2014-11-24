#include "vgdTest/ImageTest.hpp"

#include <sbf/pkg/Module.hpp>

#define TEST_INFO(method_)	testInfos("", method_, "Image.hpp", "unit_test", "cplusplus")


// Test File Loading (ImageTest)
std::tuple<std::string, int, int> const valueTable[] = 
{
	std::make_tuple(".png", 10, 10)
,	std::make_tuple(".bmp", 20, 20)
,	std::make_tuple(".tga", 15, 15)
,	std::make_tuple(".gif", 20, 10)
,	std::make_tuple(".jpg", 10, 20 )
};

INSTANTIATE_TEST_CASE_P( Extension, ImageTest, testing::ValuesIn(valueTable) );


ImageTest::ImageTest()
{
	using vgd::basic::Image;

	m_imageFile = sbf::pkg::Module::get()->getPath(sbf::pkg::SharePath) / "test";
	m_image = vgd::makeShp(new vgd::basic::Image(m_imageFile.string() + ".png"));	
}

/**
 * @brief Tests image loading. 
 */
TEST_P( ImageTest, loadTest )
{
	using vgd::basic::Image;

	auto tuple = GetParam();
	const std::string extension = std::get<0>(tuple);
	const std::string message = "vgd::basic::Image::load " + extension;
	TEST_INFO( message.c_str() );
	
	const std::string filename = m_imageFile.string() + extension;
	vgd::Shp< Image > image = vgd::makeShp(new Image(filename));
	
	if(image->pixels() != NULL)
	{
		int width = image->width();
		int height = image->height();
		EXPECT_EQ( width, std::get<1>(tuple) );
		EXPECT_EQ( height, std::get<2>(tuple) );
	}
	else
	{
		std::cout << "Couldn't load image : " << filename << std::endl;
	}
	EXPECT_NE( image, vgd::Shp< Image >() );
}

/**
 * @brief Tests incorrect image loading. 
 */
TEST_F( ImageTest, badLoadTest )
{
	using vgd::basic::Image;

	const std::string message = "vgd::basic::Image::load incorrect file";
	TEST_INFO( message.c_str() );

	const std::string filename = "toto";
	vgd::Shp< Image > image = vgd::makeShp(new Image(filename));
	
	EXPECT_EQ((const int)image->pixels(), NULL);
	EXPECT_EQ( image->voxelSize(), vgm::Vec3f(1.f, 1.f, 1.f ));
	EXPECT_EQ( image->width(), 0 );
	EXPECT_EQ( image->height(), 0 );
	EXPECT_EQ( image->components(), 0 );
}

/**
 * @brief Tests image saving. 
 */
TEST_P( ImageTest, saveTest )
{
	using vgd::basic::Image;

	auto tuple = GetParam();
	const std::string extension = std::get<0>(tuple);
	const std::string message = "vgd::basic::Image::save " + extension;
	TEST_INFO( message.c_str() );
	
	auto filepath = sbf::pkg::Module::get()->getPath(sbf::pkg::SharePath) / "output";
	const std::string filename = filepath.string() + extension;
	
	m_image->save(filename);
	
	vgd::Shp< Image > image = vgd::makeShp(new Image(filename));
	
	if(image->pixels() != NULL)
	{
		int width = image->width();
		int height = image->height();
		EXPECT_EQ( width, 10 );
		EXPECT_EQ( height, 10 );
	}
	else
	{
		const std::string message = "Image format saving not supported : " + extension;
		TEST_INFO(message.c_str());
	}
	EXPECT_NE( image, vgd::Shp< Image >() );
}

/**
 * @brief Tests  image scaling. 
 */
TEST_F( ImageTest, scalingTest )
{
	using vgd::basic::Image;

	const std::string message = "vgd::basic::Image::scale";
	TEST_INFO( message.c_str() );

	int originalWidth = m_image->width();
	int originalHeight = m_image->height();
	
	vgm::Vec3i newSize(20,30,0);
	m_image->scale(newSize);
	
	EXPECT_EQ( m_image->width(), newSize[0] );
	EXPECT_EQ( m_image->height(), newSize[1] );
}
