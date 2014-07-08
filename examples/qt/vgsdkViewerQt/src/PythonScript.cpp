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
	m_moduleName( m_filename.stem().string() )
{
	// Initialize python context.
	vgUI::python::Context::getInstance()->setCanvas( canvas );
	vgUI::python::Context::getInstance()->setBasicManipulator( canvas );

	// Initialize the python interpreter.
	Py_Initialize();

	// Import the script.
	// If successfull, performs some initializations.
	PyObject * module = import();
	if( module )
	{
		PyRun_SimpleString( "import vgd" );
		PyRun_SimpleString( "import vgm" );
		PyRun_SimpleString( "import vgUI" );

		// Calls the initialisation callback, if present.
		if( hasFunction(module, "init") )
		{
			CurWorkDir cwd( m_filename.parent_path() );
			PyRun_SimpleString( (m_moduleName + ".init(vgUI.Context.getInstance())").c_str() );
		}

		// Installs the refresh callback, if a refresh method has been defined..
		if( hasFunction(module, "refresh") )
		{
			// Installs the callback that will call the script.
			m_refreshCallback.reset( new vgd::event::TimerCallback() );
			m_refreshCallback->setFrequency( 25 );
			m_refreshCallback->setExecutionDuration( vgd::basic::TimeDuration() );
			m_refreshCallback->setApplyFunctor( vgd::makeShp( new Refresher(this) ) );
			m_canvas->getTimerEventProcessor()->add( m_refreshCallback );
		}
	}
	Py_XDECREF(module);
}


PythonScript::~PythonScript()
{
	if( m_refreshCallback )
	{
		m_canvas->getTimerEventProcessor()->remove( m_refreshCallback );
	}
	Py_Finalize();
}


const bool PythonScript::hasFunction( PyObject * module, const std::string & name )
{
	PyObject *	fun = PyObject_GetAttrString(module, name.c_str() );
	const bool	result = fun && PyCallable_Check(fun);

	Py_XDECREF(fun);
	return result;
}


PyObject * PythonScript::import()
{
	if( !boost::filesystem::exists(m_filename) )
	{
		qDebug() << "Invalid script file: " << m_filename.string().c_str();
		QMessageBox::information(0, "Python script error", m_filename.string().c_str());
		return 0;
	}

#if defined(WIN32)
#define PATH_SEP ";"
#else
#define PATH_SEP ":"
#endif

	// Inserts the directory containing the script file in the path used for the importation.
	std::string pyPath( Py_GetPath() );
	pyPath = m_filename.parent_path().string() + PATH_SEP + pyPath;
	PySys_SetPath( const_cast< char* >(pyPath.c_str()) );

	// Imports the script module.
	PyObject * module = PyImport_ImportModule( m_moduleName.c_str() );
	// Also appends the module to teh default interpreter's scope.
	if( module )
	{
		PyRun_SimpleString( ("import " + m_moduleName).c_str() );
	}

	// Job's done.
	return module;
}


void PythonScript::refresh()
{
	CurWorkDir cwd( m_filename.parent_path() );
	PyRun_SimpleString( (m_moduleName+".refresh(vgUI.Context.getInstance())").c_str() );
}


}