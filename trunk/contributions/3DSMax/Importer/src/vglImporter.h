// VGSDK - Copyright (C) 2006, Nicolas Papier and James Ballantyne.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author James Ballantyne
// Author Nicolas Papier

#ifndef __VGLIMPORTER__H
#define __VGLIMPORTER__H

#include "Max.h"
#include "resource.h"
#include "istdplug.h"
#include "iparamb2.h"
#include "iparamm2.h"
#include "decomp.h"

#include <string>

class vglImporter : public SceneImport
{
public:
	//Constructor
	vglImporter( void );

	//Deconstructor
	~vglImporter( void );

	//Methods from SceneImport that must be overridden.
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

	//Import function
	int DoImport( const TCHAR * name, ImpInterface * ii, Interface * i, BOOL suppressPrompts = FALSE );

	//Coordinate system.
	BOOL cS;			//TRUE = CLOCKWISE, FALSE = COUNTER-CLOCKWISE
};

BOOL CALLBACK vglImporterOptionsDlgProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

extern TCHAR *GetString( int id );

extern HINSTANCE hInstance;

#endif //__VGLIMPORTER__H
