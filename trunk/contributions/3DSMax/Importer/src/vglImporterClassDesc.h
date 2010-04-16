// VGSDK - Copyright (C) 2006, Nicolas Papier and James Ballantyne.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author James Ballantyne
// Author Nicolas Papier

#ifndef __VGLIMPORTERCLASSDESC__H
#define __VGLIMPORTERCLASSDESC__H

#include "vglImporter.h"

#define VGLIMPORTER_CLASS_ID	Class_ID( 0x7d09408f, 0x6d914d3d )

class vglImporterClassDesc : public ClassDesc
{
public:
	int 			IsPublic( void );
	void		*	Create( BOOL loading = FALSE );
	const TCHAR *	ClassName(  void );
	SClass_ID		SuperClassID( void );
	Class_ID		ClassID( void );
	const TCHAR	* 	Category( void );
};

ClassDesc * GetvglImporterDesc( void );

#endif //__VGLIMPORTERCLASSDESC__H
