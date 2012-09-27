// VGSDK - Copyright (C) 2012, Alexandre Di Pino
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Alexandre Di Pino

#include "vgQt/TextEditorMainWindow.hpp"
#include "vgQt/Theme.hpp"
#include <QColor>
#include <QLabel>
#include <QMenuBar>
#include <QVBoxLayout>
 #include <QComboBox>
#include <sstream>
#include <vector>

#ifdef WIN32
	#include <windows.h>
#endif


namespace vgQt
{



TextEditorMainWindow::TextEditorMainWindow(const std::string& title, QWidget* parent)
:	m_findMenu( new QWidget(this)),
	m_goToMenu( new QWidget(this)),
	m_styleMenu( new QWidget(this)),
	m_textEditor( new Editor(this)),
	m_newText(false)
{
	setWindowTitle(tr(title.c_str()));

	createFindAndReplaceMenu();
	createGoToLineMenu();
	createStyleConfigurator();

	setCentralWidget(m_textEditor);

	m_file = menuBar()->addMenu("&File");
	QAction* menuQuit = m_file->addAction("&Exit");
	menuQuit->setShortcut(QKeySequence("Ctrl+Q"));

	m_edit = menuBar()->addMenu("&Edit");
	QAction* menuFindReplace = m_edit->addAction("&Find/Replace");
	menuFindReplace->setShortcut(QKeySequence("Ctrl+F"));

	QAction* menuGoToLine = m_edit->addAction("&Go To...");
	menuGoToLine->setShortcut(QKeySequence("Ctrl+G"));

	QAction* menuStyle = m_edit->addAction("&Style Configurator...");

	m_menuStayTop = m_edit->addAction("&Always on Top");
	m_menuStayTop->setCheckable(true);

	connect(menuQuit, SIGNAL(triggered()), this, SLOT(close()));
	connect(menuFindReplace, SIGNAL(triggered()), this, SLOT(findAndReplaceMenu()));
	connect(menuGoToLine, SIGNAL(triggered()), this, SLOT(goToMenu()));
	connect(m_menuStayTop, SIGNAL(toggled(bool)) , this, SLOT(onTop(bool)));
	connect(menuStyle, SIGNAL(triggered(bool)), this, SLOT(onStyleConfigurator()));
}



void TextEditorMainWindow::createFindAndReplaceMenu()
{
	m_findMenu->setWindowFlags(Qt::Window);
	m_findMenu->setWindowTitle("Find/Replace");

	QVBoxLayout* layout = new QVBoxLayout;
	QLabel* findLabel = new QLabel("Find what:", m_findMenu);
	QLabel* replaceLabel = new QLabel("Replace with:", m_findMenu);
	m_findText = new QLineEdit(this);
	m_replaceText = new QLineEdit(this);
	m_findAction = new QPushButton("Find Next", this);
	m_replaceAction = new QPushButton("Replace", this);
	m_replaceAllAction = new QPushButton("Replace All", this);

	layout->addWidget(findLabel);
	layout->addWidget(m_findText);
	layout->addWidget(m_findAction);
	layout->addWidget(replaceLabel);
	layout->addWidget(m_replaceText);
	layout->addWidget(m_replaceAction);
	layout->addWidget(m_replaceAllAction);

	m_findMenu->setLayout(layout);
	m_findMenu->hide();

	connect(m_findText, SIGNAL(textChanged ( const QString &)), this, SLOT(findWithMenu(const QString &)));
	connect(m_findAction, SIGNAL(clicked( bool )), this, SLOT(setNextSelection(bool)));
	connect(m_replaceAction, SIGNAL(clicked(bool) ), this, SLOT(replaceCurrent(bool)) );
	connect(m_replaceAllAction, SIGNAL(clicked(bool) ), this, SLOT(replaceAllSelected(bool)) );
}



void TextEditorMainWindow::createStyleConfigurator()
{
	m_styleMenu->setWindowFlags(Qt::Window);
	m_styleMenu->setWindowTitle("Style Configurator");

	QVBoxLayout* layout = new QVBoxLayout;

	m_styles = new QComboBox(this);

	m_styles->addItem("Bespin");
	m_styles->addItem("Blackboard");
	m_styles->addItem("Choco");
	m_styles->addItem("DeepBlack");
	m_styles->addItem("defaultTheme");
	m_styles->addItem("HelloKitty");
	m_styles->addItem("HotFudgeSundae");
	m_styles->addItem("khaki");
	m_styles->addItem("MonoIndustrial");
	m_styles->addItem("Monokai");
	m_styles->addItem("MossyLawn");
	m_styles->addItem("Navajo");
	m_styles->addItem("Obsidian");
	m_styles->addItem("PlasticCodeWrap");
	m_styles->addItem("RubyBlue");
	m_styles->addItem("Solarized");
	m_styles->addItem("Solarizedlight");
	m_styles->addItem("Twilight");
	m_styles->addItem("VibrantInk");
	m_styles->addItem("vimDarkBlue");
	m_styles->addItem("Zenburn");
	m_styles->setCurrentIndex(4);

	layout->addWidget(m_styles);
	m_styleMenu->setLayout(layout);
	connect(m_styles, SIGNAL(currentIndexChanged (int) ), this, SLOT( styleChanged (int) ) );
	m_styleMenu->setVisible(false);
}



void TextEditorMainWindow::createGoToLineMenu()
{
	m_goToMenu->setWindowFlags(Qt::Window);
	m_goToMenu->setWindowTitle("Go To...");

	QVBoxLayout* layout = new QVBoxLayout;
	QLabel* findLabel = new QLabel("You want to go to:", m_goToMenu);
	m_line = new QLineEdit(this);

	layout->addWidget(findLabel);
	layout->addWidget(m_line);
	m_goToMenu->setLayout(layout);
	m_goToMenu->hide();

	connect(m_line, SIGNAL(textChanged( const QString &)), this, SLOT(gotoLine(const QString &)));
}



void TextEditorMainWindow::onStyleConfigurator()
{
	if (m_styleMenu->isVisible())
	{
		m_styleMenu->setVisible(false);
	}
	else
	{
		m_styleMenu->setVisible(true);
	}
}



void TextEditorMainWindow::styleChanged (int style) 
{
	std::string value = m_styles->itemText(style).toStdString();
	const std::map<int, int> referenceFor = vgQt::getThemeForeground(value);
	const std::map<int, int> referenceBack = vgQt::getThemeBackground(value);
	
	std::map<int, int>::const_iterator it;
	
	for ( it = referenceFor.begin() ; it != referenceFor.end(); ++it )
	{
		if (it->first == 11)
		{
			m_textEditor->styleSetFore(0, it->second);
			m_textEditor->styleSetFore(32, it->second);
		}
		m_textEditor->styleSetFore(it->first, it->second);
	}

	for ( it = referenceBack.begin() ; it != referenceBack.end(); ++it )
	{
		if (it->first == 11)
		{
			m_textEditor->styleSetBack(0, it->second);
			m_textEditor->styleSetBack(32, it->second);
		}
		m_textEditor->styleSetBack(it->first, it->second);
	}
}



void TextEditorMainWindow::gotoLine(const QString & lineNumber)
{
	if (lineNumber.size() > 0)
	{
		bool itsOk;
		int value = lineNumber.toInt(&itsOk, 10);

		if ( itsOk )
		{
			value--;

			if (m_textEditor->lineCount() < value)
			{
				value = m_textEditor->lineCount();
			}

			m_textEditor->gotoLine(value);
			m_textEditor->setSelection(m_textEditor->positionFromLine(value), m_textEditor->lineEndPosition(value));
		}
	}
	else
	{
		m_textEditor->clearSelections();
	}
}



void TextEditorMainWindow::replaceCurrent(bool check)
{
	Q_UNUSED(check);

	std::vector<QPair<int, int>> value = m_textEditor->find(m_findText->text().toStdString());
	const int i = m_textEditor->getCurrentSelection();

	if (i < value.size() )
	{
		m_textEditor->setSelection(value[i].first, value[i].second);

		m_textEditor->replaceSel(m_replaceText->text().toStdString().c_str());
		setNextSelection(true);
	}
}



void TextEditorMainWindow::replaceAllSelected(bool check)
{
	Q_UNUSED(check);

	const std::string textReplace = m_replaceText->text().toStdString();
	const std::string textToFind = m_findText->text().toStdString();
	std::vector<QPair<int, int>> value = m_textEditor->find(textToFind);

	while (value.size() != 0)
	{
		m_textEditor->setSelection(value[0].first, value[0].second);

		m_textEditor->replaceSel(textReplace.c_str());
		m_textEditor->clearSelections();
		value = m_textEditor->find(textToFind);
	}
}



void TextEditorMainWindow::setNextSelection(bool check)
{
	Q_UNUSED(check);

	m_textEditor->setCurrentSelection(m_textEditor->getCurrentSelection() + 1);

	if (m_findText->text().size() >= 1)
	{
		m_textEditor->selectText(m_findText->text().toStdString(), false);
	}
}



void TextEditorMainWindow::findWithMenu(const QString &text)
{
	if (text.size() >= 1)
	{
		m_textEditor->setCurrentSelection(0);
		m_textEditor->selectText(text.toStdString(), true);
	}
	else
	{
		m_textEditor->clearSelections();
	}
}



void TextEditorMainWindow::onTop( bool in )
{
#ifdef WIN32

	//
	//Needed because the Qt function on Windows calls setParent() when changing the flags for a window,
	//causing the widget to be hidden.
	//
	if ( in )
	{
		SetWindowPos(this->winId(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
	}
	else
	{
		SetWindowPos(this->winId(), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
	}

#else

	Qt::WindowFlags value = ( in == false ) ? Qt::Widget : (Qt::Widget | Qt::WindowStaysOnTopHint );
	this->setWindowFlags( value );

#endif
}



void TextEditorMainWindow::goToMenu()
{
	if (!m_goToMenu->isVisible())
	{
		m_goToMenu->show();
		m_goToMenu->setFocus();
		m_goToMenu->setWindowState( Qt::WindowActive );
		m_line->setFocus();
	}
	else
	{
		m_goToMenu->hide();
	}
}



void TextEditorMainWindow::findAndReplaceMenu()
{
	if (!m_findMenu->isVisible())
	{
		m_findMenu->show();
		m_findMenu->setFocus();
		m_findMenu->setWindowState( Qt::WindowActive );
		m_findText->setFocus();
	}
	else
	{
		m_findMenu->hide();
	}
}



} // namespace vgQt
