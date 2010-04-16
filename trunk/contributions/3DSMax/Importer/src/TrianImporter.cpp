// VGSDK - Copyright (C) 2006, Nicolas Papier and James Ballantyne.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author James Ballantyne
// Author Nicolas Papier

#include "TrianImporter.h"

TrianImporter::TrianImporter( BOOL coordSys )
{
	cS = coordSys;
}

TrianImporter::~TrianImporter( void )
{
}

int TrianImporter::DoImport( const TCHAR * name, ImpInterface *ii, Interface *i, BOOL suppressPrompts )
{
	// Split filename of import file
	TSTR tstrPath, tstrFilename, tstrExtension;
	SplitFilename( TSTR(name), &tstrPath, &tstrFilename, &tstrExtension );

	//Does a .Max file need to be generate.
	/*if( !i->CheckForSave() )
		return FALSE;*/

	//Create a triobject.
	TriObject * obj = CreateNewTriObject();

	//Make the triobject was successfully made.
	if( !obj )
	{
		delete obj;
		return FALSE; 
	}

	if( ReadFile( name, &obj->GetMesh() ) )
	{
		ImpNode * node = ii->CreateNode();

		if( !node )
		{
			delete node;
			return FALSE;
		}

		//Create identity matrix for transform.
		Matrix3 tm;
		tm.IdentityMatrix();

		//Set up the node to add to the scene.
		node->Reference( obj );
		node->SetTransform( 0, tm );
		node->SetName( tstrFilename );

		//Add the node to the scene.
		ii->AddNodeToScene( node );

		//Redraw the scene.
		ii->RedrawViews();

		return TRUE;
	}

	return FALSE;
}

bool TrianImporter::ReadFile( const TCHAR * name, Mesh * msh )
{
	//Open the file.
	std::ifstream import( name );

	if( !import )
	{
		TSTR error = TSTR( "Could not open file: " ) + TSTR( name );
		::MessageBox( NULL, error.data(), "Error", MB_OK | MB_ICONERROR );
		return false;
	}

	//Read in the number of vertices and store in the mesh.
	int numVerts;
	import >> numVerts;
	msh->setNumVerts( numVerts );

	//Read each vertex and add to the mesh.
	for( int i = 0; i < numVerts; i++ )
	{
		Point3 p;
		import >> p.x >> p.y >> p.z;
		msh->setVert( i, p );
	}

	//Read in the number of faces and store in the mesh.
	int numFaces;
	import >> numFaces;
	msh->setNumFaces( numFaces );

	//Read each face and add to the mesh.
	for( int i = 0; i < numFaces; i++ )
	{
		//Get the three edges.
		int e1, e2, e3, tmp;
		import >> e1 >> e2 >> e3 >> tmp >> tmp >> tmp;

		//Store the face based on the coordinate system.
		if( cS )
			msh->faces[i].setVerts( e3, e2, e1 );
		else
			msh->faces[i].setVerts( e1, e2, e3 );

		//Make the face visible.
		msh->faces[i].setEdgeVisFlags( EDGE_VIS, EDGE_VIS, EDGE_VIS );
	}

	return true;
}
