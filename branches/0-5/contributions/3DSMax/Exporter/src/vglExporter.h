// VGSDK - Copyright (C) 2006, Nicolas Papier and James Ballantyne.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author James Ballantyne
// Author Nicolas Papier

#ifndef __VGLEXPORTER__H
#define __VGLEXPORTER__H

#include "Max.h"
#include "resource.h"
#include "istdplug.h"
#include "iparamb2.h"
#include "iparamm2.h"
#include "decomp.h"

#include "IGame.h"
#include "IGameObject.h"
#include "IGameProperty.h"
#include "IGameControl.h"
#include "IGameModifier.h"
#include "IConversionManager.h"
#include "IGameError.h"

class vglExporter : public SceneExport
{

public:
	vglExporter();
	~vglExporter();

	int				ExtCount();					// Number of extensions supported
	const TCHAR *	Ext(int n);					// Extension #n (i.e. "3DS")
	const TCHAR *	LongDesc();					// Long ASCII description (i.e. "Autodesk 3D Studio File")
	const TCHAR *	ShortDesc();				// Short ASCII description (i.e. "3D Studio")
	const TCHAR *	AuthorName();				// ASCII Author name
	const TCHAR *	CopyrightMessage();			// ASCII Copyright message
	const TCHAR *	OtherMessage1();			// Other message #1
	const TCHAR *	OtherMessage2();			// Other message #2
	unsigned int	Version();					// Version number * 100 (i.e. v3.01 = 301)
	void			ShowAbout( HWND hWnd );		// Show DLL's "About..." box

	BOOL SupportsOptions( int ext, DWORD options );
	int	DoExport( const TCHAR *name, ExpInterface *ei, Interface *i, BOOL suppressPrompts = FALSE, DWORD options = 0 );

	BOOL ReadConfig();
	void WriteConfig();
	TSTR GetCfgFilename();

	BOOL extensionType;		//TRUE = TRIAN, FALSE = TRIAN2
	BOOL triOrientation;	//TRUE = CLOCKWISE, FALSE = COUNTER-CLOCKWISE
	BOOL exportMaterials;
	BOOL exportNormals;
	BOOL exportTexCoords;

	float version; //Version of the exporter.				
};

extern TCHAR *GetString( int id );

extern HINSTANCE hInstance;

#endif // __VGLEXPORTER__H
