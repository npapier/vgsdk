// VGSDK - Copyright (C) 2006, Nicolas Papier and James Ballantyne.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author James Ballantyne
// Author Nicolas Papier

#ifndef __VGLEXPORTERCLASSDESC__H
#define __VGLEXPORTERCLASSDESC__H

#include "resource.h"
#include "vglExporter.h"

#define VGLEXPORTER_CLASS_ID	Class_ID( 0x79d613a4, 0x4f21c3ad )

class vglExporterClassDesc : public ClassDesc2
{

public:
	int 			IsPublic();
	void *			Create( BOOL loading = FALSE );
	const TCHAR *	ClassName();
	SClass_ID		SuperClassID();
	Class_ID		ClassID();
	const TCHAR* 	Category();

	const TCHAR*	InternalName();	// returns fixed parsable name (scripter-visible name)
	HINSTANCE		HInstance();	// returns owning module handle

};

ClassDesc2* GetvglExporterDesc();

#endif //__VGLEXPORTERCLASSDESC__H