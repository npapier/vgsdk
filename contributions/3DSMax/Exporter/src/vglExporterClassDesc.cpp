// VGSDK - Copyright (C) 2006, Nicolas Papier and James Ballantyne.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author James Ballantyne
// Author Nicolas Papier

#include "vglExporterClassDesc.h"

int vglExporterClassDesc::IsPublic()
{
	return TRUE;
}

void * vglExporterClassDesc::Create( BOOL loading )
{
	return new vglExporter();
}

const TCHAR * vglExporterClassDesc::ClassName()
{
	return GetString( IDS_CLASS_NAME );
}

SClass_ID vglExporterClassDesc::SuperClassID()
{
	return SCENE_EXPORT_CLASS_ID;
}

Class_ID vglExporterClassDesc::ClassID()
{
	return VGLEXPORTER_CLASS_ID;
}

const TCHAR * vglExporterClassDesc::Category()
{
	return GetString( IDS_CATEGORY );
}

const TCHAR * vglExporterClassDesc::InternalName()
{
	return _T( "vglExporter" );
}

HINSTANCE vglExporterClassDesc::HInstance()
{
	return hInstance;
}

static vglExporterClassDesc vglExporterDesc;
ClassDesc2* GetvglExporterDesc()
{ 
	return &vglExporterDesc;
}