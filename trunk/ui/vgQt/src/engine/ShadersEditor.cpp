// VGSDK - Copyright (C) 2012, Alexandre Di Pino
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Alexandre Di Pino

#include "vgQt/engine/ShadersEditor.hpp"
#include <vgd/field/FieldManager.hpp>
#include <QBrush>
#include <QLabel>
#include <QListWidgetItem>
#include <QMenuBar>
#include <QTimer>
#include <boost/regex.hpp>
#include <sstream>

#include <boost/foreach.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/tokenizer.hpp>

#include <vector>

#ifdef WIN32
#include <windows.h>
#endif


namespace vgQt
{

namespace engine
{



ShadersEditor::ShadersEditor(vgUI::Canvas* canvas, QWidget *parent)
:	//QMainWindow(),
	m_findMenu( new QWidget(this)),
	m_goToMenu( new QWidget(this)),
	m_upDock( new QDockWidget("Shader", this) ),
	m_bottomDock( new QDockWidget("Log", this) ),
	m_upWidget( new QWidget(m_upDock) ),
	m_bottomWidget( new QWidget(m_bottomDock) ),
	m_textEditor( new Editor(this) ),
	m_editorLog( new QPlainTextEdit(m_bottomWidget) ),
	m_mode( new QGroupBox("Mode", m_upDock) ),
	m_core( new QRadioButton("Core", m_upDock) ),
	m_compatibility( new QRadioButton("Compatibility", m_upDock) ),
	m_shaderList( new QListWidget(m_upDock) ),
	m_versionList( new QComboBox(m_upDock) ),
	m_currentProgram(0),
	m_itemType(glo::GLSLProgram::VERTEX),
	m_managerSaved(0),
	m_currentShader(0),
	m_canvas(canvas),
	m_newText(false)
{
	m_engine = m_canvas->getGLEngine();

	resize(1024, 768);

	setWindowTitle(tr("Shaders Viewer"));

	createFindAndReplaceMenu();
	createGoToLineMenu();

	setCentralWidget(m_textEditor);

	m_file = menuBar()->addMenu("&File");
	QAction* menuQuit = m_file->addAction("&Exit");
	menuQuit->setShortcut(QKeySequence("Ctrl+Q"));

	m_edit = menuBar()->addMenu("&Edit");
	QAction* menuFindReplace = m_edit->addAction("&Find/Replace");
	menuFindReplace->setShortcut(QKeySequence("Ctrl+F"));

	QAction* menuGoToLine = m_edit->addAction("&Go To...");
	menuGoToLine->setShortcut(QKeySequence("Ctrl+G"));

	m_menuStayTop = m_edit->addAction("&Always on Top");
	m_menuStayTop->setCheckable(true);


	QVBoxLayout* m_progLayout = new QVBoxLayout;
	QVBoxLayout* m_logLayout = new QVBoxLayout;
	QHBoxLayout* m_radioLayout = new QHBoxLayout;

	m_upDock->setWidget(m_upWidget);
	m_bottomDock->setWidget(m_bottomWidget);

	addDockWidget(Qt::RightDockWidgetArea, m_upDock);
	addDockWidget(Qt::RightDockWidgetArea, m_bottomDock);

	m_core->setChecked(true);

	m_textEditor->setLanguage(Editor::GLSL);

	m_editorLog->setReadOnly(true);

	m_versionList->addItem("OpenGL 2.1 / GLSL 1.2", "1.2");
	m_versionList->addItem("OpenGL 3.0 / GLSL 1.3", "1.3");
	m_versionList->addItem("OpenGL 3.1 / GLSL 1.4", "1.4");
	m_versionList->addItem("OpenGL 3.2 / GLSL 1.5", "1.5");
	m_versionList->addItem("OpenGL 3.3 / GLSL 3.3", "3.3");
	m_versionList->addItem("OpenGL 4.0 / GLSL 4.0", "4.0");
	m_versionList->addItem("OpenGL 4.1 / GLSL 4.1", "4.1");
	m_versionList->addItem("OpenGL 4.2 / GLSL 4.2", "4.2");
	m_versionList->setCurrentIndex( m_textEditor->getGLSLVersion() );

	m_radioLayout->addWidget(m_core);
	m_radioLayout->addWidget(m_compatibility);

	m_mode->setLayout(m_radioLayout);

	m_progLayout->addWidget(m_versionList);
	m_progLayout->addWidget(m_mode);
	m_progLayout->addWidget(m_shaderList);
	m_progLayout->setAlignment(Qt::AlignTop);

	m_logLayout->addWidget(m_editorLog);
	m_logLayout->setAlignment(Qt::AlignBottom);

	m_upWidget->setLayout(m_progLayout);
	m_bottomWidget->setLayout(m_logLayout);

	m_upWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	m_bottomWidget->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);

	connect(menuQuit, SIGNAL(triggered()), this, SLOT(close()));
	connect(menuFindReplace, SIGNAL(triggered()), this, SLOT(findAndReplaceMenu()));
	connect(menuGoToLine, SIGNAL(triggered()), this, SLOT(goToMenu()));
	connect(m_menuStayTop, SIGNAL(toggled(bool)) , this, SLOT(onTop(bool)));

	connect(m_shaderList, SIGNAL(itemClicked ( QListWidgetItem * )), this, SLOT( checkText(  QListWidgetItem * ) ));
	connect(m_textEditor, SIGNAL( modified(int , int , int , int ,
	              const QByteArray &, int , int , int ) ), this, SLOT( compile(int , int , int , int ,
	              const QByteArray &, int , int , int ) ) );

	connect(m_versionList, SIGNAL(currentIndexChanged (int) ), this, SLOT( versionChanged (int) ) );

	connect(m_core, SIGNAL( clicked( bool )), this, SLOT( modeCore( bool ) ) );
	connect(m_compatibility, SIGNAL( clicked( bool )), this, SLOT( modeCompatibility( bool ) ) );

	refreshUI();
}



void ShadersEditor::createFindAndReplaceMenu()
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



void ShadersEditor::createGoToLineMenu()
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



void ShadersEditor::gotoLine(const QString & lineNumber)
{
	if (lineNumber.size() > 0)
	{
		bool itsOk;
		int value = lineNumber.toInt(&itsOk, 10);

		if (itsOk)
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
}



void ShadersEditor::replaceCurrent(bool check)
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



void ShadersEditor::replaceAllSelected(bool check)
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



void ShadersEditor::setNextSelection(bool check)
{
	Q_UNUSED(check);

	m_textEditor->setCurrentSelection(m_textEditor->getCurrentSelection() + 1);
	if (m_findText->text().size() >= 1)
	{
		m_textEditor->selectText(m_findText->text().toStdString(), false);
	}
}



void ShadersEditor::findWithMenu(const QString &text)
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



void ShadersEditor::checkErrorLine(const std::string& log)
{
	std::string regex;
	if (gleGetCurrent()->getDriverProvider() == gle::OpenGLExtensions::ATI_DRIVERS)
	{
		regex = ".*\\d+:"
				"(\\d+): error.*";	// like 0:10: error
	}
	else if (gleGetCurrent()->getDriverProvider() == gle::OpenGLExtensions::NVIDIA_DRIVERS)
	{
		regex = ".*\\d\\("
				"(\\d+)"
				"\\)"
				"[[:space:]]+: error.*";	// like 0(28) : error
	}
	else
	{
		return;
	}

	boost::regex expression(regex.c_str());

	boost::char_separator<char> sep("\n");
    boost::tokenizer<boost::char_separator<char>> tokens(log, sep);

	boost::cmatch matches;

	BOOST_FOREACH(std::string t, tokens)
	{
		if(boost::regex_match(t.c_str(), matches, expression))
		{
			std::string tmpversion(matches[1].first, matches[1].second);
			std::istringstream iss(tmpversion);
			int value;
			iss >> value;
			m_textEditor->setLineMarker(value);
		}
	}
}



void ShadersEditor::checkVersionOnShader(const std::string& shader)
{
	boost::regex expression(
		".*#version"				//check version
		"[[:space:]]+"				//check space and tabulation
		"(\\d{3})"					//capture version
		"[[:space:]]+"				//check space and tabulation
		"(compatibility|core).*"	//capture mode
		);

	boost::cmatch matches;
	std::string myversion;
	std::string mode;

	if (boost::regex_match(shader.c_str(), matches, expression))
	{
		for (unsigned int i = 1; i < matches.size(); i++)
		{
			std::string tmpversion(matches[i].first, matches[i].second);

			if ( i == 1 )
			{
				myversion += tmpversion[0];
				myversion += ".";
				myversion += tmpversion[1];
			}
			else if ( i == 2 )
			{
				mode = tmpversion;
			}
		}

		if (mode == "compatibility")
		{
			m_compatibility->setChecked(true);
			m_core->setChecked(false);
			m_versionList->setCurrentIndex( static_cast<int>(gle::glslVersionToEnum(myversion)) );
		}
		else if (mode == "core")
		{
			m_core->setChecked(true);
			m_compatibility->setChecked(false);
			m_versionList->setCurrentIndex( static_cast<int>(gle::glslVersionToEnum(myversion)) );
		}
	}
}



void ShadersEditor::checkText(QListWidgetItem *item)
{
	blockSignals(true);

	std::vector<std::string>::iterator	shaderName;
	std::vector<std::string>::iterator	shaderString;
	const std::string itemName = item->text().toStdString();

	const uint progLength = m_engine->getGLSLManagerExt().getNum();

	m_canvas->setCurrent();

	gle::GLSL_VERSION_LANGUAGE version = gle::glslVersionToEnum(gle::getCurrentGLSLVersion());

	m_textEditor->setGLSLVersion( version );
	m_versionList->setCurrentIndex( static_cast<int>(version) );

	if ( progLength > 0 )
	{
		std::vector<int> keys;
		typedef std::back_insert_iterator< std::vector<int> >	InsertIterator;
		InsertIterator keys_it( keys );
		m_engine->getGLSLManagerExt().getKeys( keys_it );
		m_currentShader = item->type() - 1000;

		for ( std::vector<int>::const_iterator pos = keys.begin(); pos != keys.end(); ++pos )
		{
			glo::GLSLProgram* manager = m_engine->getGLSLManagerExt().get< glo::GLSLProgram >(*pos);

			const uint shaderNameSize = glo::GLSLProgram::MAX_SHADER_INDEX - 1;

			if ( m_currentShader == manager->getProgramObject() )
			{
				m_editorLog->setPlainText(manager->getLinkLog().c_str());
				m_currentProgram = manager->getProgramObject();
				m_textEditor->setText("");
				return;
			}

			for (uint i = 0; i < shaderNameSize; i++)
			{
				std::ostringstream	oss;
				glo::GLSLProgram::ShaderType type = (glo::GLSLProgram::ShaderType)i;
				oss << manager->getName(type);
				const std::string name = manager->convertShaderType2String(type) + " " + oss.str();

				//If clicked value exist on the manager, save all needed data
				if (itemName == name)
				{
					QString actualShader =  m_textEditor->getText(m_textEditor->textLength());

					if ( manager->getShaderCode(type).c_str() == actualShader.toStdString() )	return;

					checkVersionOnShader(manager->getShaderCode(type).c_str());
					m_currentProgram = manager->getProgramObject();
					m_currentShader = manager->getName(type);
					m_itemType = type;
					m_managerSaved = manager;
					m_newText = true;
					m_textEditor->setText( manager->getShaderCode(type).c_str() );
					m_editorLog->setPlainText(manager->getLogError(type).c_str());
					findWithMenu(m_findText->text());
					checkErrorLine(manager->getLogError(type));
					break;
				}
			}
		}
	}
	blockSignals(false);
}



void ShadersEditor::refreshUI()
{
	blockSignals(true);

	const uint progLength = m_engine->getGLSLManagerExt().getNum();

	QBrush brush(Qt::red);

	QFont	font("Helvetica");
	font.setBold(true);

	if (isVisible() == false)	return;

	if ( progLength > 0 )
	{
		//Clear all the elements
		m_shaderList->clear();
		std::vector<int> keys;
		typedef std::back_insert_iterator< std::vector<int> >	InsertIterator;
		InsertIterator keys_it( keys );
		m_engine->getGLSLManagerExt().getKeys( keys_it );

		for ( std::vector<int>::const_iterator pos = keys.begin(); pos != keys.end(); ++pos )
		{
			glo::GLSLProgram* manager = m_engine->getGLSLManagerExt().get< glo::GLSLProgram >(*pos);

			std::ostringstream	ossP;
			ossP << (int)manager->getProgramObject();

			std::string prgName =  "Program " + ossP.str();
			QListWidgetItem* prog = new QListWidgetItem(tr( prgName.c_str() ), m_shaderList, (int)manager->getProgramObject() + 1000);
			if (manager->getInfoLog() != "")
			{
				prog->setForeground(brush);
			}
			prog->setFont(font);

			//Add Shader name on shader list
			for (uint i = 0; i < glo::GLSLProgram::MAX_SHADER_INDEX; ++i)
			{
				std::string tmp;
				std::ostringstream	oss;
				glo::GLSLProgram::ShaderType type = (glo::GLSLProgram::ShaderType)i;

				if (type < glo::GLSLProgram::PROGRAM)
				{
					tmp = manager->convertShaderType2String(type) + " ";

					if ( manager->getName(type) != 0 )
					{
						oss << manager->getName(type);
						tmp += oss.str();
						QListWidgetItem* listShader = new QListWidgetItem(tr(tmp.c_str()), m_shaderList, manager->getName(type) + 1000 );

						if (manager->getLogError(type) != "")
						{
							listShader->setForeground(brush);
						}
					}
				}
			}

			std::string log("");

			//Draw the compilation log
			for (uint i = 0; i < glo::GLSLProgram::MAX_SHADER_INDEX; ++i)
			{
				glo::GLSLProgram::ShaderType type = (glo::GLSLProgram::ShaderType)i;
				if (type < glo::GLSLProgram::PROGRAM)
				{
					log += manager->getLogError(type) + "\n";
				}
			}

			log += manager->getLinkLog();

			//Set the log compilation in the log screen
			m_editorLog->setPlainText(log.c_str());
		}
	}

	blockSignals(false);
}



void ShadersEditor::compile(int notificationType, int position, int length, int linesAdded,
	              const QByteArray &text, int line, int foldNow, int foldPrev)
{
	std::ostringstream	oss;

	std::string InfoLog("");
	//QFont	fontError("Helvetica");

	if ( m_newText )
	{
		m_newText = false;
		return;
	}

	if (m_currentProgram && m_managerSaved
		&& ( ( notificationType & SC_MOD_INSERTTEXT ) || ( notificationType & SC_MOD_DELETETEXT ) ) )
	{
		if ( m_currentProgram == (int)m_managerSaved->getProgramObject() )
		{
			if ( m_currentShader == m_currentProgram )
			{
				m_editorLog->setPlainText(m_managerSaved->getLinkLog().c_str());
				m_textEditor->setText("");
				return;
			}

			int len = m_textEditor->textLength();

			if ( len == 0 )	return;

			QString	tmp = m_textEditor->getText(len + 1);
			const std::string shader = tmp.toStdString();
			m_canvas->setCurrent();
			if ( m_managerSaved->getShaderCode((glo::GLSLProgram::ShaderType)m_itemType) == shader )	return;

			m_textEditor->clearAllUnderligned();
			//Compile the modify shader
			const bool compileRetVal = m_managerSaved->addShader( shader.c_str(), m_itemType, false);

			if ( !compileRetVal )
			{
				InfoLog = m_managerSaved->getLogError(m_itemType);
				checkErrorLine(m_managerSaved->getLogError(m_itemType));
				//fontError.setItalic(true);
			}
			else
			{
				m_managerSaved->setLogError(m_itemType, "");
				//Linking
				const bool linkRetVal = m_managerSaved->link();

				if ( !linkRetVal )
				{
					InfoLog += m_managerSaved->getInfoLog();
					checkErrorLine(m_managerSaved->getInfoLog());
				}
				else
				{
					// Async refresh
					m_canvas->refreshForced();
				}
			}
			refreshUI();
			m_editorLog->setPlainText(InfoLog.c_str());
		}
	}
}



void ShadersEditor::onTop( bool in )
{
#ifdef WIN32

	//
	//Needed because the Qt function on Windows calls setParent() when changing the flags for a window,
	//causing the widget to be hidden.
	//
	if (in)
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



void ShadersEditor::versionChanged(int index)
{
	std::string value = m_versionList->itemData( index ).toString().toStdString();
	if ( m_core->isChecked() )
	{
		m_textEditor->setGLSLVersion( gle::glslVersionToEnum( value ) );
	}
	else
	{
		m_textEditor->setGLSLVersionCompatibility( gle::glslVersionToEnum( value ) );
	}
}



void ShadersEditor::modeCore( bool )
{
	m_textEditor->setGLSLVersion(m_textEditor->getGLSLVersion());
}



void ShadersEditor::modeCompatibility( bool )
{
	m_textEditor->setGLSLVersionCompatibility(m_textEditor->getGLSLVersion());
}



void ShadersEditor::goToMenu()
{
	if (m_goToMenu->isVisible() == false)
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



void ShadersEditor::findAndReplaceMenu()
{
	if (m_findMenu->isVisible() == false)
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



bool ShadersEditor::event(QEvent * e)
{
	if (e->type() == QEvent::WindowActivate)
	{
		refreshUI();
		return true;
	}
	return QMainWindow::event(e);
}



} // namespace engine

} // namespace vgQt

