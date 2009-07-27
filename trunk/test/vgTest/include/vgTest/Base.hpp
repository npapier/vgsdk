// VGSDK - Copyright (C) 2009, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGTEST_BASE_HPP
#define _VGTEST_BASE_HPP

#include "vgTest.hpp"



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
	virtual void			setQuit(bool b);

protected:
	bool			m_quit;

private:
	/**
	 * @brief Prerun the Gtk application : create canvas and window
	 * @param true to take screenshot in the paint function
	 */
	virtual void	prerun()=0;

};

} // namespace dtTest



#endif // #ifndef _VGTEST_BASE_HPP

