// VGSDK - Copyright (C) 2014, Yakhouba Keita.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Yakhouba Keita

#include "vgsdkViewerQt/PythonScript.hpp"

#include <vgd/event/TimerCallback.hpp>
#include <vgeGL/event/TimerEventProcessor.hpp>
#include <vgUI/python/Context.hpp>

#include "vgsdkViewerQt/MyCanvas.hpp"

#include <QTextStream>
#include <QFile>
#include <QIODevice>
#include <QDebug>
#include <QMessageBox>
#include <Python.h>

namespace vgsdkViewerQt
{


struct Refresher : public vgd::event::ApplyFunctor
{
	Refresher( PythonScript * script )
	: m_script( script )
	{}

	void apply( const vgd::Shp< vgd::event::TimerEvent > event, vgd::event::TimerCallback * timerCallbackSource )
	{
		m_script->refresh();
	}

private:

	PythonScript * m_script;
};



PythonScript::PythonScript( MyCanvas * canvas, const std::string & filename )
: m_canvas( canvas )
{
	// Initialize python context.
	vgUI::python::Context::getInstance()->setCanvas( canvas );
	vgUI::python::Context::getInstance()->setBasicManipulator( canvas );

	// Initialize the python interpreter.
	Py_Initialize();

	// Loads the given script
	load( filename );

	// Calls the initialisation callback.
	PyRun_SimpleString( "import vgd" );
	PyRun_SimpleString( "import vgm" );
	PyRun_SimpleString( "import vgUI" );
	PyRun_SimpleString( "init(vgUI.Context.getInstance())" );

	// Installs the callback that will call the script.
	m_refreshCallback.reset( new vgd::event::TimerCallback() );
	m_refreshCallback->setFrequency( 25 );
	m_refreshCallback->setExecutionDuration( vgd::basic::TimeDuration() );
	m_refreshCallback->setApplyFunctor( vgd::makeShp( new Refresher(this) ) );
	m_canvas->getTimerEventProcessor()->add( m_refreshCallback );
}


PythonScript::~PythonScript()
{
	m_canvas->getTimerEventProcessor()->remove( m_refreshCallback );
	Py_Finalize();
}


void PythonScript::load( const std::string & filename )
{
	QFile file(QString::fromStdString(filename));
	std::string fileContent = ""; 
	if(!file.open(QIODevice::ReadOnly))
	{
		qDebug() << "error opening file: " << file.error();
		QMessageBox::information(0, "error while opening file", file.errorString());
		return;
	}
	QTextStream in(&file);
	while(!in.atEnd()) 
	{
		QString line = in.readLine();   
		if( !line.endsWith("\n") )
		{				
			fileContent += line.toStdString();
			fileContent += "\n";
		}
	}
	

	// Runs the script.
	PyRun_SimpleString( fileContent.c_str() );
			
/*	PyRun_SimpleString("import sys");
	//PyRun_SimpleString("sys.path.append(r\"D:\\local_win32_cl10-0Exp\\bin\")");
	PyRun_SimpleString(	"class CatchOutErr(object):	\n\t"
						"def __init__(self) :\n\t\t"
						"self.data = ''\n\t"
						"def write(self, stuff) :\n\t\t"
						"self.data += stuff\n\t"
						"def reset(self) :\n\t\t"
						"self.data = ''");
	PyRun_SimpleString("import vgm");
	PyRun_SimpleString("import vgd");
	PyRun_SimpleString("import vge");
	PyRun_SimpleString("import vgUI");

	//PyRun_SimpleString("mySearchPath.append(\"" + path + "\"");
	PyObject* m_pyModuleRedirect = PyImport_AddModule("__main__");	// Creation d'un module main pour la redirection des sorties

	// création d'un objet Python qui va contenir les stdout et stderr de Python
	PyRun_SimpleString("catchOutErr		= CatchOutErr()");
	PyRun_SimpleString("sys.stdout		= catchOutErr");

	// Mise en place des contextes de base
	PyRun_SimpleString("context = vgUI.Context.getInstance()");
	PyRun_SimpleString("canvas = context.getBasicManipulator()");

	PyRun_SimpleString("sys.stderr		= catchOutErr");	
	//Execution du contenu du fichier
	PyRun_SimpleString(fileContent.c_str());		
	std::string str = "";
	PyObject * catcher = PyObject_GetAttrString(m_pyModuleRedirect, "catchOutErr");		// on récupère l'objet catchOutErr
	PyErr_Print();
		
	PyObject * stdoutCatcher = PyObject_GetAttrString(catcher, "data");					// on récupère les valeurs de l'objet catchOutErr
	str = PyString_AsString(stdoutCatcher);		
	// on retourne les messages dans le buffer de sortie				
	std::cout << "=== Sortie python ===\n" << str << std::endl;	
	PyRun_SimpleString("catchOutErr.reset()");*/
}


void PythonScript::refresh()
{
	PyRun_SimpleString( "refresh(vgUI.Context.getInstance())" );
}


}