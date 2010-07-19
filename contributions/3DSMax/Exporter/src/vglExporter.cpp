// VGSDK - Copyright (C) 2006, Nicolas Papier and James Ballantyne.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author James Ballantyne
// Author Nicolas Papier

#include "vglExporter.h"
#include "vglExporterClassDesc.h"
#include "TrianExporter.h"
#include "TrianExporter2.h"

BOOL CALLBACK vglExporterOptionsDlgProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	vglExporter * exp = ( vglExporter * )GetWindowLongPtr( hWnd, GWLP_USERDATA ); 
	
	switch( message ) 
	{
	case WM_INITDIALOG:
		exp = ( vglExporter * )lParam;
		SetWindowLongPtr( hWnd, GWLP_USERDATA, lParam ); 
		CenterWindow( hWnd, GetParent( hWnd ) );
		
		CheckDlgButton( hWnd, IDC_EXT_TRIAN, exp->extensionType );
		CheckDlgButton( hWnd, IDC_EXT_TRIAN2, !exp->extensionType );

		CheckDlgButton( hWnd, IDC_FACE_CLOCK, exp->triOrientation );
		CheckDlgButton( hWnd, IDC_FACE_CCLOCK, !exp->triOrientation );

		CheckDlgButton( hWnd, IDC_EXP_MATERIAL, exp->exportMaterials );

		CheckDlgButton( hWnd, IDC_EXP_NORMALS, exp->exportNormals );
		CheckDlgButton( hWnd, IDC_EXP_TEXCOORD, exp->exportTexCoords );			

		EnableWindow( GetDlgItem( hWnd, IDC_EXP_MATERIAL ), !exp->extensionType );

		EnableWindow( GetDlgItem( hWnd, IDC_EXP_NORMALS ), !exp->extensionType );
		EnableWindow( GetDlgItem( hWnd, IDC_EXP_TEXCOORD ), !exp->extensionType );

		return TRUE;

	case WM_COMMAND:
		switch( LOWORD( wParam ) )
		{
		case IDC_EXT_TRIAN:
		case IDC_EXT_TRIAN2:
			exp->extensionType = !exp->extensionType;

			CheckDlgButton( hWnd, IDC_EXT_TRIAN, exp->extensionType );
			CheckDlgButton( hWnd, IDC_EXT_TRIAN2, !exp->extensionType );

			EnableWindow( GetDlgItem( hWnd, IDC_EXP_MATERIAL ), !exp->extensionType );
			EnableWindow( GetDlgItem( hWnd, IDC_EXP_NORMALS ), !exp->extensionType );
			EnableWindow( GetDlgItem( hWnd, IDC_EXP_TEXCOORD ), !exp->extensionType );
            break;
			
		case IDC_EXP_MATERIAL:
			exp->exportMaterials = !exp->exportMaterials;

			//CheckDlgButton( hWnd, IDC_EXP_NORMALS, exp->exportMaterials );
			//CheckDlgButton( hWnd, IDC_EXP_TEXCOORD, exp->exportMaterials );

			//EnableWindow( GetDlgItem( hWnd, IDC_EXP_NORMALS ), exp->exportMaterials );
			EnableWindow( GetDlgItem( hWnd, IDC_EXP_TEXCOORD ), exp->exportMaterials );
			break;

		case IDC_FACE_CLOCK:
		case IDC_FACE_CCLOCK:
			exp->triOrientation = !exp->triOrientation;

			CheckDlgButton( hWnd, IDC_FACE_CLOCK, exp->triOrientation );
			CheckDlgButton( hWnd, IDC_FACE_CCLOCK, !exp->triOrientation );
			break;

		case IDOK:
			exp->extensionType	 = IsDlgButtonChecked( hWnd, IDC_EXT_TRIAN );
			exp->triOrientation	 = IsDlgButtonChecked( hWnd, IDC_FACE_CLOCK );
			exp->exportMaterials = IsDlgButtonChecked( hWnd, IDC_EXP_MATERIAL );
			exp->exportNormals	 = IsDlgButtonChecked( hWnd, IDC_EXP_NORMALS );
			exp->exportTexCoords = IsDlgButtonChecked( hWnd, IDC_EXP_TEXCOORD );

			EndDialog( hWnd, 1 );
			break;

		case IDCANCEL:
			EndDialog( hWnd,0 );
			break;
		}
		
	default:
		return FALSE;
	}

	return TRUE;
}

//--- vglExporter -------------------------------------------------------
vglExporter::vglExporter()
{
	//Set default values.
	extensionType	= TRUE;
	triOrientation	= TRUE;
	exportMaterials = TRUE;
	exportNormals	= TRUE;
	exportTexCoords = TRUE;

	version = Version() / 100.0f;
}

vglExporter::~vglExporter() 
{
}

int vglExporter::ExtCount()
{
	//Returns the number of file name extensions supported by the plug-in.
	return 2;
}

const TCHAR *vglExporter::Ext( int n )
{		
	//Return the 'i-th' file name extension (i.e. "3DS").
	switch( n )
	{
	case 0:
		return _T( "trian" );

	case 1:
	default:
		return _T( "trian2" );
	}
}

const TCHAR *vglExporter::LongDesc()
{
	//Return long ASCII description (i.e. "Targa 2.0 Image File")
	return GetString( IDS_LIBDESCRIPTION );
}
	
const TCHAR *vglExporter::ShortDesc() 
{			
	//Return short ASCII description (i.e. "Targa")
	return _T( "VGL Exporter" );
}

const TCHAR *vglExporter::AuthorName()
{			
	//Return ASCII Author name
	return _T( "Nicolas Papier and James Ballantyne" );
}

const TCHAR *vglExporter::CopyrightMessage() 
{	
	// Return ASCII Copyright message
	return _T( "Copyright (C) 2006, Nicolas Papier and James Ballantyne" );
} 

const TCHAR *vglExporter::OtherMessage1() 
{		
	//TODO: Return Other message #1 if any
	return _T("");
}

const TCHAR *vglExporter::OtherMessage2() 
{		
	//TODO: Return other message #2 in any
	return _T("");
}

unsigned int vglExporter::Version()
{				
	//TODO: Return Version number * 100 (i.e. v3.01 = 301)
	return 100;
}

void vglExporter::ShowAbout(HWND hWnd)
{			
	// Optional
}

BOOL vglExporter::SupportsOptions( int ext, DWORD options )
{
	// TODO Decide which options to support.  Simply return
	// true for each option supported by each Extension 
	// the exporter supports.

	return TRUE;
}

int	vglExporter::DoExport( const TCHAR *name, ExpInterface *ei, Interface *i, BOOL suppressPrompts, DWORD options )
{
	//Read the values from the config file.  This will make the dialog open into
	//the user last used options.
	ReadConfig();

	//Do we display the dialog?
	bool showPrompts = suppressPrompts ? FALSE : TRUE;

	if( showPrompts ) 
	{
		// Prompt the user with our dialogbox, and get all the options.
		if ( !DialogBoxParam( hInstance, MAKEINTRESOURCE( IDD_PANEL ),
			 i->GetMAXHWnd(), reinterpret_cast<DLGPROC>(vglExporterOptionsDlgProc), ( LPARAM )this ) ) //HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam
		{
			return 1;
		}
	}

	//Re-write the config file, so that the next time the user runs the exporter
	//they will be presented with their previous options.
	WriteConfig();

	//Make sure the extensions is correct.
	std::string file( name );
	int index = file.rfind( "." );
	file = file.substr( 0, index );

	//Create the extension based on the file type selected.
	if( extensionType )
	{
		file.append( ".trian" );
		TrianExporter * tE = new TrianExporter( triOrientation );
		return tE->DoExport( file.c_str(), ei, i, suppressPrompts, options );
	}
	else
	{
		file.append( ".trian2" );
		TrianExporter2 * tE2 = new TrianExporter2( triOrientation, Version() );
		return tE2->DoExport( file.c_str(), ei, i, suppressPrompts, options );
	}

	return TRUE;
}


TSTR vglExporter::GetCfgFilename()
{
	TSTR filename;
	
	filename += GetCOREInterface()->GetDir( APP_PLUGCFG_DIR );
	filename += "\\";
	filename += "vglExporter.cfg";

	return filename;
}

// NOTE: Update anytime the CFG file changes
#define CFG_VERSION 0x03

BOOL vglExporter::ReadConfig()
{
	//Get the config file name.
	TSTR filename = GetCfgFilename();
	FILE * cfgStream;

	//Open the file, if possible, otherwise go with default values
	//for dialog.
	cfgStream = fopen( filename, "rb" );
	if( !cfgStream )
		return FALSE;
	
	//Get the values.
	extensionType	= fgetc( cfgStream );
	triOrientation	= fgetc( cfgStream );
	exportMaterials = fgetc( cfgStream );
	exportNormals	= fgetc( cfgStream );
	exportTexCoords = fgetc( cfgStream );

	//Close the stream.
	fclose( cfgStream );

	return TRUE;
}

void vglExporter::WriteConfig()
{
	//Get the filname.
	TSTR filename = GetCfgFilename();
	FILE * cfgStream;

	//See if it can be opened.
	cfgStream = fopen( filename, "wb" );
	if( !cfgStream )
	{
		::MessageBox( NULL, "Could not open file.", "Error", MB_OK );
		return;
	}

	//Write config information to file.
	fputc( extensionType, cfgStream );
	fputc( triOrientation, cfgStream );
	fputc( exportMaterials, cfgStream );
	fputc( exportNormals, cfgStream );
	fputc( exportTexCoords, cfgStream );

	//Close the file.
	fclose( cfgStream );
}
