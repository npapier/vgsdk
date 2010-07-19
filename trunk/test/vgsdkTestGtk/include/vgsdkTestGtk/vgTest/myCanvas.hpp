// VGSDK - Copyright (C) 2008, 2009, Guillaume Brocker, Nicolas Papier, Maxime Peresson.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier
// Author Maxime Peresson

#ifndef _VGSDKTESTGTK_VGTEST_MYCANVAS_HPP
#define _VGSDKTESTGTK_VGTEST_MYCANVAS_HPP

#include <glibmm/ustring.h>
#include <vector>

#include <vgGTK/TBasicManipulator.hpp>

#include "vgsdkTestGtk/vgTest/TestManipulator.hpp"

namespace vgsdkTestGtk
{

namespace vgTest
{
/**
 * @brief	Implements a BasicManipulator with some content loading features.
 *
 */
	struct myCanvas : public vgGTK::TBasicManipulator< vgsdkTestGtk::vgTest::TestManipulator >
{
	typedef std::vector< Glib::ustring > Strings;	///< Defines a collection of strings.

	/**
	 * @name	Constructors & destructor
	 */
	//@{
	myCanvas();

	//~myCanvas();
	//@}

	/**
	 * @name Scene management methods
	 */
	//@{
	/**
	 * @brief	Loads and appends an object to the scene.
	 *
	 * @param	filename	a string containing the path to the file to load
	 * @param	viewAll 	true to move the camera so every object is in the view field
	 *
	 * @return	true on success, false otherwise
	 */
	const bool appendToScene( const Glib::ustring & filename, const bool viewAll = true );

	/**
	 * @brief	Loads and appends objects to the scene.
	 *
	 * @param	filenames	a collection of strings containing the paths to the files to load
	 * @param	viewAll 	true to move the camera so every object is in the view field
	 *
	 * @return	true on success, false otherwise
	 */
	const bool appendToScene( const Strings & filenames, const bool viewAll = true );

	const bool load( const Glib::ustring & pathfilename );

	const bool loadCollada( const Glib::ustring & pathfilename );

	const bool loadOpenCollada( const Glib::ustring & pathfilename );

	const bool loadObj( const Glib::ustring & pathfilename );

	const bool loadTrian( const Glib::ustring & pathfilename );

	const bool loadTrian2( const Glib::ustring & pathfilename );


private:
	Strings				m_filenames;			///< Contains the paths of the files currently loaded.
};


} // namespace vgTest

} //namespace vgsdkTestGtk

#endif // #ifndef _VGSDKTESTGTK_VGTEST_MYCANVAS_HPP

