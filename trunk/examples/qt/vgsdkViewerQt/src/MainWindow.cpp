// VGSDK - Copyright (C) 2012, Guillaume Brocker, Bryan Schuller
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Guillaume Brocker
// Author Bryan Schuller

#include "vgsdkViewerQt/MainWindow.hpp"
#include "vgsdkViewerQt/MyCanvas.hpp"

#include <vgd/node/LightModel.hpp>
#include <vgTrian/Loader.hpp>
#include <vgObj/Loader.hpp>
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

namespace vgsdkViewerQt
{

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_isFullScreen(false)
{
    // The style for the treeView
    setStyleSheet("QTreeView::branch:has-siblings:!adjoins-item {border-image: url(:/images/stylesheet-vline.png) 0;}"
                  "QTreeView::branch:has-siblings:adjoins-item {border-image: url(:/images/stylesheet-branch-more.png) 0;}"
                  "QTreeView::branch:!has-children:!has-siblings:adjoins-item {border-image: url(:/images/stylesheet-branch-end.png) 0;}"
                  "QTreeView::branch:has-children:!has-siblings:closed,QTreeView::branch:closed:has-children:has-siblings {border-image: none;image: url(:/images/stylesheet-branch-closed.png);}"
                  "QTreeView::branch:open:has-children:!has-siblings,QTreeView::branch:open:has-children:has-siblings{border-image: none;image: url(:/images/stylesheet-branch-open.png);}"
                  );

    // The window
    resize(1024,768);
    setWindowTitle(tr("VgsdkViewerQt"));
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
    QAction *actionResolution = new QAction(QIcon(":/images/resolution-16.xpm"), "Set Resolution", this);
	QAction *actionShadersEditor = new QAction("Shader Editor", this);
    m_actionProperties = new QAction(QIcon(":/images/document-properties.png"), "&Properties", this);
    m_actionProperties->setCheckable(true);
    QAction *actionRenderSettings = new QAction(QIcon(":/images/document-properties.png"), "Render Settings", this);
    QAction *actionAbout = new QAction(QIcon(":/images/help-about.png"), "&About", this);
    QAction *actionSingleView = new QAction(QIcon(":/images/single-view-16.xpm"), "Single View", this);
    actionSingleView->setCheckable(true);
    actionSingleView->setChecked(true);
    QAction *actionLeftSidedViews = new QAction(QIcon(":/images/multi-view-sided-16.xpm"), "Left-Sided Views", this);
    actionLeftSidedViews->setCheckable(true);
    QAction *actionFourViews = new QAction(QIcon(":/images/multi-view-squared-16.xpm"), "Four Views", this);
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

    menuHelp->addAction(actionAbout);

    m_toolBar->setIconSize(QSize(16,16));
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
    connect(actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));

    // View Menu
    connect(m_actionProperties, SIGNAL(triggered()), this, SLOT(showHideProperties()));
    connect(actionViewAll, SIGNAL(triggered()), this, SLOT(viewAll()));
    connect(actionFullScreen, SIGNAL(triggered()), this, SLOT(fullscreen()));
    connect(actionResolution, SIGNAL(triggered()), this, SLOT(setResolution()));
    connect(actionSingleView, SIGNAL(triggered()), this, SLOT(onSingleView()));
    connect(actionLeftSidedViews, SIGNAL(triggered()), this, SLOT(onLeftSidedViews()));
    connect(actionFourViews, SIGNAL(triggered()), this, SLOT(onFourViews()));

	// Settings Menu
    connect(actionMouseOnly, SIGNAL(triggered()), this, SLOT(settingManipulationBinding()));
    connect(m_actionMouseAndKeyboard, SIGNAL(triggered()), this, SLOT(settingManipulationBinding()));
    connect(actionRenderSettings, SIGNAL(triggered()), this, SLOT(renderSettings()));

    // Help Menu
    connect(actionAbout, SIGNAL(triggered()), this, SLOT(helpAbout()));

    m_canvas = new vgsdkViewerQt::MyCanvas();
    setCentralWidget(m_canvas);

    m_properties = new vgsdkViewerQt::DockProperties(this);
    m_properties->setCanvas(m_canvas) ;

	connect(actionShadersEditor, 
			SIGNAL(triggered()), 
			m_properties->getShaderEditor(), 
			SLOT(changeVisibility()));

    addDockWidget(Qt::LeftDockWidgetArea, m_properties);

    connect(m_properties, SIGNAL(visibilityChanged()), this, SLOT(onPropertiesVisibilityChanged()));
    connect(m_canvas, SIGNAL(key(QKeyEvent*)), this, SLOT(onKeyPressed(QKeyEvent*)));
}

void MainWindow::fileOpen()
{
    loadFile(true);
}

void MainWindow::addFile()
{
    loadFile(false);
}

void MainWindow::loadFile(bool clearScene)
{
    vgTrian::Loader loader; // @todo must be here to be registered in LoaderRegistry
    vgObj::Loader loader2; // This is only to force the register of obj loader

    QStringList file = QFileDialog::getOpenFileNames(
                            this,
                            "Choose file(s)",
                            "",
                "All supported files (*.trian *.trian2 *.trian2.cryp *.dae *.dae.crypt *.obj *.vgarch);;Trian files (*.trian, *.trian2, *.trian2.crypt);;All collada files (*.dae, *.dae.crypt);;Wavefront objects (*.obj);;Vgsdk compressed files (*.vgarch)");
    if(file.size() > 0)
    {
        // Clears the canvas if requested.
        if( clearScene )
        {
            m_canvas->clearScene();
        }

        Q_FOREACH(QString fileName, file)
        {
            bool success = false;
            success = m_canvas->appendToScene( fileName );
            if (success)
            {
                // We add it in the recent file history
                addFileInHistory(fileName);
            }
        }
    }
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
        m_canvas->clearScene();
        m_canvas->refresh();
    }
}

void MainWindow::fileReload()
{
    if ( !m_canvas->isEmpty() )
    {
        m_canvas->reloadScene();
        m_canvas->refresh();
    }
}

void MainWindow::viewAll()
{
    m_canvas->viewAll();
    m_canvas->refresh();
}

void MainWindow::fullscreen()
{
    const bool isFullscreen = m_canvas->isFullscreen();
    m_canvas->switchFullscreen();
    // Configures the layout.
    if ( isFullscreen )
    {
        // Exit fullscreen mode
        showNormal();
    }
    else
    {
        // Enter fullscreen mode
        showFullScreen();
    }
}

void MainWindow::showFullScreen()
{
    menuBar()->setVisible(false);
    m_toolBar->setVisible(false);
    QMainWindow::showFullScreen();
    m_canvas->showFullScreen();
}

void MainWindow::showNormal()
{
    menuBar()->setVisible(true);
    m_toolBar->setVisible(true);
    QMainWindow::showNormal();
}

void MainWindow::settingManipulationBinding()
{
    int binding = 0;
    binding = m_actionMouseAndKeyboard->isChecked() ? 1 : 2;
    switch( binding )
    {
        case 1:
            m_canvas->getSceneTransformation()->setBindingsToDefaults();
            break;

        case 2:
            m_canvas->getSceneTransformation()->setBindingsToDefaults2();
            break;

        default:
            vgLogWarning( "Invalid manipulation binding specified." );
    }
}

void MainWindow::renderSettings()
{
    vgQt::engine::UserSettingsDialog* renderSettings = m_canvas->getRenderSettingsDialog(this);

    // Show or hide dialog
    if( renderSettings->isVisible() )
    {
        renderSettings->setVisible(false);
    }
    else
    {
        renderSettings->setVisible(true);
    }
}

void MainWindow::setResolution()
{
    vgQt::ResolutionDialog*	dialog = new vgQt::ResolutionDialog( this );
    dialog->exec();
}

void MainWindow::showHideProperties()
{
    m_properties->isVisible() ? m_properties->setVisible(false) : m_properties->setVisible(true);
}

void MainWindow::onPropertiesVisibilityChanged()
{
    m_properties->isVisible() ? m_actionProperties->setChecked(true) : m_actionProperties->setChecked(false);
}

void MainWindow::onSingleView()
{
    m_canvas->setViewMode(MyCanvas::SINGLE_VIEW);
}

void MainWindow::onLeftSidedViews()
{
    m_canvas->setViewMode(MyCanvas::LEFT_SIDED_VIEWS);
}

void MainWindow::onFourViews()
{
    m_canvas->setViewMode(MyCanvas::SQUARED_VIEWS);
}

void MainWindow::helpAbout()
{
    vgQt::AboutDialog* aboutDialog = new vgQt::AboutDialog(this);

    QList<QString>	authors;
    authors.append( QString("Guillaume Brocker") );
    authors.append( QString("Nicolas Papier") );
    authors.append( QString("Maxime Peresson") );
    authors.append( QString("Bryan Schuller") );


    aboutDialog->set_title( QString("VgsdkViewerQt") );
    aboutDialog->set_authors( authors );
    aboutDialog->set_comments( QString("This program is a simple demonstration of vgSDK capabilities.\n It allows you to load meshes (obj, trian, trian2 and dae),\n manipulate them and browse the rendering scene graph.") );
    aboutDialog->set_copyright( QString("Copyright (C) 2008-2012, Guillaume Brocker, Nicolas Papier, Maxime Peresson, Bryan Schuller and Digital Trainers SAS.") );
    aboutDialog->set_license( QString("Distributed under the terms of the GNU Library General Public License (LGPL) as published by the Free Software Foundation.") );
    aboutDialog->set_website( QString("http://code.google.com/p/vgsdk") );

    aboutDialog->exec();
}

void MainWindow::onHistoryClicked()
{
    QAction* action = (QAction*) sender();

    QMessageBox* dialog = new QMessageBox();
    dialog->setText("Clear scene prior loading new files ?");
    dialog->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    dialog->setDefaultButton(QMessageBox::No);

    if(dialog->exec() == QMessageBox::Yes)
    {
        m_canvas->clearScene();
    }

    m_canvas->appendToScene(action->text(), false);
    addFileInHistory(action->text());

    m_canvas->viewAll();
    m_canvas->doRefresh();
}

void MainWindow::onKeyPressed(QKeyEvent* event)
{
    if( m_canvas->isFullscreen() && event->key() == Qt::Key_Escape)
    {
        fullscreen();
    }
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
            m_canvas->clearScene();
        }

        Q_FOREACH(QUrl url, event->mimeData()->urls())
        {
            QString path = url.path().remove(0,1);
            m_canvas->appendToScene(path, false);
            addFileInHistory(path);
        }

        m_canvas->viewAll();
        m_canvas->doRefresh();
    }
}

void MainWindow::addFileInHistory(QString filename)
{
    filename.replace("\\","/");

    Q_FOREACH(QAction* action, m_recentFileMenu->actions())
    {
        if (action->text() == filename || action->text() == "Empty")
        {
            m_recentFileMenu->removeAction(action);
        }
    }

    // Max 10 files in the history
    if(m_recentFileMenu->actions().size() == 10)
    {
        m_recentFileMenu->removeAction(m_recentFileMenu->actions().last());
    }

    QAction* action = new QAction(filename, m_recentFileMenu);
    if(m_recentFileMenu->actions().size() > 0)
    {
        m_recentFileMenu->insertAction(m_recentFileMenu->actions().first(), action);
    }
    else
    {
        m_recentFileMenu->addAction(action);
    }
    connect(action, SIGNAL(triggered()), this, SLOT(onHistoryClicked()));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	m_properties->getShaderEditor()->close();
}

} // namespace vgsdkViewerQt
