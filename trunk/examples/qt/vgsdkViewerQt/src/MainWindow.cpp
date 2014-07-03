// VGSDK - Copyright (C) 2012, 2013, Guillaume Brocker, Bryan Schuller, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller
// Author Nicolas Papier

#include "vgsdkViewerQt/MainWindow.hpp"

#include <boost/lexical_cast.hpp>
#include <vgd/node/LightModel.hpp>
#include <vgTrian/Loader.hpp>
#include <vgObj/Loader.hpp>
#include <vgOpenAssetImport/Loader.hpp>
#include <vgQt/engine/RecordSettings.hpp>
#include <vgQt/engine/RecordSettingsDialog.hpp>
#include <vgQt/engine/UserSettingsDialog.hpp>
#include <vgQt/node/EditMenu.hpp>
#include <vgQt/ResolutionDialog.hpp>
#include <vgQt/AboutDialog.hpp>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QApplication>
#include <QToolBar>
#include <QFileDialog>
#include <QDockWidget>
#include <QUrl>
#include <QMessageBox>
#include <QFileDialog>
#include <QSettings>

#include "vgsdkViewerQt/actions.hpp"
#include "vgsdkViewerQt/PythonLoader.hpp"


namespace vgsdkViewerQt
{


WindowList MainWindow::m_windows;


MainWindow::MainWindow( MainWindow * sharedWindow )
:	QMainWindow(),
	m_isFullScreen(false),
	m_toolBar(0),
	m_actionProperties(0),
	m_actionMouseAndKeyboard(0),
	m_recentFileMenu(0),
	m_renderSettingsDialog(0),
	m_recordSettingsDialog(0),
	m_canvas( sharedWindow ? &sharedWindow->m_canvas : 0 )
{
	initialize();
}



void MainWindow::initialize()
{
	// Positionnates a flag so that the window gets destroyed when closed.
	setAttribute( Qt::WA_DeleteOnClose, true );

	// Updates the window list.
	m_windows.add( this );

	// The style for the treeView
	setStyleSheet("QTreeView::branch:has-siblings:!adjoins-item {border-image: url(:/images/stylesheet-vline.png) 0;}"
				  "QTreeView::branch:has-siblings:adjoins-item {border-image: url(:/images/stylesheet-branch-more.png) 0;}"
				  "QTreeView::branch:!has-children:!has-siblings:adjoins-item {border-image: url(:/images/stylesheet-branch-end.png) 0;}"
				  "QTreeView::branch:has-children:!has-siblings:closed,QTreeView::branch:closed:has-children:has-siblings {border-image: none;image: url(:/images/stylesheet-branch-closed.png);}"
				  "QTreeView::branch:open:has-children:!has-siblings,QTreeView::branch:open:has-children:has-siblings{border-image: none;image: url(:/images/stylesheet-branch-open.png);}"
				  );

	// The window
	resize(1024,768);
	setWindowTitle( QString("vgsdkViewerQt - %1").arg(m_windows.counter()) );
	setWindowIcon( QIcon(":/images/vgsdkViewerQt.ico") );
	setWindowIconText( "setWindowIconText" );
	setAcceptDrops(true);

	// The Menu bar in the top of the window
	QMenu *menuFile = menuBar()->addMenu("&File");
	vgQt::node::EditMenu* editMenu = new vgQt::node::EditMenu();
	menuBar()->addMenu(editMenu);
	QMenu *menuView = menuBar()->addMenu("&View");
	QMenu *menuSettings = menuBar()->addMenu("&Settings");
	QMenu *menuHelp = menuBar()->addMenu("&Help");
	m_recentFileMenu = new QMenu("Recent Files", this);

	// The toolbar
	m_toolBar = addToolBar("Toolbar");
	m_toolBar->setObjectName( "vgsdkViewerQt.Toolbar" );
	m_toolBar->setMovable(false);
	m_toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

	// The actions associated with the items menu
	QAction *actionNew = new QAction(QIcon(":/images/document-new.png"), "&New", this);
	QAction *actionOpen = new QAction(QIcon(":/images/document-open.png"), "&Open", this);
	QAction *actionAdd = new QAction(QIcon(":/images/list-add.png"), "&Add", this);
	QAction *actionReload = new QAction("Reload", this);
	QAction *actionQuit = new QAction(QIcon(":/images/application-exit.png"), "&Quit", this);
	QAction *actionViewAll = new QAction(QIcon(":/images/zoom-fit-best.png"), "View All", this);
	QAction *actionFullScreen = new QAction(QIcon(":/images/view-fullscreen.png"), "Full Screen", this);
	QAction *actionResolution = new QAction(QIcon(":/images/resolution.png"), "Set Resolution", this);
	QAction *actionShadersEditor = new QAction("Shader Editor", this);
	m_actionProperties = new QAction(QIcon(":/images/document-properties.png"), "&Properties", this);
	m_actionProperties->setCheckable(true);
	QAction *actionRenderSettings = new QAction(QIcon(":/images/document-properties.png"), "Render Settings", this);
	QAction * actionNewWindow = newNewWindowAction(this);
	// @todo Tango Desktop Project advertising (http://tango.freedesktop.org/Tango_Icon_Library)
	QAction *actionRecording = new QAction(QIcon(":/images/media-record.png"), "&Recording settings", this);

	QAction *actionAbout = new QAction(QIcon(":/images/help-about.png"), "&About", this);
	QAction *actionSingleView = new QAction(QIcon(":/images/single-view.png"), "Single View", this);
	actionSingleView->setCheckable(true);
	actionSingleView->setChecked(true);
	QAction *actionLeftSidedViews = new QAction(QIcon(":/images/multi-view-sided.png"), "Left-Sided Views", this);
	actionLeftSidedViews->setCheckable(true);
	QAction *actionFourViews = new QAction(QIcon(":/images/multi-view-squared.png"), "Four Views", this);
	actionFourViews->setCheckable(true);
	QAction *actionMouseOnly = new QAction("Mouse Only Manipulation", this);
	actionMouseOnly->setCheckable(true);
	m_actionMouseAndKeyboard = new QAction("Mouse & Keyboard Manipulation", this);
	m_actionMouseAndKeyboard->setCheckable(true);
	m_actionMouseAndKeyboard->setChecked(true);
	QActionGroup* manipulationGroup = new QActionGroup( this );
	manipulationGroup->addAction(actionMouseOnly);
	manipulationGroup->addAction(m_actionMouseAndKeyboard);

	QActionGroup* viewGroup = new QActionGroup( this );
	viewGroup->addAction(actionSingleView);
	viewGroup->addAction(actionLeftSidedViews);
	viewGroup->addAction(actionFourViews);

	// The shortcuts
	actionNew->setShortcut(QKeySequence("Ctrl+N"));
	actionOpen->setShortcut(QKeySequence("Ctrl+O"));
	actionReload->setShortcut(QKeySequence("Ctrl+R"));
	actionQuit->setShortcut(QKeySequence("Ctrl+Q"));
	actionFullScreen->setShortcut(QKeySequence("F11"));
	actionShadersEditor->setShortcut(QKeySequence("Ctrl+Shift+S"));

	menuFile->addAction(actionNew);
	menuFile->addAction(actionOpen);
	menuFile->addAction(actionAdd);
	menuFile->addMenu(m_recentFileMenu);
	QAction* actionEmpty = new QAction("Empty", m_recentFileMenu);
	actionEmpty->setDisabled(true);
	m_recentFileMenu->addAction(actionEmpty);
	menuFile->addAction(actionReload);
	menuFile->addAction(actionQuit);
	menuView->addAction(actionShadersEditor);
	menuView->addAction(m_actionProperties);
	menuView->addSeparator();
	menuView->addAction(actionViewAll);
	menuView->addAction(actionFullScreen);
	menuView->addAction(actionResolution);
	menuView->addSeparator();

	menuView->addAction(actionSingleView);
	menuView->addAction(actionLeftSidedViews);
	menuView->addAction(actionFourViews);

	menuSettings->addAction(actionMouseOnly);
	menuSettings->addAction(m_actionMouseAndKeyboard);
	menuSettings->addSeparator();
	menuSettings->addAction(actionRenderSettings);
	menuSettings->addSeparator();
	menuSettings->addAction(actionRecording);

	menuHelp->addAction(actionAbout);

	m_toolBar->addAction(actionNew);
	m_toolBar->addAction(actionOpen);
	m_toolBar->addAction(actionAdd);
	m_toolBar->addSeparator();
	m_toolBar->addAction(m_actionProperties);
	m_toolBar->addAction(actionRenderSettings);
	m_toolBar->addSeparator();
	m_toolBar->addAction(actionViewAll);
	m_toolBar->addAction(actionFullScreen);
	m_toolBar->addAction(actionResolution);
	m_toolBar->addSeparator();
	m_toolBar->addAction(actionSingleView);
	m_toolBar->addAction(actionLeftSidedViews);
	m_toolBar->addAction(actionFourViews);
	m_toolBar->addSeparator();
	m_toolBar->addAction(actionNewWindow);
	m_toolBar->addSeparator();
	m_toolBar->addAction(actionRecording);
	m_toolBar->addSeparator();
	m_toolBar->addAction(actionAbout);

	// if the toobar is hidden (in fullscreen mode), the QActions are disabled, so we add them to the MainWindow
	addAction(actionNew);
	addAction(actionOpen);
	addAction(actionQuit);
	addAction(actionFullScreen);
	Q_FOREACH(QAction* action, editMenu->findChildren<QAction*>())
	{
		addAction(action);
	}

	// We connect the actions with the buttons

	// File Menu
	connect(actionNew, SIGNAL(triggered()), this, SLOT(fileNew()));
	connect(actionOpen, SIGNAL(triggered()), this, SLOT(fileOpen()));
	connect(actionAdd, SIGNAL(triggered()), this, SLOT(addFile()));
	connect(actionReload, SIGNAL(triggered()), this, SLOT(fileReload()));
	connect(actionQuit, SIGNAL(triggered()), &m_windows, SLOT(closeAll()));

	// View Menu
	connect(m_actionProperties, SIGNAL(triggered()), this, SLOT(showHideProperties()));
	connect(actionViewAll, SIGNAL(triggered()), this, SLOT(viewAll()));
	connect(actionFullScreen, SIGNAL(triggered()), this, SLOT(fullscreen()));
	connect(actionResolution, SIGNAL(triggered()), this, SLOT(setResolution()));
	connect(actionSingleView, SIGNAL(triggered()), this, SLOT(singleView()));
	connect(actionLeftSidedViews, SIGNAL(triggered()), this, SLOT(leftSidedViews()));
	connect(actionFourViews, SIGNAL(triggered()), this, SLOT(fourViews()));

	// Settings Menu
	connect(actionMouseOnly, SIGNAL(triggered()), this, SLOT(settingManipulationBinding()));
	connect(m_actionMouseAndKeyboard, SIGNAL(triggered()), this, SLOT(settingManipulationBinding()));
	connect(actionRenderSettings, SIGNAL(triggered()), this, SLOT(renderSettings()));
	connect(actionRecording, SIGNAL(triggered()), this, SLOT(recordingSettings()));

	// Window Menu
	connect(actionNewWindow, SIGNAL(triggered()), this, SLOT(newWindow()));

	// Help Menu
	connect(actionAbout, SIGNAL(triggered()), this, SLOT(helpAbout()));

	setCentralWidget(&m_canvas);

	m_properties = new vgsdkViewerQt::DockProperties(this);
	m_properties->setCanvas(&m_canvas) ;

	connect(actionShadersEditor, 
			SIGNAL(triggered()), 
			m_properties->getShaderEditor(), 
			SLOT(changeVisibility()));

	addDockWidget(Qt::LeftDockWidgetArea, m_properties);

	connect(m_properties, SIGNAL(visibilityChanged()), this, SLOT(onPropertiesVisibilityChanged()));

	readSettings();
}


void MainWindow::newWindow()
{
	MainWindow * newWindow = new MainWindow( this );

	// Shared the scene
	newWindow->m_canvas.setScene( m_canvas.getScene() );

	//
	newWindow->show();
}


void MainWindow::showFullScreen()
{
	menuBar()->setVisible(false);
	m_toolBar->setVisible(false);
	QMainWindow::showFullScreen();
}


void MainWindow::showNormal()
{
	menuBar()->setVisible(true);
	m_toolBar->setVisible(true);
	QMainWindow::showNormal();
}


vgQt::engine::UserSettingsDialog * MainWindow::getRenderSettingsDialog()
{
	if( !m_renderSettingsDialog )
	{
		m_renderSettingsDialog = new vgQt::engine::UserSettingsDialog(this);
		m_renderSettingsDialog->set( vgd::makeShp(new vge::engine::UserSettings(m_canvas)) );
		connect( m_renderSettingsDialog, SIGNAL(changed()), this, SLOT(renderSettingsChanged()) );
	}

	return m_renderSettingsDialog;
}


vgQt::engine::RecordSettingsDialog * MainWindow::getRecordSettingsDialog()
{
	if( !m_recordSettingsDialog )
	{
		m_recordSettingsDialog = new vgQt::engine::RecordSettingsDialog(this);
		m_recordSettingsDialog->getGUI()->setCanvas( &m_canvas );
	}

	return m_recordSettingsDialog;
}



void MainWindow::fileNew()
{
	QMessageBox* messageDialog = new QMessageBox(this);
	messageDialog->setWindowTitle("");
	messageDialog->setText("Reset the content of the current scene ?");
	messageDialog->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	messageDialog->setIcon(QMessageBox::Question);

	if(messageDialog->exec() == QMessageBox::Yes)
	{
		//m_canvas.clearScene();
		m_canvas.resetSceneGraph();
		m_canvas.createOptionalNodes();
		m_properties->setCanvas(&m_canvas);

		m_canvas.refresh();
	}
}


void MainWindow::fileOpen()
{
	loadFile(true);
}


void MainWindow::addFile()
{
	loadFile(false);
}


void MainWindow::fileReload()
{
	if ( !m_canvas.isEmpty() )
	{
		m_canvas.reloadScene();
		m_canvas.refresh();
	}
}


void MainWindow::showHideProperties()
{
	m_properties->isVisible() ? m_properties->setVisible(false) : m_properties->setVisible(true);
}


void MainWindow::viewAll()
{
	m_canvas.viewAll();
	m_canvas.refresh();
}


void MainWindow::fullscreen()
{
	const bool isFullscreen = m_canvas.isFullscreen();
	
	m_canvas.switchFullscreen();
	// Configures the layout.
	isFullscreen ? showNormal() : showFullScreen();
}


void MainWindow::setResolution()
{
	vgQt::ResolutionDialog dialog( this );
	dialog.exec();
}


void MainWindow::singleView()
{
	m_canvas.setViewMode(MyCanvas::SINGLE_VIEW);
}


void MainWindow::leftSidedViews()
{
	m_canvas.setViewMode(MyCanvas::LEFT_SIDED_VIEWS);
}


void MainWindow::fourViews()
{
	m_canvas.setViewMode(MyCanvas::SQUARED_VIEWS);
}


void MainWindow::settingManipulationBinding()
{
	int binding = 0;
	binding = m_actionMouseAndKeyboard->isChecked() ? 1 : 2;
	switch( binding )
	{
		case 1:
			m_canvas.getSceneTransformation()->setBindingsToDefaults();
			break;

		case 2:
			m_canvas.getSceneTransformation()->setBindingsToDefaults2();
			break;

		default:
			vgLogWarning( "Invalid manipulation binding specified." );
	}
}


void MainWindow::renderSettings()
{
	getRenderSettingsDialog()->get()->setLevel( m_canvas );
	getRenderSettingsDialog()->getGUI()->refreshLevel();
	getRenderSettingsDialog()->show();
}


void MainWindow::renderSettingsChanged()
{
	getRenderSettingsDialog()->get()->apply( m_canvas );
	m_canvas.refresh();
}


void MainWindow::recordingSettings()
{
	getRecordSettingsDialog()->setVisible( !getRecordSettingsDialog()->isVisible() );
}


void MainWindow::helpAbout()
{
	vgQt::AboutDialog aboutDialog(this);

	QList<QString>	authors;
	authors.append( QString("Guillaume Brocker") );
	authors.append( QString("Nicolas Papier") );
	authors.append( QString("Maxime Peresson") );
	authors.append( QString("Bryan Schuller") );

	aboutDialog.set_title( QString("vgsdkViewerQt") );
	aboutDialog.set_authors( authors );
	aboutDialog.set_comments( QString("This program is a simple demonstration of vgSDK capabilities.\n It allows you to load meshes (obj, trian, trian2 and dae),\n manipulate them and browse the rendering scene graph.") );
	aboutDialog.set_copyright( QString("Copyright (C) 2008-2013, Guillaume Brocker, Nicolas Papier, Maxime Peresson, Bryan Schuller and Digital Trainers SAS.") );
	aboutDialog.set_license( QString("Distributed under the terms of the GNU Library General Public License (LGPL) as published by the Free Software Foundation.") );
	aboutDialog.set_website( QString("http://code.google.com/p/vgsdk") );

	aboutDialog.exec();
}



void MainWindow::onPropertiesVisibilityChanged()
{
	m_properties->isVisible() ? m_actionProperties->setChecked(true) : m_actionProperties->setChecked(false);
}


void MainWindow::onHistoryClicked()
{
	QAction* action = (QAction*) sender();

	m_canvas.clearScene();

	m_canvas.appendToScene(action->text(), false);
	addFileInHistory(action->text());

	m_canvas.viewAll();
	m_canvas.refresh( vgUI::Canvas::REFRESH_FORCE, vgUI::Canvas::SYNCHRONOUS );
}


void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
	event->acceptProposedAction();
}


void MainWindow::dropEvent(QDropEvent *event)
{
	if (event->mimeData()->hasUrls())
	{
		QMessageBox* dialog = new QMessageBox();
		dialog->setText("Clear scene prior loading new files ?");
		dialog->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
		dialog->setDefaultButton(QMessageBox::No);

		if(dialog->exec() == QMessageBox::Yes)
		{
			m_canvas.clearScene();
		}

		Q_FOREACH(QUrl url, event->mimeData()->urls())
		{
			QString path = url.path().remove(0,1);
			m_canvas.appendToScene(path, false);
		
			addFileInHistory(path);
		}

		m_canvas.viewAll();
		m_canvas.refresh( vgUI::Canvas::REFRESH_FORCE, vgUI::Canvas::SYNCHRONOUS );
	}
}


void MainWindow::closeEvent(QCloseEvent *event)
{
	m_windows.remove( this );
	writeSettings();
	m_properties->getShaderEditor()->close();
	QMainWindow::closeEvent(event);
}


void MainWindow::loadFile(bool clearScene)
{
	vgTrian::Loader				loader;		// @todo must be here to be registered in LoaderRegistry
	vgObj::Loader				loader2;	// This is only to force the register of obj loader
	vgOpenAssetImport::Loader	loader3;	// This is only to force the register of assimp loader

	// Prompts a file selection dialog to the user.
	static QString		dir;
	const QStringList	files = QFileDialog::getOpenFileNames(
							this,
							"Choose file(s)",
							dir,
							"All supported files (*.dae *.blend *.3ds *.obj *.trian *.trian2 *.py);;All collada files (*.dae);;Wavefront objects (*.obj);;Trian files (*.trian, *.trian2);;All files (*.*)" );

	// Loads files selected by the user.
	if( !files.empty() )
	{
		// Clears the canvas if requested.
		if( clearScene )
		{
			m_canvas.clearScene();
		}

		// Keep track of the directory where the files are located,
		// so the next time the dialog is prompted, it will be pointing at tha location.
		dir = QDir::fromNativeSeparators( files.front() );
		dir = dir.section( '/', 0, -2 );

		Q_FOREACH(QString fileName, files)
		{
			bool success = false;
			success = m_canvas.appendToScene( fileName );
			if (success)
			{
				// We add it in the recent file history
				addFileInHistory(fileName);
			}
		}
	}
}


void MainWindow::addFileInHistory( const QString filename, const bool addAtTheBeginning )
{
	QString lFilename(filename);
	lFilename.replace("\\","/");

	// Removes any action named filename or "Empty"
	Q_FOREACH(QAction* action, m_recentFileMenu->actions())
	{
		if (action->text() == lFilename || action->text() == "Empty")
		{
			m_recentFileMenu->removeAction(action);
		}
	}

	// maxRecentScenes files in the history
	if(m_recentFileMenu->actions().size() == maxRecentScenes)
	{
		m_recentFileMenu->removeAction(m_recentFileMenu->actions().last());
	}

	// New action for filename
	QAction* action = new QAction(lFilename, m_recentFileMenu);
	if ( addAtTheBeginning )
	{
		if ( m_recentFileMenu->actions().size() > 0 )
		{
			m_recentFileMenu->insertAction(m_recentFileMenu->actions().first(), action);
		}
		else
		{
			m_recentFileMenu->addAction(action);
		}
	}
	else
	{
		m_recentFileMenu->addAction(action);
	}

	// Removes shortcuts
	int i = 1;
	Q_FOREACH(QAction* action, m_recentFileMenu->actions())
	{
		const std::string seq( "Ctrl+" + boost::lexical_cast<std::string>(i) );
		action->setShortcut( QKeySequence(seq.c_str()) );
		++i;
	}

	//
	connect(action, SIGNAL(triggered()), this, SLOT(onHistoryClicked()));
}


void MainWindow::readSettings()
{
    QSettings settings("vgsdk", "vgsdkViewerQt");

    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("state").toByteArray());

	// Path of the recent scenes
	QStringList recentScenes = settings.value("recentScenes").toStringList();
	Q_FOREACH(QString filename, recentScenes)
	{
		addFileInHistory(filename, false/*addAtTheEnd*/);
	}
}


void MainWindow::writeSettings()
{
    QSettings settings("vgsdk", "vgsdkViewerQt");

    settings.setValue("geometry", saveGeometry());
    settings.setValue("state", saveState());

	//
	QStringList recentScenes;
	Q_FOREACH(QAction* action, m_recentFileMenu->actions())
	{
		if (action->text() != "Empty")
		{
			recentScenes << action->text();
		}
	}
    settings.setValue("recentScenes", recentScenes);
}


} // namespace vgsdkViewerQt
