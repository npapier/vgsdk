// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGSDKVIEWERQT_MYCANVAS_HPP_
#define _VGSDKVIEWERQT_MYCANVAS_HPP_

#include <vgQt/BasicManipulator.hpp>
#include <vgQt/engine/UserSettingsDialog.hpp>

namespace vgsdkViewerQt
{

/**
 * @brief	Implements a BasicManipulator with some content loading features.
 *
 */
struct MyCanvas : public vgQt::BasicManipulator
{
public:
    /**
     * @brief	Constructor
     */
    MyCanvas();

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
    //@}

    /**
     * @brief	Removes all objects from the scene.
     */
    void clearScene();

    /**
     * @brief	Loads and appends an object to the scene.
     *
     * @param	filename	a string containing the path to the file to load
     * @param	viewAllAfterLoading 	true to move the camera so every object is in the view field
     *
     * @return	true on success, false otherwise
     */
    const bool appendToScene( const QString filename, const bool viewAllAfterLoading = true );

    /**
     * @brief	Loads and appends a list of objects to the scene.
     *
     * @param	filenames	a string containing the path to the file to load
     * @param	viewAllAfterLoading 	true to move the camera so every object is in the view field
     *
     * @return	true on success, false otherwise
     */
    const bool appendToScene( const QList<QString> filenames, const bool viewAllAfterLoading = true);

    vgQt::engine::UserSettingsDialog* getRenderSettingsDialog(QWidget* parent);

    const bool isEmpty() const;
    const bool reloadScene();

private:
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

    vgQt::engine::UserSettingsDialog* m_renderSettingsDialog; ///< rendering settings dialog
    QList<QString> m_filenames; ///< Contains the paths of the files currently loaded.

    void keyPressEvent(QKeyEvent * event);

Q_SIGNALS:
    void keyPressed(QKeyEvent * event);
};

} // namespace vgsdkViewerQt

#endif // _VGSDKVIEWERQT_MYCANVAS_HPP_
