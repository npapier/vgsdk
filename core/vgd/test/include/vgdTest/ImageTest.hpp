#ifndef _VGDTEST_IMAGETEST_HPP
#define _VGDTEST_IMAGETEST_HPP

#include "vgdTest/ModuleTest.hpp"

#include <vgd/basic/Image.hpp>
#include <boost/filesystem/path.hpp>


struct ImageTest : public ::testing::TestWithParam< std::tuple<std::string, int, int> >
{
	ImageTest();

	/**
	 * @brief Fixtures 
	 */
	//@{
	vgd::Shp< vgd::basic::Image > m_image;		///< An instance of an Image class which is the subject of the tests. 
	boost::filesystem::path m_imageFile;		///< An example of an image file used to test the class.
	//@}
	
	protected:
	virtual void SetUp() {}

	virtual void TearDown() {}
};

#endif //_VGDTEST_IMAGETEST_HPP
