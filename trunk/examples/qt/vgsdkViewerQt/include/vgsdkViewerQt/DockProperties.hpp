// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGSDKVIEWERQT_PROPERTIES_HPP_
#define _VGSDKVIEWERQT_PROPERTIES_HPP_

#include <vgQt/Notebook.hpp>

#include <QDockWidget>

namespace vgsdkViewerQt
{

struct MyCanvas;



/**
 * @brief	A widget that holds the vgSdk properties notebook and allows to request the widget to hide or close.
 */
class DockProperties : public QDockWidget
{
Q_OBJECT
public:
    /**
     * @brief	Constructor
     */
    DockProperties( QWidget* parent );

    /**
     * @brief	Assignes the canvas.
     */
    void setCanvas( MyCanvas *canvas );

protected:
    void hideEvent ( QHideEvent * event );
    void showEvent ( QShowEvent * event );

private:
    vgQt::Notebook* m_notebook;

Q_SIGNALS:
    void visibilityChanged();
};



} // namespace vgdkViewerQt



#endif // _VGSDKVIEWERQT_PROPERTIES_HPP_
