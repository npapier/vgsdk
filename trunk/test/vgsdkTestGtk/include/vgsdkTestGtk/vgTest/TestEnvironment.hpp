// VGSDK - Copyright (C) 2009, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Maxime Peresson

#ifndef _VGSDKTESTGTK_VGTEST_TESTENVIRONMENT_HPP
#define _VGSDKTESTGTK_VGTEST_TESTENVIRONMENT_HPP

#include <gtest/gtest.h>

namespace Gtk
{
	class Main;
	class Window;
}

namespace vgsdkTestGtk
{

namespace vgTest
{

/**
 * @brief Environnement of the program
 */
struct TestEnvironment : public testing::Environment
{
	/**
	 * @name Constructor / Desctructor
	 */
	//@{
	/**
	 * @brief Construct the environnement with program command line argument
	 */
	TestEnvironment( int argc, char **argv );

	/**
	 * @brief Destructor
	 */
	~TestEnvironment();
	//@}


	/**
	 * Initialize the environnement (GTK, SDL, logging....)
	 */
	void SetUp();
	void TearDown();

private:
	Gtk::Main	*m_kit;
	int			m_argc;
	char		**m_argv;
};

} // namespace vgTest

} //namespace vgsdkTestGtk

#endif // #ifndef _VGSDKTESTGTK_VGTEST_TESTENVIRONMENT_HPP