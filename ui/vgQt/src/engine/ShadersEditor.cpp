// VGSDK - Copyright (C) 2012, Alexandre Di Pino
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Alexandre Di Pino

#include "vgQt/engine/ShadersEditor.hpp"
#include <vgd/field/FieldManager.hpp>
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
	m_versionList( new QComboBox ),
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

	m_versionList->addItem("OpenGL 2.1 / GLSL 1.2", "1.2");
	m_versionList->addItem("OpenGL 3.0 / GLSL 1.3", "1.3");
	m_versionList->addItem("OpenGL 3.1 / GLSL 1.4", "1.4");
	m_versionList->addItem("OpenGL 3.2 / GLSL 1.5", "1.5");
	m_versionList->addItem("OpenGL 3.3 / GLSL 3.3", "3.3");
	m_versionList->addItem("OpenGL 4.0 / GLSL 4.0", "4.0");
	m_versionList->addItem("OpenGL 4.1 / GLSL 4.1", "4.1");
	m_versionList->addItem("OpenGL 4.2 / GLSL 4.2", "4.2");
	m_versionList->setCurrentIndex( m_textEditor->getGLSLVersion() );

	m_progLayout->addWidget(m_versionList.get());

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
	
	connect(m_shaderList.get(), SIGNAL(itemClicked ( QListWidgetItem * )), this, SLOT( checkText(  QListWidgetItem * ) ));
	connect(m_refresh.get(), SIGNAL( clicked() ), this, SLOT( refreshUI() ) );
	connect(m_textEditor.get(), SIGNAL( modified(int , int , int , int ,
	              const QByteArray &, int , int , int ) ), this, SLOT( compile(int , int , int , int ,
	              const QByteArray &, int , int , int ) ) );
	connect(m_stayTop.get(), SIGNAL( stateChanged ( int ) ), this, SLOT( onTop( int ) ) );
	connect(m_versionList.get(), SIGNAL(currentIndexChanged (int) ), this, SLOT( versionChanged (int) ) );
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

	m_canvas->setCurrent();

	gle::GLSL_VERSION_LANGUAGE version = gle::glslVersionToEnum(gle::getCurrentGLSLVersion());

	m_textEditor->setGLSLVersion( version );
	m_versionList->setCurrentIndex( static_cast<int>(version) );

	if (m_managerSaved)
	{
		if (m_currentType == PROGRAM_SHADER)
		{
			m_editorLog->setPlainText(m_managerSaved->getLinkLog().c_str());
		}
	}

	if ( progLength > 0 )
	{
		std::vector<int> keys;
		typedef std::back_insert_iterator< std::vector<int> >	InsertIterator;
		InsertIterator keys_it( keys );
		m_engine->getGLSLManagerExt().getKeys( keys_it );

		for ( std::vector<int>::const_iterator pos = keys.begin(); pos != keys.end(); ++pos )
		{
			glo::GLSLProgram* manager = m_engine->getGLSLManagerExt().get< glo::GLSLProgram >(*pos);

			const uint shaderNameSize = glo::GLSLProgram::MAX_SHADER_INDEX;
			
			if (m_currentType == PROGRAM_SHADER)
			{
				m_editorLog->setPlainText(manager->getLinkLog().c_str());
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
					
					if ( manager->getShaderCode(type).c_str() == actualShader.toStdString() )
					{
						return;
					}

					m_itemSaved = item;
					m_managerSaved = manager;
					m_shaderSaved = i;
					m_newText = true;
					m_textEditor->setText( manager->getShaderCode(type).c_str() );
					m_editorLog->setPlainText(manager->getLogError(type).c_str());
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
			QListWidgetItem* prog = new QListWidgetItem(tr( prgName.c_str() ), m_shaderList.get(), vgQt::engine::PROGRAM_SHADER);
			prog->setFont(font);

			//Add Shader name on shader list
			for (uint i = 0; i < glo::GLSLProgram::MAX_SHADER_INDEX; ++i)
			{
				std::string tmp;
				std::ostringstream	oss;
				glo::GLSLProgram::ShaderType type = (glo::GLSLProgram::ShaderType)i;

				tmp = manager->convertShaderType2String(type) + " ";
				if ( manager->getName(type) != 0 )
				{
					oss << manager->getName(type);
					tmp += oss.str();
					QListWidgetItem* listShader = new QListWidgetItem(tr(tmp.c_str()), m_shaderList.get(), vgQt::engine::DEFAULT_SHADER_TYPE + i );

					QFont	fontError("Helvetica");

					if (manager->getLogError(type) != "")
					{
						fontError.setItalic(true);
					}

					listShader->setFont(fontError);
				}
			}

			std::string log("");

			//Draw the compilation log
			for (uint i = 0; i < glo::GLSLProgram::MAX_SHADER_INDEX; ++i)
			{
				glo::GLSLProgram::ShaderType type = (glo::GLSLProgram::ShaderType)i;
				log += manager->getLogError(type);
				log += "\n";
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
	QFont	fontError("Helvetica");
	const glo::GLSLProgram::ShaderType type = (glo::GLSLProgram::ShaderType)(m_currentType - 1000) ;

	if ( m_newText )
	{
		m_newText = false;
		return;
	}

	if (m_managerSaved && m_itemSaved 
		&& ( ( notificationType & SC_MOD_INSERTTEXT ) || ( notificationType & SC_MOD_DELETETEXT ) ) )
	{
		int len = m_textEditor->textLength();

		if ( len == 0 )	return;

		QString	tmp = m_textEditor->getText(len + 1);
		const std::string shader = tmp.toStdString();
		m_canvas->setCurrent();
		if ( m_managerSaved->getShaderCode((glo::GLSLProgram::ShaderType)m_shaderSaved) == shader )
		{
			return;
		}

		//Compile the modify shader

		const bool compileRetVal = m_managerSaved->addShader( shader.c_str(), type, false);

		if ( !compileRetVal )	
		{
			InfoLog = m_managerSaved->getLogError(type);
			fontError.setItalic(true);
		}
		else
		{
			m_managerSaved->setLogError(type, "");
			//Linking
			const bool linkRetVal = m_managerSaved->link();

			if ( !linkRetVal )	
			{
				InfoLog += m_managerSaved->getInfoLog();
			}
			else
			{
				// Async refresh
				m_canvas->refreshForced();
			}
		}

		//Set the new shader name
		const int programNumber = m_managerSaved->getName(type);
		oss << programNumber;
		std::string newName = m_managerSaved->convertShaderType2String(type) + " " + oss.str();

		//Set the new name in the shader list
		if ( m_itemSaved )	
		{
			m_itemSaved->setText( QString(newName.c_str()) );
			m_itemSaved->setFont(fontError);
		}

		if ( m_currentType == PROGRAM_SHADER )
		{
			m_editorLog->setPlainText(m_managerSaved->getLinkLog().c_str());
			return;
		}
		else
		{
			//Set the log error in the shader log
			m_editorLog->setPlainText(InfoLog.c_str());
		}

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



void ShadersEditor::versionChanged(int index)
{
	std::string value = m_versionList->itemData( index ).toString().toStdString();
	m_textEditor->setGLSLVersion( gle::glslVersionToEnum(value ) );
}



bool ShadersEditor::event(QEvent * e)
{
	if (e->type() == QEvent::WindowActivate)
	{
		refreshUI();
		return true;
	}
	return QWidget::event(e);
}



} // namespace engine

} // namespace vgQt

