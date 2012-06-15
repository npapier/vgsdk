// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_RESOLUTIONDIALOG_HPP_
#define _VGQT_RESOLUTIONDIALOG_HPP_

#include <QMainWindow>
#include <QDialog>
#include <QComboBox>
#include <QPushButton>

#include "vgQt/vgQt.hpp"

namespace vgQt
{


class VGQT_API ResolutionDialog : public QDialog
{
Q_OBJECT
public:
    /**
     * @brief	Constructor
     *
     * @param	widget	a pointer to the widget to change its resolution
     */
    ResolutionDialog( QMainWindow* widget );

private:

    /**
     * @name	Edition widgets
     */
    //@{
    QPushButton*				m_resetButton;	///< Allows to reset the widget to its original size.
    QPushButton*				m_applyButton;	///< Allows to apply the desired resolution.
    QComboBox*              	m_resolutions;	///< Allows the user to define a resolution.
    //@}

    /**
     * @name	Widget whose resolution is being edited
     */
    //@{
    QMainWindow*					m_widget;			///< Points to the widget o edit.
    const std::pair< int, int >	m_oldResolution;        ///< Holds the original widget resolution.
    std::pair< int, int >		m_newResolution;        ///< Holds the resolution to apply on the widget.
    //@}

    void applyResolution( const int width, const int height );  ///< Applies the resolution of the widget.

    /**
     * @name	Helpers
     */
    //@{
    static const bool resolutionFromString( QString text, int &width, int &height );    ///< Parses the given string to extract the resolution and tells if it succeeded.
    static const QString resolutionToString( const int width, const int height );		///< Builds the string representing the given resolution.
    //@}

public Q_SLOTS:
    /**
     * @name	Signal handlers
     */
    //@{
    void applyClicked();
    void resetClicked();
    void resolutionChanged(QString text);
    //@}
};



} // namespace vgGTK



#endif // _VGQT_RESOLUTIONDIALOG_HPP_
