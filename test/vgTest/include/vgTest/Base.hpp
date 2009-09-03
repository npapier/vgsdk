// VGSDK - Copyright (C) 2009, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGTEST_BASE_HPP
#define _VGTEST_BASE_HPP

#include "vgTest/vgTest.hpp"

#include <list>
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
	vgTest::Logging* getLog();


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
	* @brief Get the dated and numbered screenshot name. Adds one to file counter.
	*/
	const std::string					getCountedDatedScreenShotName();

	//@}

	/**
	* @brief Get total number of screenshot taken. Starts at 0.
	*/
	const int							getFileCounter() const;

protected:
	bool					m_quit;
	std::string				m_filename;
	std::string				m_datedFilename;
	int						m_fileCounter;


private:
	/**
	 * @brief Prerun the Gtk application : create canvas and window
	 * @param true to take screenshot in the paint function
	 */
	virtual void	prerun()=0;

	Logging			*m_log;

};

} // namespace vgTest



#endif // #ifndef _VGTEST_BASE_HPP

