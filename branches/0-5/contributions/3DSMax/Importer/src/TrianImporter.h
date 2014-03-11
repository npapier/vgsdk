// VGSDK - Copyright (C) 2006, Nicolas Papier and James Ballantyne.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author James Ballantyne
// Author Nicolas Papier

#ifndef __TRIANIMPORTER__H
#define __TRIANIMPORTER__H

#include "Max.h"

#include <fstream>

class TrianImporter
{
public:
	//Constructor
	TrianImporter( BOOL coordSys );

	//Deconstructor
	~TrianImporter( void );

	//Import
	int DoImport( const TCHAR * name, ImpInterface *ii, Interface *i, BOOL suppressPrompts = FALSE );

private:
	//Read the trian file and store in mesh object.
	bool ReadFile( const TCHAR * name, Mesh * msh );

	//Coordinate system.
	BOOL cS;
};

#endif //__TRIANIMPORTER__H
