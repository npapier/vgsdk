// VGSDK - Copyright (C) 2006, Nicolas Papier and James Ballantyne.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author James Ballantyne
// Author Nicolas Papier

#include "vglImporter.h"
#include "vglImporterClassDesc.h"

HINSTANCE hInstance;
int controlsInit = FALSE;

BOOL WINAPI DllMain( HINSTANCE hinstDLL, ULONG fdwReason, LPVOID lpvReserved )
{
	hInstance = hinstDLL;				// Hang on to this DLL's instance handle.

	if( !controlsInit ) {
		controlsInit = TRUE;
		//InitCustomControls( hInstance );	// Initialize MAX's custom controls
		//InitCommonControls();			// Initialize Win95 controls
	}
			
	return (TRUE);
}

__declspec( dllexport ) const TCHAR* LibDescription()
{
	return GetString( IDS_LIBDESCRIPTION );
}

//TODO: Must change this number when adding a new class
__declspec( dllexport ) int LibNumberClasses()
{
	return 1;
}

__declspec( dllexport ) ClassDesc* LibClassDesc( int i )
{
	switch( i ) {
		case 0: return GetvglImporterDesc();
		default: return 0;
	}
}

__declspec( dllexport ) ULONG LibVersion()
{
	return VERSION_3DSMAX;
}

// Let the plug-in register itself for deferred loading
__declspec( dllexport ) ULONG CanAutoDefer()
{
	return 1;
}

TCHAR *GetString( int id )
{
	static TCHAR buf[256];

	if( hInstance )
		return LoadString( hInstance, id, buf, sizeof( buf ) ) ? buf : NULL;
	return NULL;
}
