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


struct CurWorkDir
{
	CurWorkDir( const boost::filesystem::path & cwd )
	: m_cwdBackup( boost::filesystem::current_path() )
	{
		boost::filesystem::current_path( cwd );
	}

	~CurWorkDir()
	{
		boost::filesystem::current_path( m_cwdBackup );
	}

private:

	const boost::filesystem::path m_cwdBackup;
};



PythonScript::PythonScript( MyCanvas * canvas, const std::string & filename )
:	m_canvas( canvas ),
	m_filename( filename ),
	m_pyModule( 0 )
{
	// Initialize python context.
	vgUI::python::Context::getInstance()->setCanvas( canvas );
	vgUI::python::Context::getInstance()->setBasicManipulator( canvas );

	// Initialize the python interpreter.
	Py_Initialize();

	// Import the script, and if successfull, performs some initializations.
	if( import() )
	{
		PyRun_SimpleString("import vgUI");

		// Calls the initialisation callback, if present.
		if( hasFunction(m_pyModule, "init") )
		{
			CurWorkDir cwd( m_filename.parent_path() );
			PyRun_SimpleString( "script.init(vgUI.Context.getInstance())" );
		}

		// Installs the refresh callback, if a refresh method has been defined..
		if( hasFunction(m_pyModule, "refresh") )
		{
			// Installs the callback that will call the script.
			m_refreshCallback.reset( new vgd::event::TimerCallback() );
			m_refreshCallback->setFrequency( 25 );
			m_refreshCallback->setExecutionDuration( vgd::basic::TimeDuration() );
			m_refreshCallback->setApplyFunctor( vgd::makeShp( new Refresher(this) ) );
			m_canvas->getTimerEventProcessor()->add( m_refreshCallback );
		}
	}
}


PythonScript::~PythonScript()
{
	if( m_refreshCallback )
	{
		m_canvas->getTimerEventProcessor()->remove( m_refreshCallback );
	}
	Py_XDECREF(m_pyModule);
	Py_Finalize();
}


const bool PythonScript::hasFunction( PyObject * module, const std::string & name )
{
	PyObject *	fun = PyObject_GetAttrString(module, name.c_str() );
	const bool	result = fun && PyCallable_Check(fun);

	Py_XDECREF(fun);
	return result;
}


const bool PythonScript::import()
{
	// Opens the script's source file.
	QFile file( QString::fromStdString(m_filename.string()) );
	if( !file.open(QIODevice::ReadOnly) )
	{
		qDebug() << "Error opening file: " << file.error();
		QMessageBox::information( 0, "Script loading error", file.errorString() );
		return false;
	}
	

	// Loads the module's source code.
	std::string source; 
	QTextStream in(&file);
	for(;;)
	{
		const QString line = in.readLine();   
		if( !line.isEmpty() )
		{				
			source += line.toStdString();
			source += "\n";
		}
		else
		{
			break;
		}
	}

	// Compiles the code from the given python source file and create the associated module.
	PyObject * code = 0;
	code = Py_CompileString( source.c_str(), m_filename.string().c_str(), Py_file_input );
	if( !code )
	{
		PyErr_Print();
		QMessageBox::warning( 0, "Script error", "An error has occured while load the script. Please see the console for additional details." );
		return false;
	}
	m_pyModule = PyImport_ExecCodeModule( "script", code ) ;
	Py_DECREF(code);


	// References the module of the script module in the __main___ module for later use.
	PyObject * mainModule = PyImport_AddModule("__main__");
	PyObject * mainDict = PyModule_GetDict(mainModule);
	PyDict_SetItemString(mainDict, "script", m_pyModule);


	// Job's done.
	return true;
}


void PythonScript::refresh()
{
	CurWorkDir cwd( m_filename.parent_path() );
	PyRun_SimpleString( "script.refresh(vgUI.Context.getInstance())" );
}


}