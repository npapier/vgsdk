// VGSDK - Copyright (C) 2006, Nicolas Papier and James Ballantyne.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author James Ballantyne
// Author Nicolas Papier

#include "TrianImporter.h"
#include "TrianImporter2.h"
#include "vglImporter.h"

vglImporter::vglImporter( void )
{
	//Initialize the coordinate to clockwise
	cS = TRUE;
}

vglImporter::~vglImporter( void )
{
}

int vglImporter::ExtCount( void )
{
	//Return the number of extensions supported by this plugin.
	return 2;
}

const TCHAR * vglImporter::Ext( int n )
{
	//Return the 'i-th' file name extensions
	switch( n )
	{
	case 0:
		return _T( "trian" );

	case 1:
	default:
		return _T( "trian2" );
	}
}

const TCHAR * vglImporter::LongDesc( void )
{
	//Return the ascii long description of the plug-in
	return GetString( IDS_LIBDESCRIPTION );
}

const TCHAR * vglImporter::ShortDesc( void )
{
	//Return the ascii short description of the plug-in
	return _T( "VGL Importer" );
}

const TCHAR * vglImporter::AuthorName( void )
{
	//Return the authors name of the plug-in
	return _T( "Nicolas Papier and James Ballantyne" );
}

const TCHAR * vglImporter::CopyrightMessage( void )
{
	//Return the copyright message
	return _T( "Copyright (C), 2006, Nicolas Papier and James Ballantyne" );
}

const TCHAR * vglImporter::OtherMessage1( void )
{
	//Return other message 1.
	return _T( "" );
}

const TCHAR * vglImporter::OtherMessage2( void )
{
	//Return the other message 2
	return _T( "" );
}

unsigned int vglImporter::Version( void )
{
	//Return the version number * 100 ( i.e v3.01 = 301 )
	return 100;
}

void vglImporter::ShowAbout( HWND hWnd )
{
	//Optional
}

int vglImporter::DoImport( const TCHAR * name, ImpInterface *ii, Interface *i, BOOL suppressPrompts )
{
	//Do we display the dialog?
	bool showPrompts = suppressPrompts ? FALSE : TRUE;

	if( showPrompts ) 
	{
		// Prompt the user with our dialogbox, and get all the options.
		if ( !DialogBoxParam( hInstance, MAKEINTRESOURCE( IDD_PANEL ),
			i->GetMAXHWnd(), reinterpret_cast<DLGPROC>(vglImporterOptionsDlgProc), ( LPARAM )this ) )
		{
			return IMPEXP_CANCEL;
		}
	}

	//Import based on the extension.
	std::string extension( name );
	int index = extension.rfind( "." );
	extension = extension.substr( index + 1, extension.size() );

	if( extension.compare( "trian" ) == 0 )
	{
		//TRIAN extension.
		TrianImporter * trianImp = new TrianImporter( cS );
		return trianImp->DoImport( name, ii, i, suppressPrompts );
	}
	else if( extension.compare( "trian2" ) == 0 )
	{
		//TRIAN2 extension.
		TrianImporter2 * trianImp = new TrianImporter2( cS );
		return trianImp->DoImport( name, ii, i, suppressPrompts );
	}

	return FALSE;
}

BOOL CALLBACK vglImporterOptionsDlgProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	vglImporter * imp = ( vglImporter * )GetWindowLongPtr( hWnd, GWLP_USERDATA ); 

	switch( message )
	{
	case WM_INITDIALOG:
		imp = ( vglImporter * )lParam;
		SetWindowLongPtr( hWnd, GWLP_USERDATA, lParam ); 
		CenterWindow( hWnd, GetParent( hWnd ) );

		//We want clockise coordinate system to be default.
		CheckDlgButton( hWnd, IDC_CS_CLOCK, imp->cS );
		CheckDlgButton( hWnd, IDC_CS_CCLOCK, !imp->cS );

		//Enable All windows.
		EnableWindow( GetDlgItem( hWnd, IDC_CS_CLOCK ), TRUE );
		EnableWindow( GetDlgItem( hWnd, IDC_CS_CCLOCK ), TRUE );

		return TRUE;

	case WM_COMMAND:
		switch( LOWORD( wParam ) )
		{
		case IDC_CS_CLOCK:
		case IDC_CS_CCLOCK:
			imp->cS = !imp->cS;

			CheckDlgButton( hWnd, IDC_CS_CLOCK, imp->cS );
			CheckDlgButton( hWnd, IDC_CS_CCLOCK, !imp->cS );
			break;

		case IDOK:
			imp->cS = IsDlgButtonChecked( hWnd, IDC_CS_CLOCK );

			EndDialog( hWnd, 1 );
			return TRUE;

		case IDCANCEL:
			EndDialog( hWnd, 0 );
			return FALSE;
		}
	
		return TRUE;

	default:
		return FALSE;
	}
}
