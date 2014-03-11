// VGSDK - Copyright (C) 2012, 2013, Guillaume Brocker, Bryan Schuller, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller
// Author Nicolas Papier

#include <vgsdkViewerQt/MainWindow.hpp>

#include <displayDriverConnector/displayDriverConnector.hpp>

#include <sbf/debug.hpp>
#include <sbf/log/GlobalLogger.hpp>
#include <sbf/log/Logging.hpp>
#include <sbf/pkg/Module.hpp>

#include <vgQt/engine/UserSettingsDialog.hpp>
#include <QApplication>



int main(int argc, char *argv[])
{
	// Retrieves and prints informations about primary display adapter
	ddc_display_device_info_t displayDevice;
	ddc_get_primary_display_device_informations( &displayDevice );

	ddc_print_display_device_info( &displayDevice );

	// Installs an exception handler to generate core dump file.
	//sbf::installToplevelExceptionHandler( sbf::CoreFull );
	sbf::installToplevelExceptionHandler( sbf::CoreNormal, sbf::pkg::Module::get()->getPath(sbf::pkg::VarPath) );

	//
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
