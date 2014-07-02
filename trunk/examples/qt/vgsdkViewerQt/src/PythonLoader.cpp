// VGSDK - Copyright (C) 2014, Yakhouba Keita.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Yakhouba Keita

#include "vgsdkViewerQt/PythonLoader.hpp"
#include <QTextStream>
#include <QFile>
#include <QIODevice>
#include <QDebug>
#include <QMessageBox>
#include <Python.h>

namespace vgsdkViewerQt
{
	void PythonLoader::load(const std::string & filePath)
	{
		QFile file(QString::fromStdString(filePath));
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

		Py_Initialize();
		
		PyRun_SimpleString("import sys");
		PyRun_SimpleString("sys.path.append(r\"D:\\local_win32_cl10-0Exp\\bin\")");
		PyRun_SimpleString("sys.path.append(r\"D:\\Dev\\lib\\dtPython\\share\")");
		PyRun_SimpleString("import CatchOutErr");
		PyRun_SimpleString("import vgm");
		PyRun_SimpleString("import vgd");
		PyRun_SimpleString("import vge");
		PyRun_SimpleString("import vgUI");

		//PyRun_SimpleString("mySearchPath.append(\"" + path + "\"");
		PyObject* m_pyModuleRedirect = PyImport_AddModule("__main__");	// Creation d'un module main pour la redirection des sorties

		// création d'un objet Python qui va contenir les stdout et stderr de Python
		PyRun_SimpleString("catchOutErr		= CatchOutErr.CatchOutErr()");
		PyRun_SimpleString("sys.stdout		= catchOutErr");
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
		PyRun_SimpleString("catchOutErr.reset()");
		Py_Finalize();
	}
}