// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_ENGINE_SETTINGS_HPP_
#define _VGQT_ENGINE_SETTINGS_HPP_

#include <QHBoxLayout>
#include <QCheckBox>
#include <QPushButton>

#include "vgQt/vgQt.hpp"

namespace vgUI
{
    struct Canvas;
}


namespace vgQt
{

namespace engine
{

class VGQT_API Settings : public QVBoxLayout
{
Q_OBJECT

public:
    /**
     * @brief	Constructor
     */
    Settings();

    /**
     * @brief	Assignes the canvas used for rendering
     *
     * @param	canvas	a pointer to a canvas, null if none
     */
    void setCanvas( vgUI::Canvas * canvas );

private:

    vgUI::Canvas	* m_canvas;	///< Points to the rendering canvas.

private Q_SLOTS:
    /**
     * @name	Signal Handlers
     */
    //@{
    void onGLSL();

    void onDisableLighting();
    void onDisableTexture();
    void onDisableShadow();
    void onDisableDisplayList();
    void onDisableVBO();
    void onDisableDepthPrePass();

    void onBench();

    void onShowFPS();
    void onDebugEvents();
    void onClearGLResources();

    void onCaptureButton();
    //@}

private:
    QCheckBox   * m_glslButton;			///< Button to enable/disable glsl rendering pipeline

    QCheckBox	* m_disableLighting;	///< Button to disable lighting in engine
    QCheckBox	* m_disableTexture;		///< Button to disable texture in engine
    QCheckBox	* m_disableShadow;		///< Button to disable shadow in engine

    QCheckBox	* m_disableDisplayList;	///< Button to disable display list in engine
    QCheckBox	* m_disableVBO;			///< Button to disable VBO in engine
    QCheckBox	* m_disableDepthPrePass;///< Button to disable depth pre-pass in engine

    QCheckBox	* m_showFPS;			///< Widget to choose which debug overlay must be displayed
    QCheckBox	* m_debugEvents;		///< Button to enable/disable event logging
    QCheckBox	* m_captureButton;		///< Widget to enable screenshot/video capture hotkey

    QPushButton * m_benchButton;
    QPushButton * m_clearGLResourcesButton;
};

} // namespace engine

} // namespace vgQt

#endif // _VGQT_ENGINE_SETTINGS_HPP_
