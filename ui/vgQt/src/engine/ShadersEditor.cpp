// VGSDK - Copyright (C) 2012, Alexandre Di Pino
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Alexandre Di Pino

#include "vgQt/engine/ShadersEditor.hpp"
#include <QListWidgetItem>
#include <sstream>

#ifdef WIN32
#include <windows.h>
#endif


namespace vgQt
{

namespace engine
{



ShadersEditor::ShadersEditor(vgUI::Canvas* canvas, QWidget *parent)
:	QWidget(parent), 
	m_currentType(vgQt::engine::NONE),
	m_program(0), 
	m_itemSaved(0), 
	m_managerSaved(0), 
	m_shaderSaved(0),
	m_newText(false),
	m_canvas(canvas),
	m_textEditor( new Editor(this) ),
	m_editorLog( new QPlainTextEdit(this) ),
	m_progLayout( new QVBoxLayout ),
	m_buttonLayout( new QVBoxLayout ),
	m_logLayout( new QVBoxLayout ),
	m_rightLayout( new QVBoxLayout ),
	m_layout( new QHBoxLayout ),
	m_refresh( new QPushButton("Refresh", this)),
	m_shaderList( new QListWidget ),
	m_stayTop( new QCheckBox("Stay on Top", this) )
{
	m_engine = m_canvas->getGLEngine();
	resize(1024, 768);
	setWindowTitle(tr("Shaders Viewer"));

	m_refresh->setShortcut(tr("F6"));
	m_refresh->setToolTip("Shortcut : 'F6'");

	m_textEditor->setLanguage(Editor::GLSL);

	m_shaderList->setMaximumWidth(200);

	m_layout->addWidget(m_textEditor.get());

	m_editorLog->setReadOnly(true);
	m_editorLog->setMaximumWidth(200);

	m_progLayout->addWidget(m_shaderList.get());
	m_progLayout->setAlignment(Qt::AlignTop);

	m_buttonLayout->addWidget(m_refresh.get());
	m_buttonLayout->addWidget(m_stayTop.get());
	m_buttonLayout->setAlignment(Qt::AlignAbsolute);
	
	m_logLayout->addWidget(m_editorLog.get());
	m_logLayout->setAlignment(Qt::AlignBottom);

	m_rightLayout->addLayout(m_progLayout.get());
	m_rightLayout->addLayout(m_logLayout.get());
	m_rightLayout->addLayout(m_buttonLayout.get());
	
	m_layout->addLayout(m_rightLayout.get());
	setLayout(m_layout.get());
	
	connect(m_shaderList.get(), SIGNAL(itemDoubleClicked ( QListWidgetItem * )), this, SLOT( checkText(  QListWidgetItem * ) ));
	connect(m_refresh.get(), SIGNAL( clicked() ), this, SLOT( refreshUI() ) );
	connect(m_textEditor.get(), SIGNAL( modified(int , int , int , int ,
	              const QByteArray &, int , int , int ) ), this, SLOT( compile(int , int , int , int ,
	              const QByteArray &, int , int , int ) ) );
	connect(m_stayTop.get(), SIGNAL( stateChanged ( int ) ), this, SLOT( onTop( int ) ) );

	refreshUI();
}



void ShadersEditor::checkText(QListWidgetItem *item)
{
	blockSignals(true);
	std::vector<std::string>::iterator	shaderName;
	std::vector<std::string>::iterator	shaderString;
	const std::string itemName = item->text().toStdString();

	const uint progLength = m_engine->getGLSLManagerExt().getNum();
	m_currentType = (eShaderType)item->type();

	if ( progLength > 0 )
	{
		for ( uint program = 1; program <= progLength; program++ )
		{
			shaderEditorManager manager = m_engine->getGLSLManagerExt().get< vgeGL::engine::Engine::ProgramProperties >( program );
			const uint shaderNameSize = manager->shadersName.size();

			for (uint i = 0; i < shaderNameSize; i++)
			{
				std::ostringstream	oss;
				oss << manager->objectName[i];
				const std::string name = manager->shadersName[i] + oss.str();

				//If clicked value exist on the manager, save all needed data
				if (itemName == name) 	
				{
					QString actualShader =  m_textEditor->getText(m_textEditor->textLength());
					
					if ( manager->shaders[i].c_str() == actualShader.toStdString() )
					{
						return;
					}

					m_itemSaved = item;
					m_program = manager->pProgram;
					m_managerSaved = manager;
					m_shaderSaved = i;
					m_newText = true;
					m_textEditor->setText( manager->shaders[i].c_str() );
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
	m_itemSaved = 0;

	QFont	font("Helvetica");
	font.setBold(true);

	if ( progLength > 0 )
	{
		uint program = 1;

		//Clear all the elements
		m_shaderList->clear();

		while ( program <= progLength )
		{
			vgeGL::engine::Engine::ProgramProperties* manager = m_engine->getGLSLManagerExt().get< vgeGL::engine::Engine::ProgramProperties >(program);

			QListWidgetItem* prog = new QListWidgetItem(tr( manager->programName.c_str() ), m_shaderList.get(), vgQt::engine::PROGRAM_SHADER);
			prog->setFont(font);

			//Add Shader name on shader list
			for (uint i = 0; i < manager->shadersName.size(); ++i)
			{
				std::string tmp;
				std::ostringstream	oss;

				tmp = manager->shadersName[i];
				if ( manager->objectName[i] != 0 )
				{
					oss << manager->objectName[i];
					tmp += oss.str();
					new QListWidgetItem(tr(tmp.c_str()), m_shaderList.get(), vgQt::engine::DEFAULT_SHADER_TYPE + i );
				}
			}

			std::string log("");

			//Draw the compilation log
			for (uint i = 0; i < manager->shadersLog.size(); ++i)
			{
				log += manager->shadersLog[i];
				log += "\n";
			}

			log += manager->linkLog;

			//Set the log compilation in the log screen
			m_editorLog->setPlainText(log.c_str());
			program++;
		}
	}
	blockSignals(false);
}



void ShadersEditor::compile(int notificationType, int position, int length, int linesAdded,
	              const QByteArray &text, int line, int foldNow, int foldPrev)
{
	std::ostringstream	oss;

	std::string InfoLog("");
	const glo::GLSLProgram::ShaderType type = (glo::GLSLProgram::ShaderType)(m_currentType - 1000) ;

	if ( m_newText )
	{
		m_newText = false;
		return;
	}

	if ( m_currentType == PROGRAM_SHADER )	return;

	if ( m_program && m_managerSaved && m_itemSaved 
		&& ( ( notificationType & SC_MOD_INSERTTEXT ) || ( notificationType & SC_MOD_DELETETEXT ) ) )
	{
		int len = m_textEditor->textLength();

		if ( len == 0 )	return;

		QString	tmp = m_textEditor->getText(len + 1);
		const std::string shader = tmp.toStdString();
		
		if ( m_managerSaved->shaders[m_shaderSaved] == shader )
		{
			return;
		}

		m_managerSaved->shaders[m_shaderSaved] = shader;

		//Compile the modify shader
		const bool compileRetVal = m_program->addShader( shader.c_str(), type, false );

		if ( !compileRetVal )	
		{
			InfoLog = m_program->getLogError(type);
		}
		else
		{
			//Linking
			const bool linkRetVal = m_program->link();

			if ( !linkRetVal )	
			{
				InfoLog += m_program->getInfoLog();
			}
			//@ TODO correct
			//else	
			//{	
			//	m_canvas->refreshForced();
			//}
		}

		//Set the new shader name
		std::string newName(m_managerSaved->shadersName[type]);
		const int programNumber = m_program->getName(type);
		oss << programNumber;
		newName += oss.str();

		//Set the new name in the shader list
		if ( m_itemSaved )	m_itemSaved->setText( QString(newName.c_str()) );

		m_managerSaved->objectName[m_shaderSaved] = programNumber;

		//Set the log error in the shader log
		m_editorLog->setPlainText(InfoLog.c_str());
	}
}



void ShadersEditor::onTop( int in )
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
	
	Qt::WindowFlags value = ( in == Qt::Unchecked ) ? Qt::Widget : (Qt::Widget | Qt::WindowStaysOnTopHint );
	this->setWindowFlags( value );

#endif
}



} // namespace engine

} // namespace vgQt
