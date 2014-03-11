// VGSDK - Copyright (C) 2006, Nicolas Papier and James Ballantyne.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author James Ballantyne
// Author Nicolas Papier

#include "TrianExporter.h"

TrianExporter::TrianExporter( void )
{
	//Initialize
	m_triOrientation = TRUE;
	m_pIGame		 = 0;
}

TrianExporter::TrianExporter( BOOL triOrientation )
{
	//Initialize
	m_triOrientation = triOrientation;
	m_pIGame		 = 0;
}

TrianExporter::~TrianExporter( void )
{
	if( m_pIGame != 0 )
	{
		m_pIGame->ReleaseIGame();
		m_pIGame = 0;
	}
}

// Dummy function for progress bar
DWORD WINAPI fn( LPVOID arg )
{
	return( 0 );
}

int TrianExporter::DoExport( const TCHAR * name, ExpInterface *ei, Interface *i, BOOL suppressPrompts, DWORD options )
{
	//Open the file to export to.
	m_of.open( name );

	//Create an Error procedure.
	MyErrorProc pErrorProc;
	SetErrorCallBack( &pErrorProc );

	//Get the game interface
	m_pIGame = GetIGameInterface();

	//Start the progress bar.
	i->ProgressStart( _T( "Exporting to .trian file..." ), TRUE, fn, NULL );

	//Set up the conversion manager.
	IGameConversionManager * cm = GetConversionManager();
	
	//Set up the whacky coordinate system that 3DS Max uses.
	UserCoord whacky = 
	{
		1, //Right-Handed.
		1, //X Axis goes right.
		4, //Y Axis goes in.
		3, //Z Axis goes down.
		0, //U Tex Axis is left.
		1  //V Tex Axis is down.
	};
	cm->SetUserCoordSystem( whacky );

	//Set the coordinate system.
	cm->SetCoordSystem( IGameConversionManager::IGAME_MAX );
	
	//Initialize the game scene.
	m_pIGame->InitialiseIGame( options & SCENE_EXPORT_SELECTED );

	//Go through all the nodes of the scene and export only the Game Meshes.
	for( int l = 0; l < m_pIGame->GetTopLevelNodeCount(); l++ )
	{
		//Get the current Game node.
		IGameNode * node = m_pIGame->GetTopLevelNode( l );

		//Check for selected state.
		if( node->IsTarget() )
			continue;

		ExportNodeInfo( node );
	}

	//End the progress bar.
	i->ProgressEnd();

	//Release the scene.
	m_pIGame->ReleaseIGame();
	m_pIGame = 0;

	//Close the output stream.
	m_of.close();

	return TRUE;
}

void TrianExporter::ExportNodeInfo( IGameNode * node )
{
	//If the node is a group owner, do nothing with it.
	if( !node->IsGroupOwner() )
	{
		//Get the game object.
		IGameObject * obj = node->GetIGameObject();

		//We will only dump the info if it is a IGAME_MESH.
		if( obj->GetIGameType() == IGameObject::IGAME_MESH )
		{
			//Get the Mesh.
			IGameMesh * gm = ( IGameMesh * )obj;

			//If initialization works, dump the mesh.
			if( gm->InitializeData() )
				DumpMesh( gm );
		}
	}
}

void TrianExporter::DumpMesh( IGameMesh * gm )
{
	/*
	 * The trian file files the following format:
	 *		# of vertices.
	 *		List of vertices.
	 *		x y z
	 *		# of faces.
	 *		List of edges.
	 *		e1 e2 e3 0 0 0.
	 *
	 * The 0 0 0, refers to the neighbor information. But .trian does not use neighbors.
	 * However, the vgsdk importer requires the neighbor informatin to be there.
	 */

	//Get the number of vertices.
	int numVerts = gm->GetNumberOfVerts();

	//Output
	m_of << numVerts << std::endl;

	//Output the vertices.
	for( int i = 0; i < numVerts; i++ )
	{
		Point3 v;
		if( gm->GetVertex( i, v ) )
			m_of << v.x <<  " " << v.y << " " << v.z << std::endl;
	}

	//Get the number of faces.
	int numFaces = gm->GetNumberOfFaces();

	//Output
	m_of << numFaces << std::endl;

	//Output the edge information.
	for( int i = 0; i < numFaces; i++ ) 
	{
		//Get the face.
		FaceEx * face = gm->GetFace( i );

		//The order depends on the triOrientation.
		if( m_triOrientation )
			m_of << face->vert[2] << " " << face->vert[1] << " " << face->vert[0];
		else
			m_of << face->vert[0] << " " << face->vert[1] << " " << face->vert[2];

		//Handle neighbor information.
		m_of << " 0 0 0" << std::endl;
	}
}
