// VGSDK - Copyright (C) 2006, Nicolas Papier and James Ballantyne.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author James Ballantyne
// Author Nicolas Papier

#include "vglImporterClassDesc.h"

int vglImporterClassDesc::IsPublic( void )
{
	return TRUE;
}

void * vglImporterClassDesc::Create( BOOL loading )
{
	return new vglImporter();
}

const TCHAR * vglImporterClassDesc::ClassName( void )
{
	return GetString( IDS_CLASS_NAME );
}

SClass_ID vglImporterClassDesc::SuperClassID( void )
{
	return SCENE_IMPORT_CLASS_ID;
}

Class_ID vglImporterClassDesc::ClassID( void )
{
	return VGLIMPORTER_CLASS_ID;
}

const TCHAR * vglImporterClassDesc::Category( void )
{
	return GetString( IDS_CATEGORY );
}

static vglImporterClassDesc vglImporterDesc;
ClassDesc * GetvglImporterDesc( void )
{
	return &vglImporterDesc;
}
