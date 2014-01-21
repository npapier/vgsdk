// VGSDK - Copyright (C) 2009, 2013, Maxime Peresson, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson
// Author Nicolas Papier

#ifndef _VGTEST_BASE_HPP
#define _VGTEST_BASE_HPP

#include <list>
#include <sbf/pkg/Module.hpp>
#include <vgd/Shp.hpp>

#include "vgTest/vgTest.hpp"

namespace vgTest { struct Logging; }



namespace vgTest
{

/**
 * @brief Abstract base class which make link between test application, GTK/Qt and vgsdk.
 */
struct VGTEST_API Base
{
	/**
	 * @name Constructors and destructor
	 */
	//@{

	/**
	 * @brief Default constructor
	 */
	Base( const std::string filename = "test", const boost::shared_ptr< sbf::pkg::Module > module = sbf::pkg::Module::get() );

	/**
	 * @brief Virtual destructor
	 */
	virtual ~Base();
	//@}


	/**
	 * @name Have to be overridden in subclass.
	 */
	//@{

	/**
	 * @brief Run the GUI main loop
	 */
	virtual void run( const bool callViewAll = true )=0;

	/**
	 * @brief Quit the GUI main loop and destroy the canvas and window
	 */
	virtual bool quit()=0;
	//@}


	/**
	 * @brief Set if the GUI main loop must quit next idle time
	 * @param true to quit
	 */
	virtual void setQuit(const bool b);


	/**
	 * @brief Get logging class
	 */
	vgd::Shp< vgTest::Logging > getLog();


	/**
	 * @name Path accessors
	 */
	//@{

	/**
	* @brief Get the path of the reference image
	*/
	const boost::filesystem::path		getReferencePath() const;

	/**
	* @brief Get the path of the screenshot
	*/
	const boost::filesystem::path		getScreenShotPath() const;

	/**
	* @brief Get the path of the difference
	*/
	const boost::filesystem::path		getDifferencePath() const;

	/**
	* @brief Get the images path for xml attribute for one capture
	* @param diff true if the capture contains differences
	*/
	const std::string					getImagesPath( const bool diff ) const;

	/**
	* @brief Get the images path for xml attribute for different capture (using file counter)
	* @param diff	list of capture containing differences
	*/
	const std::string					getImagesPath( const std::list<int>& diff ) const;

	//@}


	/**
	 * @name Screenshot name accessors
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
	* @brief Get the dated and numbered screenshot name. Adds one to file counter if n == true.
	*/
	const std::string					getCountedDatedScreenShotName(const bool n = true);

	const std::string					getCountedScreenShotName(const bool n = true);
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
	virtual void prerun()=0;

	vgd::Shp< vgTest::Logging > m_log;

	const boost::shared_ptr< sbf::pkg::Module > m_module;
};

} // namespace vgTest



#endif // #ifndef _VGTEST_BASE_HPP
