// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include <vgsdkViewerQt/MainWindow.hpp>

#include <sbf/log/GlobalLogger.hpp>
#include <sbf/log/Logging.hpp>

#include <vgQt/engine/UserSettingsDialog.hpp>
#include <QApplication>




int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Installs the GTK-based logging.
    sbf::log::set< sbf::log::Logging >();

    vgsdkViewerQt::MainWindow mainWindow;
	mainWindow.setWindowIcon( QIcon(":/images/vgsdkViewerQt.ico") );
	mainWindow.setWindowIconText( "setWindowIconText" );

	mainWindow.show();
	mainWindow.getRenderSettingsDialog()->get()->setLevel(2);
	mainWindow.renderSettingsChanged();

    return app.exec();
}
