// VGSDK - Copyright (C) 2013, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGQT_ENGINE_RECORDSETTINGS_HPP_
#define _VGQT_ENGINE_RECORDSETTINGS_HPP_

#include <QCheckBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>

#include <vgd/Shp.hpp>

#include "vgQt/vgQt.hpp"

namespace vgUI
{
    struct Canvas;
}

namespace vgUI { namespace event { struct CaptureEventProcessor; } }


namespace vgQt
{

namespace engine
{

struct VGQT_API RecordSettings : public QVBoxLayout
{
Q_OBJECT
public:
    /**
     * @brief	Constructor
     */
    RecordSettings();

    /**
     * @brief	Assignes the canvas used for rendering
     *
     * @param	canvas	a pointer to a canvas, null if none
     */
    void setCanvas( vgUI::Canvas * canvas );

private:

    vgUI::Canvas *									m_canvas;					///< Points to the rendering canvas
	vgd::Shp< vgUI::event::CaptureEventProcessor >	m_captureEventProcessor;	///< Reference to the event processor used to start/stop capture
private Q_SLOTS:
    /**
     * @name	Signal Handlers
     */
    //@{
	void onCaptureFPS();
	void onActivate();
    //@}

private:
	QLineEdit	* m_captureFPS;			///< see Canvas::m_maxNumberOfCapturesPerSecond
    QCheckBox   * m_color;				///< Button to enable/disable color buffer recording
    QCheckBox	* m_depth;				///< Button to enable/disable depth buffer recording
    QCheckBox	* m_camera;				///< Button to enable/disable camera parameters recording

    QTextEdit	* m_shortcutkey;		///< Button to start/stop recording
	QCheckBox  * m_activate;
};

} // namespace engine

} // namespace vgQt

#endif // _VGQT_ENGINE_RECORDSETTINGS_HPP_
