// VGSDK - Copyright (C) 2012, 2013, 2014, Alexandre Di Pino, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Alexandre Di Pino
// Author Nicolas Papier

#include "vgQt/engine/ShadersEditor.hpp"

#include <vgd/field/FieldManager.hpp>

#include <QBrush>
#include <QLineEdit>
#include <QListWidgetItem>
#include <QVBoxLayout>

#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/regex.hpp>
#include <boost/tokenizer.hpp>

#ifdef POSIX
	#include <GL/glx.h>
#endif
#include <gle/OpenGLExtensionsGen.hpp> // @todo remove this include, but refactoring needed in => if (gleGetCurrent()->getDriverProvider() == gle::OpenGLExtensions::ATI_DRIVERS)

namespace vgQt
{

namespace engine
{



namespace
{

const std::string buildLog( glo::GLSLProgram * program )
{
	// For each shader type, do
	std::string log;
	for (uint i = 0; i < glo::GLSLProgram::PROGRAM; ++i)
	{
		typedef glo::GLSLProgram::ShaderType ShaderType;
		const ShaderType type = static_cast<ShaderType>(i);

		// Construct the compilation log
		const std::string logError( program->getLogError(type) );
		if ( logError.size() > 0 )	log +=  logError + "\n";
	}

	if ( program->getLinkLog().size() > 0 ) log += program->getLinkLog();

	return log;
}

}


ShadersEditor::ShadersEditor(QWidget *parent)
:	vgQt::TextEditorMainWindow("Shaders Viewer"),
	m_upDock( new QDockWidget("Shader", this) ),
	m_bottomDock( new QDockWidget("Log", this) ),
	m_editorLog( new QPlainTextEdit(m_bottomDock) ),
	m_mode( new QGroupBox("Mode", m_upDock) ),
	m_core( new QRadioButton("Core", m_upDock) ),
	m_compatibility( new QRadioButton("Compatibility", m_upDock) ),
	m_shaderList( new QListWidget(m_upDock) ),
	m_versionList( new QComboBox(m_upDock) ),
	m_currentProgram(0),
	m_itemType(glo::GLSLProgram::VERTEX),
	m_managerSaved(0),
	m_currentShader(0),
	m_canvas(0)
{
	// Resize the window
	resize(1024, 768);

	// Create all needed layout
	QVBoxLayout* m_progLayout = new QVBoxLayout;
	QVBoxLayout* m_logLayout = new QVBoxLayout;
	QHBoxLayout* m_radioLayout = new QHBoxLayout;

	// Create widgets for the dock
	QWidget* upWidget = new QWidget(m_upDock) ;
	QWidget* bottomWidget =  new QWidget(m_bottomDock) ;

	// Set widgets on the dock
	m_upDock->setWidget(upWidget);
	m_bottomDock->setWidget(bottomWidget);

	// Add dock on the mainwindow
	addDockWidget(Qt::RightDockWidgetArea, m_upDock);
	addDockWidget(Qt::RightDockWidgetArea, m_bottomDock);

	// Set by default the core api
	m_core->setChecked(true);

	// Set the text editor language
	m_textEditor->setLanguage(Editor::GLSL);

	// Set the default zoom
	m_textEditor->zoomIn();

	// Set the editor log read only
	m_editorLog->setReadOnly(true);

	// Adds all versions of OpenGL on the combobox
	m_versionList->addItem("OpenGL 2.1 / GLSL 1.2", "1.2");
	m_versionList->addItem("OpenGL 3.0 / GLSL 1.3", "1.3");
	m_versionList->addItem("OpenGL 3.1 / GLSL 1.4", "1.4");
	m_versionList->addItem("OpenGL 3.2 / GLSL 1.5", "1.5");
	m_versionList->addItem("OpenGL 3.3 / GLSL 3.3", "3.3");
	m_versionList->addItem("OpenGL 4.0 / GLSL 4.0", "4.0");
	m_versionList->addItem("OpenGL 4.1 / GLSL 4.1", "4.1");
	m_versionList->addItem("OpenGL 4.2 / GLSL 4.2", "4.2");
	m_versionList->addItem("OpenGL 4.3 / GLSL 4.3", "4.3");

	// Attach widgets on the mainwindow
	m_radioLayout->addWidget(m_core);
	m_radioLayout->addWidget(m_compatibility);

	m_mode->setLayout(m_radioLayout);

	m_progLayout->addWidget(m_versionList);
	m_progLayout->addWidget(m_mode);
	m_progLayout->addWidget(m_shaderList);
	m_progLayout->setAlignment(Qt::AlignTop);

	m_logLayout->addWidget(m_editorLog);
	m_logLayout->setAlignment(Qt::AlignBottom);

	upWidget->setLayout(m_progLayout);
	bottomWidget->setLayout(m_logLayout);

	upWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	bottomWidget->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);

	// Connect widget witch SLOT
	connect(m_shaderList, SIGNAL(itemClicked ( QListWidgetItem * )), this, SLOT( selectItemInShaderList(  QListWidgetItem * ) ));
	connect(m_textEditor,
			SIGNAL( modified(int, int, int, int, const QByteArray &, int, int, int) ),
			this,
			SLOT( compile(int, int, int, int,const QByteArray &, int, int, int) ) );

	connect(m_versionList, SIGNAL(currentIndexChanged (int) ), this, SLOT( versionChanged (int) ) );

	connect(m_core, SIGNAL( clicked( bool )), this, SLOT( modeCore( bool ) ) );
	connect(m_compatibility, SIGNAL( clicked( bool )), this, SLOT( modeCompatibility( bool ) ) );
}


// Change visibility of the shaders editor and refresh the shader list
void ShadersEditor::changeVisibility()
{
	setVisible ( (isVisible()) ? false : true );
	refreshUI();
}


// Check if the log contain error. If true, set a marker on the text editor margin
void ShadersEditor::checkErrorLine(const std::string& log)
{
	std::string regex;
	// Choose regex between Ati driver and Nvidia driver.
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
		vgAssertN(false, "Check error not supported on this GPU");
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
			// Adds a marker
			m_textEditor->setLineMarker( boost::lexical_cast<int>( tmpversion ));
		}
	}
}


// Set the current canvas
void ShadersEditor::setCanvas(vgUI::Canvas* canvas)
{
	m_canvas = canvas;
	m_engine = m_canvas->getGLEngine();
}


// Check if the current shader contain a #version. If true, set the version on the text editor
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
		else
		{
			vgAssert(false);
		}
	}
}



void ShadersEditor::selectItemInShaderList(QListWidgetItem *item)
{
	blockSignals(true);

	const std::string itemName = item->text().toStdString();

	m_canvas->setCurrent();

	gle::GLSL_VERSION_LANGUAGE version = gle::glslVersionToEnum(gle::getCurrentGLSLVersion());
	m_textEditor->setGLSLVersion( version );
	m_versionList->setCurrentIndex( static_cast<int>(version) );

	// If GLSL Manager extended is not empty
	vgd::Shp< vgeGL::engine::Engine::GLSLProgramManagerExtType > glslManagerExt = m_engine->getGLSLManagerExt();
	const uint numProgram = glslManagerExt->getNum();
	if ( numProgram > 0 )
	{
		m_currentShader = item->type() - 1000;

		KeysContainer keys;
		glslManagerExt->gethKeys( keys );

		for ( KeysContainer::const_iterator pos = keys.begin(); pos != keys.end(); ++pos )
		{
			glo::GLSLProgram* glslProgram = glslManagerExt->get< glo::GLSLProgram >(*pos);

			// If the selected element is a program
			if ( m_currentShader == glslProgram->getProgramObject() )
			{
				// Set link log
				const std::string log = buildLog( glslProgram );

				m_editorLog->setPlainText( log.c_str());

				m_currentProgram = glslProgram->getProgramObject();

				// Erase the text editor
				m_textEditor->setText("");
				return;
			}
			else // selected element is a shader
			{
				for (uint i = 0; i < glo::GLSLProgram::PROGRAM; i++)
				{
					typedef glo::GLSLProgram::ShaderType ShaderType;
					const ShaderType type = static_cast<ShaderType>(i);

					// Found selected element
					// see shaderName construction in refreshUI()
					const std::string shaderName = " " + glslProgram->convertShaderType2String(type) + " " + boost::lexical_cast<std::string>( glslProgram->getName(type) );
					if ( itemName == shaderName )
					{

						QString actualShader = m_textEditor->getText(m_textEditor->textLength());

						if ( glslProgram->getShaderCode(type).c_str() == actualShader.toStdString() )	return;

						checkVersionOnShader(glslProgram->getShaderCode(type).c_str());		// Check the version
						m_currentProgram = glslProgram->getProgramObject();					// Save the current program
						m_currentShader = glslProgram->getName(type);						// Save the current shader, save also if is a program
						m_itemType = type;													// Save the shader type
						m_managerSaved = glslProgram;										// Save the current GLSL Manager
						m_newText = true;													// New text is set on the editor
						m_textEditor->setText( glslProgram->getShaderCode(type).c_str() );	// Set the shader on the editor
						m_editorLog->setPlainText(glslProgram->getLogError(type).c_str());	// Set the log
						findWithMenu(m_findText->text());									// Set selection if a current word is needed to find
						checkErrorLine(glslProgram->getLogError(type));						// Check line error and higlight this
						break;
					}
				}
			}
		}
	}
	blockSignals(false);
}



void ShadersEditor::refreshUI()
{
	blockSignals(true);

	// If the editor is not visible, bypass
	if (!isVisible())	return;

	QBrush	brush(Qt::red);

	QFont	font("Helvetica");
	font.setBold(true);

	// If GLSL Manager extended is not empty
	vgd::Shp< vgeGL::engine::Engine::GLSLProgramManagerExtType > glslManagerExt = m_engine->getGLSLManagerExt();
	const uint numProgram = glslManagerExt->getNum();
	if ( numProgram > 0 )
	{
		//Clear all the elements
		m_shaderList->clear();

		KeysContainer keys;
		glslManagerExt->gethKeys( keys );

		for ( KeysContainer::const_iterator pos = keys.begin(); pos != keys.end(); ++pos )
		{
			glo::GLSLProgram* glslProgram = glslManagerExt->get< glo::GLSLProgram >(*pos);

			// Adds the program element on the shader list
			const std::string progName =  "Program " + boost::lexical_cast<std::string>( glslProgram->getProgramObject() );
			QListWidgetItem* prog = new QListWidgetItem(tr( progName.c_str() ), m_shaderList, static_cast<int>(glslProgram->getProgramObject()) + 1000);
			prog->setFont(font);
			if (!glslProgram->getLinkSuccess())	prog->setForeground(brush); // If program doesnt link, set color to red

			// For each shader type, do
			for (uint i = 0; i < glo::GLSLProgram::PROGRAM; ++i)
			{
				typedef glo::GLSLProgram::ShaderType ShaderType;
				const ShaderType type = static_cast<ShaderType>(i);

				// Adds shader name on shader list
				if ( glslProgram->getShaderCode(type).size() > 0 )
				{
					// see shaderName construction in selectItemInShaderList()
					const std::string shaderName = " " + glslProgram->convertShaderType2String(type) + " " + boost::lexical_cast<std::string>( glslProgram->getName(type) );
					QListWidgetItem* listShader = new QListWidgetItem(tr(shaderName.c_str()), m_shaderList, glslProgram->getName(type) + 1000 );
					if (glslProgram->getLogError(type).size() > 0)	listShader->setForeground(brush); // If shader contain error, set background to red
				}
			}
		}
	}

	blockSignals(false);
}



void ShadersEditor::compile(int notificationType, int position, int length, int linesAdded,
							const QByteArray &text, int line, int foldNow, int foldPrev)
{
	std::ostringstream	oss;

	std::string InfoLog("");

	// If new text is set on the text editor, do nothing
	if ( m_newText )
	{
		m_newText = false;
		return;
	}

	// If text are insert or remove on the text editor
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
				//Construct the shader log
				InfoLog = m_managerSaved->getLogError(m_itemType);
				checkErrorLine(m_managerSaved->getLogError(m_itemType));
			}
			else
			{
				m_managerSaved->setLogError(m_itemType, "");
				//Linking
				const bool linkRetVal = m_managerSaved->link();

				if ( !linkRetVal )
				{
					//Construct the link log
					InfoLog += m_managerSaved->getLinkLog();
					checkErrorLine(m_managerSaved->getLinkLog());
				}
				else
				{
					// Async refresh
					m_canvas->refreshForced();
				}
			}
			refreshUI();
			//Set log on the editor log widget
			m_editorLog->setPlainText(InfoLog.c_str());
		}
	}
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



bool ShadersEditor::event(QEvent * e)
{
	// If the Shader editor is focus, refresh the shader list
	if (e->type() == QEvent::WindowActivate)
	{
		refreshUI();
		return true;
	}
	return QMainWindow::event(e);
}



} // namespace engine

} // namespace vgQt
