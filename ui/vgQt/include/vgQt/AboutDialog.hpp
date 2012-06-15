// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#ifndef _VGQT_ABOUTDIALOG_HPP_
#define _VGQT_ABOUTDIALOG_HPP_

#include <QDialog>
#include <QList>
#include <QLabel>

#include "vgQt/vgQt.hpp"

namespace vgQt
{

/**
 * @brief	A simple About dialog, with customizable content
 */
class VGQT_API AboutDialog : public QDialog
{
Q_OBJECT

public:
    AboutDialog( QWidget* parent );

    void set_title( QString title );
    void set_authors( QList< QString > authors );
    void set_comments( QString comment );
    void set_copyright ( QString copyright );
    void set_license ( QString licence );
    void set_website ( QString website );

private:
    QLabel* m_title;
    QList< QString > m_authors;
    QLabel* m_comment;
    QLabel* m_copyright;
    QString m_licence;
    QLabel* m_website;

public Q_SLOTS:
    void onCredits();
    void onLicence();
};

} // namespace vgQt

#endif // _VGQT_ABOUTDIALOG_HPP_
