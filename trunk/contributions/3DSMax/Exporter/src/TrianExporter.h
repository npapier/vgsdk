// VGSDK - Copyright (C) 2006, Nicolas Papier and James Ballantyne.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author James Ballantyne
// Author Nicolas Papier

#ifndef __TRIANEXPORTER__H
#define __TRIANEXPORTER__H

#include <fstream>

#include "IGame.h"
#include "IGameObject.h"
#include "IGameProperty.h"
#include "IGameControl.h"
#include "IGameModifier.h"
#include "IConversionManager.h"
#include "IGameError.h"

#include "MyErrorProc.h"

class TrianExporter
{
public:
	//Default Constructor
	TrianExporter( void );

	//Constructor
	TrianExporter( BOOL triOrientation );

	//Deconstructor
	~TrianExporter( void );

	//Export
	int DoExport( const TCHAR * name, ExpInterface *ei, Interface *i, BOOL suppressPrompts = FALSE, DWORD options = 0 );

protected:
	//Export a Game Mesh Node.
	void ExportNodeInfo( IGameNode * node );

	//Dump the mesh to a file.
	void DumpMesh( IGameMesh * gm );

	//Triangle orientation.  TRUE = CLOCKWISE, FALSE = COUNTER-CLOCKWISE.
	BOOL m_triOrientation;

	//Game Scene.
	IGameScene * m_pIGame;

	//Output Stream.
	std::ofstream m_of;
};

#endif //__TRIANEXPORTER__H
