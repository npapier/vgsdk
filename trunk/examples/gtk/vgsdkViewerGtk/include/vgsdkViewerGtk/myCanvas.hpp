// VGSDK - Copyright (C) 2008, 2009, Guillaume Brocker, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Nicolas Papier

#ifndef _VGSDKVIEWERGTK_MYCANVAS_HPP
#define _VGSDKVIEWERGTK_MYCANVAS_HPP

#include <vector>
#include <glibmm/ustring.h>
#include <vgeGL/technique/Technique.hpp>
#include <vgGTK/BasicManipulator.hpp>



namespace vgsdkViewerGtk
{



/**
 * @brief	Implements a BasicManipulator with some content loading features.
 *
 * @todo	The file list management should get externalized to another object.
 * 			This would allow to load an object, keep it somewhere in a lobby
 * 			instead of having it directly appended to the scene. An usage example
 * 			is the recent file loading.
 */
struct myCanvas : public vgGTK::BasicManipulator
{
	typedef std::vector< Glib::ustring > Strings;	///< Defines a collection of strings.


	/**
	 * @brief	Constructor
	 */
	myCanvas();


	bool onKeyPressed( GdkEventKey * event );


	/**
	 * @name Overrides
	 */
	//@{
	void initialize();
	//@}


	/**
	 * @name	View Mode Accessors
	 */
	//@{

	enum ViewMode
	{
		SINGLE_VIEW = 0,
		LEFT_SIDED_VIEWS,
		SQUARED_VIEWS,
		VIEW_MODE_COUNT
	};

	/**
	 * @brief	Enables or disables the multi-view rendering.
	 * 
	 * @param	mode	the multi view mode.
	 */
	void setViewMode( const ViewMode mode );

	// @todo getViewMode

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

	/**
	 * @brief	Removes all objects from the scene.
	 */
	void clearScene();

	/**
	 * @brief	Tells if the scene is empty.
	 *
	 * @return	true or false
	 */
	const bool isEmpty() const;

	/**
	 * @brief	Reloads all objects of the scene from the filesystem.
	 *
	 * @return	true on succes, false otherwise
	 */
	const bool reloadScene();
	//@}


private:

	/**
	 * @name Loading methods
	 */
	//@{
	const bool load( const Glib::ustring & pathfilename );
	//const bool loadCollada( const Glib::ustring & pathfilename );
	//const bool loadOpenCollada( const Glib::ustring & pathfilename, bool crypted = false );
	//const bool loadObj( const Glib::ustring & pathfilename );
	//const bool loadTrian( const Glib::ustring & pathfilename );
	//const bool loadTrian2( const Glib::ustring & pathfilename, bool crypted = false );
	//@}


	/**
	 * @name	View Mode Technique Factories
	 */
	//@{
	vgd::Shp< vgeGL::technique::Technique > createMultiViewSingleTechnique();
	vgd::Shp< vgeGL::technique::Technique > createMultiViewSidedTechnique();
	vgd::Shp< vgeGL::technique::Technique > createMultiViewSquaredTechnique();
	//@}

	typedef std::vector< vgd::Shp< vgeGL::technique::Technique > > TechniqueContainer;
	TechniqueContainer	m_viewModeTechniques;	///< Contains all view mode techniques.

	Strings				m_filenames;			///< Contains the paths of the files currently loaded.
};



} // namespace vgsdkViewerGtk

#endif // #ifndef _VGSDKVIEWERGTK_MYCANVAS_HPP
