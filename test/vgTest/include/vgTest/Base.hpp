// VGSDK - Copyright (C) 2009, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGTEST_BASE_HPP
#define _VGTEST_BASE_HPP

#include "vgTest/vgTest.hpp"

#include <gtest/gtest.h>

#include <list>
#include <vgd/Shp.hpp>

#include "vgTest/Logging.hpp"


namespace vgTest
{

/**
 * @brief Abstract base class which make link between test application, Gtk and vgsdk.
 */
struct VGTEST_API Base
{
	/**
	 * @brief Default constructor
	 */
	Base();

	Base( const std::string& filename );
	
	/**
	 * @brief Virtual destructor
	 */
	virtual ~Base();

	/**
	 * @brief Run the Gtk main loop
	 */
	virtual void	run()=0;

	/**
	 * @brief Quit the Gtk main loop and destroy the canvas and window
	 */
	virtual bool	quit()=0;

	/**
	 * @brief Set if the Gtk main loop must quit next idle time
	 * @param true to quit
	 */
	virtual void	setQuit(const bool b);

	/**
	 * @brief Get logging class
	 */
	vgd::Shp< vgTest::Logging >	getLog();


	/**
	 * @name Path accessor
	 */
	//@{
	/**
	* @brief Get the path of the reference image
	*/
	const std::string					getReferencePath() const;

	/**
	* @brief Get the path of the screenshot
	*/
	const std::string					getScreenShotPath() const;

	/**
	* @brief Get the path of the difference
	*/
	const std::string					getDifferencePath() const;

	/**
	* @brief Get the images path for xml attribute for one capture
	* @param diff true if the capture contains differences
	*/
	const std::string					getImagesPath( const bool diff ) const;

	/**
	* @brief Get the images path for xml attribute for different capture (using file counter)
	* @param diff list of capture containing differences
	*/
	const std::string					getImagesPath( const std::list<int>& diff ) const;
	//@}


	/**
	 * @name Screenshot name accessor
	 */
	//@{
	/**
	* @brief Get the screenshot name
	*/
	const std::string					getScreenShotName() const;

	/**
	* @brief Get the dated screenshot name
	*/
	const std::string					getDatedScreenShotName() const;

	/**
	* @brief Get the dated and numbered screenshot name. Adds one to file counter if nn == true.
	*/
	const std::string					getCountedDatedScreenShotName(bool n = true);

	//@}

	/**
	* @brief Get total number of screenshot taken. Starts at 0.
	*/
	const int							getFileCounter() const;

	/**
	* @brief Get frequency for screenshot.
	*/
	const int							getScreenshotFrenquency() const;

	/**
	* @brief Set frequency for screenshot. One every 'f' paint.
	*/
	void								setScreenshotFrequency(int f);

	/**
	 * @brief Compare all screenshots done with reference.
	 * @todo Will work if gtest is compiled as a DLL
	 */
	void								compareScreenShots() const;

	/**
	 * @brief Move screenshots done to reference folder.
	 */
	void								moveToReference() const;

protected:
	bool					m_quit;
	std::string				m_filename;
	std::string				m_datedFilename;
	int						m_fileCounter;
	int						m_screenshotFrequency;


private:
	/**
	 * @brief Prerun the Gtk application : create canvas and window
	 * @param true to take screenshot in the paint function
	 */
	virtual void	prerun()=0;

	vgd::Shp< vgTest::Logging > m_log;

};

} // namespace vgTest



//Macro which replace compareScreenShots function
#define macroCompareScreenShots(base) \
	std::list<int> differences; \
	for (int i = 0; i <= base->getFileCounter(); i++) \
	{ \
		if (!boost::filesystem::exists(base->getReferencePath() + vgTest::getNumberedImageName(base->getScreenShotName(), i))) \
		{ \
			FAIL() << "REFERENCES FILES : " + base->getReferencePath() + vgTest::getNumberedImageName(base->getScreenShotName(), i) + " IS NOT CREATED"; \
		} \
		\
		SCOPED_TRACE("Screenshot : " + vgTest::getNumberedImageName(base->getDatedScreenShotName(), i) + " Reference : " +  vgTest::getNumberedImageName(base->getScreenShotName(), i)); \
		\
		int diff = vgTest::compare(base->getReferencePath() + vgTest::getNumberedImageName(base->getScreenShotName(), i), \
			base->getScreenShotPath() + vgTest::getNumberedImageName(base->getDatedScreenShotName(), i), \
			base->getDifferencePath() + vgTest::getNumberedImageName(base->getDatedScreenShotName(), i)); \
		\
		EXPECT_EQ( diff, 0 ); \
		\
		if( diff != 0) \
		{ \
			differences.push_back(i); \
		} \
	} \
	\
	base->getLog()->add("ImagePath", base->getImagesPath(differences)); \

#endif // #ifndef _VGTEST_BASE_HPP

