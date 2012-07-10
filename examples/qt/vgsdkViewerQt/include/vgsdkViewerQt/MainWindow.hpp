// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGSDKVIEWERQT_MAINWINDOW_HPP
#define _VGSDKVIEWERQT_MAINWINDOW_HPP

#include <vgQt/graph/Browser.hpp>
#include "vgsdkViewerQt/MyCanvas.hpp"
#include "vgsdkViewerQt/DockProperties.hpp"
#include <vgQt/engine/ShadersEditor.hpp>
#include <QMainWindow>
#include <QDockWidget>

namespace vgsdkViewerQt
{

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    void showFullScreen();
    void showNormal();
    void addFileInHistory(QString filename);

Q_SIGNALS:

public Q_SLOTS:

    /**
     * @brief	Implements the file/open action
     */
    void fileOpen();

    /**
     * @brief	Implements an action that will recenter the camera on the objects visible in the scene.
     */
    void viewAll();

    /**
     * @brief	Implements the file/add action
     */
    void addFile();

    /**
     * @brief	Implements the file/new action.
     *
     * This will ask the user to confirm the reset of the scene, and if confirmed, will
     * remove all objects.
     */
    void fileNew();

    /**
     * @brief	Implements an action that reloads all objects currently in the canvas.
     */
    void fileReload();

    /**
     * @brief	Shows/hides the vgSdk properties widget.
     */
    void showHideProperties();

	void showShadersEditor();
	
    /**
     * @brief	Configure user engine's settings
     */
    void renderSettings();

    /**
     * @brief	Updates the resolution of the window.
     */
    void setResolution();

    /**
     * @brief	Implements an action that show the about box on top of the top level window.
     */
    void helpAbout();

    /**
     * @brief	Implements an action that shows the canvas in full screen
     */
    void fullscreen();


    void onSingleView();
    void onLeftSidedViews();
    void onFourViews();

    /**
     * @brief	Implements an action that updates the properties button according to the visibility changes of the properties widget
     */
    void onPropertiesVisibilityChanged();

    /**
     * @brief	Updates the manipulation bindings of the canvas
     */
    void settingManipulationBinding();

    /**
     * @brief	Implements an action that will load a file from the recent chooser menu.
     */
    void onHistoryClicked();

    /**
     * @brief	Handle the Escape key event when the canvas is in fullscreen
     */
    void onKeyPressed(QKeyEvent* event);

protected:
    /**
     * @name Drag&Drop handler
     */
    //@{
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    //@}

    /**
     * @brief	Replaces or append objects in the canvas
     *
     * This will ask the user to chose one or more objects to load
     */
    void loadFile( bool clearScene );
    void closeEvent(QCloseEvent *event);
	
private:
    vgsdkViewerQt::DockProperties*  m_properties;
    MyCanvas*                       m_canvas;
    bool                            m_isFullScreen;

    QToolBar*						m_toolBar;
    QAction*						m_actionProperties;
    QAction*						m_actionMouseAndKeyboard;
    QMenu*							m_recentFileMenu;
	vgQt::engine::ShadersEditor*	m_shaderEditor;
};

} // namespace vgsdkViewerQt

#endif // _VGSDKVIEWERQT_MAINWINDOW_HPP
